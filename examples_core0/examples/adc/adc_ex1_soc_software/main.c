// #############################################################################
//
//  FILE:   adc_ex1_soc_software.c
//
//  TITLE:  Structure Refresh Stress Test
//
//! \addtogroup driver_example_list
//! <h1>Structure Refresh Stress Test</h1>
//!
//! This example keeps the board initialization from the ADC software-trigger
//! sample, but replaces the application loop with a continuously changing
//! structure-heavy compute workload.
//!
//! The intent is to verify whether the IDE can refresh nested structure fields
//! in real time while the target keeps running.
//!
//! \b Watch \b Variables \n
//! - \b gDbgFrame - Root structure with nested members, arrays, pointers, and
//!   rolling counters.
//! - \b gMirror - Secondary structure that captures derived values.
//! - \b gHeartbeat - Monotonic counter that proves the loop is still running.
//
// #############################################################################
//
// Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of STARRYSTONETECH nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// #############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Type Definitions
//
typedef struct
{
    uint16_t raw[8];
    uint16_t filtered[8];
    uint32_t sum;
    uint32_t energy;
    float scale;
} SignalBank;

typedef struct
{
    SignalBank channels;
    uint16_t history[4];
    uint16_t index;
    uint16_t limit;
    uint32_t checksum;
} SignalWindow;

typedef struct
{
    uint32_t tick;
    uint32_t runningMax;
    uint32_t runningMin;
    uint32_t runningAvg;
    float gain;
    float offset;
} StatsBlock;

typedef struct
{
    uint16_t a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
    uint16_t e;
    uint16_t f;
} PackedFields;

typedef struct
{
    PackedFields packed;
    SignalWindow window;
    StatsBlock stats;
    uint32_t phase;
    uint32_t crcLike;
    uint16_t flags;
} DebugFrame;

typedef struct
{
    volatile DebugFrame *frame;
    const uint16_t *source;
    uint16_t sourceLength;
    uint16_t sourceIndex;
    uint32_t accumulator;
    uint32_t transform;
} DebugMirror;

//
// Globals
//
static volatile DebugFrame gDbgFrame;
static volatile DebugMirror gMirror;
static volatile uint32_t gHeartbeat = 0U;

static const uint16_t gSeedTable[16] = {
    3U, 11U, 29U, 47U, 71U, 97U, 131U, 173U,
    211U, 257U, 307U, 353U, 401U, 449U, 503U, 557U
};

//
// Local Helpers
//
static uint32_t computeFold32(uint32_t value)
{
    value ^= value >> 16U;
    value *= 0x45D9F3BU;
    value ^= value >> 16U;
    value *= 0x45D9F3BU;
    value ^= value >> 16U;
    return value;
}

static uint32_t updateWindow(volatile DebugFrame *frame, uint16_t sample)
{
    uint32_t i;
    uint32_t sum = 0U;
    uint32_t energy = 0U;
    uint16_t mix = sample;

    frame->window.channels.raw[frame->window.index & 7U] = sample;
    for (i = 0U; i < 8U; i++)
    {
        mix = (uint16_t)(mix + (uint16_t)(frame->window.channels.raw[i] ^ (uint16_t)(i * 13U)));
        frame->window.channels.filtered[i] = (uint16_t)((mix >> 1U) + (frame->window.channels.raw[i] >> 2U));
        sum += frame->window.channels.filtered[i];
        energy += (uint32_t)frame->window.channels.filtered[i] * (uint32_t)(i + 1U);
    }

    frame->window.channels.sum = sum;
    frame->window.channels.energy = energy;
    frame->window.channels.scale = ((float)(sum & 0xFFFFU) / 1024.0f) + 0.125f;

    frame->window.history[frame->window.index & 3U] = (uint16_t)(sum ^ energy);
    frame->window.index = (uint16_t)((frame->window.index + 1U) & 0xFFFFU);
    frame->window.limit = (uint16_t)(frame->window.limit + 1U);

    return computeFold32(sum ^ energy ^ (uint32_t)frame->window.index);
}

static uint32_t updatePacked(volatile DebugFrame *frame, uint32_t fold)
{
    frame->packed.a = (uint16_t)(fold & 0xFFFFU);
    frame->packed.b = (uint16_t)((fold >> 3U) & 0xFFFFU);
    frame->packed.c = (uint16_t)((fold >> 7U) & 0xFFFFU);
    frame->packed.d = (uint16_t)(frame->window.channels.sum & 0xFFFFU);
    frame->packed.e = (uint16_t)(frame->window.channels.energy & 0xFFFFU);
    frame->packed.f = (uint16_t)((frame->packed.a ^ frame->packed.c ^ frame->packed.e) + frame->flags);

    frame->phase = frame->phase + 1U;
    frame->flags = (uint16_t)(((frame->flags << 1U) | (frame->packed.f & 1U)) & 0x00FFU);

    return computeFold32((uint32_t)frame->packed.a |
                         ((uint32_t)frame->packed.b << 1U) |
                         ((uint32_t)frame->packed.c << 2U) |
                         ((uint32_t)frame->packed.d << 3U));
}

static void updateStats(volatile DebugFrame *frame, uint32_t fold)
{
    uint32_t current = frame->stats.tick;
    uint32_t maxv = frame->stats.runningMax;
    uint32_t minv = frame->stats.runningMin;

    current += fold + frame->window.channels.sum;
    maxv = (current > maxv) ? current : maxv;
    minv = (current < minv) ? current : minv;

    frame->stats.tick = current;
    frame->stats.runningMax = maxv;
    frame->stats.runningMin = minv;
    frame->stats.runningAvg = (frame->stats.runningAvg + current + fold) >> 1U;
    frame->stats.gain = 1.0f + ((float)(frame->packed.a & 0x3FU) / 64.0f);
    frame->stats.offset = ((float)(frame->packed.b & 0x1FU) / 10.0f) - 1.5f;
}

static void updateMirror(volatile DebugMirror *mirror, volatile DebugFrame *frame, uint32_t fold)
{
    uint16_t idx = mirror->sourceIndex;
    uint16_t value = mirror->source[idx & (mirror->sourceLength - 1U)];

    mirror->frame = frame;
    mirror->source = gSeedTable;
    mirror->sourceLength = (uint16_t)(sizeof(gSeedTable) / sizeof(gSeedTable[0]));
    mirror->sourceIndex = (uint16_t)((idx + 1U) & (mirror->sourceLength - 1U));
    mirror->accumulator += (uint32_t)value + fold + frame->phase;
    mirror->transform = computeFold32(mirror->accumulator ^ (uint32_t)value ^ frame->crcLike);
}

static void initDebugFrame(volatile DebugFrame *frame)
{
    uint16_t i;

    frame->packed.a = 1U;
    frame->packed.b = 2U;
    frame->packed.c = 3U;
    frame->packed.d = 4U;
    frame->packed.e = 5U;
    frame->packed.f = 6U;

    frame->window.index = 0U;
    frame->window.limit = 0U;
    frame->window.checksum = 0U;
    frame->window.channels.sum = 0U;
    frame->window.channels.energy = 0U;
    frame->window.channels.scale = 1.0f;

    for (i = 0U; i < 8U; i++)
    {
        frame->window.channels.raw[i] = gSeedTable[i];
        frame->window.channels.filtered[i] = 0U;
    }

    for (i = 0U; i < 4U; i++)
    {
        frame->window.history[i] = 0U;
    }

    frame->stats.tick = 0U;
    frame->stats.runningMax = 0U;
    frame->stats.runningMin = 0xFFFFFFFFUL;
    frame->stats.runningAvg = 0U;
    frame->stats.gain = 1.0f;
    frame->stats.offset = 0.0f;
    frame->phase = 0U;
    frame->crcLike = 0U;
    frame->flags = 0x5AU;
}

static void initMirror(volatile DebugMirror *mirror, volatile DebugFrame *frame)
{
    mirror->frame = (DebugFrame *)frame;
    mirror->source = gSeedTable;
    mirror->sourceLength = (uint16_t)(sizeof(gSeedTable) / sizeof(gSeedTable[0]));
    mirror->sourceIndex = 0U;
    mirror->accumulator = 0U;
    mirror->transform = 0U;
}

//
// Main
//
int main(void)
{
    uint32_t fold;
    uint32_t combined;
    uint16_t sample;

    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();

    initDebugFrame(&gDbgFrame);
    initMirror(&gMirror, &gDbgFrame);

    EINT;
    ERTM;

    while (1)
    {
        sample = gSeedTable[gHeartbeat & 0x0FU];
        sample = (uint16_t)(sample + (uint16_t)(gHeartbeat & 0x03FFU));
        sample ^= (uint16_t)(gDbgFrame.phase << 1U);

        fold = updateWindow(&gDbgFrame, sample);
        fold ^= updatePacked(&gDbgFrame, fold);
        updateStats(&gDbgFrame, fold);
        updateMirror(&gMirror, &gDbgFrame, fold);

        combined = gDbgFrame.window.channels.sum ^
                   gDbgFrame.window.channels.energy ^
                   gDbgFrame.stats.tick ^
                   gMirror.transform ^
                   gMirror.accumulator;

        gDbgFrame.window.checksum = computeFold32(combined ^ gDbgFrame.phase);
        gDbgFrame.crcLike = computeFold32(gDbgFrame.window.checksum ^ gMirror.transform ^ gDbgFrame.flags);
        gHeartbeat++;

        DEVICE_DELAY_US(1000U);
    }
}
