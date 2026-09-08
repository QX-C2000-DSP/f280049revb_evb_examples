#include "sci_printf.h"

u8 sim_env_flag = 0; // 前仿环境标志位

volatile struct SCI_REGS *dbg_uart; // 调试使用的串口

/* chip autotest tool uses one 32-bit DRAM location to indicate testcase starts or
 * ends its running.
 *
 * The 32-bit DRAM location is chosen by chip type, and must be match with that in
 * chip autotest tool. The DRAM location is set to 0x202101AA to indicate case start,
 * and set to 0xCA5E8EAD to indicate case end.
 */

#ifdef CHIP_AUTOTEST
// In the middle of CORE1 DRAM, must match with chip autotest tool
#define CHIP_AUTOTEST_CASE_STS_MEM_ADDR (0x30000)
#define CHIP_AUTOTEST_CASE_STS_START    (0x202101AA)
#define CHIP_AUTOTEST_CASE_STS_END      (0xCA5E8EAD)
#endif

void chipAutotestCaseStart()
{
#ifdef CHIP_AUTOTEST
    HWREG(CHIP_AUTOTEST_CASE_STS_MEM_ADDR) = CHIP_AUTOTEST_CASE_STS_START;
#endif
}

void chipAutotestCaseEnd()
{
#ifdef CHIP_AUTOTEST
    HWREG(CHIP_AUTOTEST_CASE_STS_MEM_ADDR) = CHIP_AUTOTEST_CASE_STS_END;
#endif
}

// 1s ~= 500000 at 25Mhz cpu_clk
void simple_delay(u32 count)
{
    volatile int i = 0;
    for (i = 0; i < count; i++)
        ;
}

__attribute__((weak)) void StdOutInit(
    volatile struct SCI_REGS *sci, int baudrate, uint32_t pin, uint32_t pin_mux)
{
    dbg_uart = sci;

    if (sci == &SciaRegs)
        CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    else
        CpuSysRegs.PCLKCR7.bit.SCI_B = 1;

    // 为加速前仿, 前仿环境波特率总是配置到最高(由于bclk产生机制限制,DLL小于2时将无法打印)
    if (sim_env_flag)
    {
        sci->SCICCR.bit.SCICHAR  = 7;
        sci->SCILBAUD.all        = 3;
        sci->SCICTL1.bit.SWRESET = 1;
        sci->SCICTL1.bit.TXENA   = 1;
    }
    else
    {
        // Baud = LSPCLK / ((BRR + 1) * 8)
        float tmp = (float)DEVICE_LSPCLK_FREQ / 8 / baudrate;
        if ((tmp - (int)tmp) >= 0.5)
            tmp = tmp + 1;
        int val = (int)tmp - 1;

        sci->SCICCR.bit.SCICHAR  = 7;
        sci->SCILBAUD.all        = val & 0xFF;
        sci->SCIHBAUD.all        = val >> 8;
        sci->SCICTL1.bit.SWRESET = 1;
        sci->SCICTL1.bit.TXENA   = 1;

        GPIO_setPinConfig(pin_mux);
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
    }
}

// 主动结束 VCS or FPGA 仿真
__attribute__((weak)) void EndSimulation(void)
{
    // for VCS simulation end
    putchar(0x4);
    // for chip autotest
    chipAutotestCaseEnd();
}

__attribute__((weak)) void verify_data_byte(void *buf1, void *buf2, u32 len)
{
    for (int i = 0; i < len; i++)
    {
        if (((u8 *)buf1)[i] != ((u8 *)buf2)[i])
        {
            printf("ERR:[%d]=%x, [%d]=%x\n", i, ((u8 *)buf1)[i], i, ((u8 *)buf2)[i]);
            break;
        }
    }
}

// 以wireshack相似的格式打印数据, 主要为了方便包信息分析和调试
__attribute__((weak)) void buf_dump(const char *head, const char *buf, int len)
{
    if (head)
        printf("%s\n", head);
    int i;
    printf("---------------------------------------------------------------------\n");
    printf("%08X ---| %02X ", 0, buf[0]);
    for (i = 1; i < len; ++i)
    {
        if (!(i % 16))
            printf("|\n%08X ---| ", i / 16 * 16);
        else if (!(i % 4))
            printf("| ");
        printf("%02X ", buf[i]);
    }
    if (!(i % 16))
        printf("|");
    printf("\n---------------------------------------------------------------------\n\n");
}

// 自实现puts+printf函数(不依赖libc库)
#include <stdarg.h>

__attribute__((weak)) void putchar(char c)
{
    while (!dbg_uart->SCICTL2.bit.TXRDY)
        ;
    dbg_uart->SCITXBUF.all = c;
    while (!dbg_uart->SCICTL2.bit.TXRDY)
        ;
}

__attribute__((weak)) void puts(const char *str)
{
    while (*str)
    {
        putchar(*str);
        str++;
    }
    putchar('\n');
}

// 计算m^n
__attribute__((weak)) unsigned long m_pow_n(unsigned long m, unsigned long n)
{
    unsigned long i = 0, ret = 1;
    if (n < 0)
        return 0;
    for (i = 0; i < n; i++)
        ret *= m;
    return ret;
}

// 返回值为打印字符的个数
// 支持%d, %x，%s，%c，%f（只打印6位数字）
__attribute__((weak)) int printf(const char *str, ...)
{
    unsigned int ret_num    = 0;           // 返回打印字符的个数
    char *pStr              = (char *)str; // 指向str
    int ArgIntVal           = 0;           // 接收整型
    unsigned long ArgHexVal = 0;           // 接十六进制
    char *ArgStrVal         = NULL;        // 接收字符型
    double ArgFloVal        = 0.0;         // 接受浮点型
    unsigned long val_seg   = 0;           // 数据切分
    unsigned long val_temp  = 0;           // 临时保存数据
    int cnt                 = 0;           // 数据长度计数
    int i                   = 0;

    va_list pArgs;        // 定义va_list类型指针，用于存储参数的地址
    va_start(pArgs, str); // 初始化pArgs
    while (*pStr != '\0')
    {
        switch (*pStr)
        {
            case ' ':
            case '\r':
            case '\n':
                putchar(*pStr);
                ret_num++;
                break;
            case '\t':
                putchar(*pStr);
                ret_num += 4;
                break;
            case '%':
                pStr++;
                // % 格式解析
                switch (*pStr)
                {
                    case '%':
                        putchar('%'); // %%，输出%
                        ret_num++;
                        pStr++;
                        continue;
#if 1
                    case 'c':
                        ArgIntVal = va_arg(pArgs, int); // %c，输出char
                        putchar((char)ArgIntVal);
                        ret_num++;
                        pStr++;
                        continue;
                    case 's':
                        // 接收字符
                        ArgStrVal = va_arg(pArgs, char *);
                        ret_num += (unsigned int)strlen(ArgStrVal);
                        while (*ArgStrVal)
                        {
                            putchar(*ArgStrVal);
                            ArgStrVal++;
                        }
                        pStr++;
                        continue;
#endif
#if 1
                    case 'x':
                        // 接收16进制
                        ArgHexVal = va_arg(pArgs, unsigned long);
                        val_seg   = ArgHexVal;
                        // 计算ArgIntVal长度
                        if (ArgHexVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 16;
                            }
                        }
                        else
                            cnt = 1; // 数字0的长度为1

                        ret_num += cnt; // 字符个数加上整数的长度
                        // 将整数转为单个字符打印
                        while (cnt)
                        {
                            val_seg = ArgHexVal / m_pow_n(16, cnt - 1);
                            ArgHexVal %= m_pow_n(16, cnt - 1);
                            if (val_seg <= 9)
                                putchar((char)val_seg + '0');
                            else
                            {
                                // putchar((char)val_seg - 10 + 'a'); //小写字母
                                putchar((char)val_seg - 10 + 'A');
                            }
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 1
                    case 'd':
                        // 接收整型
                        ArgIntVal = va_arg(pArgs, int);
                        if (ArgIntVal < 0) // 如果为负数打印，负号
                        {
                            ArgIntVal = -ArgIntVal; // 取相反数

                            putchar('-');
                            ret_num++;
                        }
                        val_seg = ArgIntVal; // 赋值给 val_seg处理数据
                        // 计算ArgIntVal长度
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 10;
                            }
                        }
                        else
                            cnt = 1; // 数字0的长度为1

                        ret_num += cnt; // 字符个数加上整数的长度

                        // 将整数转为单个字符打印
                        while (cnt)
                        {
                            val_seg = ArgIntVal / m_pow_n(10, cnt - 1);
                            ArgIntVal %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 1 // %f 打印支持
                    case 'f':
                        // 接收浮点型 保留6为小数，不采取四舍五入
                        ArgFloVal = va_arg(pArgs, double);
                        val_seg   = (unsigned long)ArgFloVal; // 取整数部分
                        val_temp  = val_seg;                  // 临时保存整数部分数据
                        ArgFloVal = ArgFloVal - val_seg;      // 得出余下的小数部分
                        // 计算整数部分长度
                        if (val_seg)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 10;
                            }
                        }
                        else
                            cnt = 1;    // 数字0的长度为1
                        ret_num += cnt; // 字符个数加上整数的长度
                        // 将整数转为单个字符打印
                        while (cnt)
                        {
                            val_seg = val_temp / m_pow_n(10, cnt - 1);
                            val_temp %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        // 打印小数点
                        putchar('.');
                        ret_num++;
                        // 开始输出小数部分
                        ArgFloVal *= 1000000;
                        // printf("\r\n %f\r\n", ArgFloVal);
                        cnt      = 6;
                        val_temp = (int)ArgFloVal; // 取整数部分
                        while (cnt)
                        {
                            val_seg = val_temp / m_pow_n(10, cnt - 1);
                            val_temp %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        ret_num += 6;
                        pStr++;
                        continue;
                    default: // % 匹配错误，暂输出空格
                        putchar(' ');
                        ret_num++;
                        continue;
#endif
                }
            default:
                putchar(*pStr);
                ret_num++;
                break;
        }
        pStr++;
    }
    va_end(pArgs); // 结束取参数

    return ret_num;
}
