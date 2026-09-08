#ifndef HW_INTS_H
#define HW_INTS_H

//*****************************************************************************
//
// PIE Interrupt Numbers
// 0x00FF = PIE Table Row
// 0xFF00 = PIE Table Column
//
//*****************************************************************************

// Lower PIE Group 1
#define INT_RTOS     0x0101 // 1.1 - RTOS Interrupt
#define INT_TRACE    0x0102 // 1.2 - Debug Trace Interrupt
#define INT_WP       0x0103 // 1.3 - Debug WatchPoint Interrupt
#define INT_ADCA1    0x0104 // 1.4 - ADCA Interrupt 1
#define INT_ADCB1    0x0105 // 1.5 - ADCB Interrupt 1
#define INT_ADCC1    0x0106 // 1.6 - ADCC Interrupt 1
#define INT_XINT1    0x0107 // 1.7 - XINT1 Interrupt
#define INT_XINT2    0x0108 // 1.8 - XINT2 Interrupt
#define INT_TIMER0   0x010A // 1.10 - Timer 0 Interrupt
#define INT_WAKE     0x010B // 1.11 - Halt Wakeup/Watchdog Interrupt
#define INT_ADCA1_HR 0x010E // 1.14 - ADCA_HR Interrupt 1
#define INT_ADCB1_HR 0x010F // 1.15 - ADCB_HR Interrupt 1
#define INT_ADCC1_HR 0x0110 // 1.16 - ADCC_HR Interrupt 1

// Lower PIE Group 2
#define INT_EPWM1_TZ  0x0201 // 2.1 - ePWM1 Trip Zone Interrupt
#define INT_EPWM2_TZ  0x0202 // 2.2 - ePWM2 Trip Zone Interrupt
#define INT_EPWM3_TZ  0x0203 // 2.3 - ePWM3 Trip Zone Interrupt
#define INT_EPWM4_TZ  0x0204 // 2.4 - ePWM4 Trip Zone Interrupt
#define INT_EPWM5_TZ  0x0205 // 2.5 - ePWM5 Trip Zone Interrupt
#define INT_EPWM6_TZ  0x0206 // 2.6 - ePWM6 Trip Zone Interrupt
#define INT_EPWM7_TZ  0x0207 // 2.7 - ePWM7 Trip Zone Interrupt
#define INT_EPWM8_TZ  0x0208 // 2.8 - ePWM8 Trip Zone Interrupt
#define INT_EPWM9_TZ  0x0209 // 2.9 - ePWM9 Trip Zone Interrupt
#define INT_EPWM10_TZ 0x020A // 2.10 - ePWM10 Trip Zone Interrupt
#define INT_EPWM11_TZ 0x020B // 2.11 - ePWM11 Trip Zone Interrupt
#define INT_EPWM12_TZ 0x020C // 2.12 - ePWM12 Trip Zone Interrupt

// Lower PIE Group 3
#define INT_EPWM1  0x0301 // 3.1 - ePWM1 Interrupt
#define INT_EPWM2  0x0302 // 3.2 - ePWM2 Interrupt
#define INT_EPWM3  0x0303 // 3.3 - ePWM3 Interrupt
#define INT_EPWM4  0x0304 // 3.4 - ePWM4 Interrupt
#define INT_EPWM5  0x0305 // 3.5 - ePWM5 Interrupt
#define INT_EPWM6  0x0306 // 3.6 - ePWM6 Interrupt
#define INT_EPWM7  0x0307 // 3.7 - ePWM7 Interrupt
#define INT_EPWM8  0x0308 // 3.8 - ePWM8 Interrupt
#define INT_EPWM9  0x0309 // 3.9 - ePWM9 Interrupt
#define INT_EPWM10 0x030A // 3.10 - ePWM10 Interrupt
#define INT_EPWM11 0x030B // 3.11 - ePWM11 Interrupt
#define INT_EPWM12 0x030C // 3.12 - ePWM12 Interrupt

// Lower PIE Group 4
#define INT_ECAP1   0x0401 // 4.1 - eCAP1 Interrupt
#define INT_ECAP2   0x0402 // 4.2 - eCAP2 Interrupt
#define INT_ECAP3   0x0403 // 4.3 - eCAP3 Interrupt
#define INT_ECAP4   0x0404 // 4.4 - eCAP4 Interrupt
#define INT_ECAP5   0x0405 // 4.5 - eCAP5 Interrupt
#define INT_ECAP6   0x0406 // 4.6 - eCAP6 Interrupt
#define INT_ECAP7   0x0407 // 4.7 - eCAP7 Interrupt
#define INT_ECAP6_2 0x040E // 4.14 - eCAP6_2 (HRCAL) Interrupt
#define INT_ECAP7_2 0x040F // 4.15 - eCAP7_2 (HRCAL) Interrupt

// Lower PIE Group 5
#define INT_EQEP1    0x0501 // 5.1 - eQEP1 Interrupt
#define INT_EQEP2    0x0502 // 5.2 - eQEP2 Interrupt
#define INT_SDFM1    0x0509 // 5.9 - SDFM1 Interrupt
#define INT_SDFM1DR1 0x050D // 5.13 - SDFM1DR1 Interrupt
#define INT_SDFM1DR2 0x050E // 5.14 - SDFM1DR2 Interrupt
#define INT_SDFM1DR3 0x050F // 5.15 - SDFM1DR3 Interrupt
#define INT_SDFM1DR4 0x0510 // 5.16 - SDFM1DR4 Interrupt

// Lower PIE Group 6
#define INT_SPIA_RX 0x0601 // 6.1 - SPIA Receive Interrupt
#define INT_SPIA_TX 0x0602 // 6.2 - SPIA Transmit Interrupt
#define INT_SPIB_RX 0x0603 // 6.3 - SPIB Receive Interrupt
#define INT_SPIB_TX 0x0604 // 6.4 - SPIB Transmit Interrupt

// Lower PIE Group 7
#define INT_DMA_CH1     0x0701 // 7.1 - DMA Channel 1 Interrupt
#define INT_DMA_CH2     0x0702 // 7.2 - DMA Channel 2 Interrupt
#define INT_DMA_CH3     0x0703 // 7.3 - DMA Channel 3 Interrupt
#define INT_DMA_CH4     0x0704 // 7.4 - DMA Channel 4 Interrupt
#define INT_DMA_CH5     0x0705 // 7.5 - DMA Channel 5 Interrupt
#define INT_DMA_CH6     0x0706 // 7.6 - DMA Channel 6 Interrupt
#define INT_FSITXA_INT1 0x070B // 7.11 - FSITXA_INT1 Interrupt
#define INT_FSITXA_INT2 0x070C // 7.12 - FSITXA_INT2 Interrupt
#define INT_FSIRXA_INT1 0x070D // 7.13 - FSIRXA_INT1 Interrupt
#define INT_FSIRXA_INT2 0x070E // 7.14 - FSIRXA_INT2 Interrupt
#define INT_DCC         0x0710 // 7.16 - DCC Interrupt

// Lower PIE Group 8
#define INT_I2CA      0x0801 // 8.1 - I2CA Interrupt 1
#define INT_I2CA_FIFO 0x0802 // 8.2 - I2CA Interrupt 2
#define INT_LINA      0x0809 // 8.9 - LINA (OR SCIC_RX) Interrupt0
#define INT_SCIC_RX   0x0809 // 8.9 - LINA (OR SCIC_RX) Interrupt0
#define INT_SCIC_TX   0x080A // 8.10 - SCIC_TX Interrupt0
#define INT_PMBUSA    0x080D // 8.13 - PMBUSA Interrupt

// Lower PIE Group 9
#define INT_SCIA_RX  0x0901 // 9.1 - SCIA RX Interrupt
#define INT_SCIA_TX  0x0902 // 9.2 - SCIA TX Interrupt
#define INT_SCIB_RX  0x0903 // 9.3 - SCIB RX Interrupt
#define INT_SCIB_TX  0x0904 // 9.4 - SCIB TX Interrupt
#define INT_CANA     0x0905 // 9.5 - CANA Interrupt
#define INT_CANB     0x0906 // 9.6 - CANB Interrupt
#define INT_ADCG_EVT 0x0907 // 9.7 - ADCG Event Interrupt
#define INT_ADCG_1   0x0908 // 9.8 - ADCG Interrupt 1
#define INT_ADCG_2   0x0909 // 9.9 - ADCG Interrupt 2
#define INT_ADCG_3   0x090A // 9.10 - ADCG Interrupt 3
#define INT_ADCG_4   0x090B // 9.11 - ADCG Interrupt 4
#define INT_ADCH_EVT 0x090C // 9.12 - ADCH Event Interrupt
#define INT_ADCH_1   0x090D // 9.13 - ADCH Interrupt 1
#define INT_ADCH_2   0x090E // 9.14 - ADCH Interrupt 2
#define INT_ADCH_3   0x090F // 9.15 - ADCH Interrupt 3
#define INT_ADCH_4   0x0910 // 9.16 - ADCH Interrupt 4

// Lower PIE Group 10
#define INT_ADCA_EVT 0x0A01 // 10.1 - ADCA Event Interrupt
#define INT_ADCA2    0x0A02 // 10.2 - ADCA Interrupt 2
#define INT_ADCA3    0x0A03 // 10.3 - ADCA Interrupt 3
#define INT_ADCA4    0x0A04 // 10.4 - ADCA Interrupt 4
#define INT_ADCB_EVT 0x0A05 // 10.5 - ADCB Event Interrupt
#define INT_ADCB2    0x0A06 // 10.6 - ADCB Interrupt 2
#define INT_ADCB3    0x0A07 // 10.7 - ADCB Interrupt 3
#define INT_ADCB4    0x0A08 // 10.8 - ADCB Interrupt 4
#define INT_ADCC_EVT 0x0A09 // 10.9 - ADCC Event Interrupt
#define INT_ADCC2    0x0A0A // 10.10 - ADCC Interrupt 2
#define INT_ADCC3    0x0A0B // 10.11 - ADCC Interrupt 3
#define INT_ADCC4    0x0A0C // 10.12 - ADCC Interrupt 4

// Lower PIE Group 11
#define INT_IPC0 0x0B01 // 11.1 - IPC interrupts0
#define INT_IPC1 0x0B02 // 11.2 - IPC interrupts1
#define INT_IPC2 0x0B03 // 11.3 - IPC interrupts2
#define INT_IPC3 0x0B04 // 11.4 - IPC interrupts3
#define INT_LUF  0x0B0F // 11.15 - LUF interrupts
#define INT_LVF  0x0B10 // 11.16 - LVF interrupts

// Lower PIE Group 12
#define INT_XINT3       0x0C01 // 12.1 - XINT3 Interrupt
#define INT_XINT4       0x0C02 // 12.2 - XINT4 Interrupt
#define INT_XINT5       0x0C03 // 12.3 - XINT5 Interrupt
#define INT_XINTF       0x0C04 // 12.4 - XINTF Interrupt
#define INT_ADCA_HR_EVT 0x0C05 // 12.4 - HR ADC EVT Interrupt
#define INT_ADCA2_HR    0x0C06 // 12.4 - HR ADC Interrupt 2
#define INT_ADCA3_HR    0x0C07 // 12.4 - HR ADC Interrupt 3
#define INT_ADCA4_HR    0x0C08 // 12.4 - HR ADC Interrupt 4
#define INT_ADCB_HR_EVT 0x0C09 // 12.4 - HR ADC EVT Interrupt
#define INT_ADCB2_HR    0x0C0A // 12.4 - HR ADC Interrupt 2
#define INT_ADCB3_HR    0x0C0B // 12.4 - HR ADC Interrupt 3
#define INT_ADCB4_HR    0x0C0C // 12.4 - HR ADC Interrupt 4
#define INT_ADCC_HR_EVT 0x0C0D // 12.4 - HR ADC EVT Interrupt
#define INT_ADCC2_HR    0x0C0E // 12.4 - HR ADC Interrupt 2
#define INT_ADCC3_HR    0x0C0F // 12.4 - HR ADC Interrupt 3
#define INT_ADCC4_HR    0x0C10 // 12.4 - HR ADC Interrupt 4

// Other interrupts
#define INT_TIMER1 0x0D01 // CPU Timer 1 Interrupt
#define INT_TIMER2 0x0E01 // CPU Timer 2 Interrupt
#define INT_NMI    0x0F01 // Non-Maskable Interrupt

#endif // HW_INTS_H
