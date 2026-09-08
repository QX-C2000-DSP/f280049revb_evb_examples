#include "driverlib.h"
#include "device.h"

#include "IQmathLib.h"

typedef short int Sint;
typedef unsigned long Ulong;
typedef long long llong;

void UVWToAlphBetaAxes(long uvw_U, long uvw_V, long uvw_W, long Alph, long Beta)
{
    Alph = _IQmpy(uvw_U, _IQ(0.7071)); // 23170=((1/2)^0.5)*7FFF
    Beta = _IQmpy((uvw_V - uvw_W), _IQ(0.408242));
}

void AlphBetaToDQ(long Alph, long Beta, Sint angle, long M, long T)
{
    long m_sin, m_cos;
    long m_Long;

    //  silan_IQsinPU_IQcosPU((long)angle << (GLOBAL_IQ - 16), &m_sin, &m_cos);
    //  MT->M = silan_mult_abPcd(AlphBeta->Alph, m_cos, AlphBeta->Beta, m_sin);
    //  MT->T = silan_mult_abMcd(AlphBeta->Beta, m_cos, AlphBeta->Alph, m_sin);

    m_sin = _IQ24sin((angle));
    m_cos = _IQ24sin((16384 - angle));
    M     = (((llong)m_cos * (llong)(Alph)) + ((llong)m_sin * (llong)(Beta))) >> 24;
    T     = (-((llong)m_sin * (llong)(Alph)) + ((llong)m_cos * (llong)(Beta))) >> 24;
}
long Alph, Beta;
long Alph_12, Beta_12;
long M_24, T_24;
long M_12, T_12;
long Theta;

int test_atan(int x, int y)
{
    int32 result;
    long m_Input;

    if (x == 0)
    {
        if (y < 0)
        {
            return (-16384);
        }
        else
        {
            return (16384);
        }
    }
    m_Input = (((long)y) << 16) / x;
#if 0
        result = qatan(m_Input);
#else
    result = _IQ16atan2(1, m_Input);
#endif
    if (x < 0)
    {
        result += 32768;
    }
    return 0;
}

void ChangeCurrent(void)
{
    Sint temp1, temp2;
    Ulong tmpAmp;

    // 获取三相电流瞬时值, 三相电流转换为定子两相坐标轴下的电流
    UVWToAlphBetaAxes(_IQ(0.1), _IQ(0), _IQ(0.2), Alph, Beta);
    Alph_12 = Alph >> 12;
    Beta_12 = Beta >> 12;
    // 定子两相坐标轴下电流转换为DQ下的电流
    AlphBetaToDQ(Alph_12, Beta_12, _IQ(0.1), M_24, T_24);

    M_12 = M_24 >> 12; // 取消滤波，滤波严重影响SVC电流环带宽
    T_12 = T_24 >> 12;

    Theta = test_atan(M_12, T_12); // 计算MT轴夹角
}

int main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    ChangeCurrent();
}
