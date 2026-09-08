# EPWM边沿触发100ns脉冲生成

## 功能描述

在EPWM4A信号的**上升沿**和**下降沿**分别触发输出100ns脉冲：
- **GPIO0 (EPWM1A)**：上升沿触发100ns脉冲
- **GPIO2 (EPWM2A)**：下降沿触发100ns脉冲

## 实现方法

### 上升沿脉冲 (EPWM1A)
```
EPWM4A上升沿 → EPWM4 SYNCOUT → EPWM1 SYNCIN → T1事件 → GPIO0输出HIGH → 100ns后PERIOD → GPIO0输出LOW
```

### 下降沿脉冲 (EPWM2A)
```
EPWM4A → INPUTXBAR5 → OUTPUTXBAR2(反相) → GPIO3 → INPUTXBAR6 → EXTSYNCIN2 → EPWM2 SYNCIN → T1事件 → GPIO2输出HIGH → 100ns后PERIOD → GPIO2输出LOW
```

## 关键配置

| 模块 | 配置 | 说明 |
|------|------|------|
| EPWM1 SYNCIN | SEL=24 | EPWM4 SYNCOUT |
| EPWM2 SYNCIN | SEL=25 | EXTSYNCIN2 |
| INPUTXBAR5 | GPIO6 | EPWM4A信号输入 |
| INPUTXBAR6 | GPIO3 | 反相信号输入 |
| OUTPUTXBAR2 | INPUTXBAR5反相 | 输出到GPIO3 |
| TBPRD | 9 | 100ns脉宽 (100MHz时钟) |

## 引脚功能

| 引脚 | 功能 | 说明 |
|------|------|------|
| GPIO0 | EPWM1A | 上升沿100ns脉冲输出 |
| GPIO2 | EPWM2A | 下降沿100ns脉冲输出 |
| GPIO3 | OUTPUTXBAR2 | 反相信号输出（调试用） |
| GPIO6 | EPWM4A | 触发信号源 |

## 时序图

```
GPIO6 (EPWM4A):  ____/‾‾‾‾‾‾‾‾‾‾‾‾\____/‾‾‾‾‾‾‾‾‾‾‾‾\____
GPIO3 (反相):    ‾‾‾‾\____________/‾‾‾‾\____________/‾‾‾‾
GPIO0 (上升沿):  ____/‾\_________________/‾\______________
GPIO2 (下降沿):  ________________/‾\________________/‾\___
                     ↑           ↑   ↑              ↑
                   上升沿      下降沿 上升沿        下降沿
```
