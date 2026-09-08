#include "driverlib.h"

/* start addresses for DSP text/data image and their length information
 * Their values are from flash image generation script of file 'gen_flash_image.py'
 */
#define DSP_IMAGE_INFO_START_ADDR (0x30005000U)
#define DSP_IMAGE_START_ADDR      (0x30005400U)

#define TRIM_VALID_KEY (0x5A5A5A5A)
static inline void copy_trim()
{
    uint32_t key = HWREG(FLASH0OTP1_BASE + 0);
    if (key != TRIM_VALID_KEY)
    {
        return;
    }

    HWREG(REGFILE_BASE + 0x24) = 0x55AA55AA; // unlock trim

    // copy trim data
    HWREG(REGFILE_BASE + 0) = HWREG(FLASH0OTP1_BASE + 0x4);
    HWREG(REGFILE_BASE + 4) = HWREG(FLASH0OTP1_BASE + 0x8);
    HWREG(REGFILE_BASE + 8) = HWREG(FLASH0OTP1_BASE + 0xC);

    HWREG(REGFILE_BASE + 0x20) = 1;          // enable efuse
    HWREG(REGFILE_BASE + 0x24) = 0xAA55AA55; // lock trim
}

#define DMA_LENGTH (256)
static void dma_read(int dst_addr, int src_addr, int len)
{
    while (len > 0)
    {
        // 每次用DMA传输256字节
        DmaCh1Regs.SAR = src_addr;
        DmaCh1Regs.DAR = dst_addr;
        DmaRegs.CHEN   = 0x0101; // DMA CH1 启动

        while (!(DmaCh1Regs.INTSTATUS & 0x02)) // 等待结束中断标志位
            ;
        DmaCh1Regs.INTCLEAR = 0x02; // 清除结束中断标志位

        src_addr += DMA_LENGTH;
        dst_addr += DMA_LENGTH;
        len -= DMA_LENGTH;
    }
}

extern void _dsp_boot_jmp_to_core(int);

// bit[17:15] of _CORE<n>_IRAM_START
#define CPU_EXP_START_MASK (0x3F)
#define CPU_EXP_START_OFST (15)

_Noreturn void qx_bootloader_main(void)
{
    __asm("EALLOW||");

#ifdef __boot_core0__

#define FLASH2DCSM_WORK_REG  (0x01001254)
#define FLASH2DCSM_WORK_MASK (0x1 << 4)
    // wait DCSM DMA transfer done
    //
    while (HWREG(FLASH2DCSM_WORK_REG) & FLASH2DCSM_WORK_MASK)
        ;

    copy_trim();

    // HW-related init
    //
    // set GPIODAT[119:96] to 1
    HWREG(0x01004030) = 0xFFFFFF;
    // set GPIOLPSEL to 1; GPIO can wake up DSP in low power mode
    HWREG(0x01001078) = 0x8;

    // copy core1 bootloader and application from Flash to SRAM
    //
    CpuSysRegs.PCLKCR0.bit.DMA     = 1;
    DmaRegs.CFG.all                = 0x03; // DMA 使能, 中断使能
    DmaCh1Regs.BLOCK_TS            = 0x3f; // DMA block为256字节
    DmaCh1Regs.CFG_H.all           = 0x00; // DMA MEM to MEM
    DmaCh1Regs.CTL_L.bit.SRC_WIDTH = 2;    // SRC 位宽为32Bits
    DmaCh1Regs.CTL_L.bit.DST_WIDTH = 2;    // DST 位宽为32 Bits
    DmaCh1Regs.INTSIGNAL_EN        = 0x02; // DMA中断只保留DMA传输结束中断

    // copy core1 bootloader
    dma_read(0x00282000, 0x30002000, 8 * 1024);

    // copy application
    int lenCore0Text = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x0);
    int lenCore0Data = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x4);
    int lenCore1Text = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x8);
    int lenCore1Data = HWREG(DSP_IMAGE_INFO_START_ADDR + 0xC);

    int flashCore0Text = DSP_IMAGE_START_ADDR;
    int flashCore0Data = flashCore0Text + lenCore0Text;
    int flashCore1Text = flashCore0Data + lenCore0Data;
    int flashCore1Data = flashCore1Text + lenCore1Text;

    int sramCore0Text = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x10);
    int sramCore0Data = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x14);
    int sramCore1Text = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x18);
    int sramCore1Data = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x1C);

    // 先搬运DATA_RAM以避免flash ecc出错时nmi_isr函数中无法访问数据段数据
    dma_read(sramCore0Data, flashCore0Data, lenCore0Data);
    dma_read(sramCore0Text, flashCore0Text, lenCore0Text);
    dma_read(sramCore1Data, flashCore1Data, lenCore1Data);
    dma_read(sramCore1Text, flashCore1Text, lenCore1Text);

    // DMA reset and disable
    //
    DmaRegs.RESET = 1;
    while (DmaRegs.RESET)
        ;
    CpuSysRegs.PCLKCR0.bit.DMA = 0;

    extern void boot_postprocess();
    boot_postprocess();

    // SRAM config
    //
    DevCfgRegs.GSRAM_SEL.all  = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x20);
    DevCfgRegs.FARRAM_SEL.all = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x24);

    // core0 enable instruction prefetch before jumping to DSP core
    //
    HWREG(0x01001328) = 0x1;
    HWREG(0x0100132C) = 0x1;
#endif

    // enable CPU timers CLK
    //
    CpuSysRegs.PCLKCR0.all |= 0x7E0;

#ifdef __boot_core0__
    CpuSysRegs.CPU1EXPSTART.all    = (sramCore0Text >> CPU_EXP_START_OFST) & CPU_EXP_START_MASK;
    NmiIntruptRegs.NMICFG.bit.NMIE = 1;

    _dsp_boot_jmp_to_core(sramCore0Text + 0x400U);
#else
    int sramCore1Text           = HWREG(DSP_IMAGE_INFO_START_ADDR + 0x18);
    CpuSysRegs.CPU2EXPSTART.all = (sramCore1Text >> CPU_EXP_START_OFST) & CPU_EXP_START_MASK;

    _dsp_boot_jmp_to_core(sramCore1Text + 0x400U);
#endif

    // add infinite loop to make compiler happy on _Noreturn
    while (1)
        ;
}
