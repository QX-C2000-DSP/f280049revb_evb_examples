.global _dsp_start

# declare C function main()
.extern main
.extern boot_init_280049

.section .text.interrupt.vector
# 0-0: offset = 0x0
_int_entry_group0_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x0|
jmpr gr0||

# 0-1: offset = 0x10
_int_entry_group0_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1|
jmpr gr0||

# 0-2: offset = 0x20
_int_entry_group0_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2|
jmpr gr0||

# 0-3: offset = 0x30
_int_entry_group0_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x3|
jmpr gr0||

# 0-4: offset = 0x40
_int_entry_group0_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4|
jmpr gr0||

# 0-5: offset = 0x50
_int_entry_group0_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5|
jmpr gr0||

# 0-6: offset = 0x60
_int_entry_group0_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6|
jmpr gr0||

# 0-7: offset = 0x70
_int_entry_group0_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7|
jmpr gr0||

# 0-8: offset = 0x80
_int_entry_group0_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8|
jmpr gr0||

# 0-9: offset = 0x90
_int_entry_group0_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9|
jmpr gr0||

# 0-10: offset = 0xa0
_int_entry_group0_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa|
jmpr gr0||

# 0-11: offset = 0xb0
_int_entry_group0_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb|
jmpr gr0||

# 0-12: offset = 0xc0
_int_entry_group0_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc|
jmpr gr0||

# 0-13: offset = 0xd0
_int_entry_group0_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xd|
jmpr gr0||

# 0-14: offset = 0xe0
_int_entry_group0_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xe|
jmpr gr0||

# 0-15: offset = 0xf0
_int_entry_group0_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xf|
jmpr gr0||

# 1-0: offset = 0x100
_int_entry_group1_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x10|
jmpr gr0||

# 1-1: offset = 0x110
_int_entry_group1_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x11|
jmpr gr0||

# 1-2: offset = 0x120
_int_entry_group1_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x12|
jmpr gr0||

# 1-3: offset = 0x130
_int_entry_group1_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x13|
jmpr gr0||

# 1-4: offset = 0x140
_int_entry_group1_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x14|
jmpr gr0||

# 1-5: offset = 0x150
_int_entry_group1_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x15|
jmpr gr0||

# 1-6: offset = 0x160
_int_entry_group1_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x16|
jmpr gr0||

# 1-7: offset = 0x170
_int_entry_group1_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x17|
jmpr gr0||

# 1-8: offset = 0x180
_int_entry_group1_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x18|
jmpr gr0||

# 1-9: offset = 0x190
_int_entry_group1_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x19|
jmpr gr0||

# 1-10: offset = 0x1a0
_int_entry_group1_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1a|
jmpr gr0||

# 1-11: offset = 0x1b0
_int_entry_group1_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1b|
jmpr gr0||

# 1-12: offset = 0x1c0
_int_entry_group1_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1c|
jmpr gr0||

# 1-13: offset = 0x1d0
_int_entry_group1_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1d|
jmpr gr0||

# 1-14: offset = 0x1e0
_int_entry_group1_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1e|
jmpr gr0||

# 1-15: offset = 0x1f0
_int_entry_group1_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x1f|
jmpr gr0||

# 2-0: offset = 0x200
_int_entry_group2_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x20|
jmpr gr0||

# 2-1: offset = 0x210
_int_entry_group2_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x21|
jmpr gr0||

# 2-2: offset = 0x220
_int_entry_group2_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x22|
jmpr gr0||

# 2-3: offset = 0x230
_int_entry_group2_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x23|
jmpr gr0||

# 2-4: offset = 0x240
_int_entry_group2_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x24|
jmpr gr0||

# 2-5: offset = 0x250
_int_entry_group2_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x25|
jmpr gr0||

# 2-6: offset = 0x260
_int_entry_group2_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x26|
jmpr gr0||

# 2-7: offset = 0x270
_int_entry_group2_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x27|
jmpr gr0||

# 2-8: offset = 0x280
_int_entry_group2_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x28|
jmpr gr0||

# 2-9: offset = 0x290
_int_entry_group2_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x29|
jmpr gr0||

# 2-10: offset = 0x2a0
_int_entry_group2_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2a|
jmpr gr0||

# 2-11: offset = 0x2b0
_int_entry_group2_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2b|
jmpr gr0||

# 2-12: offset = 0x2c0
_int_entry_group2_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2c|
jmpr gr0||

# 2-13: offset = 0x2d0
_int_entry_group2_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2d|
jmpr gr0||

# 2-14: offset = 0x2e0
_int_entry_group2_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2e|
jmpr gr0||

# 2-15: offset = 0x2f0
_int_entry_group2_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x2f|
jmpr gr0||

# 3-0: offset = 0x300
_int_entry_group3_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x30|
jmpr gr0||

# 3-1: offset = 0x310
_int_entry_group3_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x31|
jmpr gr0||

# 3-2: offset = 0x320
_int_entry_group3_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x32|
jmpr gr0||

# 3-3: offset = 0x330
_int_entry_group3_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x33|
jmpr gr0||

# 3-4: offset = 0x340
_int_entry_group3_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x34|
jmpr gr0||

# 3-5: offset = 0x350
_int_entry_group3_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x35|
jmpr gr0||

# 3-6: offset = 0x360
_int_entry_group3_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x36|
jmpr gr0||

# 3-7: offset = 0x370
_int_entry_group3_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x37|
jmpr gr0||

# 3-8: offset = 0x380
_int_entry_group3_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x38|
jmpr gr0||

# 3-9: offset = 0x390
_int_entry_group3_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x39|
jmpr gr0||

# 3-10: offset = 0x3a0
_int_entry_group3_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x3a|
jmpr gr0||

# 3-11: offset = 0x3b0
_int_entry_group3_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x3b|
jmpr gr0||

# 3-12: offset = 0x3c0
_int_entry_group3_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x3c|
jmpr gr0||

# 3-13: offset = 0x3d0
_int_entry_group3_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x3d|
jmpr gr0||

# 3-14: offset = 0x3e0
_int_entry_group3_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x3e|
jmpr gr0||

# 3-15: offset = 0x3f0
# interrupt not exist here, stay nop
_int_entry_group3_15:
jmp _int_entry_group3_15||
nop||
nop||
nop||

#
# nc means not connected with any interrupt sources
#
# nc-0: reset, offset = 0x400
_dsp_start:
jmp _dsp_call_main||
xor gr27 gr27 gr27||
nop||
nop||

# nc-1: offset = 0x410
nop||
nop||
nop||
nop||

# nc-2: offset = 0x420
nop||
nop||
nop||
nop||

# nc-3: offset = 0x430
nop||
nop||
nop||
nop||

# nc-4: offset = 0x440
nop||
nop||
nop||
nop||

# nc-5: offset = 0x450
nop||
nop||
nop||
nop||

# nc-6: offset = 0x460
nop||
nop||
nop||
nop||

# nc-7: offset = 0x470
nop||
nop||
nop||
nop||

# nc-8: offset = 0x480
nop||
nop||
nop||
nop||

# nc-9: offset = 0x490
nop||
nop||
nop||
nop||

# nc-10: offset = 0x4a0
nop||
nop||
nop||
nop||

# nc-11: offset = 0x4b0
nop||
nop||
nop||
nop||

# nc-12: offset = 0x4c0
nop||
nop||
nop||
nop||

# nc-13: offset = 0x4d0
nop||
nop||
nop||
nop||

# nc-14: offset = 0x4e0
nop||
nop||
nop||
nop||

# nc-15: offset = 0x4f0
nop||
nop||
nop||
nop||

# 4-0: offset = 0x500
_int_entry_group4_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x40|
jmpr gr0||

# 4-1: offset = 0x510
_int_entry_group4_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x41|
jmpr gr0||

# 4-2: offset = 0x520
_int_entry_group4_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x42|
jmpr gr0||

# 4-3: offset = 0x530
_int_entry_group4_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x43|
jmpr gr0||

# 4-4: offset = 0x540
_int_entry_group4_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x44|
jmpr gr0||

# 4-5: offset = 0x550
_int_entry_group4_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x45|
jmpr gr0||

# 4-6: offset = 0x560
_int_entry_group4_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x46|
jmpr gr0||

# 4-7: offset = 0x570
_int_entry_group4_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x47|
jmpr gr0||

# 4-8: offset = 0x580
_int_entry_group4_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x48|
jmpr gr0||

# 4-9: offset = 0x590
_int_entry_group4_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x49|
jmpr gr0||

# 4-10: offset = 0x5a0
_int_entry_group4_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4a|
jmpr gr0||

# 4-11: offset = 0x5b0
_int_entry_group4_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4b|
jmpr gr0||

# 4-12: offset = 0x5c0
_int_entry_group4_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4c|
jmpr gr0||

# 4-13: offset = 0x5d0
_int_entry_group4_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4d|
jmpr gr0||

# 4-14: offset = 0x5e0
_int_entry_group4_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4e|
jmpr gr0||

# 4-15: offset = 0x5f0
_int_entry_group4_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x4f|
jmpr gr0||

# 5-0: offset = 0x600
_int_entry_group5_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x50|
jmpr gr0||

# 5-1: offset = 0x610
_int_entry_group5_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x51|
jmpr gr0||

# 5-2: offset = 0x620
_int_entry_group5_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x52|
jmpr gr0||

# 5-3: offset = 0x630
_int_entry_group5_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x53|
jmpr gr0||

# 5-4: offset = 0x640
_int_entry_group5_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x54|
jmpr gr0||

# 5-5: offset = 0x650
_int_entry_group5_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x55|
jmpr gr0||

# 5-6: offset = 0x660
_int_entry_group5_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x56|
jmpr gr0||

# 5-7: offset = 0x670
_int_entry_group5_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x57|
jmpr gr0||

# 5-8: offset = 0x680
_int_entry_group5_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x58|
jmpr gr0||

# 5-9: offset = 0x690
_int_entry_group5_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x59|
jmpr gr0||

# 5-10: offset = 0x6a0
_int_entry_group5_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5a|
jmpr gr0||

# 5-11: offset = 0x6b0
_int_entry_group5_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5b|
jmpr gr0||

# 5-12: offset = 0x6c0
_int_entry_group5_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5c|
jmpr gr0||

# 5-13: offset = 0x6d0
_int_entry_group5_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5d|
jmpr gr0||

# 5-14: offset = 0x6e0
_int_entry_group5_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5e|
jmpr gr0||

# 5-15: offset = 0x6f0
_int_entry_group5_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x5f|
jmpr gr0||

# 6-0: offset = 0x700
_int_entry_group6_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x60|
jmpr gr0||

# 6-1: offset = 0x710
_int_entry_group6_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x61|
jmpr gr0||

# 6-2: offset = 0x720
_int_entry_group6_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x62|
jmpr gr0||

# 6-3: offset = 0x730
_int_entry_group6_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x63|
jmpr gr0||

# 6-4: offset = 0x740
_int_entry_group6_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x64|
jmpr gr0||

# 6-5: offset = 0x750
_int_entry_group6_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x65|
jmpr gr0||

# 6-6: offset = 0x760
_int_entry_group6_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x66|
jmpr gr0||

# 6-7: offset = 0x770
_int_entry_group6_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x67|
jmpr gr0||

# 6-8: offset = 0x780
_int_entry_group6_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x68|
jmpr gr0||

# 6-9: offset = 0x790
_int_entry_group6_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x69|
jmpr gr0||

# 6-10: offset = 0x7a0
_int_entry_group6_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6a|
jmpr gr0||

# 6-11: offset = 0x7b0
_int_entry_group6_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6b|
jmpr gr0||

# 6-12: offset = 0x7c0
_int_entry_group6_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6c|
jmpr gr0||

# 6-13: offset = 0x7d0
_int_entry_group6_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6d|
jmpr gr0||

# 6-14: offset = 0x7e0
_int_entry_group6_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6e|
jmpr gr0||

# 6-15: offset = 0x7f0
_int_entry_group6_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x6f|
jmpr gr0||

# 7-0: offset = 0x800
_int_entry_group7_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x70|
jmpr gr0||

# 7-1: offset = 0x810
_int_entry_group7_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x71|
jmpr gr0||

# 7-2: offset = 0x820
_int_entry_group7_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x72|
jmpr gr0||

# 7-3: offset = 0x830
_int_entry_group7_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x73|
jmpr gr0||

# 7-4: offset = 0x840
_int_entry_group7_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x74|
jmpr gr0||

# 7-5: offset = 0x850
_int_entry_group7_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x75|
jmpr gr0||

# 7-6: offset = 0x860
_int_entry_group7_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x76|
jmpr gr0||

# 7-7: offset = 0x870
_int_entry_group7_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x77|
jmpr gr0||

# 7-8: offset = 0x880
_int_entry_group7_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x78|
jmpr gr0||

# 7-9: offset = 0x890
_int_entry_group7_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x79|
jmpr gr0||

# 7-10: offset = 0x8a0
_int_entry_group7_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7a|
jmpr gr0||

# 7-11: offset = 0x8b0
_int_entry_group7_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7b|
jmpr gr0||

# 7-12: offset = 0x8c0
_int_entry_group7_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7c|
jmpr gr0||

# 7-13: offset = 0x8d0
_int_entry_group7_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7d|
jmpr gr0||

# 7-14: offset = 0x8e0
_int_entry_group7_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7e|
jmpr gr0||

# 7-15: offset = 0x8f0
_int_entry_group7_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x7f|
jmpr gr0||

# 8-0: offset = 0x900
_int_entry_group8_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x80|
jmpr gr0||

# 8-1: offset = 0x910
_int_entry_group8_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x81|
jmpr gr0||

# 8-2: offset = 0x920
_int_entry_group8_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x82|
jmpr gr0||

# 8-3: offset = 0x930
_int_entry_group8_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x83|
jmpr gr0||

# 8-4: offset = 0x940
_int_entry_group8_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x84|
jmpr gr0||

# 8-5: offset = 0x950
_int_entry_group8_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x85|
jmpr gr0||

# 8-6: offset = 0x960
_int_entry_group8_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x86|
jmpr gr0||

# 8-7: offset = 0x970
_int_entry_group8_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x87|
jmpr gr0||

# 8-8: offset = 0x980
_int_entry_group8_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x88|
jmpr gr0||

# 8-9: offset = 0x990
_int_entry_group8_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x89|
jmpr gr0||

# 8-10: offset = 0x9a0
_int_entry_group8_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8a|
jmpr gr0||

# 8-11: offset = 0x9b0
_int_entry_group8_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8b|
jmpr gr0||

# 8-12: offset = 0x9c0
_int_entry_group8_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8c|
jmpr gr0||

# 8-13: offset = 0x9d0
_int_entry_group8_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8d|
jmpr gr0||

# 8-14: offset = 0x9e0
_int_entry_group8_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8e|
jmpr gr0||

# 8-15: offset = 0x9f0
_int_entry_group8_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x8f|
jmpr gr0||

# 9-0: offset = 0xa00
_int_entry_group9_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x90|
jmpr gr0||

# 9-1: offset = 0xa10
_int_entry_group9_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x91|
jmpr gr0||

# 9-2: offset = 0xa20
_int_entry_group9_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x92|
jmpr gr0||

# 9-3: offset = 0xa30
_int_entry_group9_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x93|
jmpr gr0||

# 9-4: offset = 0xa40
_int_entry_group9_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x94|
jmpr gr0||

# 9-5: offset = 0xa50
_int_entry_group9_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x95|
jmpr gr0||

# 9-6: offset = 0xa60
_int_entry_group9_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x96|
jmpr gr0||

# 9-7: offset = 0xa70
_int_entry_group9_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x97|
jmpr gr0||

# 9-8: offset = 0xa80
_int_entry_group9_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x98|
jmpr gr0||

# 9-9: offset = 0xa90
_int_entry_group9_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x99|
jmpr gr0||

# 9-10: offset = 0xaa0
_int_entry_group9_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9a|
jmpr gr0||

# 9-11: offset = 0xab0
_int_entry_group9_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9b|
jmpr gr0||

# 9-12: offset = 0xac0
_int_entry_group9_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9c|
jmpr gr0||

# 9-13: offset = 0xad0
_int_entry_group9_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9d|
jmpr gr0||

# 9-14: offset = 0xae0
_int_entry_group9_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9e|
jmpr gr0||

# 9-15: offset = 0xaf0
_int_entry_group9_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0x9f|
jmpr gr0||

# 10-0: offset = 0xb00
_int_entry_group10_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa0|
jmpr gr0||

# 10-1: offset = 0xb10
_int_entry_group10_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa1|
jmpr gr0||

# 10-2: offset = 0xb20
_int_entry_group10_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa2|
jmpr gr0||

# 10-3: offset = 0xb30
_int_entry_group10_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa3|
jmpr gr0||

# 10-4: offset = 0xb40
_int_entry_group10_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa4|
jmpr gr0||

# 10-5: offset = 0xb50
_int_entry_group10_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa5|
jmpr gr0||

# 10-6: offset = 0xb60
_int_entry_group10_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa6|
jmpr gr0||

# 10-7: offset = 0xb70
_int_entry_group10_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa7|
jmpr gr0||

# 10-8: offset = 0xb80
_int_entry_group10_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa8|
jmpr gr0||

# 10-9: offset = 0xb90
_int_entry_group10_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xa9|
jmpr gr0||

# 10-10: offset = 0xba0
_int_entry_group10_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xaa|
jmpr gr0||

# 10-11: offset = 0xbb0
_int_entry_group10_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xab|
jmpr gr0||

# 10-12: offset = 0xbc0
_int_entry_group10_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xac|
jmpr gr0||

# 10-13: offset = 0xbd0
_int_entry_group10_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xad|
jmpr gr0||

# 10-14: offset = 0xbe0
_int_entry_group10_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xae|
jmpr gr0||

# 10-15: offset = 0xbf0
_int_entry_group10_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xaf|
jmpr gr0||

# 11-0: offset = 0xc00
_int_entry_group11_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb0|
jmpr gr0||

# 11-1: offset = 0xc10
_int_entry_group11_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb1|
jmpr gr0||

# 11-2: offset = 0xc20
_int_entry_group11_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb2|
jmpr gr0||

# 11-3: offset = 0xc30
_int_entry_group11_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb3|
jmpr gr0||

# 11-4: offset = 0xc40
_int_entry_group11_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb4|
jmpr gr0||

# 11-5: offset = 0xc50
_int_entry_group11_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb5|
jmpr gr0||

# 11-6: offset = 0xc60
_int_entry_group11_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb6|
jmpr gr0||

# 11-7: offset = 0xc70
_int_entry_group11_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb7|
jmpr gr0||

# 11-8: offset = 0xc80
_int_entry_group11_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb8|
jmpr gr0||

# 11-9: offset = 0xc90
_int_entry_group11_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xb9|
jmpr gr0||

# 11-10: offset = 0xca0
_int_entry_group11_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xba|
jmpr gr0||

# 11-11: offset = 0xcb0
_int_entry_group11_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xbb|
jmpr gr0||

# 11-12: offset = 0xcc0
_int_entry_group11_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xbc|
jmpr gr0||

# 11-13: offset = 0xcd0
_int_entry_group11_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xbd|
jmpr gr0||

# 11-14: offset = 0xce0
_int_entry_group11_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xbe|
jmpr gr0||

# 11-15: offset = 0xcf0
_int_entry_group11_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xbf|
jmpr gr0||

# 12-0: offset = 0xd00
_int_entry_group12_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc0|
jmpr gr0||

# 12-1: offset = 0xd10
_int_entry_group12_1:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc1|
jmpr gr0||

# 12-2: offset = 0xd20
_int_entry_group12_2:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc2|
jmpr gr0||

# 12-3: offset = 0xd30
_int_entry_group12_3:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc3|
jmpr gr0||

# 12-4: offset = 0xd40
_int_entry_group12_4:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc4|
jmpr gr0||

# 12-5: offset = 0xd50
_int_entry_group12_5:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc5|
jmpr gr0||

# 12-6: offset = 0xd60
_int_entry_group12_6:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc6|
jmpr gr0||

# 12-7: offset = 0xd70
_int_entry_group12_7:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc7|
jmpr gr0||

# 12-8: offset = 0xd80
_int_entry_group12_8:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc8|
jmpr gr0||

# 12-9: offset = 0xd90
_int_entry_group12_9:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xc9|
jmpr gr0||

# 12-10: offset = 0xda0
_int_entry_group12_10:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xca|
jmpr gr0||

# 12-11: offset = 0xdb0
_int_entry_group12_11:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xcb|
jmpr gr0||

# 12-12: offset = 0xdc0
_int_entry_group12_12:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xcc|
jmpr gr0||

# 12-13: offset = 0xdd0
_int_entry_group12_13:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xcd|
jmpr gr0||

# 12-14: offset = 0xde0
_int_entry_group12_14:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xce|
jmpr gr0||

# 12-15: offset = 0xdf0
_int_entry_group12_15:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xcf|
jmpr gr0||

# 13-0: offset = 0xe00
_int_entry_group13_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xd0|
jmpr gr0||

# 14-0: offset = 0xe10
_int_entry_group14_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xe0|
jmpr gr0||

# 15-0: offset = 0xe20
_int_entry_group15_0:
movigh gr0 %hi16(PIEVECTTABLE_BASE)||
movigl gr0 %lo16(PIEVECTTABLE_BASE)||
|load32 gr0 gr0 0xf0|
jmpr gr0||

# padding
_lb_padding_nops:
nop||
nop||
nop||
nop||

_lb_func_init_bss:
# gr2 <= bss_start
movigh gr2 %hi16(__bss_start)||
movigl gr2 %lo16(__bss_start)||
# gr3 <= data_end
movigh gr3 %hi16(__data_end__)||
movigl gr3 %lo16(__data_end__)||
# gr4 <= constant 0
movigh gr4 0x0||
movigl gr4 0x0||
_lb_assign_0_loop:
eq gr2 gr3||
jc _lb_func_init_bss_end||
nop||
nop||
||store8 gr4 gr2 0
addi gr2 gr2 1||
jmp _lb_assign_0_loop||
nop||
nop||
_lb_func_init_bss_end:
ret||
nop||
nop||

_dsp_call_main:
# set .bss data section to all zero
call _lb_func_init_bss||
nop||
nop||
# set SP and call main()
movigh GR30 %hi16(_DSP_STACK_TOP)||
movigl GR30 %lo16(_DSP_STACK_TOP)||
call main||
nop||
nop||

_main_exit_stay_nop:
jmp _main_exit_stay_nop||
nop||
nop||
nop||

.global qx_precise_delay
# gr4 is the loop count from caller
qx_precise_delay:
addi gr4 gr4 0xffffffff||
nop||
nop||
lei gr4 0||
jnc qx_precise_delay||
nop||
nop||
ret||
nop||
nop||

.global fast_interrupt_initvectortable
# GR4: PIEVECTTABLE_BASE
# GR5: Interrupt_defaultHandler
# GR2: address offset rellative to PIEVECTTABLE_BASE
# GR3: upper limit for GR2, 0x400
# GR0: PIEVECTTABLE_BASE
fast_interrupt_initvectortable:
movigh gr2 0x0||
movigl gr2 0x0||
movigh gr3 0x0||
movigl gr3 0x400||
fast_ivecinit_loop:
add gr6 gr4 gr2||
addi gr2 gr2 4||store32 gr5 gr6 0
eq gr2 gr3||
jnc fast_ivecinit_loop||
nop||
nop||
movg2g gr0 gr4||
ret||
nop||
nop||

# fake bootloader for debugging on RAM
.section .text.qxboot0debug
eallow||
movigh GR30 %hi16(_DSP_STACK_TOP)||
movigl GR30 %lo16(_DSP_STACK_TOP)||
call boot_init_280049||
nop||
nop||
# enable NMI
movigh gr3 0x100||
movigl gr3 0x1200||
|load32 gr4 gr3 0|
bst gr4 0||
||store32 gr4 gr3 0
# set exp start for DSP cores
movigh gr3 0x100||
movigl gr3 0x1000||
movigh gr4 0x0||
movigl gr4 %lo16(_core0_exp_start)||
||store8 gr4 gr3 0x38
movigl gr4 %lo16(_core1_exp_start)||
||store8 gr4 gr3 0x3c
# HW init
movigh gr3 0x0100||
movigl gr3 0x4030||
movigh gr2 0x00ff||
movigl gr2 0xffff||
||store32 gr2 gr3 0
movigh gr3 0x0100||
movigl gr3 0x1078||
moviglz gr2 0x8||
||store32 gr2 gr3 0
# config SRAM
movigh gr2 0x100||
movigl gr2 0x1000||
movigh gr3 0x0||
movigl gr3 0xe000||
||store32 gr3 gr2 0xc8
movigh gr3 0x0||
movigl gr3 0x00ff||
||store32 gr3 gr2 0xc9
#movigh gr3 0x0||
#movigl gr3 0xfff0||
#||store32 gr3 gr2 0xcc
# copy trim
movigh gr2 0x3010||
movigl gr2 0x0||
movigh gr3 0x5a5a|load32 gr2 gr2 0|
movigl gr3 0x5a5a||
neq gr2 gr3||
jc _lb_skip_trim||
nop||
nop||
movigh gr2 0x101||
movigl gr2 0xc024||
movigh gr3 0x55aa||
movigl gr3 0x55aa||
movigh gr4 0x3010||
movigl gr4 0x4||store32 gr3 gr2 0
|load32 gr3 gr4 0|
movigh gr4 0x101||
movigl gr4 0xc000||
movigh gr5 0x3010||
movigl gr5 0x8||store32 gr3 gr4 0
movigh gr4 0x101|load32 gr3 gr5 0|
movigl gr4 0xc004||
movigh gr5 0x3010||
movigl gr5 0xc||store32 gr3 gr4 0
movigh gr4 0x101|load32 gr3 gr5 0|
movigl gr4 0xc008||
movigh gr5 0x101||
movigl gr5 0xc020||
movigh gr6 0||
movigl gr6 1||store32 gr3 gr4 0
movigh gr3 0xaa55||
movigl gr3 0xaa55||store32 gr6 gr5 0
||store32 gr3 gr2 0
_lb_skip_trim:
# enable instruction prefetch
movigh gr3 0x0100||
movigl gr3 0x1328||
moviglz gr2 1||
||store32 gr2 gr3 0
movigl gr3 0x132C||
||store32 gr2 gr3 0
jmp _dsp_start||
nop||
nop||

.section .text.qxboot1debug
eallow||
jmp _dsp_start||
nop||
nop||
