#ifndef F28004X_PIEVECT_H
#define F28004X_PIEVECT_H
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// PIE Interrupt Vector Table Definition:
// Create a user type called PINT (pointer to interrupt):

typedef void (*PINT)(void);

// Define Vector Table:
struct PIE_VECT_TABLE
{
    PINT BUSERROR0_INT;     // 0.1 - bus error 0
    PINT BUSERROR1_INT;     // 0.2 - bus error 1
    PINT BUSERROR2_INT;     // 0.3 - bus error 2
    PINT BUSERROR3_INT;     // 0.4 - bus error 3
    PINT ILLEGALINST_INT;   // 0.5 - exception illegal instruction
    PINT OVERFLOW_INT;      // 0.6 - exception overflow
    PINT ILLEGALADDR_INT;   // 0.7 - exception illegal address
    PINT EXCEPTION3_INT;    // 0.8 - exception 3
    PINT UNAVOIDEDPIC0_INT; // 0.9 - unavoided pic 0
    PINT PIE0_RESERVED_INT; // 0.10
    PINT PIE1_RESERVED_INT; // 0.11
    PINT PIE2_RESERVED_INT; // 0.12
    PINT PIE3_RESERVED_INT; // 0.13
    PINT PIE4_RESERVED_INT; // 0.14
    PINT PIE5_RESERVED_INT; // 0.15
    PINT PIE6_RESERVED_INT; // 0.16

    PINT RTOS_INT;          // 1.1 - RTOS Interrupt
    PINT TRACE_INT;         // 1.2 - trace buffer Interrupt
    PINT WP_INT;            // 1.3 - watch point Interrupt
    PINT ADCA1_INT;         // 1.4 - ADCA Interrupt 1
    PINT ADCB1_INT;         // 1.5 - ADCB Interrupt 1
    PINT ADCC1_INT;         // 1.6 - ADCC Interrupt 1
    PINT XINT1_INT;         // 1.7 - XINT1 Interrupt
    PINT XINT2_INT;         // 1.8 - XINT2 Interrupt
    PINT PIE7_RESERVED_INT; // 1.9
    PINT TIMER0_INT;        // 1.10 - Timer 0 Interrupt
    PINT WAKE_INT;          // 1.11 - Halt Wakeup Interrupt
    PINT PIE8_RESERVED_INT; // 1.12
    PINT PIE9_RESERVED_INT; // 1.13
    PINT ADCA1_HR_INT;      // 1.14 - HR ADCA Interrupt 1
    PINT ADCB1_HR_INT;      // 1.15 - HR ADCB Interrupt 1
    PINT ADCC1_HR_INT;      // 1.16 - HR ADCC Interrupt 1

    PINT EPWM1_TZ_INT;       // 2.1 - ePWM1 Trip Zone Interrupt
    PINT EPWM2_TZ_INT;       // 2.2 - ePWM2 Trip Zone Interrupt
    PINT EPWM3_TZ_INT;       // 2.3 - ePWM3 Trip Zone Interrupt
    PINT EPWM4_TZ_INT;       // 2.4 - ePWM4 Trip Zone Interrupt
    PINT EPWM5_TZ_INT;       // 2.5 - ePWM5 Trip Zone Interrupt
    PINT EPWM6_TZ_INT;       // 2.6 - ePWM6 Trip Zone Interrupt
    PINT EPWM7_TZ_INT;       // 2.7 - ePWM7 Trip Zone Interrupt
    PINT EPWM8_TZ_INT;       // 2.8 - ePWM8 Trip Zone Interrupt
    PINT EPWM9_TZ_INT;       // 2.9 - ePWM9 Trip Zone Interrupt
    PINT EPWM10_TZ_INT;      // 2.10 - ePWM10 Trip Zone Interrupt
    PINT EPWM11_TZ_INT;      // 2.11 - ePWM11 Trip Zone Interrupt
    PINT EPWM12_TZ_INT;      // 2.12 - ePWM12 Trip Zone Interrupt
    PINT PIE10_RESERVED_INT; // 2.13
    PINT PIE11_RESERVED_INT; // 2.14
    PINT PIE12_RESERVED_INT; // 2.15
    PINT PIE13_RESERVED_INT; // 2.16

    PINT EPWM1_INT;          // 3.1 - ePWM1 Interrupt
    PINT EPWM2_INT;          // 3.2 - ePWM2 Interrupt
    PINT EPWM3_INT;          // 3.3 - ePWM3 Interrupt
    PINT EPWM4_INT;          // 3.4 - ePWM4 Interrupt
    PINT EPWM5_INT;          // 3.5 - ePWM5 Interrupt
    PINT EPWM6_INT;          // 3.6 - ePWM6 Interrupt
    PINT EPWM7_INT;          // 3.7 - ePWM7 Interrupt
    PINT EPWM8_INT;          // 3.8 - ePWM8 Interrupt
    PINT EPWM9_INT;          // 3.9 - ePWM9 Interrupt
    PINT EPWM10_INT;         // 3.10 - ePWM10 Interrupt
    PINT EPWM11_INT;         // 3.11 - ePWM11 Interrupt
    PINT EPWM12_INT;         // 3.12 - ePWM12 Interrupt
    PINT PIE14_RESERVED_INT; // 3.13
    PINT PIE15_RESERVED_INT; // 3.14
    PINT PIE16_RESERVED_INT; // 3.15
    PINT PIE17_RESERVED_INT; // 3.16

    PINT ECAP1_INT;          // 4.1 - eCAP1 Interrupt
    PINT ECAP2_INT;          // 4.2 - eCAP2 Interrupt
    PINT ECAP3_INT;          // 4.3 - eCAP3 Interrupt
    PINT ECAP4_INT;          // 4.4 - eCAP4 Interrupt
    PINT ECAP5_INT;          // 4.5 - eCAP5 Interrupt
    PINT ECAP6_INT;          // 4.6 - eCAP6 Interrupt
    PINT ECAP7_INT;          // 4.7 - eCAP7 Interrupt
    PINT PIE18_RESERVED_INT; // 4.8
    PINT PIE19_RESERVED_INT; // 4.9
    PINT PIE20_RESERVED_INT; // 4.10
    PINT PIE21_RESERVED_INT; // 4.11
    PINT PIE22_RESERVED_INT; // 4.12
    PINT PIE23_RESERVED_INT; // 4.13
    PINT HRCAP1_INT;         // 4.14 - HRCAP1 Interrupt
    PINT HRCAP2_INT;         // 4.15 - HRCAP2 Interrupt
    PINT PIE24_RESERVED_INT; // 4.16

    PINT EQEP1_INT;          // 5.1 - eQEP1 Interrupt
    PINT EQEP2_INT;          // 5.2 - eQEP2 Interrupt
    PINT PIE25_RESERVED_INT; // 5.3
    PINT PIE26_RESERVED_INT; // 5.4
    PINT PIE27_RESERVED_INT; // 5.5
    PINT PIE28_RESERVED_INT; // 5.6
    PINT PIE29_RESERVED_INT; // 5.7
    PINT PIE30_RESERVED_INT; // 5.8
    PINT SDFM1_INT;          // 5.9 - SDFM1 Interrupt
    PINT PIE31_RESERVED_INT; // 5.10
    PINT PIE32_RESERVED_INT; // 5.11
    PINT PIE33_RESERVED_INT; // 5.12
    PINT SDFM1DR1_INT;       // 5.13 - SDFM1DR1 Interrupt
    PINT SDFM1DR2_INT;       // 5.14 - SDFM1DR1 Interrupt
    PINT SDFM1DR3_INT;       // 5.15 - SDFM1DR1 Interrupt
    PINT SDFM1DR4_INT;       // 5.16 - SDFM1DR1 Interrupt

    PINT SPIA_RX_INT;        // 6.1 - SPIA RX Interrupt
    PINT SPIA_TX_INT;        // 6.2 - SPIA TX Interrupt
    PINT SPIB_RX_INT;        // 6.3 - SPIB RX Interrupt
    PINT SPIB_TX_INT;        // 6.4 - SPIB TX Interrupt
    PINT PIE34_RESERVED_INT; // 6.5
    PINT PIE35_RESERVED_INT; // 6.6
    PINT PIE36_RESERVED_INT; // 6.7
    PINT PIE37_RESERVED_INT; // 6.8
    PINT PIE38_RESERVED_INT; // 6.9
    PINT PIE39_RESERVED_INT; // 6.10
    PINT PIE40_RESERVED_INT; // 6.11
    PINT PIE41_RESERVED_INT; // 6.12
    PINT PIE42_RESERVED_INT; // 6.13
    PINT PIE43_RESERVED_INT; // 6.14
    PINT PIE44_RESERVED_INT; // 6.15
    PINT PIE45_RESERVED_INT; // 6.16

    PINT DMA_CH1_INT;        // 7.1 - DMA Channel 1 Interrupt
    PINT DMA_CH2_INT;        // 7.2 - DMA Channel 2 Interrupt
    PINT DMA_CH3_INT;        // 7.3 - DMA Channel 3 Interrupt
    PINT DMA_CH4_INT;        // 7.4 - DMA Channel 4 Interrupt
    PINT DMA_CH5_INT;        // 7.5 - DMA Channel 5 Interrupt
    PINT DMA_CH6_INT;        // 7.6 - DMA Channel 6 Interrupt
    PINT PIE46_RESERVED_INT; // 7.7
    PINT PIE47_RESERVED_INT; // 7.8
    PINT PIE48_RESERVED_INT; // 7.9
    PINT PIE49_RESERVED_INT; // 7.10
    PINT FSITXA_INT1;        // 7.11 - FSITXA_INT1
    PINT FSITXA_INT2;        // 7.12 - FSITXA_INT2
    PINT FSIRXA_INT1;        // 7.13 - FSIRXA_INT1
    PINT FSIRXA_INT2;        // 7.14 - FSIRXA_INT2
    PINT PIE50_RESERVED_INT; // 7.15
    PINT DCC_INT;            // 7.16 - DCC Interrupt

    PINT I2CA_INT;           // 8.1 - I2CA Interrupt 1
    PINT I2CA_FIFO_INT;      // 8.2
    PINT PIE52_RESERVED_INT; // 8.3
    PINT PIE53_RESERVED_INT; // 8.4
    PINT PIE54_RESERVED_INT; // 8.5
    PINT PIE55_RESERVED_INT; // 8.6
    PINT PIE56_RESERVED_INT; // 8.7
    PINT PIE57_RESERVED_INT; // 8.8
    PINT LINA_INT;           // 8.9 - LINA Interrupt (OR SCIC_RX_INT)
    PINT SCIC_TX_INT;        // 8.10 - SCIC TX Interrupt
    PINT PIE59_RESERVED_INT; // 8.11
    PINT PIE60_RESERVED_INT; // 8.12
    PINT PMBUSA_INT;         // 8.13 - PMBUSA Interrupt
    PINT PIE61_RESERVED_INT; // 8.14
    PINT PIE62_RESERVED_INT; // 8.15
    PINT PIE63_RESERVED_INT; // 8.16

    PINT SCIA_RX_INT;  // 9.1 - SCIA RX Interrupt
    PINT SCIA_TX_INT;  // 9.2 - SCIA TX Interrupt
    PINT SCIB_RX_INT;  // 9.3 - SCIB RX Interrupt
    PINT SCIB_TX_INT;  // 9.4 - SCIB TX Interrupt
    PINT CANA_INT;     // 9.5 - CANA Interrupt
    PINT CANB_INT;     // 9.6 - CANB Interrupt
    PINT ADCG_EVT_INT; // 9.7 - ADCG Event Interrupt
    PINT ADCG_1_INT;   // 9.8 - ADCG Interrupt 1
    PINT ADCG_2_INT;   // 9.9 - ADCG Interrupt 2
    PINT ADCG_3_INT;   // 9.10 - ADCG Interrupt 3
    PINT ADCG_4_INT;   // 9.11 - ADCG Interrupt 4
    PINT ADCH_EVT_INT; // 9.12 - ADCG Event Interrupt
    PINT ADCH_1_INT;   // 9.13 - ADCG Interrupt 1
    PINT ADCH_2_INT;   // 9.14 - ADCG Interrupt 2
    PINT ADCH_3_INT;   // 9.15 - ADCG Interrupt 3
    PINT ADCH_4_INT;   // 9.16 - ADCG Interrupt 4

    PINT ADCA_EVT_INT;       // 10.1 - ADCA Event Interrupt
    PINT ADCA2_INT;          // 10.2 - ADCA Interrupt 2
    PINT ADCA3_INT;          // 10.3 - ADCA Interrupt 3
    PINT ADCA4_INT;          // 10.4 - ADCA Interrupt 4
    PINT ADCB_EVT_INT;       // 10.5 - ADCB Event Interrupt
    PINT ADCB2_INT;          // 10.6 - ADCB Interrupt 2
    PINT ADCB3_INT;          // 10.7 - ADCB Interrupt 3
    PINT ADCB4_INT;          // 10.8 - ADCB Interrupt 4
    PINT ADCC_EVT_INT;       // 10.9 - ADCC Event Interrupt
    PINT ADCC2_INT;          // 10.10 - ADCC Interrupt 2
    PINT ADCC3_INT;          // 10.11 - ADCC Interrupt 3
    PINT ADCC4_INT;          // 10.12 - ADCC Interrupt 4
    PINT PIE76_RESERVED_INT; // 10.13
    PINT PIE77_RESERVED_INT; // 10.14
    PINT PIE78_RESERVED_INT; // 10.15
    PINT PIE79_RESERVED_INT; // 10.16

    PINT IPC0_INT;           // 11.1 - IPC0 Interrupt
    PINT IPC1_INT;           // 11.2 - IPC1 Interrupt
    PINT IPC2_INT;           // 11.3 - IPC2 Interrupt
    PINT IPC3_INT;           // 11.4 - IPC3 Interrupt
    PINT PIE80_RESERVED_INT; // 11.5
    PINT PIE81_RESERVED_INT; // 11.6
    PINT PIE82_RESERVED_INT; // 11.7
    PINT PIE83_RESERVED_INT; // 11.8
    PINT PIE84_RESERVED_INT; // 11.9
    PINT PIE85_RESERVED_INT; // 11.10
    PINT PIE86_RESERVED_INT; // 11.11
    PINT PIE87_RESERVED_INT; // 11.12
    PINT PIE88_RESERVED_INT; // 11.13
    PINT PIE89_RESERVED_INT; // 11.14
    PINT PIE90_RESERVED_INT; // 11.15
    PINT PIE91_RESERVED_INT; // 11.16

    PINT XINT3_INT;       // 12.1 - XINT3 Interrupt
    PINT XINT4_INT;       // 12.2 - XINT4 Interrupt
    PINT XINT5_INT;       // 12.3 - XINT5 Interrupt
    PINT XINTF_INT;       // 12.4 - XINTF Interrupt
    PINT ADCA_HR_EVT_INT; // 12.5 - HR ADCA Event Interrupt
    PINT ADCA2_HR_INT;    // 12.6 - HR ADCA Interrupt 2
    PINT ADCA3_HR_INT;    // 12.7 - HR ADCA Interrupt 3
    PINT ADCA4_HR_INT;    // 12.8 - HR ADCA Interrupt 4
    PINT ADCB_HR_EVT_INT; // 12.9 - HR ADCB Event Interrupt
    PINT ADCB2_HR_INT;    // 12.10  - HR ADCB Interrupt 2
    PINT ADCB3_HR_INT;    // 12.11 - HR ADCB Interrupt 3
    PINT ADCB4_HR_INT;    // 12.12 - HR ADCB Interrupt 4
    PINT ADCC_HR_EVT_INT; // 12.13 - HR ADCC Event Interrupt
    PINT ADCC2_HR_INT;    // 12.14 - HR ADCC Interrupt 2
    PINT ADCC3_HR_INT;    // 12.15 - HR ADCC Interrupt 3
    PINT ADCC4_HR_INT;    // 12.16 - HR ADCC Interrupt 4

    PINT TIMER1_INT;             // 13.1 - CPU Timer 1 Interrupt
    PINT PIE92_RESERVED_INT[15]; // 13.2 ~ 13.16

    PINT TIMER2_INT;             // 14.1 - CPU Timer 2 Interrupt
    PINT PIE93_RESERVED_INT[15]; // 14.2 ~ 14.16

    PINT NMI_INT;                // 15.1 - Non-Maskable Interrupt
    PINT PIE94_RESERVED_INT[15]; // 15.2 ~ 15.16
};

//---------------------------------------------------------------------------
// PieVect External References & Function Declarations:
//

extern volatile struct PIE_VECT_TABLE PieVectTable0;
extern volatile struct PIE_VECT_TABLE PieVectTable1;

#ifdef __CORE0__
#define PieVectTable PieVectTable0
#else
#define PieVectTable PieVectTable1
#endif
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // end of F28004X_PIEVECT_H definition
//===========================================================================
// End of file.
//===========================================================================
