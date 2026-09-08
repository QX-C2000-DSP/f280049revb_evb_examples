# ADC (模数转换器) 驱动库 API 参考文档

本手册详细整理了芯片底层驱动库（driverlib）中 ADC 模块的所有 `static inline` 与 `extern` API 函数。针对每个函数，我们结合芯片硬件架构特点，提供了细化的功能描述、参数说明、返回值，并在关键函数处附带了示例代码，旨在帮助开发者深入理解并快速上手。

---

## 1. 全局与基础配置

### 1.1 `ADC_isBaseValid`
* **功能详细描述**：
  检查传入的 ADC 基地址是否合法有效。此函数主要用于在调试模式下，结合驱动库的 `ASSERT` 宏，对用户的输入参数进行内存地址安全性验证，防止由于传入错误的宏定义导致非法指针操作。
* **参数**：
  * `base`: ADC 模块的基地址（例如 `ADCA_BASE`）。
* **返回值**：`bool`，若地址有效返回 `true`，否则返回 `false`。

### 1.2 `ADC_setPrescaler`
* **功能详细描述**：
  设置 ADC 模块的时钟预分频器。ADC 模块的内核工作时钟 (ADCCLK) 是从系统高速外设时钟分频而来的，此函数决定了该分频比例。合理设置时钟频率对于保证内部电容充放电时间、维持采样精度至关重要。配置时，需确保分频后的时钟频率未超过芯片数据手册中规定的 ADCCLK 最大允许频率（通常为 50MHz 或更高）。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `clkPrescale`: 预分频值，枚举类型 `ADC_ClkPrescale`（如 `ADC_CLK_DIV_1_0` 表示输入时钟不分频，`ADC_CLK_DIV_2_0` 表示二分频，以此类推直到 `ADC_CLK_DIV_31_0`）。
* **返回值**：无。
* **示例代码**：
  ```c
  // 将 ADCA 的时钟预分频设为 /4.0
  ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);
  ```

### 1.3 `ADC_enableConverter` / `ADC_disableConverter`
* **功能详细描述**：
  这两组函数用于开启或关闭 ADC 核心模拟转换器电路的供电。系统上电默认状态下，ADC 处于掉电模式以最大化地节省功耗。在进行任何采样转换之前，必须调用 `ADC_enableConverter` 唤醒 ADC 模拟电路，**并在调用后务必插入至少 1 毫秒的软件延时**，以等待模拟参考带隙电路彻底上电稳定，否则首次采样的数值可能会出现剧烈偏差。
* **参数**：
  * `base`: ADC 模块的基地址。
* **返回值**：无。
* **示例代码**：
  ```c
  ADC_enableConverter(ADCA_BASE);
  // 必须插入延时等待上电稳定
  DEVICE_DELAY_US(1000); 
  ```

### 1.4 `ADC_isBusy`
* **功能详细描述**：
  检查当前 ADC 硬件是否正在执行模数转换操作。在需要动态修改 ADC 核心配置（如切换系统时钟、修改参考电压）或者系统准备进入深度睡眠前，可以通过轮询此函数的返回值，确保 ADC 处于完全空闲的状态，防止破坏正在进行的采样流程。
* **参数**：
  * `base`: ADC 模块的基地址。
* **返回值**：`bool`，若正在转换则返回 `true`，若处于空闲状态则返回 `false`。

### 1.5 `ADC_setVREF`
* **功能详细描述**：
  配置 ADC 模块的参考电压源和参考电压幅值。ADC 在执行模数转换时，必须依赖一个高精度的参考电压作为满量程基准来量化外部的模拟信号。通过此函数，开发者可以基于具体的硬件板级设计，选择激活芯片内部自带的高精度参考基准，或者配置为接受来自外部 VREF 引脚引入的基准电压。同时，针对内部参考源，还可设定 3.3V 或 2.5V 两种不同的满量程范围以适配不同幅度的输入。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `refMode`: 参考源模式，`ADC_REFERENCE_INTERNAL`（内部参考） 或 `ADC_REFERENCE_EXTERNAL`（外部参考）。
  * `refVoltage`: 参考电压标称值选择，`ADC_REFERENCE_3_3V` 或 `ADC_REFERENCE_2_5V`。
* **返回值**：无。
* **示例代码**：
  ```c
  // 配置 ADCA 使用内部产生的 3.3V 参考电压
  ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
  ```

---

## 2. SOC (Start-of-Conversion) 配置与控制

### 2.1 `ADC_setupSOC`
* **功能详细描述**：
  **这是进行 ADC 采样配置最核心的函数。** ADC 的每一次采样动作都由一个称为 "SOC (Start-of-Conversion)" 的独立硬件结构控制。该函数用于全方位定义某一个具体 SOC 的工作行为：规定它在什么硬件事件下启动、选择采集哪个物理引脚的电压、以及保持电容对该引脚充电的时间。芯片支持 16 个独立或级联的 SOC 配置，用户既能将同一个 PWM 触发源分配给所有 SOC 实现多通道严格同步采样，也能让它们独立工作。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `socNumber`: 需要配置的 SOC 编号，枚举 `ADC_SOCNumber`（支持 `ADC_SOC_NUMBER0` ~ `ADC_SOC_NUMBER15`）。
  * `trigger`: 触发此 SOC 启动采样的硬件或软件事件源，枚举 `ADC_Trigger`（例如 `ADC_TRIGGER_SW_ONLY` 仅允许软件触发, `ADC_TRIGGER_EPWM1_SOCA` 允许由 EPWM1 模块产生的 SOCA 信号触发等）。
  * `channel`: 对应要进行采样的外部物理引脚或内部通道，枚举 `ADC_Channel`（例如 `ADC_CH_ADCIN0` 到 `ADC_CH_ADCIN15`）。
  * `sampleWindow`: 采样/保持 (S/H) 窗口持续时间，以系统时钟 (SYSCLK) 周期为单位。根据外部调理电路运算放大器的驱动能力与输入阻抗，需要合理调整此值（通常推荐在十几个到几十个周期），确保内部采样电容能充满至与外部电压等电位。
* **返回值**：无。
* **示例代码**：
  ```c
  // 配置 SOC0：由 EPWM1_SOCA 信号硬件自动触发，采集 ADCIN0 通道，采样窗宽设为 15 个 SYSCLK 周期
  ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 15);
  ```

### 2.2 `ADC_setSOCPriority`
* **功能详细描述**：
  设置各个 SOC 之间的仲裁与抢占优先级模式。当多个 SOC 几乎同时收到触发请求时，仲裁器决定了它们的执行顺序。ADC 默认采用“全轮询 (Round-Robin)”模式：SOC0 起始，依次往下均匀服务。如果系统中存在高频或极其关键的安全信号需要被立即采样，可以使用此函数将某个或某几个前置 SOC 提升为最高优先级。此时，一旦高优先级 SOC 被触发，它会打断常规的轮询队列排队，在其获取转换资源的下一刻立即执行采样。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `priMode`: 优先级模式，枚举 `ADC_PriorityMode`（如 `ADC_PRI_ALL_ROUND_ROBIN` 全部轮询，或 `ADC_PRI_SOC0_HIPRI` 将 SOC0 设为最高优先级）。
* **返回值**：无。

### 2.3 `ADC_forceSOC` / `ADC_forceMultipleSOC`
* **功能详细描述**：
  通过纯软件指令，强制且立即向指定的 SOC（或多个 SOC）下发启动采样的命令。这种方式完全绕过硬件触发源。它通常被用于完全靠软件定时器驱动的慢速轮询采样系统，或在系统开机初始化阶段对模拟通道连接状态进行诊断自检。
  当强制多个 SOC 时，可以一次性提交按位或组合的掩码，这可以显著降低多次调用单通道强制函数所带来的 CPU 指令开销。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `socNumber` / `socMask`: 被强制触发的单个 SOC 编号，或由掩码（如 `ADC_FORCE_SOC0 | ADC_FORCE_SOC1`）组合的多个 SOC。
* **返回值**：无。
* **示例代码**：
  ```c
  // 软件同步强制启动 ADCA 中的 SOC0 和 SOC1 进行一次转换
  ADC_forceMultipleSOC(ADCA_BASE, (ADC_FORCE_SOC0 | ADC_FORCE_SOC1));
  ```

---

## 3. 中断配置与管理

### 3.1 `ADC_setInterruptSource`
* **功能详细描述**：
  此函数用于将特定 SOC 的采样完成标志（End of Conversion, EOC）与芯片级的 ADC 中断请求线（通常每个 ADC 模块包含 INT1~INT4 四条线路）进行路由绑定。当用户指定的 SOC 结束从模拟量到数字量的整个转换流程并锁存结果后，它将自动向中断控制器发出所绑定的特定中断请求。通过合理编排，用户可以让所有通道采样全部结束后，仅利用最后一个 SOC 的完成事件来触发统一的控制算法中断。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `adcIntNum`: 要配置的 ADC 内部中断编号（如 `ADC_INT_NUMBER1`）。
  * `socNumber`: 负责触发该中断的 SOC 编号。
* **返回值**：无。
* **示例代码**：
  ```c
  // 配置当 SOC0 转换彻底结束后，触发触发 ADC 内部中断 1
  ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
  ```

### 3.2 `ADC_enableInterrupt` / `ADC_disableInterrupt`
* **功能详细描述**：
  负责使能或屏蔽指定的 ADC 内部中断脉冲向更上层的 PIE（外设中断扩展）控制器传递。在对触发源和脉冲模式配置完毕后，切记调用该函数开启中断通路的闸门，否则 CPU 永远不会跳转至对应的中断服务函数（ISR）。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `adcIntNum`: ADC 内部中断编号。
* **返回值**：无。

### 3.3 `ADC_getInterruptStatus` / `ADC_clearInterruptStatus`
* **功能详细描述**：
  * **获取状态**：实时读取指定 ADC 中断的当前挂起标志位。在无中断轮询（Polling）的设计架构中，程序需要在一个 `while` 循环中死等该标志位变高，以此判定转换是否结束并可以安全地读取结果寄存器。
  * **清除状态**：手动清除已挂起的中断标志位。**特别注意**：在中断服务子程序 (ISR) 执行结束前，必须调用清除函数将对应的标志位归零。如果漏除了此操作，ADC 硬件状态机会认为上一次转换处理尚未完结，从而彻底拦截后续的同源中断脉冲，最终导致系统“卡死”或周期性丢失采样。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `adcIntNum`: ADC 内部中断编号。
* **返回值**：获取状态函数返回 `bool`（已触发返回 `true`），清除函数无返回值。
* **示例代码**：
  ```c
  __interrupt void adca1_isr(void) {
      // (在此处读取并处理最新的 ADC 结果)
      
      // 必须清除 ADC 模块本身的中断挂起标志位
      ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
      // 同时需要清除顶层 PIE 系统的应答标志，放行同组中断
      Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
  }
  ```

### 3.4 `ADC_getInterruptOverflowStatus` / `ADC_clearInterruptOverflowStatus`
* **功能详细描述**：
  如果前一次转换引发的中断标志位因为 CPU 正在处理其他高优先级任务而没有及时得到清除（积压状态），在此期间硬件又产生了第二次同源的中断触发事件，硬件则会自动置位一个溢出标志。此对函数即用于诊断或清除溢出状态。在对时序极度敏感的电机或变频控制系统中，检测到溢出通常意味着控制环路计算严重超时，需引起警惕并处理。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `adcIntNum`: ADC 内部中断编号。
* **返回值**：获取函数返回 `bool`（发生溢出返回 `true`），清除函数无返回值。

### 3.5 `ADC_setInterruptPulseMode`
* **功能详细描述**：
  由于转换数字量这一步骤也需要消耗时钟周期，该函数赋予了开发者控制 ADC 中断信号发送精确时刻的能力。若配置为“采样窗口结束时”，当采样电容刚刚切断与引脚连通开始内部逼近转换时，中断信号便提前发出，这允许 CPU 利用这段空隙提前保存现场或执行前置计算；如果配置为“转换完全结束时”，则中断发出时结果必定已就绪并存在了寄存器中。通用场合下建议配置为转换结束后。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `pulseMode`: 脉冲生成模式，`ADC_PULSE_END_OF_ACQ_WIN`（采样窗结束）或 `ADC_PULSE_END_OF_CONV`（整个转换阶段结束）。
* **返回值**：无。

### 3.6 `ADC_setInterruptSOCTrigger`
* **功能详细描述**：
  配置 ADC 发生中断时内部发出的脉冲去硬件触发另一个指定的 SOC 进行采样。通过这种内部交叉触发的特性，可以实现“级联链式采样”。例如，硬件先启动 SOC0，在 SOC0 中断产生后再链式触发 SOC1 与 SOC2，形成对时间敏感的时序采集方案。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `socNumber`: 需要被后续触发的 SOC 编号。
  * `trigger`: 用于触发该 SOC 的本模块内部中断源。
* **返回值**：无。

### 3.7 `ADC_setInterruptCycleOffset`
* **功能详细描述**：
  只有在采用“采样窗口提前结束模式”产生中断时此功能才有效。它允许开发者设定一段系统时钟周期的延迟偏移量。合理校准这个周期偏移，能刚好使得 CPU 完成现场进栈动作，准备好读取寄存器时，数字量转换亦同刻完成。这种极其精细的时序微调能够有效降低控制代码的总等待开销。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `cycleOffset`: 延迟的系统时钟周期数。
* **返回值**：无。

### 3.8 `ADC_enableContinuousMode` / `ADC_disableContinuousMode`
* **功能详细描述**：
  使能或关闭 ADC 中断信号产生的连续发生模式。正常情况下，如果不手动清空中断标志，后续的转换事件将不再发出中断脉冲给 PIE 控制器；一旦使能了连续模式，不管标志位是否被清零，每当发生 EOC 转换结束事件，ADC 硬件必定会向外强行发送一次脉冲请求。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `adcIntNum`: ADC 内部中断编号。
* **返回值**：无。

---

## 4. 突发模式 (Burst Mode)

### 4.1 `ADC_setBurstModeConfig`
* **功能详细描述**：
  配置 ADC 突发硬件模式的工作参数。在常规使用中一个触发信号仅能启动一个关联的 SOC，但在使能了突发模式的环境下，接收到一个特定触发信号后，ADC 会自动地接连强行启动一连串的多次转换过程（称为Burst）。该函数定义了启动整个 Burst 的源，以及单次爆发需要执行的转换连续次数。这对于需要做高频快速数字滤波降噪的场景非常有用。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `trigger`: 触发发起突发采样的源头事件。
  * `burstSize`: 一次触发连续转换的次数（取值范围：1~16 次）。
* **返回值**：无。

### 4.2 `ADC_enableBurstMode` / `ADC_disableBurstMode`
* **功能详细描述**：
  正式激活或禁用 ADC 的突发模式调度器。开启该模式后，原有的常规 SOC 轮询和优先级机制的排队策略将被该模式彻底接管并改变。
* **参数**：
  * `base`: ADC 模块的基地址。
* **返回值**：无。

---

## 5. 结果读取

### 5.1 `ADC_readResult`
* **功能详细描述**：
  完成采样之后，从相对应的结果存放寄存器中直接提取出纯数字量数据。此函数通常是在 ADC 的回调 ISR 或者轮询探测的尾端调用，其返回值未经任何格式化加工，完全映射了外加电位与基准电压之间的线性数字量比例。
* **参数**：
  * `resultBase`: ADC 专属的独立结果寄存器存储基地址（**注意**：切勿混淆传入 `ADCA_BASE`等控制基址，必须传入形如 `ADCARESULT_BASE` 的专用地址空间）。
  * `socNumber`: 需要读取对应通道转换结果的 SOC 编号。
* **返回值**：`uint32_t`，获取到的 ADC 采样所产生的原始数字量（具体值为无符号型，12位模式下跨度为 `0~4095`，16位模式下跨度为 `0~65535`）。
* **示例代码**：
  ```c
  uint16_t adcData;
  // 从 ADCA 的结果存储区，攫取关联 SOC0 最新的采样数值
  adcData = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
  ```

---

## 6. PPB (后处理块) 配置 (高级功能)

芯片为每个 ADC 集成了至多 4 个独立运作于主频之下的后处理运算块 (Post-Processing Block, PPB)，旨在利用硬件代替 CPU 进行常态化的零偏扣除、极性反转及越限保护，实现零时钟开销。

### 6.1 `ADC_setupPPB`
* **功能详细描述**：
  通过该接口将某一处于空闲状态的 PPB 运算通道，静态“挂靠”绑定到一个具体的采样源 SOC 上。一旦该 SOC 完成采样转换，并产生原始数据后，对应的 PPB 硬件加速模块将在后台自动接管并对原数据流进行加工，而完全不侵占 CPU 取指周期。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: 欲分配的硬件 PPB 编号（`ADC_PPB_NUMBER1` ~ `ADC_PPB_NUMBER4`）。
  * `socNumber`: 与之深度绑定的原始信号采集的 SOC 通道号。
* **返回值**：无。
* **示例代码**：
  ```c
  // 分配 PPB1 硬件来托管处理 SOC0 的数字结果流
  ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
  ```

### 6.2 `ADC_setPPBCalibrationOffset` / `ADC_setPPBReferenceOffset`
* **功能详细描述**：
  赋予指定 PPB 一定的静态数字偏置量，以便于硬件从采集的原始数字量中作减法运算。
  * **标定偏移（Calibration Offset）** 常被用于抵消系统运放或传感器自身固有的恒定零点静态漂移，或者常用于交流采样（如互感器输出以 1.65V 中点作为零轴），减去中点偏置后直接获取带正负的真实幅值。
  * **参考偏移（Reference Offset）** 用法相似，更常被灵活配置用于系统在运行过程中依据动态参考点求取数据的相对差值。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
  * `offset`: 填入硬件减法器的带符号数字偏移量（有效应用范畴通常在 -4096 至 4095 间）。
* **返回值**：无。

### 6.3 `ADC_enablePPBTwosComplement` / `ADC_disablePPBTwosComplement`
* **功能详细描述**：
  配合减法偏置操作。当 ADC 读出的原始无符号数据减去了设定的偏移量后变为了负数值，若使能了此处的二进制补码模式，PPB 硬件最后输出的数据将自动按标准的计算机带符号整型补码（Two's Complement）体系编码。这项特性非常契合于各类以交变有符号数作为输入源的 DSP 数字滤波运算库（如 FFT、IIR等）。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
* **返回值**：无。

### 6.4 `ADC_readPPBResult`
* **功能详细描述**：
  相比于直接调阅 `ADC_readResult`，此函数用于专门获取经过 PPB 处理链条（包括相减校正、符号扩位）加工过后的最终数据结果。
* **参数**：
  * `resultBase`: ADC 结果寄存器区基址（如 `ADCARESULT_BASE`）。
  * `ppbNumber`: 已配置好的 PPB 编号。
* **返回值**：`int32_t`，返回最终带符号并可能已被扩展加工后的整型数据。

### 6.5 `ADC_setPPBTripLimits`
* **功能详细描述**：
  配置并装载内部 PPB 的硬件限幅跳闸比较器参数。给它设定一个过压极限高值（Trip Hi）和一个欠压极限低值（Trip Lo）。一旦 PPB 计算出来的结果跨越了这两个边界任意其一，比较器均会瞬间判定并生成越限警报信号，这可以不借助于代码即时去切断 PWM 发波，是确保电源与变频控制安然运行的关键核心级保护策略。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
  * `tripHiLimit`: 过压高限位数值。
  * `tripLoLimit`: 欠压低限位数值。
* **返回值**：无。

### 6.6 `ADC_enablePPBEvent` / `ADC_disablePPBEvent`
* **功能详细描述**：
  单独放行或者屏蔽 PPB 所能捕捉到的特殊异常比较事件，包括超出高设限（Trip Hi）、低于低设限（Trip Lo）以及当减法差值为0时所发出的过零事件（Zero Crossing）。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
  * `evtFlags`: 相应的事件类型标志位掩码合集（包含 `ADC_EVT_TRIPHI`, `ADC_EVT_TRIPLO`, `ADC_EVT_ZERO`）。
* **返回值**：无。

### 6.7 `ADC_enablePPBEventInterrupt` / `ADC_disablePPBEventInterrupt`
* **功能详细描述**：
  控制 PPB 特殊比较事件除了联动 PWM 外，是否同步触发 CPU 进入中断报警状态。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
  * `intFlags`: 配置允许引起中断请求的事件标志位掩码。
* **返回值**：无。

### 6.8 `ADC_getPPBEventStatus` / `ADC_clearPPBEventStatus`
* **功能详细描述**：
  读取或清除在运行过程中 PPB 所检测到的实际异常事件标志（如是否真的发生了过压）。在进入与 PPB 相关的保护中断服务函数或轮询恢复机制时，必须显式调用清除函数清零报警事件标志，否则模块不能接受新的事件比较更新。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
  * `evtFlags`（仅清除函数存在）: 需要被清零处理的事件标志位组合。
* **返回值**：获取状态时将返回 `uint32_t` 类型的挂起事件映射集，清除时无返回。

### 6.9 `ADC_enablePPBEventCBCClear` / `ADC_disablePPBEventCBCClear`
* **功能详细描述**：
  是否支持通过 EPWM 模块提供的周期级（Cycle-by-Cycle, CBC）清除脉冲来自动复位 PPB 的越限报警状态。这一高级同步机制被广泛应用在逐周期峰值电流限制控制领域（硬件自动封波并在下一 PWM 周期自动恢复，形成稳定的过流调制带）。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: PPB 编号。
* **返回值**：无。

### 6.10 `ADC_getPPBDelayTimeStamp`
* **功能详细描述**：
  读取该次采样操作经历在硬件序列池中排队，从对应 SOC 通道被下发触发信号时开始计数，直至其真切地开始捕捉模拟数据时中间所跨越的时间戳刻度值。借助该项诊断数据，研发人员能够准确量化推演出当多任务并行采样请求扎堆时由于通道“抢占排队”现象导致的纯硬件延时耗散，以作环路相位补偿的修正依据。
* **参数**：
  * `base`: ADC 模块的基地址。
  * `ppbNumber`: 绑定的 PPB 编号。
* **返回值**：`uint32_t`，返回被推迟的系统时钟周期计数总额。

---

## 7. 校准与内置温度传感器

### 7.1 `ADC_setOffsetTrim` & `ADC_setINLTrim`
* **功能详细描述**：
  出厂时，芯片制造厂商会将每一颗芯片独特的、在严格环境下测得的零点漂移偏移量（Offset）和积分非线性误差（INL）的补正数据烧结于一次性可编程区域（OTP ROM）内。当开发板卡或目标板经历上电冷启动对 ADC 进行配置调优时，务必调用这两条接口函数将内置矫正参数直接装载推入核心电路寄存器阵列内。唯有正确运行，方能确保芯片达到电气标称特性的终极采样高保真度。
* **参数**：
  * `base`: ADC 模块的基地址。
* **返回值**：无。

### 7.2 `ADC_getTemperatureC` / `ADC_getTemperatureK`
* **功能详细描述**：
  芯片自身在硅晶圆级层面刻印有一枚高精密的温度监控传感器引出，并被绑定到 ADC 的内部通道中。该类函数将 ADC 从温度通道拿到的裸数值（Raw ADC code）经过驱动库内蕴含该批次特征斜率与恒偏参数的多项式代数解算，直接输出转换成物理直观的摄氏度数据（°C）或开尔文绝对温度数据（K）。常作为板级监控，过热降载算法的数据给料点。
* **参数**：
  * `tempResult`: 取自内部温度测量专用 ADC 采样通道中的裸转换量。
  * `vref`: 当下系统供给 ADC 的真实外部参考基准基准电压标称。
* **返回值**：`int16_t`，以十六位有符号整数量化计算后得到的直接物理温度值。

---

## 8. ASYSCTL (模拟子系统控制) 模块

ASYSCTL (Analog System Control) 模块用于集中管理和配置芯片片上模拟相关的基础设施。该模块的控制范围涵盖了芯片内的高精度温度传感器、DAC 和 ADC 共享的模拟参考电压网络 (ANAREF)、片上 DC-DC 转换器、电源电压监控系统 (VMON) 以及模拟比较器模块 (CMPSS) 复杂的信号引脚复用网络配置。对该模块的合理配置，是保障整个芯片各类模拟外设精度、能效与安全的前置条件。

### 8.1 内部温度传感器配置

#### `ASysCtl_enableTemperatureSensor` / `ASysCtl_disableTemperatureSensor`
* **功能详细描述**：
  芯片在硅片级别集成了一个温度传感器，供用户监测芯片内核的实时发热情况。默认情况下，由于测温电路是一直工作的纯模拟组件，为了降低芯片的基础功耗是被关闭的。在用户希望利用 ADC 某个特定的测温通道来对系统热工况采样之前，必须调用使能函数对内部测温电路进行上电。反之，当不需要持续监控时可以关闭以节能。
* **参数**：无。
* **返回值**：无。
* **示例代码**：
  ```c
  // 开启片上模拟温度传感器电路，随后可配置 ADC 通道采压换算
  ASysCtl_enableTemperatureSensor();
  ```

### 8.2 模拟基准电压控制 (ANAREF)

该部分主要用于统筹配置 ADC、DAC 与比较器基准所使用的宏观参考电压网。由于多个外设可以共享参考网络，利用 ASYSCTL 可将芯片引脚 VREFHI/VREFLO 的来源配置为内部产生或者由外设输入。

#### `ASysCtl_setAnalogReferenceInternal` / `ASysCtl_setAnalogReferenceExternal`
* **功能详细描述**：
  明确指定指定的模拟模块（例如 ADCA, ADCB, ADCC 或全选）它们所依仗的基准源流向。
  * **Internal**：让目标 ADC 模块断开与外部引脚基准源的物理连接，切换到芯片内置自产的高精带隙基准源。此模式下，相应 VREFHI 引脚不能外接强驱动电压，建议外挂储能滤波电容即可。
  * **External**：要求指定的 ADC 模块绕过内置网络，强制使用由外部 VREFHI 引脚灌入的电源系统作为基准。
* **参数**：
  * `reference`: 需要进行配置的目标模块掩码（例如 `ASYSCTL_VREFHIA`, `ASYSCTL_VREFHIB` 等，可以进行位或运算以便一次性切换多个 ADC 核心的参考流向）。
* **返回值**：无。

#### `ASysCtl_setAnalogReference2P5` / `ASysCtl_setAnalogReference1P65`
* **功能详细描述**：
  在确认使用**内部参考模式**的情况下，设置内部带隙基准输出的具体幅值。
  * **2P5**：将所选模块的内部参考电压精确调节为 2.5V。
  * **1P65**：调低内部参考源满量程输出，配置为 1.65V。
  *(注：该芯片部分变种型号还支持 3.3V 配置，此时请参照 `ASysCtl_setAnalogReferenceVol` API)*
* **参数**：
  * `reference`: 配置的目标模块掩码。
* **返回值**：无。

#### `ASysCtl_setAnalogReferenceVol`
* **功能详细描述**：
  一个更高阶抽象的枚举配置函数。用于在已知使用内部参考时，一步将所选模块网络设定至具体的额定电压阈值（如 2.5V 或 3.3V）。推荐日常代码使用此现代接口，以增强跨型号可移植性。
* **参数**：
  * `reference`: 需应用该设置的模块位掩码合集。
  * `vol`: 目标内置满量程电压值（如 `ASYSCTL_VREFHI_2P5V` 或 `ASYSCTL_VREFHI_3P3V`）。
* **返回值**：无。
* **示例代码**：
  ```c
  // 将 ADCA 和 ADCB 这两个模块的参考网络，切换为内部自产，并校准在 3.3V 挡位
  ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIA | ASYSCTL_VREFHIB);
  ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIA | ASYSCTL_VREFHIB, ASYSCTL_VREFHI_3P3V);
  ```

### 8.3 内部高效率 DC-DC 转换器控制

这颗芯片包含一个内置的高效率同步降压 DC-DC 转换模块，可以完全替代传统的内部线性稳压器（LDO）为1.2V数字内核供电，大幅度改善系统满载运行时（特别是在高频100MHz+及双核系统）的整机发热情况与静态能效。

#### `ASysCtl_enableDCDC` / `ASysCtl_disableDCDC`
* **功能详细描述**：
  开启或关闭此内嵌的 DC-DC 控制器。在使能 DC-DC 之前，硬件上对应的引脚必须已连接好所需的外部储能电感和滤波电容阵列。使能函数内部存在一个硬件状态轮询死循环，该循环会不断检视 DC-DC 切换到位的序列状态（Switch Sequence Status）和电感是否探测到短路等硬件异常。如果硬件配置正确，DC-DC 成功接管内核供电，函数会返回 true，芯片随即开始进入低发热工作状态。一旦发生硬件失效或电感脱落报警，芯片将自动跌落回 LDO 供电以求自保，并在此函数返回 false 报错。
* **参数**：无。
* **返回值**：`bool`，若 DC-DC 使能握手成功且工作正常，返回 `true`；若自检失败（电感异常等），拒绝切入并返回 `false`。
* **示例代码**：
  ```c
  // 尝试接管内部供电控制权，若外围电感焊装无误则启用高效开关降压
  if (!ASysCtl_enableDCDC()) {
      // 若硬件报警，可以执行向控制台输出错误，或置位标志让 LDO 继续勉力支撑
      ESTOP0; 
  }
  ```

#### `ASysCtl_getInductorFaultStatus` / `ASysCtl_getSwitchSequenceStatus`
* **功能详细描述**：
  用于底层诊断与追踪。前者反馈电感环路是否有检测到由于过流或断路引发的硬件级异常故障位；后者反馈 DC-DC 在进行上电稳压切入交接过程中的内部状态机进度，供更复杂的自研电源管理代码做状态监察。
* **返回值**：`bool`。返回对应的状态标志是否置位。

### 8.4 CMPSS 模拟比较器多路复用网络 (MUX) 路由配置

CMPSS 模块拥有一套极其复杂的信号路由分配网络。由于芯片引脚资源有限，多个 CMPSS 实例的正极输入（HPMX/LPMX）和负极输入（HNMX/LNMX）在实际分配引脚时是可以动态切分的。

#### `ASysCtl_selectCMPHPMux` / `ASysCtl_selectCMPLPMux`
* **功能详细描述**：
  针对比较器的高阈值模块(High CMP)与低阈值模块(Low CMP)的**正极（Positive）端**，选择实际连接到底层硬件多路选择器 (Mux) 中的哪个输入源。利用这个开关矩阵，例如，你可以把一个物理引脚模拟量并行扇出到多个不同比较器的正极，从而在不同的跳闸阈值面上执行多次判断。
* **参数**：
  * `select`: 选择对应的那个开关节点（例如 `ASYSCTL_CMPHPMUX_SELECT_1` 代表对开关节点 1 的正极管脚复用）。
  * `value`: 输入路由线的值索引（通常取值 0~4 选择不同的外部引脚通道，若取值为 7，则该输入端被挂起至内部高阻态 (Hi-Z)，相当于该端点悬空不接）。
* **返回值**：无。

#### `ASysCtl_selectCMPHNMux` / `ASysCtl_selectCMPLNMux` 及其扩展 `...Value`
* **功能详细描述**：
  这两组函数用于路由高阈值/低阈值比较器的**反相输入负极（Negative）端**信号来源。芯片内比较器的负极极其灵活，既可以直接接入外部引脚去同正极比较绝对压差；也可以内部直连片上的微型 DAC，用代码生成的数字量去和正极做动态跳闸比较。
  * 简易版 (`selectCMPHNMux`)：参数直接传内部掩码宏定义执行快切。
  * 值控版 (`selectCMPHNMuxValue`)：对特定的选择节点 (`select` 参数)，赋以具体的复用通道索引值 (`value`)。
* **返回值**：无。

### 8.5 ASYSCTL 寄存器写保护安全锁

考虑到 ASYSCTL 掌管了整个模拟电路核心生死相关的基准配置及高风险的电源交接开关控制，如果程序跑飞或者数组越界不慎篡改这些参数，轻则采压大乱，重则系统烧毁断电。因此，库提供了一套只能锁死、一旦锁住复位前不得再行解锁的只写单向安全闭锁功能。

#### `ASysCtl_lockTemperatureSensor` / `ASysCtl_lockANAREF` / `ASysCtl_lockVMON` / `ASysCtl_lockDCDC` / 等
* **功能详细描述**：
  上述一整套前缀为 `ASysCtl_lock...` 的功能接口被设计来锁定特定模拟子块控制寄存器的可写权限。
  在系统加电、初始化、分配好参考基准和 MUX 路由之后，强烈建议系统主程序立刻调用相关的锁定函数。调用后，对应的寄存器会被硬件写保护死锁。直至下一次硬件看门狗复位或断电冷启动来临前，CPU 乃至调试器仿真都将**永久失去**对此区域的再次修改能力。这是对于严苛车规/工控功能安全极为关键的防护屏障。
* **返回值**：无。
* **示例代码**：
  ```c
  // 初始化阶段完毕，为防止后续程序飞跑窜改引线连接，把比较器 MUX 路由配置硬件锁死。
  ASysCtl_lockCMPHPMux();
  ASysCtl_lockCMPLPMux();
  ```

---

## 9. CAN / CAN-FD (控制器局域网络) 模块

本模块提供对 CAN 以及更高波特率的 CAN-FD 控制器进行全方位控制的驱动接口。主要功能涵盖：工作模式与波特率的初始化、经典与灵活数据速率（FD）双标准的切换、基于 ID 掩码的硬件验收滤波、发送/接收缓冲区的调度管理以及中断与故障状态机的监控。该 CAN 外设高度独立，能够自主完成 CRC 校验、自动重发和帧组装，极大减轻 CPU 负担。

### 9.1 初始化与波特率配置

#### `CAN_initModule` / `CAN_structInit` / `CANFD_structInit`
* **功能详细描述**：
  这组函数用于在系统启动时对 CAN 核心模块进行底层的复位与初始化。
  `CAN_structInit` 与 `CANFD_structInit` 被用来给用户声明的配置结构体赋上安全的默认值，防止由于未初始化的野指针或乱码引发不可预知的故障。
  `CAN_initModule` 是正式的生效函数，它接受已经配置好的结构体参数，执行对控制器的软复位，将收发引脚与内部时钟对接，并建立最初的通信时序。在调用此函数期间，CAN 控制器会自动进入配置模式。
* **参数**：
  * `base`: CAN 模块的基地址（例如 `CANA_BASE`）。
  * `ptrCanInit` / `ptrCanFd`: 指向初始化配置结构体的指针。
* **返回值**：无。
* **示例代码**：
  ```c
  CAN_Init_Config canCfg;
  CAN_structInit(&canCfg);       // 赋默认值
  canCfg.mode = CAN_NORMAL_MODE; // 修改为正常工作模式
  CAN_initModule(CANA_BASE, &canCfg);
  ```

#### `CAN_setBitRateSlow` / `CANFD_setBitRateFast`
* **功能详细描述**：
  * `Slow` 对应经典的 CAN 2.0 波特率配置（仲裁段时序）。它根据输入的主频，自动为您计算和分配预分频器（BRP）、传播段、相位缓冲段（TSEG1/TSEG2）以及同步跳转宽度（SJW），以尽力逼近您设定的目标波特率。
  * `Fast` 则专用于 CAN-FD 模式下的数据段（Data Phase）高速波特率配置。在 FD 帧中，ID 仲裁阶段仍使用 Slow 速率，而在数据阶段自动拉高至 Fast 速率以缩短总线占用时间。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `clock`: 供给 CAN 模块的外设时钟频率（以 Hz 为单位）。
  * `bitRate`: 期望设定的波特率（以 bps 为单位，如 `500000` 即 500kbps）。
* **返回值**：无。

#### `CAN_setWorkMode`
* **功能详细描述**：
  控制 CAN 外设参与总线活动的方式。常见的模式包括正常模式（Normal，允许双向收发）、仅监听模式（Listen Only，只接收不发送，甚至不发送 ACK 应答位，常用于抓包工具防干扰）、自测回环模式（Loopback，将 Tx 内部短接到 Rx 以供软件自行诊断硬件逻辑是否完好）。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `workMode`: 工作模式枚举。
* **返回值**：无。

#### `CANFD_config`
* **功能详细描述**：
  对于支持 CAN-FD 协议的控制器，此函数用于专门开启并详细配置 FD 特性。包括是否允许在总线上发送具备可变波特率（BRS）的加长帧（最高 64 字节），以及设定 TDC（发送机延迟补偿）参数，这在进行 2Mbps 以上的高速通讯时，用于解决导线物理传播延迟导致的内部采样错位问题。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `ptrCanFd`: 包含 FD 专属配置项的结构体指针。
* **返回值**：无。

### 9.2 报文发送管理

#### `CAN_fillMessage` / `CAN_fillRemoteRequestMessage`
* **功能详细描述**：
  准备一帧需要发送出去的数据包。CAN 硬件通常具备主发送缓冲区（PTB）和次级发送缓冲区（STB）。此函数用于将用户定义的 11位（标准）或 29位（扩展）ID 标识符、数据长度代码（DLC）以及实际的报文负载数据（Payload）打包写入到指定的硬件发送缓冲插槽内。`RemoteRequestMessage` 版本用于发出不带实际数据但请求其他节点回复数据的远程帧（RTR）。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `txBufType`: 目标发送缓冲区槽位（例如主缓冲或次级缓冲区）。
  * `msgID`: 报文的唯一标识符 ID。
  * `ptrTBUFCtrl`: 控制帧结构的参数（如帧类型、DLC 长度等）。
  * `msgData`: 存放将要被发出数据的内存指针。
* **返回值**：无。

#### `CAN_startTx`
* **功能详细描述**：
  命令 CAN 控制器立刻将先前利用 `fillMessage` 填入缓冲区的报文排队并发往物理总线。硬件会自动执行空闲总线侦听并在取得仲裁后送出。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `txRequest`: 欲激活的发送缓冲区标识。
* **返回值**：无。
* **示例代码**：
  ```c
  // 将数据打包装填进发送次级缓冲 (STB)
  CAN_fillMessage(CANA_BASE, CAN_TX_BUF_STB, 0x123, &tbufCtrl, txData);
  // 扣动扳机，启动硬件发送
  CAN_startTx(CANA_BASE, CAN_TX_REQ_STB);
  ```

#### `CAN_abortTx` / `CAN_isTransmitterBusy` / `CAN_getTxBufStatus`
* **功能详细描述**：
  提供对发送过程的管理。若发出的报文因总线持续被更高优先级 ID 占用而迟迟发不出去，可使用 `abortTx` 强行终止排队以换发其他紧急报文。`isTransmitterBusy` 和 `getTxBufStatus` 则常用于发送前的探查，以防止缓冲区覆写。
* **返回值**：对应状态位或布尔值。

### 9.3 验收滤波与报文接收

#### `CAN_setAcceptFilter` / `CAN_filterCmd`
* **功能详细描述**：
  CAN 协议的灵魂在于其广播特性，即所有节点都能听到总线上的信号。为了让 CPU 免受无关海量报文的中断骚扰，验收滤波器（ACF）应运而生。`CAN_setAcceptFilter` 可配置一组硬件筛网（掩码与目标 ID）。只有在总线上通过了掩码比对的特定 ID 报文，硬件才会将它装入接收 FIFO。`CAN_filterCmd` 则用于单独开启或关闭某一号筛网。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `acfSelect`: 欲配置的滤波器硬件编号（通常有十几组）。
  * `ptrAcf`: 包含了掩码逻辑、目标 ID、匹配模式（仅标准 / 仅扩展 / 两者皆可）的结构体。
* **返回值**：无。

#### `CAN_readMessage` / `CAN_readMessageWithID`
* **功能详细描述**：
  当接收缓冲区收到通过了滤波器的新报文后，用于从深层硬件 FIFO 中将其取出。
  `readMessage` 是简易版，只提取有效载荷数据。
  `readMessageWithID` 是完整版，除了数据，它还会将该帧的源 ID 标识符以及帧结构信息（实际收取的数据长度 DLC，是否为远程帧等）一并提取，这对于应对接收多种不同 ID 报文共用同一缓冲区的设计非常关键。
* **返回值**：`bool`。若缓冲区确实有新数据并成功读出，返回 `true`。若为空读取，返回 `false`。
* **示例代码**：
  ```c
  uint32_t rxId;
  CAN_RBUF_Ctrl rxCtrl;
  uint8_t rxData[8];
  
  // 尝试从硬件提取一帧完整接收报文
  if (CAN_readMessageWithID(CANA_BASE, &rxId, &rxCtrl, rxData)) {
      // 成功，依照 rxId 对 rxData 进行协议解析
  }
  ```

### 9.4 状态机与中断控制

#### `CAN_enableInterrupt` / `CAN_disableInterrupt`
* **功能详细描述**：
  除了常规的接收和发送完成中断，CAN 硬件还提供了种类繁多的总线级诊断中断，如总线错误越限报警、总线脱离（Bus-Off）、接收缓冲溢出覆盖报警等。用户可组合这些枚举选项，开启通往内核的中断线，以便在系统出状况的瞬间能用极短的代码作出应对防宕机。
* **参数**：
  * `base`: CAN 模块的基地址。
  * `ints`: 中断类型掩码宏，可位或组合（例如 `CAN_INT_RX_BUF_FULL | CAN_INT_BUS_OFF` 等）。
* **返回值**：无。

#### `CAN_getStatus` / `CAN_clearInterruptStatus`
* **功能详细描述**：
  读取当前的综合状态或中断触发标志。并在 ISR 的末尾使用 `clearInterruptStatus` 确认并清除已发生的中断请求。
* **返回值**：特定状态的置位情况。

#### `CAN_getErrorInfo` / `CAN_setErrorWarnLimit`
* **功能详细描述**：
  CAN 协议自带极其坚固的硬件错误计分与隔离惩罚机制。当节点在收发过程中检测到干扰导致 CRC 或格式出错时，硬件内的 TEC (发送错误计数) 或 REC (接收错误计数) 会自动步进。`CAN_getErrorInfo` 允许 CPU 实时将这些底层计分板的数值抽查出来，从而提前对极有可能即将发生的总线崩溃进行预警干预。`setErrorWarnLimit` 则是人为地调整硬件发出第一级轻度警报阈值的敏感度。
* **返回值**：`getErrorInfo` 会将详细计数填入入参结构体，并返回是否已跨越危险线。


---

## 10. CMPSS (比较器子系统) 模块

比较器子系统（Comparator Subsystem）是芯片上用于模拟信号高速阈值监控和保护的核心模块。每个 CMPSS 模块内部均包含两个独立的高速比较器（High 和 Low）、两组由 12位参考微型 DAC 提供的可编程阈值发生器、数字防抖滤波器，以及支持斜坡补偿的斜坡发生器。CMPSS 主要用于电机控制或数字电源中的**峰值电流控制 (PCMC)**、过流短路极速保护，并能将跳闸信号无缝直接传递给 EPWM 实施关波。

### 10.1 基础模块使能与启停

#### `CMPSS_enableModule` / `CMPSS_disableModule`
* **功能详细描述**：
  打开或关闭整个 CMPSS 模块的运行时钟和内部模拟供电。在使用该模块任何功能之前必须先调用使能函数。为了保证精度，开启模块后，建议在比较器建立稳定工作点前加入短延时后再将其输出并入 EPWM 封波网络。
* **参数**：
  * `base`: CMPSS 模块的基地址（如 `CMPSS1_BASE`）。
* **返回值**：无。

### 10.2 比较器配置与 DAC 阈值设定

#### `CMPSS_configHighComparator` / `CMPSS_configLowComparator`
* **功能详细描述**：
  对高 / 低侧比较器的反相输入（负极）来源进行配置。通常比较器的正极连接外部采集引脚（代表真实电流或电压反馈），而负极可配置为连接内部参考 DAC 提供静态判断阈值。此函数还可用来对比较器翻转极性进行逻辑反相。
* **参数**：
  * `base`: CMPSS 模块基址。
  * `config`: 比较器配置位掩码（如 `CMPSS_INSRC_DAC` 使用内部 DAC 作为负极，或 `CMPSS_INV_INVERTED` 对比较结果反相）。
* **返回值**：无。

#### `CMPSS_configDAC`
* **功能详细描述**：
  配置 CMPSS 模块内置的两路 12 位 DAC 的参考源和数值加载模式。DAC 主要用作给比较器提供对比"门限"。此函数可决定该门限是依据 `VDDA` 还是内部独立基准（如 `VDAC`），并且设定在何时更新 DAC 的阈值寄存器（如立即更新，或等待系统 PWM 同步信号（SYSCLK）来临时一齐更新，以避免在发波中途门限突变引发错误跳闸）。
* **参数**：
  * `base`: CMPSS 模块基址。
  * `config`: 位掩码组合配置（如 `CMPSS_DACREF_VDDA | CMPSS_DACVAL_SYSCLK | CMPSS_DACSRC_SHDW`）。
* **返回值**：无。

#### `CMPSS_setDACValueHigh` / `CMPSS_setDACValueLow`
* **功能详细描述**：
  为高/低比较器设定实际的 12 位数字比较跳闸阈值。
* **参数**：
  * `base`: CMPSS 模块基址。
  * `value`: DAC 设定的数值（范围 `0` ~ `4095`），数值将由内部 DAC 转化为模拟电平供比较器负极使用。
* **返回值**：无。
* **示例代码**：
  ```c
  // 将 CMPSS1 高侧比较器的跳闸门限定位量程的一半（通常对应某过流警戒线）
  CMPSS_setDACValueHigh(CMPSS1_BASE, 2048);
  ```

### 10.3 比较器信号滤波与输出控制

为了防止引脚端偶然的 EMI 杂波或者 MOSFET 开关时的密勒振铃造成比较器误翻转，CMPSS 为每个比较器输出端配备了一套数字消抖滤波器（Digital Filter）。

#### `CMPSS_configFilterHigh` / `CMPSS_configFilterLow`
* **功能详细描述**：
  配置高/低侧数字防抖滤波器参数。滤波器基于采样窗原理工作：在一个定义长度为 `samplePrescale` 的时间窗内，系统会连续采样多次，仅当采样结果中出现 `threshold` 次一致时，滤波器输出才会翻转。
* **参数**：
  * `base`: CMPSS 模块基址。
  * `samplePrescale`: 对系统时钟的预分频，决定采样的基础时间跨度。
  * `sampleWindow`: 采样的总窗口数量范围（最大 32）。
  * `threshold`: 判定翻转所需的有效票数门槛（必须大于 `sampleWindow/2`）。
* **返回值**：无。

#### `CMPSS_initFilterHigh` / `CMPSS_initFilterLow`
* **功能详细描述**：
  对高/低滤波器的内部采样 FIFO 与历史状态机进行软复位清零。在开始使用前或者更改滤波器参数后，应调用此函数以确保滤波器初始状态的干净。
* **返回值**：无。

#### `CMPSS_configOutputsHigh` / `CMPSS_configOutputsLow`
* **功能详细描述**：
  高度灵活的输出选择矩阵网络。此函数规定高/低比较器的结果信号到底走哪条路径离开 CMPSS。
  它不仅能决定送给 EPWM 去执行跳闸（Trip）的信号是使用比较器的**原始未经滤波直通信号（Asynch）** 还是经过了**滤波器的干净信号（Sync / Filtered）**；还能决定这路跳闸信号是否要在锁存器（Latch）中被硬件持久扣留，直到软件人为清零才松开。这在构建一次性彻底锁定（One-Shot）的灾难性过流保护中极为必要。
* **参数**：
  * `base`: CMPSS 模块基址。
  * `config`: 输出路由掩码，包含送往 CTRIPH（给 PWM 跳闸使用）及 CTRIPOUTH（给外部 GPIO 输出使用）的选择（例如 `CMPSS_TRIP_FILTER | CMPSS_TRIPOUT_LATCH`）。
* **返回值**：无。

### 10.4 状态读取与锁存复位

#### `CMPSS_getStatus`
* **功能详细描述**：
  直接读取 CMPSS 内部比较器阵列当前的状态快照，包括高侧/低侧比较器的实时翻转状态，以及其经过锁存器处理后的锁存状态。
* **返回值**：`uint16_t` 类型的标志位。

#### `CMPSS_clearFilterLatchHigh` / `CMPSS_clearFilterLatchLow`
* **功能详细描述**：
  当将比较器输出配置为“硬件锁存（Latch）”模式后，一旦比较器发现过压过流，即使随后的电平由于 PWM 被封锁而迅速恢复到安全阈值以下，向外发出的跳闸信号仍旧会被锁死保持，致使后续的系统无法重开 PWM。此函数用于在软件中断检查无误、确认安全后，人为手动将这个死锁释放，恢复运行。
* **返回值**：无。
* **示例代码**：
  ```c
  // 确认短路隐患排除后，复位 CMPSS1 比较器高侧的硬件触发锁存
  CMPSS_clearFilterLatchHigh(CMPSS1_BASE);
  ```

#### `CMPSS_configLatchOnPWMSYNC`
* **功能详细描述**：
  配合数字电源里非常常用的“逐周期限流（CBC, Cycle-By-Cycle）”控制。如果让 CPU 每一个 PWM 周期都进入中断去执行上面提到的手动复位，开销将极其巨大且不可靠。本函数允许让锁存器的复位引脚自动挂钩到本地的 EPWM_SYNC 信号。只要这个周期内发生过流，立刻跳闸截断波形；当下一个 PWM 周期零点带来 SYNC 同步脉冲时，硬件将**全自动**清空该锁存信号，开启全新的周期试探。
* **返回值**：无。

### 10.5 峰值电流斜坡补偿发生器 (Ramp Generator)

在峰值电流模式控制（PCMC）中，当占空比超过 50% 时极易诱发次谐波振荡。CMPSS 为此集成了一个全硬件自动运行的递减斜坡生成器，通过将其信号动态迭加在 DAC 阈值之上，可以完美执行斜坡补偿以稳定控制环路。

#### `CMPSS_configRamp`
* **功能详细描述**：
  一键初始化斜坡生成器的全套参数。包括这个斜坡开始时的初始顶点（最大值），以及每个时钟滴答下它自动往下削减的坡度阶梯量（Decrement），还有该斜坡从收到 PWM 同步信号后延迟多久才真正开始往下降。
* **参数**：
  * `base`: CMPSS 模块基址。
  * `maxRampVal`: 斜坡重置初始的最大点。
  * `decrementVal`: 每步递减幅度。
  * `delayVal`: 开始递减的滞后等待时间。
* **返回值**：无。
* **示例代码**：
  ```c
  // 配置 CMPSS1 的斜坡补偿。初始门限由 DAC 提供，斜坡以此为基点逐周下降
  CMPSS_configRamp(CMPSS1_BASE, 0xFFFF, 50, 10);
  ```

#### `CMPSS_setMaxRampValue` / `CMPSS_setRampDecValue` / `CMPSS_setRampDelayValue`
* **功能详细描述**：
  以上三个函数系 `configRamp` 的子集独立调用形式，允许在控制运行阶段动态修改斜坡方程的某个单独项而不影响其它。

### 10.6 开关消隐功能 (Blanking Window)

#### `CMPSS_configBlanking` / `CMPSS_enableBlanking` / `CMPSS_disableBlanking`
* **功能详细描述**：
  MOS 晶体管在强电感性负载下硬开关切断或导通的瞬间，物理母线上必定会出现几百纳秒的巨大电压/电流尖峰干扰。为了防止比较器将这种正常的开关尖刺误判为真实的过流（即便有低通滤波也不一定防得住），CMPSS 允许从 EPWM 引入一个**同步消隐窗口**。
  在被定义为“消隐（Blanking）”的时间片段内，CMPSS 会硬性“闭上眼睛”，强行屏蔽比较器输出端的任何翻转动作。只有待该窗口结束后，才会恢复灵敏的阈值监察。
* **参数**：
  * `pwmBlankSrc`: 选择究竟要拿芯片上多路 EPWM 中哪一路的消隐脉冲来作为自身“闭眼”时序的触发源。
* **返回值**：无。


---

## 11. CPUTIMER (CPU 内部定时器) 模块

本芯片包含 3 个通用的 32 位 CPU 定时器：CPUTIMER0、CPUTIMER1 和 CPUTIMER2。
其中 Timer 0 和 Timer 1 主要预留给用户的应用程序或实时的 RTOS (如 SYS/BIOS) 节拍使用；而 Timer 2 虽然同属通用定时器，但其内部时钟源挂接了更多的系统级外部输入引脚以及专用的低速时钟（如 INTOSC），常常被分配用于系统的安全看门狗备份或者精确的 DSP 算法性能执行时间（Profile）测量基准。

### 11.1 定时器基础配置

#### `CPUTimer_setPeriod`
* **功能详细描述**：
  为指定的 32 位 CPU 定时器配置其主周期的重载值（PRD）。CPU 定时器是一个递减计数器（向下计数）。当计数器从 `periodCount` 递减到 0 时，就会产生一个周期事件，随后硬件会自动将该值重新装载到当前计数器中，开始下一个周期的减法循环。
* **参数**：
  * `base`: 定时器的基地址（如 `CPUTIMER0_BASE`, `CPUTIMER1_BASE`, `CPUTIMER2_BASE`）。
  * `periodCount`: 32 位的周期加载值。
* **返回值**：无。

#### `CPUTimer_setPreScaler`
* **功能详细描述**：
  配置 CPU 定时器的时钟预分频倍数。由于这 3 个定时器主频挂接到 CPU 核心（即 SYSCLK，通常在百兆赫兹以上），如果需要长达几秒甚至几十秒的慢速定时，纯靠 32 位计数器仍不够用。此时可以通过预分频器（Prescaler）先将核心时钟降速，再喂给主计数器进行递减。
* **参数**：
  * `base`: 定时器基址。
  * `prescaler`: 16 位的时钟预分频因子。
* **返回值**：无。
* **示例代码**：
  ```c
  // 将 CPUTimer0 设定为每秒触发 1 次：
  // 假设 SYSCLK = 100MHz。如果 prescaler 设置为 100-1 (除以100)，即 1MHz 频率喂给主计数。
  // 那主计数只需再数 1000000 即可得到 1 秒延迟。
  CPUTimer_setPreScaler(CPUTIMER0_BASE, 99);
  CPUTimer_setPeriod(CPUTIMER0_BASE, 1000000);
  ```

#### `CPUTimer_selectClockSource`
* **功能详细描述**：
  **（注意：此功能仅限 `CPUTIMER2_BASE` 独有）**。
  普通的 Timer0/1 时钟源恒定为 SYSCLK。而 Timer2 则允许用户通过一个内部复用器，选择其心跳的真正来源。除了 SYSCLK，还能选择使用备用内部振荡器（INTOSC1/2）或甚至是从外部物理引脚捕捉进来的外部系统时钟信号（XTAL）。这种异构时钟源设计赋予了 Timer2 无与伦比的安全属性——当主 PLL 时钟因为强干扰或晶振停振而挂掉时，以独立 INTOSC 运行的 Timer2 可以不受影响地继续计时并触发安全急停中断。
* **参数**：
  * `base`: 必须传入 `CPUTIMER2_BASE`。
  * `source`: 选取时钟源节点，枚举类型（如 `CPUTIMER_CLOCK_SOURCE_SYS` 或者是 `CPUTIMER_CLOCK_SOURCE_INTOSC1` 等）。
  * `prescaler`: 二级时钟预分频。
* **返回值**：无。

### 11.2 启动、挂起与运行控制

#### `CPUTimer_startTimer` / `CPUTimer_stopTimer` / `CPUTimer_resumeTimer`
* **功能详细描述**：
  这一系列函数用于直接接管定时器的生命周期。
  * `stopTimer`：置位寄存器，让正在往下扣减的计数器**硬生生冻结（挂起）**，保留当前剩余的计数值。
  * `resumeTimer`：清零控制位，解冻处于挂起状态的计数器，它将从**上一次被冻结的余数**处接着往下跑。
  * `startTimer`：这是一个复合动作，不仅能清零控制位让定时器跑起来，更关键的是它带有“Reload（重载）”属性：即无论之前计到哪里，只要一调用 Start，它都会**强行将 `setPeriod` 里设置的初始峰值重新灌满**，从而开启一个崭新的完整计时周期。
* **返回值**：无。

#### `CPUTimer_reloadTimerCounter`
* **功能详细描述**：
  如果只想将周期值重新灌满到当前计数器中，而不改变其“运行/挂起”的动静态属性，可以单独调用这个纯硬件重载触发指令。

### 11.3 状态问询与中断应答

#### `CPUTimer_getTimerCount`
* **功能详细描述**：
  实时捕捉下主计数器当前正处于的值（倒计时余量）。非常适合用于对微小代码片段的精确性能测试：在要测试的代码前面读取一次 Count 存下，在代码执行结束后再读一次，两者相减得到的数值就是被测代码真实消耗的 CPU 机器周期数。
* **返回值**：`uint32_t`，当前倒数余量。

#### `CPUTimer_enableInterrupt` / `CPUTimer_disableInterrupt`
* **功能详细描述**：
  控制当这枚 32 位定时器一直扣减到 0 的那个瞬间，要不要向顶层的 PIE 乃至 CPU 扔出一个 TINT（Timer Interrupt）脉冲。在构建系统滴答心跳（Tick）时必须使能。
* **返回值**：无。

#### `CPUTimer_getTimerOverflowStatus`
* **功能详细描述**：
  询问定时器的计数是否发生过越界归零（Overflow）。即便用户关闭了中断信号发送，底层这个 TIF（Timer Interrupt Flag）硬件标志位在每次减到 0 时依然会被忠实地置位。因此，可以在纯裸机（无中断架构）系统里放到 `while` 里面用于轮询超时。
* **返回值**：`bool`，若已发生过归零溢出返回 `true`。

#### `CPUTimer_clearOverflowFlag`
* **功能详细描述**：
  这非常重要：**必须手动复位**！无论是响应了其产生的硬件中断，还是在软件死循环里探查到了溢出，一旦被确认，程序都必须立即呼叫该函数，向其特定的位写 '1' 以清除硬件记录的溢出历史。若遗漏这步，外设就丧失了发起下一次警报的能力。
* **返回值**：无。


---

## 12. DAC (数模转换器) 模块

DAC (Digital-to-Analog Converter) 模块用于将数字量转换为连续的模拟电压输出。它通常被用于为外部运算放大器提供可调偏移量基准，或者作为闭环控制系统中的斜坡生成器以及提供调试过程中内部变量的模拟示波器观测接口。

### 12.1 基础与参考配置

#### `DAC_setReferenceVoltage`
* **功能详细描述**：
  选择决定 DAC 输出满量程范围的电压参考源。这直接决定了你写入寄存器中的数字最大值（4095）所对应的物理输出电压极值。可以配置为使用内部的 VDDA (如 3.3V) 或者是芯片集成的专用高精度内部参考引脚的 VDAC 参考（通常为内部带隙 2.5V 或是通过 ASYSCTL 配置出的电压）。
* **参数**：
  * `base`: DAC 模块基地址（例如 `DACA_BASE`）。
  * `source`: 参考源枚举（`DAC_REF_VDDA` 或 `DAC_REF_VDAC`）。
* **返回值**：无。

#### `DAC_setGainMode`
* **功能详细描述**：
  设置 DAC 输出级的模拟增益倍数。你可以选择乘以 1 倍（原样输出）或者是乘以 2 倍输出。需注意，如果选择了 2 倍增益，物理输出依然不能超过芯片供电的绝对电压轨（VDDA），一旦超出会被自动削顶限幅。
* **参数**：
  * `base`: DAC 模块基址。
  * `mode`: 增益模式（`DAC_GAIN_ONE` 倍或 `DAC_GAIN_TWO` 倍）。
* **返回值**：无。

### 12.2 启动与赋值更新

#### `DAC_enableOutput` / `DAC_disableOutput`
* **功能详细描述**：
  开启或关闭 DAC 向对应物理引脚引出的缓冲输出。关闭时，引脚呈高阻态；开启时，内置的运算放大器缓冲器启动，将寄存器转出的电压以具备一定驱动能力的形式推送到外部引脚上。
* **返回值**：无。
* **示例代码**：
  ```c
  DAC_enableOutput(DACA_BASE);
  ```

#### `DAC_setLoadMode` / `DAC_setPWMSyncSignal`
* **功能详细描述**：
  规定 CPU 写给 DAC 数据缓冲区的数值，在何时真正被推入前端硬件转换电路。
  * `LoadMode` 可选为**系统时钟同步**（写入立即生效）或者是**特定 PWM 同步**（写入后暂时挂起，只有等到配对的 PWM 发出一个 SYNC 脉冲时，新数值才切入生效）。
  * 配合 `setPWMSyncSignal` 函数，你可以精准指定全芯片几十路 PWM 信号中的哪一路作为它的门控触发扳机。这在需要极力避免 DAC 输出在 PWM 导通关键时期发生台阶跳变的电源应用中十分重要。
* **返回值**：无。

#### `DAC_setShadowValue` / `DAC_getShadowValue` / `DAC_getActiveValue`
* **功能详细描述**：
  用于更新或读取 DAC 的 12 位（0~4095）数字值。
  `setShadowValue` 永远只操作阴影（Shadow）缓冲寄存器。至于这个阴影值何时能倒到前台（Active）成为真实的模拟量，全凭上述 `setLoadMode` 的配置。`getActiveValue` 则是去读取当前硬件正在使用的那份真实前台数据。
* **参数**：
  * `base`: DAC 模块基址。
  * `value`: 欲输出的 12 位设定值。
* **返回值**：`uint16_t` 类型的当前寄存器数字。
* **示例代码**：
  ```c
  // 如果选择了直接 Load，此语句执行完后，引脚电压即刻改变为满量程的一半
  DAC_setShadowValue(DACA_BASE, 2048);
  ```

### 12.3 校准微调保护

#### `DAC_tuneOffsetTrim` / `DAC_setOffsetTrim`
* **功能详细描述**：
  受制于生产工艺，运放输出必定存在细微的零点漂移。出厂前 TI 会在芯片内固化一个 OTP（一次性可编程）校正值。`tuneOffsetTrim` 用于根据当前用户供给的实际参考电压值，进行自动运算并调用 `setOffsetTrim`，往 DAC 微调补偿寄存器中打入一个修正偏置量，以保证即便输出电压在 0V 附近时也能保持极高的平滑度和准度。
* **返回值**：无。

#### `DAC_lockRegister`
* **功能详细描述**：
  安全锁定机制。保护 DAC 的控制权，例如防止恶意或跑飞的代码修改控制位、影子值寄存器或是输出缓冲使能位。一旦被锁死（写入特定位），直到系统进行全局硬复位之前，将不可再改写。
* **参数**：
  * `base`: DAC 模块基址。
  * `reg`: 具体的欲锁死寄存器掩码。
* **返回值**：无。


---

## 13. DCC (双时钟比较器) 模块

DCC (Dual-Clock Comparator) 是芯片内置的一个非常重要的功能安全（Functional Safety）监控外设。它的核心原理是利用两个相互独立的硬件计数器分别对两个不同的时钟源进行计数。通过对比在固定时间窗内两者的计数值差异，来精准判定某一个目标时钟（如系统 PLL 主频、通信外设时钟）是否存在频率漂移、跑飞、甚至是停振等严重异常。这是符合汽车级 ASIL 等级认证必备的时钟监视器。

### 13.1 时钟源挂载与基础配置

#### `DCC_setCounter0ClkSource` / `DCC_setCounter1ClkSource`
* **功能详细描述**：
  分别为 DCC 模块内部的两个核心计数器（Counter 0 和 Counter 1）挑选挂载的时钟源网络。通常的搭配策略是：
  * **Counter 0**：作为“参考基准时钟”，挂载一个已知极度稳定且安全的内部振荡器（例如内部自带的 INTOSC1 或 INTOSC2）。
  * **Counter 1**：作为“被测时钟”，挂载你需要监视可能出问题的时钟网络（例如经过 PLL 倍频后的系统主频 SYSCLK，或是外部引脚输入的晶振时钟）。
* **参数**：
  * `base`: DCC 模块的基地址。
  * `source`: 时钟源的选择枚举（如 `DCC_COUNT1SRC_PLL` 等）。
* **返回值**：无。

#### `DCC_setCounterSeeds`
* **功能详细描述**：
  初始化比较器的各个种子装载值。这是 DCC 测量的数学核心。
  根据两个时钟预期的理想频率比率，用户需要向这三个寄存器装载合适的初值。系统启动测量后，Counter 0（参考基准）会向下递减；当 Counter 0 减到 0 时，如果 Counter 1（被测）的计数值没有完全落在用户预设的误差窗口（Valid 裕度）内，DCC 就会立即触发 Error 报警。
* **参数**：
  * `base`: DCC 模块基址。
  * `counter0`: 参考基准时钟的初始倒计数值。
  * `validCounter0`: 允许的频率容差窗口大小（即容忍多少个周期的抖动不报假警）。
  * `counter1`: 期望被测时钟在这个窗口内应当走完的理论周期数值。
* **返回值**：无。

### 13.2 测量模式与启停控制

#### `DCC_enableSingleShotMode` / `DCC_disableSingleShotMode`
* **功能详细描述**：
  选择 DCC 的工作循环模式。
  * **单次射击模式 (Single-Shot)**：当 Counter 0 减到 0 完成一次比对后，即便没发现频率异常，DCC 也会立刻停机，并通过 Done 信号通知 CPU 本次快照测量完毕。
  * **连续监视模式 (Continuous)**（默认）：如果一轮比对没报错，DCC 会自动把装载的种子值重新推入计数器，开启永不休止的连续时钟安全巡更，全天候保卫系统频准。
* **参数**：
  * `base`: DCC 模块基址。
  * `mode`: 单次模式下的附加行为配置（比如当完成时要不要强制清除状态等）。
* **返回值**：无。

#### `DCC_enableModule` / `DCC_disableModule`
* **功能详细描述**：
  正式启动或停止 DCC 的双硬件计数器比较进程。配置完毕种子值后，调用启动函数即可撒手不管，让硬件接手安全监视任务。
* **返回值**：无。

### 13.3 警报与状态管理

#### `DCC_enableErrorSignal` / `DCC_disableErrorSignal`
* **功能详细描述**：
  当被测时钟跑出容差窗口（超频或欠频）导致比对失败时，决定是否允许 DCC 模块产生物理级的 Error 报警脉冲。这个脉冲可以直接连接到系统顶层的 NMI（不可屏蔽中断）控制器去立刻重置设备，或者送到专门的错误管脚拉低向外传达死机警报。
* **返回值**：无。

#### `DCC_getErrorStatus` / `DCC_clearErrorFlag`
* **功能详细描述**：
  获取并清除由于时钟漂移触发的硬件级错误标志位。在中断处理或探查中若发现 `getErrorStatus` 为 true，必须配合 `clearErrorFlag` 人为清空异常记录，否则外部可能永远被锁定在急停报错状态。
* **返回值**：状态获取函数返回 `bool`（有错返回 `true`）。

### 13.4 高级测算封装库

除了需要人工手算 `Seed` 参数的基础驱动，TI 还在库内封装了三个高级应用数学接口，用于极大地降低使用门槛。

#### `DCC_verifyClockFrequency`
* **功能详细描述**：
  提供期望被测频率、参考基准频率和允许偏差百分比，这套函数将自动在底层利用浮点运算为您算出对应的 Counter 0/1 以及 Valid 容差的种子值并填入启动。这让你可以直接用人脑直观的 Hz 为单位来配置报警保护器。
* **参数**：
  * `base`: DCC 基址。
  * `clock1`/`clock0`: 双方的时钟源网络宏。
  * `freq1`/`freq0`: 双方实际的频率数值（例如 `100.0f` 代表 100MHz）。
  * `tolerance`: 容错百分比（如 `1.0f` 代表允许 1% 的抖动偏离）。
* **返回值**：`bool`，若计算结果合法且成功启动测量返回 `true`。

#### `DCC_measureClockFrequency`
* **功能详细描述**：
  把 DCC 当作一个高精度的数字频率计使用。只要你赋予一个精准的基准时钟（如外部 XTAL 晶体），调用此函数后，底层硬件将会在一段采样窗内捕捉脉冲，最终函数会返回被测时钟当下的真实运行频率（以 MHz 为单位的浮点数）。对于启动时的内部 RC 振荡器校准极为有用。
* **返回值**：被测时钟算出的真实频率值（`float32_t` 浮点型）。


---

## 14. DCSM (双区代码安全模块) 模块

DCSM (Dual-Zone Code Security Module) 是保护用户核心算法 IP 资产不被第三方非法读取、逆向或篡改的关键硬件模块。它将芯片内部的 Flash 与 RAM 切分为 Zone 1 (Z1)、Zone 2 (Z2) 两个相互隔离的安全区域，加上一个非安全的公共区域 (Unsecure)。每个区域都可以单独设置自己的 128 位访问密码。

### 14.1 解锁与锁定控制

#### `DCSM_unlockZone1CSM` / `DCSM_unlockZone2CSM`
* **功能详细描述**：
  尝试使用预设的 128 位密码解除对特定区域（Zone 1 或 Zone 2）的封锁。
  如果解锁成功，调试器或位于其他区域的 CPU 代码才能读取该受保护区域内的 Flash 和 RAM 数据。密码匹配通过专门的硬件密钥寄存器对比实现，若多次输入错误，内部状态机将会产生惩罚延迟甚至锁定总线。
* **参数**：
  * `psCMDKey`: 包含 4 个 32 位字组成的 128 位密码结构体指针。
* **返回值**：无。

#### `DCSM_secureZone1` / `DCSM_secureZone2`
* **功能详细描述**：
  不经过复位，通过软件主动立刻将 Zone 1 或 Zone 2 重新拉回封锁状态（Secure）。
  通常在代码中：如果临时需要从受保护区读取校验数据，可以先调用 `unlock` 提取，提取完毕后立刻调用 `secure` 将保护罩重新落下，以最大程度缩短资产裸露的空窗期。
* **返回值**：无。

### 14.2 安全状态审查

#### `DCSM_getZone1CSMSecurityStatus` / `DCSM_getZone2CSMSecurityStatus`
* **功能详细描述**：
  询问对应安全区的当前防卫状态。
* **返回值**：`DCSM_SecurityStatus` 枚举。包含 `DCSM_STATUS_SECURE`（已被保护封锁）、`DCSM_STATUS_UNSECURE`（已成功解锁或芯片处于全裸状态）、`DCSM_STATUS_BLOCKED`（因为密码输错已被惩罚冻结总线）。

#### `DCSM_getRAMZone` / `DCSM_getFlashSectorZone`
* **功能详细描述**：
  对于某一块具体的物理存储块（例如 `FLASH_SECTOR_A` 或 `RAM_LS0`），查询它目前到底是被划分归属在了哪一个控制势力范围之下（Zone 1、Zone 2 还是 Unsecure 公共区）。存储区块的归属划分是依靠提前烧录在芯片 OTP（一次性可编程）区域的 LinkPointer 配置字来决定的。
* **参数**：
  * `module` / `sector`: 被探查的 RAM 模块编号或 Flash 扇区编号。
* **返回值**：`DCSM_MemoryStatus`，返回它的地盘归属（如 `DCSM_MEMORY_ZONE1`）。

### 14.3 执行专用 (Execute-Only) 保护

芯片的顶级保护策略：允许受保护代码在 CPU 里运行，但绝对禁止包括 CPU 自身通过数据总线将其作为数据读出（防范恶意利用写出指令把代码给 “打印” 出来）。

#### `DCSM_getZone1FlashEXEStatus` / `DCSM_getZone1RAMEXEStatus`
* **功能详细描述**：
  探查某一具体的 Flash 扇区或 RAM 模块是否被置于了最高级的 EXE-Only 保护模式下。在该模式下，只要尝试用数据总线去读取哪怕一个字节，芯片都会触发硬件非法访问异常（NMI）。
* **参数**：
  * `sector` / `module`: 欲探查的物理扇区。
* **返回值**：`DCSM_EXEOnlyStatus`。

### 14.4 硬件资源互斥量 (Semaphore) 争夺

因为双核芯片中两个 CPU（甚至包括外设 CLA）可能会同时试图去擦写 Flash 或者配置安全寄存器，所以必须有一把硬件互斥锁来保证独占访问。

#### `DCSM_claimZoneSemaphore` / `DCSM_releaseZoneSemaphore`
* **功能详细描述**：
  * `claim`: 尝试夺取负责管理 Flash 烧写状态机控制权的硬件区域信号量（Semaphore）。若别的 CPU 或 DMA 正在占用，此函数会返回获取失败。
  * `release`: 在当前 CPU 搞定 Flash 写入配置后，必须调用该函数释放钥匙，好让其他 Master 能够接手配置。
* **返回值**：`bool`。夺取成功返回 `true`。
* **示例代码**：
  ```c
  // 在对 Zone1 对应的 Flash 扇区进行擦除前，先夺取控制权
  if(DCSM_claimZoneSemaphore(DCSM_FLSEM_ZONE1)) {
      // 获取成功，开始调用 Flash 擦写 API...
      // 完毕后释放控制权
      DCSM_releaseZoneSemaphore();
  }
  ```


---

## 15. DMA (直接内存访问) 模块

DMA (Direct Memory Access) 模块用于在脱离 CPU 干预的情况下，在内存与外设（例如 SPI、SCI、ADC 结果寄存器）之间，或者内存与内存之间高速、自动地搬运大块数据。使用 DMA 可以极大地释放 CPU 带宽，让内核专注于密集的数学运算控制。芯片提供多个独立的 DMA 通道供用户配置。

### 15.1 基础初始化与地址配置

#### `DMA_initController` / `DMA_Reset`
* **功能详细描述**：
  上电后必须首先调用此函数来对 DMA 整个顶层控制机进行硬复位与初始化，清空所有历史通道的状态机和未决的请求信号。
* **返回值**：无。

#### `DMA_configSourceAddress` / `DMA_configDestAddress` / `DMA_configAddress`
* **功能详细描述**：
  为特定的 DMA 通道（例如 Channel 1）绑定它的“进货口（源地址）”与“出货口（目的地址）”。地址可以是普通的 RAM 数组指针，也可以是外设的数据收发寄存器地址。
* **参数**：
  * `base`: DMA 通道基地址（如 `DMA_CH1_BASE`）。
  * `srcAddr`: 源数据所在的内存物理地址。
  * `destAddr`: 搬运目的地的内存物理地址。
* **返回值**：无。

### 15.2 核心数据搬运引擎配置

DMA 的搬运逻辑分为两个层级：**Burst（微小爆发）** 和 **Transfer（宏观传输）**。
- 一次外设触发（如 SPI 收到一个字）引发一次 Burst（通常配置为搬 1 个或几个字）。
- 多次 Burst 拼凑成一个完整的 Transfer（比如搬满了一个 128 字节的缓冲数组）。

#### `DMA_configBurst`
* **功能详细描述**：
  配置单次硬件触发后，立刻连续搬运的数据步长。对于像 SPI、UART 这样的串行外设，通常配置每次 Burst 搬 1 个字，且源/目的指针在搬运后**不要**发生跳跃，因为外设的 FIFO 数据门牌号是固定死的一个地址。
* **参数**：
  * `base`: 通道基址。
  * `srcStep` / `destStep`: 搬完一个字后，源/目的地址自动递增或递减的跨度。
* **返回值**：无。

#### `DMA_configTransfer`
* **功能详细描述**：
  配置完成整个大数据块搬运所需的总量。在这个周期内，地址指针可能需要不断按照特定的步长游走（例如往数组里逐个填数）。一旦一轮完整的 Transfer 宣告结束，DMA 通道会抛出“搬运完毕”的大中断给 CPU 去进行数组的协议解包。
* **返回值**：无。

#### `DMA_configMode`
* **功能详细描述**：
  把这个通道的搬运动力源和实际的外设硬件触发线挂上钩。比如，你可以配置由“SPI-A 接收 FIFO 满”这一硬件事件作为触发源（Trigger）来唤醒通道执行一次 Burst。同时，该函数还决定了源地址或目的地址的数据存取位宽（通常为 16 位或 32 位），这需根据外设总线的硬件宽度对症下药。
* **参数**：
  * `base`: 通道基址。
  * `srcTrigger` / `destTrigger`: 触发本通道启动的硬件信号源。
* **返回值**：无。

### 15.3 启动、停止与中断控制

#### `DMA_startChannel` / `DMA_stopChannel`
* **功能详细描述**：
  配置好一切通道细节后，调用 `startChannel`。此时通道从挂起态切入侦听态，像猎犬一样静候设定的外设触发信号降临，信号一响立刻自动搬货。若遇系统急停，可以调 `stopChannel` 强行没收它的搬运权限。
* **参数**：
  * `channel`: 通道序号。
* **返回值**：无。

#### `DMA_enableInterrupt` / `DMA_getInterruptStatus` / `DMA_clearErrorFlag`
* **功能详细描述**：
  在完整的一轮大 Transfer 搬运结束的时刻，DMA 能够发送中断向 CPU 汇报。这一套函数用于打通该中断汇报机制并管理由于源/目的速度不匹配所可能引发的溢出错误（Overflow Error）标志。
* **返回值**：无。


---

## 16. eCAP (增强型捕获) 模块

增强型捕获 (eCAP, Enhanced Capture) 模块的主要职能是精确捕获外部引脚上电平跳变沿发生时刻的时间戳，进而被广泛用于测量电机编码器脉冲速度、PWM 占空比解析、霍尔传感器测速等。此外，如果不作为捕获用途，该模块还可以兼职当做一路独立的单通道非对称 PWM (APWM) 发生器使用。

### 16.1 捕获工作模式与引脚路由

#### `ECAP_enableCaptureMode` / `ECAP_enableAPWMMode`
* **功能详细描述**：
  切换 eCAP 模块的根本工作形态。
  * **Capture 模式**：核心的 32 位计数器作为自由运行的时基（Time-Base），引脚电平变化时会触发硬件抓取当前计数器的值存入寄存器。
  * **APWM 模式**：引脚反转为输出态。核心 32 位计数器作为 PWM 时基向外发波，其具有 32 位的极高分辨率，非常适合做极低频的控制信号发生器。
* **参数**：
  * `base`: eCAP 模块基地址（如 `ECAP1_BASE`）。
* **返回值**：无。

#### `ECAP_selectECAPInput`
* **功能详细描述**：
  高度灵活的输入交叉路由网（Input X-BAR）。此函数用于决定该 eCAP 通道究竟去监听哪一个物理引脚（或内部信号）的边沿跳变。可以将 GPIO 引脚通过 X-BAR 映射过来，也可以监听内部比较器 (CMPSS) 的输出信号以实现软测量。
* **返回值**：无。

### 16.2 捕获核心参数配置

eCAP 内置了一个极其精巧的**四级状态机 (Event 1 ~ Event 4)** 和 4 个配套的 32 位时间戳锁存寄存器（CAP1~CAP4）。

#### `ECAP_setEventPolarity`
* **功能详细描述**：
  独立定义那四个事件（Event 1 ~ 4）究竟是响应引脚信号的上升沿还是下降沿。比如在测 PWM 占空比时，可以配成 Event1 抓上升沿（周期开始），Event2 抓下降沿（高电平结束），Event3 抓下一个上升沿（周期结束）。
* **参数**：
  * `base`: eCAP 基址。
  * `event`: 针对哪个事件进行设置（如 `ECAP_EVENT_1`）。
  * `polarity`: 极性（`ECAP_EVT_POLARITY_RISING` 升或 `ECAP_EVT_POLARITY_FALLING` 降）。
* **返回值**：无。

#### `ECAP_enableCounterResetOnEvent` / `ECAP_disableCounterResetOnEvent`
* **功能详细描述**：
  这是决定测速算法**“绝对时间法（Absolute）”**和**“差分时间法（Delta）”**的核心差异。
  * 如果**不复位**计数器（绝对模式），事件发生时仅拷贝时间戳，CPU 稍后需要将相近的两次 CAP 寄存器值相减来求出周期耗时。
  * 如果在某个事件处**使能了复位**（差分模式），在捕捉下那一瞬间时间戳后，时基计数器会立刻清零重新起跑。此时捕捉到的寄存器值就是纯纯的两次脉冲之间流逝的时钟周期数，无需软件再做减法。
* **返回值**：无。

#### `ECAP_setCaptureMode`
* **功能详细描述**：
  决定这 4 级状态机的循环机制。
  * **Continuous（连续模式）**：当装满配置的最后一个事件（如填满 CAP4）后，硬件自动绕回 Event 1，覆写最老的 CAP1 寄存器数据。
  * **One-Shot（单次模式）**：状态机推进至设定的最后一个事件后便死锁挂起，冻结所有时间戳，直到 CPU 读取完毕并调用 `ECAP_reArm` 重新武装它。
* **返回值**：无。

### 16.3 获取数据与软控制

#### `ECAP_startCounter` / `ECAP_stopCounter` / `ECAP_resetCounters`
* **功能详细描述**：
  控制内置 32 位时基计数器 TSCTR 的运行、挂起暂停或是彻底清零。

#### `ECAP_getEventTimeStamp`
* **功能详细描述**：
  提取被硬件锁存下来的时间戳结果。这是 eCAP 获取外部信息的灵魂函数。
* **参数**：
  * `base`: eCAP 基址。
  * `event`: 欲读取其专属寄存器的时间戳事件号（`ECAP_EVENT_1` 对应 CAP1，等）。
* **返回值**：`uint32_t`。这往往代表着某个脉冲的绝对时间坐标，或是脉冲之间的脉宽长度。

#### `ECAP_reArm`
* **功能详细描述**：
  专门针对 One-Shot (单次截获) 模式。在单次触发打满目标数量并停机后，用于清除 Modulo 状态机，让它重头开始监听等待下一轮信号的洗礼。

### 16.4 中断调度

#### `ECAP_enableInterrupt` / `ECAP_clearInterrupt`
* **功能详细描述**：
  eCAP 可以针对诸多细节触发中断，最常用的是在 Event 1~4 发生时提醒 CPU 来取时间戳（例如 `ECAP_ISR_SOURCE_CAPTURE_EVENT_1`）；或者也可以在 32 位计数器由于太久没有外部脉冲到来发生**上溢出（Overflow）**时触发中断，这常被用于判断电机“堵转”或者“超低速零速”超时告警。
* **返回值**：无。

### 16.5 兼职：辅助 APWM 发波模式

#### `ECAP_setAPWMPeriod` / `ECAP_setAPWMCompare`
* **功能详细描述**：
  在 `enableAPWMMode` 生效的前提下，把 eCAP 变成一个基础的 32 位单路 PWM 发生器。其 CAP1 寄存器被挪用为设定发波周期 (Period)，CAP2 寄存器被挪用为设定反转比较点 (Compare)。由于是 32 位，其可发出的波形频率可以降到非常低，而不用像 16 位的常规 EPWM 那样去开启复杂的预分频。
* **返回值**：无。
* **示例代码**：
  ```c
  // 将 eCAP 转化为一路简单的呼吸灯 / 音调发声器 PWM
  ECAP_enableAPWMMode(ECAP1_BASE);
  ECAP_setAPWMPeriod(ECAP1_BASE, 100000000); // 周期1秒 (假定100M主频)
  ECAP_setAPWMCompare(ECAP1_BASE, 50000000); // 50%占空比
  ```


---

## 17. EPWM (增强型脉宽调制) 模块

增强型脉宽调制 (Enhanced Pulse Width Modulator) 模块是 C2000 系列及类 C2000 芯片中最为庞大、复杂且功能强悍的核心控制外设。它由极其灵活的多个子模块级联而成（包括时基 TB、计数比较 CC、动作限定 AQ、死区 DB、斩波 PC、错误联锁跳闸 TZ 以及事件触发 ET 等）。通过这些子模块的有机组合，它可以直接胜任极为复杂的电力电子拓扑（如多相交错并联、移相全桥、三电平 LLC、空间矢量逆变等）的脉冲生成与极限保护任务。

### 17.1 时基 (Time-Base, TB) 子模块

时基子模块为整个 EPWM 模块提供最基础的计数节拍。每一个 EPWM 核心（如 EPWM1, EPWM2）都拥有自己独立的一个 16 位计数器（TBCTR），以及负责决定其最高计数值的周期寄存器（TBPRD）。

#### `EPWM_setTimeBaseCounterMode`
* **功能详细描述**：
  决定时基计数器的游走方向。有四种模式可选：
  * **UP (向上计数)**：从 0 一直数到 TBPRD 然后归零，适合生成单边沿不对称的锯齿 PWM 波（例如基础的 Buck 降压斩波）。
  * **DOWN (向下计数)**：从 TBPRD 倒数到 0。
  * **UP-DOWN (增减交替计数)**：先从 0 数到 TBPRD，再从 TBPRD 倒数回 0。这会生成双边沿对称的三角 PWM 波，由于其天生的谐波抵消特性，是几乎所有马达控制和并网逆变器采用的标配模式。
  * **FREEZE (冻结停止)**：强行暂停计数器。通常在配置关键参数前冻结它，配置完再解冻，以防运行中参数紊乱。
* **参数**：
  * `base`: EPWM 模块的基地址。
  * `counterMode`: `EPWM_COUNTER_MODE_UP`, `EPWM_COUNTER_MODE_UP_DOWN` 等。
* **返回值**：无。

#### `EPWM_setTimeBasePeriod` / `EPWM_setTimeBaseCounter`
* **功能详细描述**：
  * `setPeriod`: 定义计数器的顶峰周期值（16位，TBPRD），在 UP 模式下波形周期 = (TBPRD + 1) * TBCLK，在 UP-DOWN 模式下波形周期 = 2 * TBPRD * TBCLK。
  * `setCounter`: 强制写入当前的计数值（TBCTR）。一般在初始化起步时强制归零。
* **返回值**：无。

#### `EPWM_setSyncInPulseSource` / `EPWM_enablePhaseShiftLoad` / `EPWM_setPhaseShift`
* **功能详细描述**：
  这是构建**多相交错拓扑（如移相全桥或多相交错 PFC）**不可或缺的灵魂机制：相位同步 (Sync) 机制。
  * `setSyncInPulseSource`：为一个 EPWM 通道选择它要听命于哪里的“同步打响脉冲”（Sync-IN）。通常从硬件 Input-XBAR 引入或者直接串联上游 EPWM 的 Sync-OUT 脉冲。
  * `enablePhaseShiftLoad` / `setPhaseShift`：一旦该 EPWM 接收到了上述选定的 Sync-IN 脉冲，它**不会**简单地归零，而是会将 `setPhaseShift` 提前定好的相位偏移值（TBPHS）直接砸进当前正在跑的计数器中。这样，下游的 PWM 波形便被强行与上游拉开了一个固定、精确的相位时间差。
* **返回值**：无。

### 17.2 计数比较 (Counter Compare, CC) 子模块

比较子模块主要用于调节占空比（Duty Cycle）。它拥有 CMPA, CMPB, CMPC, CMPD 多个比较寄存器。

#### `EPWM_setCounterCompareValue` / `EPWM_setCounterCompareShadowLoadMode`
* **功能详细描述**：
  将计算好的新占空比数值写入 CMPA/B 寄存器。随着底层计数器 TBCTR 在时钟驱动下不断变动，硬件比较器每时每刻都在审查 "TBCTR 是否等于 CMPA"，一旦相等，就会触发一次翻转事件（交给下一级的动作限定器去执行）。
  `setShadowLoadMode` 是保障电力电子安全的关键：通常我们不会让写入的 CMPA 值立即生效破坏当前的波形周期（即**直接模式 Direct**），而是将其放入阴影缓冲（Shadow），并指定只有当计数器运行到一个安全节点（例如归零点 Zero 或是顶点 Period）时，才让这个新占空比刷入前台执行。
* **参数**：
  * `compModule`: 比较模块选择（`EPWM_COUNTER_COMPARE_A` 到 D）。
  * `compCount`: 要写入的具体比较值。
* **返回值**：无。

### 17.3 动作限定 (Action Qualifier, AQ) 子模块

动作限定子模块是一个高度可编程的查表状态机。它规定了当各种比较事件发生时，引脚 A (EPWMxA) 和 引脚 B (EPWMxB) 到底应该做出怎样的物理电平反应。

#### `EPWM_setActionQualifierAction`
* **功能详细描述**：
  配置核心。用于将某一“事件”与某一“输出电平动作”强绑定。
  常见的事件包括：TBCTR 减到 0（Zero），TBCTR 爬到顶（Period），TBCTR 向上数时撞见 CMPA（Up-CMPA），向下数时撞见 CMPB（Down-CMPB）等等。
  可选的动作包括：拉高为 1 (High)、拉低为 0 (Low)、翻转当前电平 (Toggle)、什么也不做保持原样 (Do Nothing)。
* **参数**：
  * `epwmOutput`: 被配置的管脚（`EPWM_AQ_OUTPUT_A` 或 `EPWM_AQ_OUTPUT_B`）。
  * `action`: 输出动作（如 `EPWM_AQ_OUTPUT_HIGH`）。
  * `event`: 触发动作的根源事件（如 `EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA`）。
* **返回值**：无。
* **示例代码**：
  ```c
  // 经典的正向占空比 PWM A：计数到 0 时拉高，向上数碰到 CMPA 时拉低
  EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
  EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW,  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
  ```

#### `EPWM_setActionQualifierContSWForceAction` / `EPWM_forceActionQualifierSWAction`
* **功能详细描述**：
  提供纯软件绕开硬件状态机，强行控制引脚电平的后门。常被用于软件手动起振发波前，强行将引脚箝位在关闭状态（如保持双低）。

### 17.4 死区发生器 (Dead-Band, DB) 子模块

为了防止半桥拓扑中上下两个 MOSFET 管因为开通关断时间不对称而发生极其危险的“直通短路 (Shoot-through)”，必须在其中一个管子关断和另一个管子开通之间硬性插入一段真空等待期，即死区时间。

#### `EPWM_setDeadBandDelayMode` / `EPWM_setDeadBandDelayPolarity`
* **功能详细描述**：
  死区发生器接收来自上一级 AQ 模块送出来的“理想化” A、B 波形。通过这组函数，你可以让 B 引脚的波形变成 A 引脚逻辑上的反相（常称作极性反转或互补输出 Active-Low / Active-High）。然后再激活上升沿延时 (RED) 或是下降沿延时 (FED) 功能。
* **返回值**：无。

#### `EPWM_setRisingEdgeDelayCount` / `EPWM_setFallingEdgeDelayCount`
* **功能详细描述**：
  设定真正的死区时间宽度。延时宽度同样也是基于 EPWM 时钟的计数个数，需要根据目标驱动开关管的规格书（例如 SiC、GaN 或是传统的 IGBT 开关速度区别很大）精准核算后写入。

### 17.5 故障联锁跳闸区 (Trip Zone, TZ) 子模块

这是最后一道，也是最坚固的一道防线。TZ 模块能够异步监听来自外部引脚（如过流检测端）、或者内部比较器 (CMPSS) 甚至时钟丢失电路发出的跳闸信号，以纳秒级的硬件级速度强行切断发波引脚。完全不需要任何 CPU 中断代码干预。

#### `EPWM_setTripZoneAction`
* **功能详细描述**：
  配置当硬件跳闸警报信号到达时，EPWMxA 或 EPWMxB 引脚应当作何响应。通常在电源应用中，会配置成强行拉低（Force Low）或是使其进入高阻态（High Impedance）从而断开栅极驱动的光耦。
* **参数**：
  * `tzEvent`: 跳闸事件源（如一次性的 `EPWM_TZ_ACTION_EVENT_TZA` 等）。
  * `tzAction`: 所要执行的动作（如 `EPWM_TZ_ACTION_LOW` 置低）。
* **返回值**：无。

#### `EPWM_enableTripZoneSignals` / `EPWM_clearTripZoneFlag`
* **功能详细描述**：
  TZ 事件分为两种：
  * **OSHT (One-Shot 单次封锁)**：只要发生一次过流，立马锁死 PWM 为低电平，即使过流信号消失，也绝不松手，直到 CPU 在确认安全后调用 `clearTripZoneFlag` 手动解锁。主要应对严重灾难故障。
  * **CBC (Cycle-by-Cycle 逐周期封锁)**：当周期内过流，立刻截断波形；但是只要下一个 PWM 周期的计数器归零点（Zero）到来，硬件就会自动尝试松开封锁。这是一种自恢复的硬稳流控制策略。
* **返回值**：无。

### 17.6 事件触发 (Event Trigger, ET) 子模块

用于将 EPWM 内部的周期节拍转化为 ADC 采样的发起扳机，或者触发向 CPU 的控制中断。

#### `EPWM_setEventTriggerInterruptSource` / `EPWM_setInterruptEventCount`
* **功能详细描述**：
  设定什么事件可以唤起 EPWM 的中断（例如每次 TBCTR 等于 0，或是等于 PRD，或者是等于指定的 CMPC 值）。`setInterruptEventCount` 可以利用其内置的小分频器，设定例如“每发生 3 次等于 0 事件，才真正向上级丢出一个中断请求”。在几百 kHz 极高频的开关频率下，CPU 无法做到每个周期都算一轮，由此来分频降低中断负荷极其有效。
* **返回值**：无。

#### `EPWM_enableADCTrigger` / `EPWM_setADCTriggerSource`
* **功能详细描述**：
  控制 EPWM 在何种特定时刻发出 SOCA（发给 ADC A）或者 SOCB 的硬件脉冲命令。这是实现无 CPU 介入自动闭环采样（如在 PWM 占空比正中央最平稳的时刻启动 ADC 采流）的配置核心。
* **返回值**：无。


---

## 18. eQEP (增强型正交编码器脉冲) 模块

增强型正交编码器脉冲 (Enhanced Quadrature Encoder Pulse) 模块专门用于与电机轴上的线性或旋转增量式正交编码器直接对接。它可以从编码器传来的 A 相、B 相、Index（零位脉冲）和 Strobe（选通）信号中，利用纯硬件逻辑完美解析出电机的旋转方向、绝对位置和精确的转速，是伺服控制系统（FOC 闭环等）中用来获取转子机械参数的基石。

### 18.1 输入与解码配置

#### `EQEP_setDecoderConfig`
* **功能详细描述**：
  配置 eQEP 最前端的解码器工作模式。它可以配置为：
  * **正交计数模式**：标准的 A/B 相位差 90 度输入，硬件根据谁先谁后自动判定方向。
  * **方向-计数模式**：A 相纯做时钟脉冲，B 相高低电平纯代表方向（常用于老式步进电机）。
  * **UP/DOWN 双计数模式**：A 相脉冲只负责正转加计数，B 相脉冲只负责反转减计数。
  同时，还可以配置是否要对输入的脉冲进行 x2 或 x4 的倍频（Resolution），从而榨干编码器的每一丝精度。
* **参数**：
  * `base`: eQEP 模块基址（如 `EQEP1_BASE`）。
  * `config`: 包含解码模式和分辨率的组合掩码。
* **返回值**：无。

#### `EQEP_setInputPolarity`
* **功能详细描述**：
  硬件上反转 A, B, Index 或是 Strobe 引脚的逻辑极性。如果发现接线反了导致软件读出来的正反转与实际相反，可以不改线，直接在代码中调用此函数将 A 或 B 相在内部反相即可修正。

### 18.2 位置计数器 (Position Counter)

#### `EQEP_setPositionCounterConfig`
* **功能详细描述**：
  配置核心 32 位位置计数器（QPOSCNT）的重置（Reset）规则。
  * **索引复位（Index Reset）**：每转一圈遇到 Z 脉冲（Index）时强制将计数器清零，防止累计误差。
  * **最大位置复位（Max Position Reset）**：设定一个电机的单圈脉冲总数，计数器数到这个最大值后自动回零。
  * **首个索引复位（First Index Reset）**：只在电机开机寻零遇到第一个 Z 脉冲时复位一次确定绝对零点，以后就不再清零，一直累加作多圈绝对位置记录。
* **参数**：
  * `base`: eQEP 基址。
  * `mode`: 复位模式配置。
  * `maxPosition`: 最大计数值（即 32 位 QPOSMAX 寄存器的值）。
* **返回值**：无。

#### `EQEP_getPosition` / `EQEP_setPosition`
* **功能详细描述**：
  读取或强制改写当前的 32 位位置计数器值。
  * `getPosition`: 闭环算法里最常调用的函数，拿到的就是当前转子相对于零点的累积角度或步数。
  * `setPosition`: 常常在绝对值编码器系统上电时，通过 SPI 拿到绝对角度后，手动强制灌入这个计数器里作为起点。
* **返回值**：位置读取返回 `uint32_t`。

#### `EQEP_getDirection`
* **功能详细描述**：
  根据最近一段 A/B 相的相位超前/滞后关系，返回经过硬件正交逻辑解码出来的当前转子瞬时物理旋转方向。
* **返回值**：`int16_t`，`1` 表示正转（Forward），`-1` 表示反转（Reverse）。

### 18.3 速度测量：单元定时器 (Unit Timer) 与捕获 (Capture)

eQEP 提供了两套互补的测速方案：
1. **高频测速（M 法）**：利用固定的时间窗（Unit Timer）去数期间进来了多少个脉冲。
2. **低频测速（T 法）**：利用高频的内部时基去测算相邻两个编码器脉冲之间的绝对时间（Capture）。

#### `EQEP_enableUnitTimer` / `EQEP_disableUnitTimer`
* **功能详细描述**：
  配置并开启 M 法测速的核心。它会设定一个固定的时间基准（比如 1ms），当这 1ms 走到头时，硬件会自动将当前累计的脉冲位置（QPOSCNT）锁存到锁存寄存器（QPOSLAT）中，并向 CPU 抛出中断，提醒 CPU：这 1ms 内的位移切片已经切好了，快来读取算速度。
* **参数**：
  * `base`: eQEP 基址。
  * `period`: 定义该单元定时器的时间窗长度（以系统时钟周期计）。
* **返回值**：无。

#### `EQEP_setCaptureConfig` / `EQEP_enableCapture`
* **功能详细描述**：
  配置并开启 T 法测速（或者叫 M/T 法）。在极低速转动时，1ms 内可能一个脉冲都等不到。此时开启 Capture，硬件会计时从上一个脉冲沿到当前脉冲沿到底流逝了多少个内部时钟滴答。此函数可配置用于计时的内部时钟分频系数（CAPCLK）和触发捕获的外部脉冲分频系数（UPEVN）。

#### `EQEP_getCapturePeriod` / `EQEP_getCaptureTimer`
* **功能详细描述**：
  读取上述 Capture 硬件抓取到的微观时间耗时差，以推算出低速下精确的转子角速度。

### 18.4 锁存、中断与看门狗

#### `EQEP_setLatchMode`
* **功能详细描述**：
  规定除了上述的单元定时器外，是否要在发生一些特殊物理事件（比如遇到 Index 零点信号或者 Strobe 选通信号）的瞬间，由硬件立刻进行位置的快照锁存。对于精准的寻零停机控制非常有帮助。

#### `EQEP_enableWatchdog`
* **功能详细描述**：
  开启 eQEP 专属的断线看门狗。你可以设置一个超时时间。如果编码器连线断开，导致在这段时间内一个脉冲都没有进来，看门狗会立刻超时并触发保护中断。这是功能安全中防止伺服飞车的最后屏障。

#### `EQEP_enableInterrupt` / `EQEP_getInterruptStatus`
* **功能详细描述**：
  配置 eQEP 通向 CPU 的中断线。可配置的触发事件包括：单元时间窗到达（Unit Time-out）、捕获完成（Capture）、正交方向改变（Direction Change，检测电机震荡或倒转）、看门狗超时、以及计数器溢出等。


---

## 19. ERAD (嵌入式实时分析与诊断) 模块

ERAD (Embedded Real-time Analysis and Diagnostics) 模块是 C2000 独有的革命性片上调试利器。它突破了传统 JTAG 硬件断点数量的限制，能够在不干扰 CPU 实时运行（不挂起）的情况下，实时监控数据总线和地址总线。它可以用于生成复杂的系统级触发信号、收集性能剖析 (Profiling) 数据，或者在极其严苛的条件下实现免停机的非侵入式软件诊断。

### 19.1 权限与模块初始化

#### `ERAD_getOwnership` / `ERAD_setOwnership`
* **功能详细描述**：
  ERAD 资源可以被仿真器 (Debugger，如 CCS) 占有，也可以被用户应用程序 (Application) 自行占有和配置。这套函数用于仲裁或强制交接使用权。如果配置为 Application 模式，程序可以通过代码自行设定 ERAD 断点来对自身执行流进行性能监测。
* **返回值**：枚举 `ERAD_OWNER_DEBUGGER` 或 `ERAD_OWNER_APPLICATION`。

#### `ERAD_initModule`
* **功能详细描述**：
  进行全局初始化，复位 ERAD 内部庞大的总线比较器 (Bus Comparator) 和系统计数器 (System Counter) 阵列的状态，同时获取其归属权。

### 19.2 总线比较器 (Bus Comparator) 监控

ERAD 包含多个强大的硬件总线比较器。它们能以 CPU 主频全速偷窥内部总线，一旦发现 CPU 正在访问某个特定地址，甚至写入了某个特定的数据，就会瞬间输出一个“命中 (Hit)” 硬件事件。

#### `ERAD_configBusComp`
* **功能详细描述**：
  全方位配置一个特定的总线比较器。你可以设定它去监视指令预取总线 (Fetch)、数据读总线 (Read) 或数据写总线 (Write)。并指定需要监控的参考物理地址以及可选的数据位掩码。当 CPU 执行到这段地址，或变量满足特定掩码时，即产生一个事件。
* **参数**：
  * `base`: 比较器基址（如 `ERAD_HWBP1_BASE`）。
  * `config_params`: 极其详细的匹配策略结构体。
* **返回值**：无。

### 19.3 系统计数器 (System Counter) 与性能剖析

#### `ERAD_configCounterInCountingMode` / `ERAD_configCounterInStartStopMode`
* **功能详细描述**：
  ERAD 内部的硬件计数器可以和上述的总线比较器联动。
  * **Counting 模式**：每当对应的总线比较器“命中”一次（比如调用了某函数一次），计数器就 +1。可用于统计某个中断在 1 秒内究竟执行了多少次。
  * **Start/Stop 模式**：用比较器 1 作为 Start，比较器 2 作为 Stop。当程序跑入某函数时计数器开始计时，跑出时停止计时。由此获得极其精准的代码段 CPU 耗时（Profiling），全程零侵入、不消耗任何汇编指令。
* **返回值**：无。

#### `ERAD_getCurrentCount` / `ERAD_getMaxCount` / `ERAD_clearCounterEvent`
* **功能详细描述**：
  读取上述硬件计数器探查到的性能数据。`getMaxCount` 还能由硬件自动为您锁存下程序运行历史中最长的一次代码耗时（最坏情况时间，Worst-Case Execution Time, WCET），这对实时操作系统的安全性评估具有决定性意义。

### 19.4 高阶组合应用封装

#### `ERAD_profile`
* **功能详细描述**：
  高度集成的性能剖析函数。只需传入一段想要测量的代码的首地址和尾地址，它会自动在底层分配和编排好总线比较器与计数器。
* **返回值**：无。

#### `ERAD_enableInterruptOnAddressHit`
* **功能详细描述**：
  无需仿真器介入，直接让 ERAD 监听某个内存地址。一旦代码跑到那里，ERAD 不会像传统 Debugger 那样把 CPU 挂起冻结，而是向 CPU 发送一个实时中断（RTOS Interrupt）。CPU 会跳转到你的自定义 ISR 中打印日志或抓取数据，随后继续全速运行，实现“非侵入式断点”。


---

## 20. FLASH (内置闪存控制器) 模块

FLASH 模块提供了对芯片内置的非易失性闪存（Flash ROM）进行底层时序配置、工作模式切换以及在线擦写（IAP, In-Application Programming）的驱动支持。这在用户需要实现软件 OTA (Over-The-Air) 空中升级、动态保存重要标定参数，或是直接访问 Flash 物理总线时至关重要。

### 20.1 时序与工作模式配置

由于 CPU 运行在极高频（例如上百 MHz），而 Flash 物理存储阵列的读取速度受限于物理工艺无法跟上 CPU 的节奏。因此必须设置正确的时钟分频与等待状态。

#### `Flash_initModule` / `Flash_setClkDiv`
* **功能详细描述**：
  初始化 Flash 控制器的核心函数。它负责根据当前系统的主频来设置访问 Flash 的时钟分频（Div）及读取等待周期。如果在系统提频前没有正确调用此函数加大等待周期，系统在预取指令时必然直接跑飞宕机。
* **参数**：
  * `div`: 针对 Flash 接口控制器的时钟分频参数（确保总线访问时序满足规格书要求）。
  * `qspi_en` (仅限 initModule): 初始化时是否一并激活 QSPI（四线高速并行读）硬件加速模式。
* **返回值**：无。

#### `Flash_enableQspiMode` / `Flash_disableQspiMode`
* **功能详细描述**：
  在系统运行中，动态开关 Flash 控制器的 QSPI (Quad-SPI) 高速预取模式。开启后，控制器每次从物理 Flash 矩阵中同时拖出多条数据线进入预取缓冲池，极大地拉高了 CPU 连续执行代码时的指令吞吐带宽。调用时函数内部会有一个短时间 `while` 轮询，必须等待之前悬而未决的写或擦除操作（WIP）彻底完结后才允许切换总线模式。
* **返回值**：无。

### 20.2 物理读写与擦除操作 (IAP)

此类函数被设计为执行擦除或写入。**极其重要**：执行这类函数的代码自身绝对不能在正被擦除或改写的 Flash 扇区内执行！通常在执行 OTA 升级或标定数据写入前，需要先将这部分驱动函数通过 MemCopy 从 Flash 搬运到 RAM 中，并在 RAM 中运行它们。

#### `Flash_eraseChip` / `Flash_eraseBlock` / `Flash_eraseSector`
* **功能详细描述**：
  闪存的物理特性决定了写入之前必须先执行擦除（将位从 0 翻转回 1）。这三个函数分别对应了三种擦除粒度：
  * `eraseChip`: 核弹级。全片数据区（除受保护的出厂区外）无差别擦除。
  * `eraseBlock`: 按照物理的 Block（通常为 64KB 大块）进行擦除，速度较快，适合大版本固件升级。
  * `eraseSector`: 按照最细粒度的 Sector（通常为 4KB 扇区）执行定点擦除，适合仅擦除存放参数的那个小尾巴扇区。
* **参数**：对应 Block 或 Sector 的硬件逻辑编号。
* **返回值**：无。

#### `Flash_eraseOTP`
* **功能详细描述**：
  擦除一次性可编程（OTP, One-Time Programmable）区域。注意：通常微控制器的 OTP 区域在出厂烧录校验或安全秘钥后便被硬件熔断或逻辑锁死，后续可能不接受擦除。此接口仅用于在工厂工程模式或特定的软模拟 OTP 段（依据具体芯片型号架构而定）中生效。

#### `Flash_readWord` / `Flash_writeWord`
* **功能详细描述**：
  * `readWord`: 提供一种带地址对齐校验的底层数据窥探方式，从给定的物理地址（必须是 32 位地址对齐，即低 2 位为 0）读取一个字（Word，此处为 32位 4 字节）。
  * `writeWord`: 将一个 32位 的新数据烧写入给定的物理地址中。调用前务必确保目标地址已被擦除干净。
* **参数**：
  * `addr`: 物理绝对地址。
  * `val`: 需要写入的数据。
* **返回值**：读取函数返回该地址内的 `vu32` (volatile uint32_t) 数值。
* **示例代码**：
  ```c
  // (在 RAM 中执行的代码)
  // 擦除第 0 号扇区
  Flash_eraseSector(0);
  // 向该扇区首地址烧入一个标志位
  Flash_writeWord(0x00080000, 0xDEADBEEF);
  ```


---

## 21. FSI (快速串行接口) 模块

FSI (Fast Serial Interface) 是 TI C2000 家族中独有的一种极高速、确定性点对点串行通信总线。它专为隔离跨板通信、多核心同步或分布式电力电子系统（如多台逆变器并联）而生。它突破了传统 SPI 或 SCI 的速度瓶颈，并且硬件原生支持高达 200Mbps 的传输速率、自动 CRC 校验、ECC 纠错以及线路断线看门狗保护。

### 21.1 发送端 (TX) 基础配置与初始化

#### `FSI_performTxInitialization` / `FSI_executeTxFlushSequence`
* **功能详细描述**：
  在系统刚上电时，为了保证高速物理层的时序握手稳定，必须严格遵守一份状态机复位序列。
  * `performTxInitialization`: 首先根据系统主频配置 FSI 时钟预分频（Prescalar），并按序解除内部各个子模块（如 Ping 发生器、时钟域）的锁定。
  * `executeTxFlushSequence`: 在初始化完毕后，强制在总线上空发一串特定的 Flush 握手波形，通知线路对端的 RX 硬件准备就绪，建立最初的链路同步。
* **返回值**：无。

#### `FSI_configTxDataWidth` / `FSI_setTxSoftwareFrameSize`
* **功能详细描述**：
  配置每次要在物理总线上打出的数据包（Frame）的几何形状。
  * `configTxDataWidth`: 决定发送端使用几根物理数据线（单线 1-Lane 或者双线 2-Lane 模式）。双线模式能让吞吐量翻倍。
  * `setTxSoftwareFrameSize`: 规定在这个数据帧中，究竟要携带多少个 16 位的有效数据字（N Words，范围通常是 1 到 16 个字）。
* **返回值**：无。

#### `FSI_setTxFrameTag` / `FSI_setTxUserDefinedData`
* **功能详细描述**：
  给 FSI 数据包打上额外的元数据“标签”。
  除了 N 个数据字外，FSI 硬件会在包头自动插入一个 4 位的 Tag 和一个 8 位的 User Data。
  * `Tag`: 常常用来标识这包数据的类型（比如：0 代表电流反馈，1 代表电压前馈等）。
  * `User Data`: 常常附带发送方的本节点 ID 或者极其简短的状态控制码，省去了在核心数据载荷里占用空间的麻烦。
* **返回值**：无。

### 21.2 接收端 (RX) 基础配置与初始化

#### `FSI_performRxInitialization`
* **功能详细描述**：
  在接收端芯片上，调用此函数对 RX 模块进行软复位，并让其进入侦听挂起状态。它不涉及预分频设置，因为 FSI 是源同步总线，RX 端的时钟完全是由 TX 端通过独立的 Clock 物理线发过来的。

#### `FSI_configRxDelayLine`
* **功能详细描述**：
  由于 FSI 极度高速（纳秒级），物理 PCB 走线上哪怕只有几厘米的布线差异或隔离光耦的微弱延迟偏差，都会导致 Clock 线和 Data 线之间发生致命的时序错位（Skew）。此函数用于校准 RX 端的内部可编程延迟线（Delay Line），精细微调皮秒级的滞后量，从而把采样点重新精准对齐到数据眼图的最宽处。这对于过板间隔离高速通讯是必须步骤。
* **参数**：
  * `base`: FSI RX 模块基址。
  * `delayTapSelect`: 选择需要校准的线路（如 RXCLK、RXD0 等）。
  * `tapValue`: 延迟步数（Tap 越多，延迟越长）。
* **返回值**：无。

### 21.3 数据的搬运与发送触发

#### `FSI_writeTxBuffer` / `FSI_readRxBuffer`
* **功能详细描述**：
  FSI 模块内部分别有 16 个字的专属 RAM 缓冲区。
  * `writeTxBuffer`: 在需要发包前，调用此函数将你准备好的数据数组批量倒灌进 TX 硬件 FIFO 中。
  * `readRxBuffer`: 当收到数据到达中断后，调用此函数一次性将完整的帧负载从 RX FIFO 中搬入系统常规 RAM。
* **返回值**：无。

#### `FSI_startTxTransmit`
* **功能详细描述**：
  当你配置好 Frame 大小、填好 Tag 并把数据灌入 TX Buffer 后，拉动这个扳机。硬件将瞬间自动完成数据串行化、CRC 尾巴附加，并在时钟线上带出精准的高频拍频发送到远端。
* **返回值**：无。

### 21.4 Ping 机制与断线看门狗

FSI 被设计于分布式电源设备中，所以它有一套纯硬件的“心跳保活”机制，连 CPU 都不用介入。

#### `FSI_enableTxPingTimer`
* **功能详细描述**：
  在发送端开启 Ping 发生器。你可以设定一个时间基准，只要这段时间里总线上没有发送过真实的数据包，硬件就会自动见缝插针地往总线上发一个不带数据纯粹只带特定 Ping Tag 的空包，以此告诉对端“我还活着，线没断”。
* **返回值**：无。

#### `FSI_enableRxPingWatchdog`
* **功能详细描述**：
  在接收端开启对应的 Ping 看门狗。设定一个超时阈值（通常略大于发送端的 Ping 周期），如果 RX 硬件超过这个时间没有收到对端的任何动静（不管是真数据包还是空 Ping 包），它将立刻触发最高优先级的硬件中断或直接连线到 EPWM TZ 模块进行全机紧急封锁。
* **返回值**：无。

### 21.5 安全与报错 (ECC / CRC)

#### `FSI_setTxECCComputeWidth` / `FSI_getRxReceivedCRC`
* **功能详细描述**：
  硬件具备在帧尾自动附加 CRC 校验和 ECC（错误纠正码）的能力。接收端一旦发现收到的帧 CRC 不匹配，会丢弃数据并在 `FSI_getRxEventStatus` 中置位报错标志。如果有配置 ECC，甚至能在一定误码率下由硬件直接把出错的那一位数据强行修补纠正回来。


---

## 22. GPIO (通用输入输出) 模块

GPIO (General-Purpose Input/Output) 是芯片最基础的引脚管理模块。C2000 的 GPIO 模块极为强大，除了基本的输入输出、内部上拉、开漏配置外，还支持多路复用（MUX）切换、极其坚固的硬件数字量输入消抖滤波（Qualification）、以及在多核系统中将任意引脚的控制权随意分配给 CPU1、CPU2 或是协处理器 CLA。

### 22.1 引脚复用与模拟/数字模式切换

#### `GPIO_setPinConfig` / `GPIO_MuxConfig`
* **功能详细描述**：
  配置物理引脚的功能复用。芯片的引脚不仅可以作为普通 IO，还可以复用给 EPWM、SCI、SPI 等外设使用。`setPinConfig` 接受形如 `GPIO_0_EPWM1_A` 的宏，在底层会自动将对应的 GPIO0 路由到 EPWM1_A 控制线路上。
* **参数**：
  * `pinConfig`: 定义在 `pin_map.h` 中的引脚复用专属宏。
* **返回值**：无。

#### `GPIO_setAnalogMode`
* **功能详细描述**：
  专门针对部分同时具备模拟特性（如连接了 ADC 通道或 CMPSS 输入）和数字特性的引脚。当你要用该引脚进行精确的电压采样时，为了防止数字输入缓冲器的不断翻转消耗功耗以及引入数字底噪，必须调用此函数将该引脚完全配置为“纯模拟（Analog）”模式，彻底隔断其与数字核心的物理联系。
* **返回值**：无。

### 22.2 方向、电气属性与多核归属

#### `GPIO_setDirectionMode` / `GPIO_getDirectionMode`
* **功能详细描述**：
  将引脚的数据流向配置为输入 (`GPIO_DIR_MODE_IN`) 或者是推挽/开漏输出 (`GPIO_DIR_MODE_OUT`)。
* **返回值**：设置无返回，获取返回当前方向模式。

#### `GPIO_setPadConfig`
* **功能详细描述**：
  配置引脚深层的硬件电气特性。可以组合使用来打开内置的弱上拉电阻（`GPIO_PIN_TYPE_PULLUP`，通常针对 I2C 或按键输入必须开启），或者切换输出驱动级为开漏模式（`GPIO_PIN_TYPE_OD`，即只拉低不拉高，需外置强上拉），亦或是保持最标准的推挽输出（`GPIO_PIN_TYPE_STD`）。
* **返回值**：无。

#### `GPIO_setControllerCore`
* **功能详细描述**：
  多核芯片（双核及包含 CLA 的系统）的神级函数。默认所有 GPIO 均由 CPU1 掌控。利用此函数，CPU1 可以将某个引脚的“指挥权”直接移交给 CPU2 或 CLA。移交后，只有对应的核心阵列有权限对该引脚的高低电平进行翻转，极大地方便了将特定外设任务物理隔离给不同核心处理。
* **参数**：
  * `pin`: GPIO 引脚号。
  * `core`: 目标归属核心（如 `GPIO_CORE_CPU1_CLA1` 交给 CLA，或 `GPIO_CORE_CPU2` 交给 CPU2）。
* **返回值**：无。

### 22.3 输入消抖滤波 (Qualification)

在极度恶劣的电磁干扰（EMI）工业现场，普通的按键或者信号引脚经常会出现几纳秒到几百纳秒的尖刺毛刺，若不加处理将导致代码状态机乱飞。

#### `GPIO_setQualificationMode` / `GPIO_setQualificationPeriod`
* **功能详细描述**：
  * `setQualificationMode`: 决定引脚硬件滤波窗的模式。可选 `GPIO_QUAL_SYNC` (仅与系统时钟同步，无额外滤波)、`GPIO_QUAL_3SAMPLE` (要求连续3次采样电平一致才认可是有效翻转) 或 `GPIO_QUAL_6SAMPLE` (连续6次一致才翻转)。如果该引脚被当做 EPWM 的外部时钟，还可以配置为 `GPIO_QUAL_ASYNC` 完全无延迟全异步直通。
  * `setQualificationPeriod`: 配合上述的 3 采样或 6 采样模式，定义每次采样之间到底要间隔多少个时钟周期（通过设定一个时钟分频器，最长可以过滤掉长达几个毫秒的慢速抖动）。
* **返回值**：无。

### 22.4 电平读写与端口批量操作

#### `GPIO_writePin` / `GPIO_readPin` / `GPIO_togglePin`
* **功能详细描述**：
  最高频使用的电平读写控制。用于单根引脚的高低电平置位、状态读取以及电平翻转（Toggle，常用于呼吸灯或示波器探针测量代码耗时）。翻转指令在底层直接操作的是专属的 `TOGGLE` 寄存器，属于原子操作（Atomic），不会被中断打断。
* **返回值**：`readPin` 返回 `0` 或 `1`。

#### `GPIO_readPortData` / `GPIO_writePortData` / `GPIO_setPortPins` / `GPIO_clearPortPins`
* **功能详细描述**：
  以上单管脚操作都是针对位的，而带有 `Port` 关键字的函数是直接对 32 位宽度的 GPIOA (Pin 0-31)、GPIOB (Pin 32-63) 等整个组进行批量并发操作。这在驱动并行总线（如并口 LCD 屏、高速并行 ADC 通信）时，能保证几十个引脚的电平在同一个机器周期内被同时拉高或拉低，无任何相位差。

### 22.5 外部中断 (XINT) 与安全锁定

#### `GPIO_setInterruptPin` / `GPIO_setInterruptType` / `GPIO_enableInterrupt`
* **功能详细描述**：
  C2000 的外部中断机制不是像别的单片机那样写死在固定管脚上的。
  * `setInterruptPin`: 通过底层的 Input-XBAR 交叉开关，你可以把芯片引脚上的**任何一根** GPIO 强行路由分配给 XINT1 ~ XINT5 这 5 个外部中断通道之一。
  * `setInterruptType`: 接着配置该中断是响应上升沿、下降沿，还是双边沿都响应。
  * `enableInterrupt`: 最后打通去往 PIE 调度器的中断闸门。
* **返回值**：无。

#### `GPIO_lockPortConfig` / `GPIO_unlockPortConfig` / `GPIO_commitPortConfig`
* **功能详细描述**：
  涉及功能安全的引脚锁死机制。配置完引脚属性后调用 `lockPortConfig`，对应的引脚配置寄存器立刻变成只读模式。这可以防止因为程序跑飞或者数组越界错误地把 PWM 驱动管脚变成了普通的 GPIO 输出，从而导致上下管直通炸机。只有输入与之匹配的 `unlockPortConfig` 配合复杂的锁死序列才能解开。


---

## 23. HR_ADC (高分辨率模数转换器) 模块

HR_ADC (High Resolution ADC) 模块是 C2000 芯片中为了满足极其精密电源控制（如高频数字电源、精密仪器仪表）而定制的增强型 ADC 控制器封装。它在保留了标准 ADC 所有特性的基础上，在宏观的接口命名与逻辑上提供了与标准 ADC 完全一致的使用体验，但底层专门针对高精度采样的噪声管理、抗锯齿时序等做了更严格的约束。由于其接口与前文的 [ADC 模块](#1-adc-模数转换器-模块) 几乎是一对一的镜像映射，此处仅作核心概念的概括性介绍。

### 23.1 与标准 ADC 模块的接口对应性

如果您已经熟练掌握了前述 `ADC_xxx` 的 API 体系，那么掌握 `HR_ADC_xxx` 几乎不需要额外的学习成本。它们拥有完全平行的函数封装：

* **基础与 SOC 控制**：
  * `HR_ADC_setPrescaler`：配置高分辨率 ADC 内核时钟。
  * `HR_ADC_enableConverter` / `HR_ADC_disableConverter`：启动或关闭模拟转换核心。
  * `HR_ADC_setupSOC`：配置具体的采样通道、触发源与采样保持窗宽。
  * `HR_ADC_forceSOC`：纯软件强制起动转换。

* **中断与执行流管理**：
  * `HR_ADC_setInterruptSource`：绑定 SOC 的转换结束（EOC）标志至硬件中断。
  * `HR_ADC_getInterruptStatus` / `HR_ADC_clearInterruptStatus`：中断标志的查询与手动复位。
  * `HR_ADC_enableContinuousMode`：开启中断连续产生模式。

* **结果抓取与后处理 (PPB)**：
  * `HR_ADC_readResult`：从专用结果寄存器内读出原始的高分辨率数字量。
  * `HR_ADC_setupPPB` / `HR_ADC_setPPBReferenceOffset` / `HR_ADC_readPPBResult`：完全支持与标准 ADC 相同的零时钟开销硬件后处理机制，自动完成零偏抵消、极性反转及越限保护报警。

### 23.2 典型应用场景差异提示

虽然 API 名字相同，但在实际硬件板级应用中，高分辨率 ADC 往往对应着芯片上布线更严苛、受到模拟地 (AGND) 屏蔽更优秀的特定引脚（例如部分带后缀的专用模拟管脚）。用户在使用时：
1. 必须查阅具体芯片数据手册，分清哪些 `base` 地址（如可能存在的独占型模块）属于高分辨率架构管辖。
2. 配置 `setupSOC` 采样窗宽时，由于高分辨率要求内部保持电容充放电更为彻底，建议给予比普通 ADC 略宽几个时钟周期的捕获时间。


---

## 24. HRCAP (高分辨率捕获) 模块

HRCAP (High-Resolution Capture) 模块是标准 eCAP 的增强版。普通的 eCAP 模块只能以系统主频（例如 100MHz，对应 10ns 的刻度）来捕捉时间戳。而 HRCAP 利用了类似微波延迟线（Delay-Line）的底层纯硬件技术，可以在百皮秒（ps，通常在 150ps ~ 300ps 之间）的极微观尺度上，精细测量输入脉冲的绝对时间。这在超高频数字隔离电源（如移相全桥的二次侧同步整流死区测量）和高精度激光测距、超声波流速计等领域是杀手锏。

### 24.1 开启与微延迟时钟配置

#### `HRCAP_enableHighResolution` / `HRCAP_disableHighResolution`
* **功能详细描述**：
  允许或关闭捕获模块内部的高分辨率延迟线硬件引擎。开启后，每当一个跳变沿到来，除了标准的 32 位主计数器会记下一个粗糙时间戳外，微延迟线还能捕捉到这个跳变沿“落在两次时钟滴答之间哪个具体的微小缝隙”内的细分数据（Fractional Data）。
* **返回值**：无。

#### `HRCAP_enableHighResolutionClock`
* **功能详细描述**：
  为高分辨率延迟线引擎供应特制的高频泵时钟。没有这个时钟，皮秒级的延迟线刻度盘将无法运转。在初始化时必须使能。

### 24.2 自动校准 (Calibration) 机制

由于 HRCAP 的皮秒级刻度是利用硅片内部的 CMOS 反相器传播延迟来实现的，而这个物理延迟极易受到芯片当下核心温度 (Temperature) 和供电电压 (Voltage) 波动的影响（即 PVT 漂移）。如果不加校准，测出来的皮秒数据是不准的。

#### `HRCAP_startCalibration` / `HRCAP_isCalibrationBusy`
* **功能详细描述**：
  在后台启动一次纯硬件的自我基准校准过程。硬件会利用一个绝对精准的系统主频周期（已知其长度，如 10ns）作为卡尺，去量一量当下这个瞬间，一条微延迟线到底被拉伸或缩短到了多长。
  * `startCalibration`：触发校准打火。
  * `isCalibrationBusy`：用于在等待循环中探查该过程是否结束。
* **返回值**：状态查询返回 `bool`，正忙返回 `true`。

#### `HRCAP_getScaleFactor`
* **功能详细描述**：
  当一次硬件 Calibration 完毕后，调用此函数能拿回一个核心的浮点数：**比例因子 (Scale Factor)**。这个因子就是连接“原始粗糙寄存器细分值”到“真实人类物理时间”的汇率转换桥梁。这个因子最好能在温度急剧变化时通过后台定期重测校准并更新。
* **返回值**：`float32_t`。代表比例因子的浮点数。

### 24.3 数据读取与物理时间换算

#### `HRCAP_convertEventTimeStampNanoseconds`
* **功能详细描述**：
  这是驱动库中为您封装好的“终极”数据提取公式。不需要您去手动拿主计数器的粗值和延迟线的细分值做数学拼接，它在底层直接把整帧时间数据抓出来，并乘上你传入的 `scaleFactor`（校准出来的比例因子），最终直接甩给你一个极其直观的物理真实时间消耗（以纳秒为单位，带多位小数的浮点数，比如 `23.456 ns`）。
* **参数**：
  * `base`: HRCAP 基址。
  * `event`: 你要提取事件戳的槽位（例如对应的脉冲上升沿）。
  * `scaleFactor`: 你刚刚利用 `getScaleFactor` 拿到的最新校准参数。
* **返回值**：`float32_t`，直接就是精准换算过的纳秒数。


---

## 25. HRPWM (高分辨率脉宽调制) 模块

HRPWM (High-Resolution PWM) 是叠加在普通 EPWM 模块之上的一种微型边缘定位器 (MEP, Micro-Edge Positioner)。普通的 EPWM 的占空比调节步长受限于系统主频时钟（比如 100MHz 对应 10ns 步长）。在极高频（例如几百 kHz 甚至 MHz）开关电源中，10ns 的步长会引起严重的占空比量化误差（即输出电压只能一格一格跳阶跃），从而导致输出产生低频极限环振荡 (Limit Cycle Oscillation)。
HRPWM 利用底层模拟微延迟线技术，能够将这个 10ns 的台阶硬生生切分为上百个微小台阶（通常步长约为 150ps）。这样在极高开关频率下，依然能得到平滑细腻的电压调节能力。

### 25.1 基础概念：粗值与微步长值 (MEP)

由于加入了 HRPWM，所有与时间有关的寄存器（如 CMPA 占空比、TBPRD 周期、TBPHS 相位、RED/FED 死区）均被扩充为了 32 位：
* **高 16 位**：原先的粗糙计数值（由系统时钟驱动）。
* **低 16 位**：前 8 位代表高分辨率微步长部分（由 MEP 延迟线驱动）。

#### `HRPWM_setCounterCompareValue` / `HRPWM_setHiResCounterCompareValueOnly`
* **功能详细描述**：
  配置带高分辨率的 32 位占空比比较值。
  * 完整版函数会同时装载传统的高 16 位粗值和低 16 位的高分辨率小数部分。
  * `Only` 版本常被用于极其严苛的时序内，只更新低 16 位的小数部分以节省 CPU 写入总线的时钟开销。
* **参数**：
  * `base`: EPWM 的基址（HRPWM 是依附于 EPWM 存在的）。
  * `compModule`: 比较模块（如 `HRPWM_COUNTER_COMPARE_A`）。
  * `compCount`: 32位的完整占空比设定值，格式通常为 `Q16.16`（整数部分在高16位，小数部分在低16位）。
* **返回值**：无。

#### `HRPWM_setTimeBasePeriod` / `HRPWM_setPhaseShift` / `HRPWM_setRisingEdgeDelay`
* **功能详细描述**：
  同理，除了调节占空比（比较点），HRPWM 还赋予了开发者在高频下进行**高分辨率频率调制**（改变微周期）、**高分辨率移相**（精确调节双主动桥 DAB 的极小移相角）以及**高分辨率死区微调**的能力，全方位消除了时钟离散化带来的量化噪声。

### 25.2 MEP 动作控制与缩放比例 (SFO)

在使用这套 32 位扩展值之前，必须先开启并配置好底层的微边沿发生器。

#### `HRPWM_setMEPEdgeSelect`
* **功能详细描述**：
  决定微调器究竟去精细修整 PWM 波形的哪个边沿。
  * **上升沿微调**（RED）：仅延长/缩短波形上升的那个时间点。
  * **下降沿微调**（FED）：仅修整下降时刻。
  * **双边沿微调**（Both）：高分辨率功能同时作用于上升和下降沿。
* **返回值**：无。

#### `HRPWM_setMEPControlMode`
* **功能详细描述**：
  决定刚才你写入的那些低 16 位高分辨率小数，到底是指代什么的。
  * `HRPWM_MEP_DUTY_PERIOD_CTRL`（常用）：指示这些小数值是由库里的 SFO（缩放因子优化）后台函数算出来的正规高分辨率比例。
  * `HRPWM_MEP_PHASE_CTRL`：指示这些值用于高分辨率移相。
* **返回值**：无。

#### `HRPWM_enableAutoConversion`
* **功能详细描述**：
  这是 HRPWM 的一个极其好用的功能：**硬件自动换算引擎**。
  由于 MEP 延迟线的物理步长（比如 150ps）会随芯片温度急剧改变，以前老的芯片需要在软件中断里跑非常复杂的乘除法来计算当前该填入什么数值。开启自动转换（Auto-Conversion）后，只要配合后端的 SFO 库，硬件底层乘法器会自动拿着 32 位的理想小数，乘以当前实时的 MEP 校准因子（Scale Factor），换算出应该打入几个真实的 MEP 台阶。极大释放了 CPU 的计算资源。
* **返回值**：无。

### 25.3 影子寄存器与锁定

#### `HRPWM_setCounterCompareShadowLoadEvent`
* **功能详细描述**：
  像传统 EPWM 一样，高分辨率的数值也不能在周期运行的中途胡乱修改生效。此函数指定一个安全点（例如计数器等于 0 或者等于 Period），只有在这个点到来时，硬件才会把高分辨率的小数部分平滑地刷新进工作区中，保证波形无跳变。


---

## 26. I2C (内部集成电路总线) 模块

I2C (Inter-Integrated Circuit) 模块提供了一个完全兼容飞利浦 I2C 协议规范的硬件控制器。它可以被配置为主机 (Master) 或是从机 (Slave)，支持标准模式 (100 kbps) 和快速模式 (400 kbps)，用于与各种低速外围设备（如 EEPROM、RTC 时钟、温湿度传感器以及各类显示屏）进行短距离双线（SDA 和 SCL）通信。

### 26.1 时钟与主从初始化

#### `I2C_initController` / `I2C_initControllerModuleFrequency`
* **功能详细描述**：
  在使能 I2C 通信前，必须对其极其复杂的分频网络进行校准。
  * `initControllerModuleFrequency` 是现代驱动中更推荐的封装库。你只需将当前系统的主频（`sysclkHz`，比如 100MHz）、你期望的 I2C 物理通讯速率（`bitRate`，比如 100000 即 100KHz）以及工作模式（主/从）传入，驱动库会自动在底层推算出最为贴近的 IPSC 预分频器和 ICCL/ICCH 高低电平持续时间。
* **参数**：
  * `base`: I2C 模块基址。
  * `sysclkHz`: 输入给 I2C 外设的系统时钟。
  * `bitRate`: 期望的 I2C 波特率。
  * `dutyCycle`: 指定高低电平的占空比（通常是 33% 左右高，66% 左右低）。
* **返回值**：无。

#### `I2C_setOwnAddress` / `I2C_setTargetAddress` / `I2C_setAddressMode`
* **功能详细描述**：
  * `setOwnAddress`: 当 I2C 被配置为从机 (Slave) 时，设定它自己的门牌号。当总线上主机呼叫这个地址时，硬件会自动做出 ACK 应答并触发中断。
  * `setTargetAddress`: 当 I2C 被配置为主机 (Master) 时，设定它接下来要寻呼的从机目标门牌号。
  * `setAddressMode`: 切换地址位宽，支持标准的 7 位地址（`I2C_ADDR_MODE_7BITS`）或更少见的 10 位扩展地址（`I2C_ADDR_MODE_10BITS`）。
* **返回值**：无。

### 26.2 硬件 FIFO 缓冲控制

为了不让 CPU 频繁地被单字节的收发中断打断，I2C 内部拥有独立的发送（TX）和接收（RX）硬件 FIFO（通常深度为 16 级）。

#### `I2C_enableFIFO` / `I2C_disableFIFO`
* **功能详细描述**：
  开启或彻底禁用双向硬件 FIFO。建议在搬运大量连续数据（如读写 EEPROM 页面）时务必开启以降低 CPU 负载。

#### `I2C_setFIFOInterruptLevel`
* **功能详细描述**：
  这是控制 FIFO 与 CPU 交互节拍的核心。
  你可以设定 TX FIFO 在“空余几个空位”时呼叫 CPU 来填充数据，以及 RX FIFO 在“积攒了多少个新字节”后才向 CPU 抛出读取中断。这允许 CPU 能够以块（Block）为单位来处理数据流。
* **参数**：
  * `txLevel`: 触发 TX 中断的剩余槽位下限（如 `I2C_FIFO_TX2`）。
  * `rxLevel`: 触发 RX 中断的已有数据上限。
* **返回值**：无。

### 26.3 状态机总控与报文收发

在进行 I2C 报文组装时，通常需要借助 `setConfig` 先行定义接下来这波传输是要读还是要写。

#### `I2C_setConfig` / `I2C_setDataCount`
* **功能详细描述**：
  * `setConfig`: 这是一个聚合配置函数，包含了一系列强力的动作控制位（如 `I2C_MASTER_SEND_MODE` 代表切换到主机发送态、`I2C_REPEAT_MODE` 代表无限长度重复传输态、以及极其重要的 `I2C_FREE_DATA_FORMAT` 以取消固定格式）。
  * `setDataCount`: 对于非 Repeat 模式，需要提前告诉硬件，接下来这轮物理传输一共有多少个有效数据字节。等计满后，硬件会自动挂起或发出停止位。

#### `I2C_sendStartCondition` / `I2C_sendStopCondition`
* **功能详细描述**：
  用于在物理总线上强行制造 I2C 协议中最特殊的开始 (Start, S) 与停止 (Stop, P) 边缘状态。只有发出了 Start 信号，总线上挂载的所有从机才会打起精神侦听随后的 ID 呼叫。这通常是驱动 I2C 传输链路走出的第一步。

#### `I2C_putData` / `I2C_getData`
* **功能详细描述**：
  极其底层的移位寄存器操作函数。
  * `putData`: 将要发出去的一个 8 位字节（高位通常被忽略）推入传输队列/TX FIFO。
  * `getData`: 从接收队列/RX FIFO 中拔出一个刚刚剥离出来的 8 位有效数据。

### 26.4 异常处理与总线拯救

I2C 是一种极其脆弱的总线，如果从机在传输中途死机并且恰好把 SDA 数据线死死拉低，整个总线就会彻底陷入死锁挂起（Lock-up）。

#### `I2C_isBusBusy` / `I2C_sendNACK`
* **功能详细描述**：
  * `isBusBusy`: 探测 SDA 和 SCL 引脚的真实物理电平状态。如果探测到总线长时间非空闲，即可判定发生了挂死，可以据此切入软件 GPIO 翻转拯救程序。
  * `sendNACK`: 软件主动向对端发出“不应答（NACK）”位，通常用在作为主机接收数据的最后一个字节之后，以此优雅地掐断从机的继续发送意图。

#### `I2C_enableInterrupt` / `I2C_getStatus` / `I2C_clearStatus`
* **功能详细描述**：
  配置 I2C 核心状态机抛给 CPU 的各种高级事件中断。包括但不限于：从机 NACK 未应答报错、总线仲裁丢失 (Arbitration Lost) 报错、SCD 停止条件检测中断、AAS 寻址成功中断。合理利用这些标志位可构建出极其健壮的容错机制。


---

## 27. INTERRUPT (外设中断扩展 PIE) 模块

INTERRUPT 模块封装了 C2000 芯片中极其关键的外设中断扩展 (PIE, Peripheral Interrupt Expansion) 架构。由于芯片内包含上百个可能产生中断的外设信号（如 ADC, PWM, 通信），而 CPU 核心仅暴露了 14 根物理中断请求线。PIE 控制器作为中介，将这上百个分散的中断请求分组、排队、仲裁，并最终路由给 CPU。

### 27.1 核心初始化与向量表配置

#### `Interrupt_initModule` / `Interrupt_initVectorTable`
* **功能详细描述**：
  * `initModule`: 彻底复位整个 PIE 控制器模块，将所有中断使能寄存器（PIEIER）和标志寄存器（PIEIFR）清零。这是系统刚刚开机后的首要步骤。
  * `initVectorTable`: 将位于 ROM 中的默认中断处理函数地址（或驱动库自带的安全死循环 Handler 地址）批量拷贝复制到 RAM 的 PIE 向量表（PIE RAM Vector Table）中。这样即便发生意料之外的中断，CPU 也会跳转到安全的默认函数中，而非跑飞。
* **返回值**：无。

### 27.2 中断挂接与解绑

#### `Interrupt_register` / `Interrupt_unregister`
* **功能详细描述**：
  在 C 语言层面实现硬件中断服务的“热插拔”。
  * `register`: 接收一个具体的中断号（如 `INT_ADCA1`），以及一个你自己编写的中断服务子程序 (ISR) 的函数指针。该函数会自动计算出该中断号在 RAM 向量表里的具体偏移物理地址，并将你的函数指针写进去。从而将该硬件事件与你的 C 函数成功绑定。
  * `unregister`: 解除绑定，并将该插槽恢复为指向出厂默认的 `Interrupt_defaultHandler`。
* **参数**：
  * `interruptNumber`: 定义在头文件中的全局系统中断编号。
  * `handler`: 自定义的 `void (*)(void)` 型中断处理函数入口地址。
* **返回值**：无。

### 27.3 中断的全局与个体闸门控制

要让一个外设中断最终抵达 CPU 执行，必须经过“外设自身使能 -> PIE 组使能 -> CPU 总闸使能”的三级验证。

#### `Interrupt_enable` / `Interrupt_disable`
* **功能详细描述**：
  开启或关闭 PIE 控制器内针对某一个**特定外设事件**（如 `INT_ADCA1`）的转发权限。这是最微观的闸门。
* **参数**：
  * `interruptNumber`: 具体的系统中断编号。
* **返回值**：无。

#### `Interrupt_enableGlobal` / `Interrupt_disableGlobal`
* **功能详细描述**：
  即俗称的“开全局中断 (EINT)”和“关全局中断 (DINT)”。它直接操控 CPU 核心寄存器（INTM 位）。
  * 关全局中断：常常在配置关键系统参数、或者执行严苛的读写-修改原子操作（不可被打断）前调用。
  * 开全局中断：系统配置全部就绪后，最后一步拉开总闸。
* **返回值**：`bool`。返回在调用该函数之前，全局中断原先到底是开着还是关着，方便你在原子操作后恢复原状。

### 27.4 中断应答与清零 (极其重要)

#### `Interrupt_clearACKGroup`
* **功能详细描述**：
  **这是使用 C2000 中断系统最容易踩坑的地方！**
  PIE 将所有上百个外设中断打散分为了 12 个组（Group 1 ~ Group 12）。当某个组内的任何一个中断发生并将请求成功递交给 CPU 后，PIE 硬件会自动把这个组的应答标志位（ACK）扣死闭锁。
  这意味着：在这个组的 ACK 被人为解开之前，该组内所有后续的中断请求（哪怕是同一个中断源的下一次请求）都会被 PIE 强行拦截在门外。
  因此，在你的**每一个中断服务函数 (ISR) 的最末尾**，除了要清除外设自身的标志位外，必须调用此函数传入对应的组号（如 `INTERRUPT_ACK_GROUP1`）来解锁通道，放行下一次中断。
* **参数**：
  * `group`: 对应被锁定的 PIE 分组宏。
* **返回值**：无。
* **示例代码**：
  ```c
  __interrupt void adcA1ISR(void) {
      // 1. 读取 ADC 结果...
      // 2. 清除 ADC 模块自身的中断挂起标志位
      ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
      // 3. 解除 PIE 第 1 组的闭锁，允许 CPU 继续响应 ADC 中断
      Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
  }
  ```

### 27.5 异常处理程序

#### `Interrupt_defaultHandler` / `Interrupt_illegalOperationHandler` / `Interrupt_nmiHandler`
* **功能详细描述**：
  系统内建的灾难处理死循环。
  * `defaultHandler`: 当一个意外发生但没有被 `register` 注册过的中断到来时，会掉入这里。
  * `illegalOperationHandler`: 当 CPU 取指时遇到了一段无法解码的乱码（非汇编机器码），触发非法指令中断 (ITRAP) 后进入这里。通常意味着代码指针跑飞进了数据区。
  * `nmiHandler`: 硬件不可屏蔽中断入口（例如时钟丢失、看门狗报警、RAM 奇偶校验出错）。


---

## 28. IPC (核间通信) 模块

IPC (Inter-Processor Communications) 模块是专为多核芯片（例如带有 CPU1, CPU2 以及独立通信协处理器的型号）设计的硬件通信桥梁。它能够在不共享同一套主内存的情况下，安全、高速地在不同核心之间传递标志位 (Flags)、简短命令 (Command/Response)、以及通过共享内存 (Shared RAM) 交换大数据包。

### 28.1 标志位 (Flags) 握手与同步

IPC 硬件内建了 32 个专属的单向标志位（Local to Remote，即 LtoR）。CPU1 有 32 个标志可以发给 CPU2，反之 CPU2 也有 32 个标志可以发给 CPU1。

#### `IPC_setFlagLtoR` / `IPC_clearFlagLtoR`
* **功能详细描述**：
  在本地核心（Local）强行拉高或拉低发往远端核心（Remote）的硬件标志位。这些标志位相当于挂在两个核心之间的“信号旗”。通常其中特定的几个标志位（如 Flag0 ~ Flag3）在远端是被硬接线到 PIE 中断控制器的，拉高它们就能直接打断远端 CPU 的执行。
* **参数**：
  * `ipcType`: 沟通的双方组合枚举（如 `IPC_CPU1_L_CPU2_R` 代表我是 CPU1，正向 CPU2 发信）。
  * `flags`: 要拉高的标志位掩码。
* **返回值**：无。

#### `IPC_isFlagBusyLtoR` / `IPC_ackFlagRtoL`
* **功能详细描述**：
  应答与繁忙侦测。
  * `isFlagBusyLtoR`: 本地核心发送了标志位后，调用此函数窥探该标志位是否被远端核心察觉并应答清零了。
  * `ackFlagRtoL`: 远端核心在其中断或轮询中发现有标志位竖起后，必须调用此函数进行应答（Acknowledge）。应答后，该标志位才会在硬件层面被降下。

#### `IPC_sync`
* **功能详细描述**：
  多核同时上电启动时极其常用的**屏障同步 (Barrier Synchronization)** 机制。
  当某个核心运行到此处时，它会竖起指定的标志位向对面致意，然后**死循环挂起**，一直等到对面核心也跑到了同样的同步代码处并竖起它对应的标志位后，两个核心才同时解除挂起，携手往下执行后续代码。确保多核配置时序的一致性。

### 28.2 短命令与响应 (Command & Response)

如果 32 个标志位不够表达复杂的控制意图，IPC 还准备了专属的 32 位命令寄存器和地址附加通道。

#### `IPC_sendCommand` / `IPC_readCommand`
* **功能详细描述**：
  发送/读取带参数的核间短报文。
  发送方可以在触发特定 IPC Flag 中断的同时，顺带在底层寄存器中塞入一个 32 位的指令码 (Command) 以及一个 32 位的物理内存地址 (Address，通常用来指代参数的存放地)。接收方被中断唤醒后，利用 `readCommand` 剥离出这个指令和地址进行执行。
* **返回值**：`bool`，发送或读取是否成功（未发生冲突）。

#### `IPC_sendResponse` / `IPC_getResponse`
* **功能详细描述**：
  配合 Command 的返回通道。当远端核心执行完 `readCommand` 下达的任务后，可以将处理结果状态码（32位数据）通过此接口反向回传给本地核心。

### 28.3 消息队列 (Message Queue) 大数据搬运

如果需要传上百字节的数组（如跨核传递 FFT 计算后的频谱数据阵列），单纯靠短命令是不够的。此时需要利用系统划定好的专属核间共享内存 (Message RAM)。

#### `IPC_initMessageQueue`
* **功能详细描述**：
  在共享内存区域内初始化一个基于环形 FIFO (Circular Buffer) 的消息队列结构体。定义好队列的深度、单次消息的最大字节数。必须在两个核心上对称地对同一个物理共享地址进行初始化。

#### `IPC_sendMessageToQueue` / `IPC_readMessageFromQueue`
* **功能详细描述**：
  向构建好的环形消息队列中推入一大块数据，或从队列中抽取出数据。驱动库内部自动通过原子的读写锁机制，完美解决了当 CPU1 正在往队列里写数据时，CPU2 恰好来读数据所引发的撕裂和冲突问题，开发者可将此队列视作线程安全的核间管道。


---

## 29. LIN (局部互联网络) 模块

LIN (Local Interconnect Network) 模块实现了一种低成本、单线串行的通信协议，广泛应用于汽车电子中不需要 CAN 那么高带宽的局部子系统（如车门、车窗、座椅控制）。该模块同样可以被配置为经典的 UART/SCI 模式使用。作为 LIN 使用时，它能作为主节点（Master）或从节点（Slave）处理帧头、同步段、PID 发送，并自动进行校验和（Checksum）的计算。

### 29.1 基础模式与波特率设置

#### `LIN_setLINMode`
* **功能详细描述**：
  确定该 LIN 节点在网络中的身份角色。
  * **Master (主节点)**：掌握总线的话语权。负责主动发起通信，先发送一个极其独特的长低电平 Break 唤醒信号，随后发送同步段，并发出目标从机的 ID。
  * **Slave (从节点)**：被动侦听。只有当侦听到 Master 发出了与自身匹配的 ID 后，才开始往总线上填充应答数据或者收取数据。
* **参数**：
  * `base`: LIN 模块基地址。
  * `mode`: `LIN_MODE_LIN_MASTER` 或 `LIN_MODE_LIN_SLAVE`。
* **返回值**：无。

#### `LIN_setBaudrate`
* **功能详细描述**：
  设置 LIN 通信的波特率。函数内部会根据你传入的系统时钟（Clock）和期望波特率（Baud），自动推算出 24 位的分频器寄存器（BRSR）的整数与小数部分。标准的 LIN 波特率通常最高不超过 20 kbps。
* **返回值**：无。

#### `LIN_enableAutomaticBaudrate` / `LIN_disableAutomaticBaudrate`
* **功能详细描述**：
  针对**从节点**的黑科技。开启此功能后，从节点不再需要预先知道主节点的确切波特率。当主节点发出同步段（Sync Field，固定为 `0x55`）时，从机的硬件会自动测量两个脉冲沿之间的物理时间，从而精准锁定并自动调节自身的波特率以与主节点咬合。

### 29.2 数据帧配置与收发

LIN 的一帧数据包含了：Break -> Sync -> ID -> Data(0~8 bytes) -> Checksum。

#### `LIN_setIDByte` / `LIN_setFrameLength` / `LIN_setChecksumType`
* **功能详细描述**：
  在发送数据前，准备帧结构。
  * `setIDByte`: 填入你要寻址的子节点 ID（0~63）。硬件会自动在最高两位算出并附加奇偶校验位形成最终的 PID 发送出去。
  * `setFrameLength`: 设定紧随 ID 之后的数据长度（通常为 1 到 8 个字节）。
  * `setChecksumType`: LIN 协议分为 1.x 版本的经典校验（Classic，仅校验数据区）和 2.x 版本的增强校验（Enhanced，连带 PID 一起校验）。通信双方必须一致。
* **返回值**：无。

#### `LIN_enableDataTransmitter` / `LIN_enableDataReceiver`
* **功能详细描述**：
  控制硬件内部底层状态机的方向。当作为主节点发起命令要求从节点回复数据时，主节点打出 ID 后应立刻使能 Receiver 准备收数；反之如果是往外写数据，则使能 Transmitter。

#### `LIN_isTxReady` / `LIN_isRxReady` / `LIN_isBusBusy`
* **功能详细描述**：
  状态探查。询问底层的缓冲 FIFO 阵列是否已经把你要发的数据全部串行推了出去，或者是否已经完整接收到了设定长度的一帧有效数据并存放好了。

### 29.3 休眠、唤醒与低功耗

由于 LIN 通常连接汽车电池并需要常驻待机，因此休眠唤醒机制是协议的核心。

#### `LIN_enterSleep`
* **功能详细描述**：
  命令该 LIN 节点模块进入极低功耗的休眠监听模式。此时它停止常规的波特率时钟运转，仅保留总线边沿触发唤醒逻辑。

#### `LIN_sendWakeupSignal`
* **功能详细描述**：
  作为主节点或从节点，强行向寂静的物理总线上输出一个持续的显性（低电平）唤醒脉冲。以此把总线上所有处于休眠状态的节点“踢醒”，让大家恢复到正常的收发准备态。

### 29.4 中断与错误处理

#### `LIN_enableInterrupt` / `LIN_interruptEnable` / `LIN_clearPendingFlags`
* **功能详细描述**：
  LIN 模块可以针对诸多细微的协议级事件抛出中断请求。包含：成功收到一帧数据（RX）、发送完成（TX）、收到唤醒信号（Wakeup）、自动波特率同步出错（Sync Error）、校验和不匹配出错（Checksum Error）、甚至物理总线死锁报错。
  开启这些中断后，CPU 可以游刃有余地在后台维护一张车内设备的节点存活状态表。


---

## 30. PGA (可编程增益放大器) 模块

PGA (Programmable Gain Amplifier) 是集成在芯片内部的纯模拟前端调理模块。它主要用于在微弱的模拟信号（如电机相电流经过毫欧级采样电阻产生的微小压降）进入 ADC 采样或 CMPSS 比较之前，对其进行纯硬件的模拟放大和低通滤波。利用内置的 PGA，用户可以省去外部昂贵的运算放大器电路，直接将分流器（Shunt）接入芯片引脚。

### 30.1 模块使能与增益设置

#### `PGA_enable` / `PGA_disable`
* **功能详细描述**：
  开启或关闭 PGA 模块的内部模拟供电。上电默认状态下为了节约功耗，PGA 是被禁用的（处于高阻态穿透或者关断模式）。使用前必须使能，并在调用后稍微给出一个微小的延时让内置运放的工作点稳定下来。
* **参数**：
  * `base`: PGA 模块的基地址（例如 `PGA1_BASE`）。
* **返回值**：无。

#### `PGA_setGain`
* **功能详细描述**：
  这是 PGA 的核心功能：动态配置闭环放大倍数。
  内置运放带有可编程的精密反馈电阻网络。通过此函数，可以非常方便地将信号放大指定的倍数。常用的增益档位包括：3倍、6倍、12倍和24倍。你甚至可以在软件运行途中根据电流大小动态切档（比如小电流用24倍，大电流用3倍以防饱和）。
* **参数**：
  * `base`: PGA 基址。
  * `gainValue`: 目标增益倍数枚举（如 `PGA_GAIN_3`, `PGA_GAIN_24`）。
* **返回值**：无。
* **示例代码**：
  ```c
  // 开启 PGA1 并将其增益配置为放大 12 倍
  PGA_enable(PGA1_BASE);
  PGA_setGain(PGA1_BASE, PGA_GAIN_12);
  ```

### 30.2 硬件低通滤波 (Low-Pass Filter)

PGA 放大后的信号在送往内部的 ADC 之前，会经过一个片上的单极点 RC 低通滤波器，用于滤除极其高频的开关噪声毛刺。

#### `PGA_setFilterResistor`
* **功能详细描述**：
  由于 RC 滤波器中的电容是固定的内置寄生或小电容，你能调节的是串联在其路径上的电阻值。此函数允许你切换几档不同的电阻（从而改变低通滤波的截止频率带宽）。你可以选择完全短路该电阻（不滤波以追求极限的高频响应速度），或者是串入几百欧姆以获得平滑的电流包络。
* **参数**：
  * `resistorValue`: 滤波电阻阻值选项（如 `PGA_LOW_PASS_FILTER_RESISTOR_200_OHM` 等）。
* **返回值**：无。

### 30.3 版本获取与安全锁定

#### `PGA_getPGARevision` / `PGA_getPGAType`
* **功能详细描述**：
  读取硅片内部硬编码的 PGA 模块硬件设计版本号和类型标识，常用于固件在不同批次或不同后缀型号芯片间的兼容性自适应判断。

#### `PGA_lockRegisters`
* **功能详细描述**：
  同其他模拟模块一样，PGA 提供了写保护死锁机制。
  一旦系统初始化定好增益后，强烈建议调用此函数锁死 PGA 的控制寄存器，防止软件跑飞意外改动了放大倍数导致后续算法算出致命的超大电流从而误报警跳闸。
* **返回值**：无。


---

## 31. PMBus (电源管理总线) 模块

PMBus (Power Management Bus) 是 I2C 的一个极其严谨的超集，专为数字电源转换器和管理芯片（如开关电源、电池管理单元、电压调节模块 VRM）设计。C2000 的 PMBus 模块在硬件底层直接集成了复杂的超时机制 (Time-out)、PEC（包错误校验）自动计算与校验，以及对 Alert（警报）引脚的硬件级支持，完全免去了用纯 I2C 软件模拟这些苛刻时序的负担。

### 31.1 工作模式与协议初始化

#### `PMBus_enableI2CMode` / `PMBus_disableI2CMode`
* **功能详细描述**：
  将 PMBus 模块切换为兼容普通标准 I2C 的工作模式，或者彻底开启 PMBus 专有的协议机（例如处理带有命令字 Command Code 和 PEC 尾巴的事务）。如果你的系统里普通 I2C 模块不够用了，你可以把 PMBus 降级当做普通 I2C 凑数。
* **返回值**：无。

#### `PMBus_configController` / `PMBus_initTargetMode`
* **功能详细描述**：
  * `configController`: （在旧版本协议中称为 Master）将该节点配置为主控制器。它允许你设定即将发起的报文字节数、是否要硬件附加/校验 PEC，以及设定目标从机的门牌号。
  * `initTargetMode`: （在旧版本协议中称为 Slave）配置自己作为从节点。你需要设定自己的自身地址以及一个地址掩码（Mask，用来允许响应广播地址或者一个地址组）。
* **返回值**：无。

#### `PMBus_configModuleClock` / `PMBus_configBusClock`
* **功能详细描述**：
  与 I2C 类似，通过填入系统主频，自动配置内部的模块基础时钟，然后再配置物理总线时钟。PMBus 协议有着严格的 100KHz 或 400KHz 标准规范，且规定了严格的 Clock Low Timeout（如果某方把时钟拉低超过 35ms 不放，必须被视作死机）。这两个函数在底层会自动配置好这些时钟及硬件超时探测器。

### 31.2 事务处理与警报 (Alert)

#### `PMBus_assertAlertLine` / `PMBus_deassertAlertLine`
* **功能详细描述**：
  PMBus 物理层不仅有 SDA 和 SCL，还有一根独立的 PMB_ALERT 引脚。
  当作为电源 Target（从机）检测到过压过流时，不要苦等主机来轮询你，直接调用 `assertAlertLine` 将物理警报线拉低。主机收到警报后，会利用特殊的 ARA（警报响应地址）进行广播寻呼，你再通过回复自己的 ID 来告诉主机是你这里出问题了。
* **返回值**：无。

#### `PMBus_ackTransaction` / `PMBus_nackTransaction`
* **功能详细描述**：
  手动应答控制。当 Target 收到数据后，硬件会挂起时钟（Clock Stretching），给你时间让 CPU 判断这笔数据（比如一条更改输出电压的指令）是否合法。如果合法，调用 `ack` 吞下数据；如果不合法或者校验出问题，调用 `nack`，硬件立刻向主机打出一个拒收信号。

### 31.3 数据搬运与 PEC 保护

#### `PMBus_putControllerData` / `PMBus_putTargetData`
* **功能详细描述**：
  将需要发送的数据块一次性填入发送队列。如果是发送，且配置了 `txPEC = true`，硬件会自动基于多项式 `C(x) = x^8 + x^2 + x^1 + 1` 算出 PEC 校验字节，并毫无违和感地把它缝合在你的最后一个数据字节之后发出去。
* **参数**：
  * `buffer`: 待发数组指针。
  * `nBytes`: 有效字节数。
* **返回值**：无。

#### `PMBus_verifyPEC` / `PMBus_generateCRCTable`
* **功能详细描述**：
  提供软件辅助的 PEC 校验能力。虽然硬件常常能自动完成，但在一些特殊极端的接收流中（比如混合了未知长度格式的变长 Block Read），你可能需要调用 `verifyPEC` 拿着接收缓冲和查表数组来手动判定这帧包的数字尾巴是否有效无损。


---

## 32. SCI (串行通信接口) 模块

SCI (Serial Communications Interface) 模块是最基础、最通用的两线制（TX 和 RX）异步串行总线接口，完全兼容标准的 UART 协议规范。在嵌入式系统中，SCI 最常用于通过转换芯片（如 CH340 或 MAX3232）与 PC 电脑的串口助手进行打印调试（`printf`），或者与外部模块（如蓝牙、WiFi 模块、旧式触摸屏）进行全双工数据交互。

### 32.1 波特率与帧格式配置

#### `SCI_setConfig` / `SCI_setBaud`
* **功能详细描述**：
  * `setConfig`: SCI 初始化的核心枢纽。它接受系统低速外设时钟（LSPCLK）、你期望的波特率（如 115200 或 9600），以及数据帧格式（Config 位掩码）。此函数在底层会自动计算出波特率发生器的分频寄存器值（BRR）。Config 参数通常由数据位（5~8位）、奇偶校验（无/奇/偶）和停止位（1或2位）组合而成。最经典的电脑端串口配置宏组合为：`SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE | SCI_CONFIG_PAR_NONE`（即 8-N-1）。
  * `setBaud`: 仅用于在运行途中热切换波特率，而不改动帧格式。
* **返回值**：无。

#### `SCI_setParityMode`
* **功能详细描述**：
  单独更改奇偶校验的模式。

### 32.2 硬件 FIFO 缓冲控制

普通 SCI 在每次收到 1 个字节或者发完 1 个字节后都会触发中断，这在 115200 甚至更高的波特率下会使 CPU 陷入严重的中断风暴。因此，C2000 的 SCI 均标配了 16 级深度的发送和接收 FIFO。

#### `SCI_enableFIFO` / `SCI_disableFIFO`
* **功能详细描述**：
  开启或关闭硬件级别的 16 级深度 FIFO。开启后，发送和接收的阈值逻辑将接管传统的单字节中断逻辑。

#### `SCI_setFIFOInterruptLevel`
* **功能详细描述**：
  配置触发 CPU 中断的 FIFO 积水线阈值。
  例如，设置 RX 阈值为 `SCI_FIFO_RX8`，那么外部发来的前 7 个字节都只会静静地躺在 RX FIFO 中，不会打扰 CPU，直到第 8 个字节到达填满了半个 FIFO 时，硬件才会向内核抛出一个大中断。CPU 进入中断后直接一个 `for` 循环连续掏出 8 个字节，极大提高了效率。
* **参数**：
  * `base`: SCI 模块基址。
  * `txLevel`: TX FIFO 触发下限阈值。
  * `rxLevel`: RX FIFO 触发上限阈值。
* **返回值**：无。

#### `SCI_resetTxFIFO` / `SCI_resetRxFIFO`
* **功能详细描述**：
  软件强行清空硬件 FIFO。通常用在检测到帧尾协议不对，或者是发生奇偶校验/溢出错误时，清空已经收到的一堆“脏数据”，重头开始侦听。

### 32.3 单字符/多字符阻塞与非阻塞收发

驱动库提供了极其丰富的数据搬运 API，分为带 FIFO/不带 FIFO，以及阻塞（Polling 死等）和非阻塞三种维度。

#### `SCI_writeCharBlockingFIFO` / `SCI_readCharBlockingFIFO`
* **功能详细描述**：
  **带阻塞的发送/读取**：
  * `write`: 尝试把一个字节塞进 TX FIFO。如果当前 TX FIFO 已经被塞满了 16 个字，此函数会**死等（阻塞）**在这个语句里，直到数据线发走了一个字腾出空位，塞进去后才返回。
  * `read`: 尝试从 RX FIFO 中读取一个字节。如果 FIFO 此时是空的，此函数会**死等（阻塞）**，直到有新数据真正来到引脚并进入 FIFO 才会返回。
* **返回值**：`read` 返回低 8 位包含有效数据的 `uint16_t`。

#### `SCI_writeCharNonBlocking` / `SCI_readCharNonBlocking`
* **功能详细描述**：
  **非阻塞收发**：
  * `write`: 尝试发送一个字节，如果缓冲满了塞不进去，它不会等，而是直接丢弃该字节并立刻返回 `false` 给 CPU。
  * `read`: 尝试读，如果没数据，立刻返回特定错误码或退出，绝对不会卡死系统。通常在没有任何 RTOS 调度的裸机主循环里（或状态机轮询时）使用。

#### `SCI_writeCharArray` / `SCI_readCharArray`
* **功能详细描述**：
  高级封装。在底层调用阻塞 API，用于一次性将一个连续的字符串或数组顺次推给 SCI 外设发走，是最基础的 `printf` 底层支撑函数。
* **参数**：
  * `array`: 指向要发送/存放的 `uint8_t` 数组。
  * `length`: 数组的字节数。
* **返回值**：无。

### 32.4 状态获取与多处理器模式

#### `SCI_getRxStatus` / `SCI_clearOverflowStatus`
* **功能详细描述**：
  用于在发生中断后提取详细的错误报告。如帧错误（Framing Error，没收到停止位）、溢出错误（Overrun Error，RX FIFO 已经满了但 CPU 没来拿，新的数据又冲进来了，导致旧数据被覆盖）。
* **返回值**：`getRxStatus` 返回包含各种错误位的掩码。

#### `SCI_setAddrMultiProcessorMode` / `SCI_setIdleMultiProcessorMode`
* **功能详细描述**：
  开启多处理器总线协议（类似 RS-485 模式下挂载多个单片机）。在唤醒位（Address/Idle）匹配前，硬件会自动屏蔽正常的 RX 数据进入 FIFO，从而在总线群聊中降低无关 CPU 的打断率。


---

## 33. SDFM (Σ-Δ 滤波器模块) 模块

SDFM (Sigma-Delta Filter Module) 是专为解码外部隔离型 Sigma-Delta 调制器（例如 AMC130x 系列、光耦隔离放大器）发出的高频 1-bit 数据流而设计的硬件模块。它通过硬件实现多路并行的 Sinc (正弦) 滤波器，能够同时输出用于闭环控制的**高精度采样数据 (Data Filter)** 以及用于极速短路保护的**低延迟比较器报警 (Comparator Filter)**，是现代高压大功率数字电源和电机驱动中实现跨隔离带电流/电压采集的最佳方案。

### 33.1 数据滤波器 (Data Filter) 配置

数据滤波器旨在滤除高频量化噪声，还原出高精度（最高可达 32 位分辨率）的真实模拟物理量。

#### `SDFM_configDataFilter` / `SDFM_configDataFilterFIFO`
* **功能详细描述**：
  配置主数据滤波器。你需要选择 Sinc 滤波器的阶数（通常可选 Sinc1, Sinc2, Sinc3 或 SincFast）。阶数越高，滤波效果越好，但群延迟也越长。接着配置过采样率（OSR, Over-Sampling Ratio，如 64、128 或 256），OSR 决定了最终数据的位宽和分辨率。如果系统需要连续采样，可以使用 `FIFO` 版本函数，它会在底层自动启用 16 级深度的 FIFO。
* **参数**：
  * `base`: SDFM 基址。
  * `config1` / `config2`: 包含 Sinc 阶数、OSR、数据位宽（16位或32位）的宏组合。
* **返回值**：无。

#### `SDFM_getFilterData` / `SDFM_getFIFOData`
* **功能详细描述**：
  在数据准备就绪中断中，从 SDFM 模块读取经过完整 Sinc 滤波的数字量。此数据往往被转换为有符号整数（16/32 位）后，直接送入 PID 调节器作为电流或电压的反馈。

### 33.2 比较滤波器 (Comparator Filter) 与极速保护

除了上述为了高精度而存在延迟的数据滤波器外，SDFM 内部还并行存在一套低精度但响应极其迅速的短滤波器。

#### `SDFM_configComparator`
* **功能详细描述**：
  配置并行的比较滤波器。通常选用阶数较低的 Sinc（如 Sinc3）和非常小的 OSR（如 16 或 32），以此换取极低的延迟（通常在 1~2 微秒内）。然后设置高/低报警阈值。一旦总线电流发生极其猛烈的突变（短路），短滤波器算出的粗糙值会瞬间撞破该阈值。
* **返回值**：无。

#### `SDFM_setCompFilterHighThreshold` / `SDFM_setCompFilterLowThreshold`
* **功能详细描述**：
  为主比较器设定警戒天花板和地板。当电流波形超出这一窗宽时，SDFM 会立刻通过芯片内部专用的连线网（X-BAR）直接将跳闸电平甩给 EPWM 的 TZ 模块，瞬间切断栅极脉冲以保护 IGBT/SiC 不被炸毁。这个过程无需任何 CPU 参与。

### 33.3 零交叉检测 (Zero-Cross)

#### `SDFM_enableZeroCrossEdgeDetect` / `SDFM_setCompFilterZeroCrossThreshold`
* **功能详细描述**：
  用于并网逆变器中捕捉交流电（AC）过零点。配置一个零点阈值窗，当信号跨越此窗口时，硬件会自动探测边沿并生成零交叉中断。大大简化了软件 PLL 锁相环的计算压力。

### 33.4 PWM 同步与触发采存

由于 Sigma-Delta 是连续发波的，为了避免在开关管硬切断瞬间采集到电磁振铃，必须和 PWM 同步采集。

#### `SDFM_setPWMSyncSource` / `SDFM_enableWaitForSync`
* **功能详细描述**：
  将 SDFM 的滤波器状态机与具体的 EPWM 同步信号挂钩。
  当开启 WaitForSync 模式后，SDFM 内部的滤波器在等待下一个 PWM 同步脉冲（Sync）到来之前，会一直处于“按兵不动”的状态。直到 Sync 脉冲到达，滤波器内部的积分器才被清零并立刻开始一轮全新的干干净净的积分计算，确保最终输出的值是严格在 PWM 周期特定相位内累积出的平均值。
* **返回值**：无。


---

## 34. SPI (串行外设接口) 模块

SPI (Serial Peripheral Interface) 是最常用的高速同步串行通信协议。它通常使用四根线（MOSI, MISO, SCK, CS）进行全双工通信。在 C2000 中，SPI 常被用于与高频外部 ADC（如解析旋变传感器用的高精度 ADC）、高速外部 Flash、显示屏驱动以及其他微控制器进行大数据量的板级交互。

### 34.1 核心协议与波特率配置

#### `SPI_setConfig`
* **功能详细描述**：
  一键初始化 SPI 核心协议机的神级函数。你可以在这里定义：
  * 主/从模式（Master or Slave）。
  * 传输协议时序（`protocol`）：包含了至关重要的极性（Polarity）与相位（Phase）。SPI 共有 4 种标准的模式（Mode 0 ~ Mode 3）。比如 `SPI_PROT_POL0PHA0` 意味着时钟平时为低，在第一个上升沿采样数据。**这一项必须与你要连接的外设芯片手册严格对齐，错一位数据就全错。**
  * 波特率（`bitRate`）：硬件最高支持将 LSPCLK 2 分频作为最大时钟频率（例如 50MHz LSPCLK 下，最高能跑到 25MHz 的 SPI 波特率）。
  * 传输位宽（`dataWidth`）：SPI 每次发送的包不一定是 8 位的字节。你可以配置为 1~16 位之间的任何数字。比如驱动很多奇葩的 12 位或 14 位 DAC/ADC 时，直接在这里填入 12 或 14 即可自动对齐，极大简化了软件移位操作。
* **返回值**：无。

#### `SPI_setBaudRate` / `SPI_setcharLength`
* **功能详细描述**：
  在不打断总协议框架的情况下，动态修改波特率或者单次收发的位宽。常常用在同一个主 SPI 接口分时复用连接了几个不同型号的外设（比如一边接低速 8 位 EEPROM，另一边接高速 16 位 ADC）的场景，切换片选（CS）前调用此函数重置硬件收发窗。

### 34.2 硬件 FIFO 与缓冲管理

同 SCI 类似，SPI 也配备了极其好用的 16 级深度 FIFO。尤其是 SPI 速度极快（几十 MHz），开启 FIFO 批量收发几乎是必须的。

#### `SPI_enableFIFO` / `SPI_disableFIFO`
* **功能详细描述**：
  接管传统的单字收发标志位逻辑，切入带有积水线阈值的 FIFO 工作模式。

#### `SPI_resetTxFIFO` / `SPI_resetRxFIFO` / `SPI_reset`
* **功能详细描述**：
  在遭遇通信同步丢失（例如从机没上电导致主机发出去读回来的全是乱码 `0xFF`）时，调用此函数将底层收发移位寄存器及 FIFO 阵列彻底排空复位。

### 34.3 基础阻塞与非阻塞读写 (针对 16 位及以内)

#### `SPI_writeDataBlockingFIFO` / `SPI_readDataBlockingFIFO`
* **功能详细描述**：
  如果你开启了 FIFO 并且不打算用中断（纯裸机死等），这是最常用的 API。
  * `write`: 把数据塞入 TX FIFO。如果满了就卡在这等。
  * `read`: 去 RX FIFO 掏数据。如果空了就卡在这等它收到为止。

#### `SPI_writeDataNonBlocking` / `SPI_readDataNonBlocking`
* **功能详细描述**：
  绝不卡死的非阻塞收发。即使当前没有数据，`read` 也会立即返回一个 0 或错误码，这在带有实时 RTOS 调度或者高频控制主循环里必须使用，以防止某个 SPI 外设死机拉垮了整个电机的控制周期。

### 34.4 高级长字节事务传输 (大于 16 位)

很多工业级的绝对值编码器（如 Tamagawa）或者隔离驱动芯片，一次 SPI 交换的数据包长达 24 位甚至 32 位。而 C2000 的 SPI 单次最大只能配置 16 位。为此，TI 提供了一组拼接传输的封装函数。

#### `SPI_transmit24Bits` / `SPI_transmit32Bits` / `SPI_receive24Bits` / `SPI_receive32Bits`
* **功能详细描述**：
  它们在底层自动将长达 32 位的输入数据截断成两个 16 位的片段，或者将 24 位截断成一个 16 位和 8 位的片段。然后巧妙地利用 TX FIFO 连续推入这些片段，最后在接收端又自动拼装回一个 `uint32_t` 类型的长整型给你。完全掩盖了硬件最高只支持 16 位的限制。

#### `SPI_pollingFIFOTransaction`
* **功能详细描述**：
  极其强大的块交换函数。你可以直接丢给它一个发送数组指针和接收数组指针，以及你要交换的长度。函数内部会通过轮询 FIFO 的方式，帮你一口气把整块数据通过 SPI 顶出去，同时把回流的数据按序填入你的接收数组。这是实现简单驱动模块（如读写整个 SPI Flash 扇区）的最佳选择。

### 34.5 特殊工作模式

#### `SPI_enableTriWire`
* **功能详细描述**：
  开启 3 线制 SPI 模式。这是一种特殊的半双工模式，MOSI 和 MISO 引脚会在芯片内部短接到一起，只通过一根数据线（外加时钟和片选）来分时收发。多用于省引脚的小体积传感器。

#### `SPI_enableLoopback`
* **功能详细描述**：
  开启硬件自测回环。芯片内部直接将 TX 引脚短接到 RX 引脚。在没有外接真实 SPI 从机的情况下，可用来自己发数据给自己，验证波特率配置、中断逻辑以及 DMA 搬运路径是否通畅。


---

## 35. SYSCTL (系统控制) 模块

SYSCTL (System Control) 是掌控整个芯片生命动脉的顶级模块。它不仅掌管着最为关键的 PLL 倍频器与时钟树分布，同时还统领着各外设的时钟门控、外设软复位、看门狗定时器 (Watchdog)、掉电/休眠模式管理以及负责拦截致命硬件错误的不可屏蔽中断 (NMI)。在 `main` 函数的第一句，通常就是调用此模块的 API。

### 35.1 时钟树核心配置 (PLL)

#### `SysCtl_setClock`
* **功能详细描述**：
  整个系统上电后的核心引爆点。通过传入一个高度整合的 Config 宏掩码，它可以一次性为你完成：
  1. 选择主时钟源（内部 10MHz 振荡器 INTOSC 或外部晶振 XTAL）。
  2. 启动并锁定 PLL 锁相环（配置整数/小数倍频器）。
  3. 配置系统时钟分频器（SYSCLKDIV），最终压出目标主频（如 100MHz）。
  此函数内部包含了极其严谨的 PLL 锁定等待和旁路切换安全机制，用户绝对不可尝试手工改写 PLL 寄存器。
* **参数**：
  * `config`: 时钟树配置宏组合，例如 `(SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(20) | SYSCTL_SYSDIV(2))` 将 10M 外部晶振倍频为 100MHz 系统主频。
* **返回值**：`bool`，如果检测出 PLL 由于硬件故障无法锁定，将返回 `false` 供软件进入安全降级模式。

#### `SysCtl_setLowSpeedClock` / `SysCtl_getClock`
* **功能详细描述**：
  * `setLowSpeedClock`: 配置低速外设时钟（LSPCLK）的分频比。LSPCLK 通常是供给 SCI、SPI 这种低速串口通讯使用的，通常默认配置为 SYSCLK 的 4 分频。
  * `getClock`: 反向推导函数。根据你配置的晶振频率，它能动态读取当前的 PLL 寄存器，算出当下实时的系统主频。常被当作参数喂给其他外设的初始化函数（如 I2C 或 UART）。

### 35.2 外设时钟门控与模块复位

为了极大地降低功耗，C2000 的所有外设在复位后其内部时钟都是**默认被掐断**的。

#### `SysCtl_enablePeripheral` / `SysCtl_disablePeripheral`
* **功能详细描述**：
  打通或掐断通往某一具体外设（如 `SYSCTL_PERIPH_CLK_EPWM1`）的 PCLKCR 时钟树。**注意：在调用任何外设（如 ADC、EPWM）的配置函数前，必须首先调用此函数为其供电供时钟，否则访问该外设的寄存器将直接导致 CPU 总线挂死。**

#### `SysCtl_resetPeripheral`
* **功能详细描述**：
  当某个外设状态机卡死或者需要彻底重置时，不用全盘重启芯片，调用此函数可以直接对某个特定外设（如 `SYSCTL_PERIPH_RES_I2CA`）执行精准的硬件软复位，清空其所有寄存器并恢复到出厂默认态。

### 35.3 看门狗 (Watchdog) 保护

#### `SysCtl_enableWatchdog` / `SysCtl_serviceWatchdog` / `SysCtl_setWatchdogMode`
* **功能详细描述**：
  * `setWatchdogMode`: 配置看门狗超时后的惩罚手段。是直接让整个芯片硬复位（Reset Mode，最安全），还是只向 CPU 发送一个 NMI 中断（Interrupt Mode，通常用于在死机前保存紧急现场数据）。
  * `serviceWatchdog`: 俗称“喂狗”。必须在主循环中定期调用，重置其内置的 8 位递增计数器。一旦程序跑飞（如卡死在某个 While 循环），未能及时喂狗导致计数器溢出，看门狗便会实施上述惩罚。

### 35.4 时钟丢失检测与不可屏蔽中断 (NMI)

这涉及到极端严苛的汽车级/工业级功能安全规范。

#### `SysCtl_enableMCD` / `SysCtl_isMCDClockFailureDetected`
* **功能详细描述**：
  使能时钟丢失检测器（Missing Clock Detection）。开启后，硬件会利用另一个独立的内部振荡器偷偷监视系统当前的外部晶振（XTAL）。如果在强电磁干扰下一旦发生晶振停振，MCD 硬件会立刻自动将系统时钟切回内部备用振荡器，避免死机，并同时抛出 NMI 中断报警。

#### `SysCtl_enableNMIGlobalInterrupt` / `SysCtl_getNMIStatus`
* **功能详细描述**：
  不可屏蔽中断（NMI）是比普通中断拥有绝对优先权的警报。它用于拦截致命故障，如：看门狗超时、MCD 测得时钟丢失、Flash 纠错出现不可修复的位翻转等。即使 CPU 屏蔽了全局中断，NMI 也能强行打断 CPU，强制其进入 `nmiHandler` 执行挽救或安全停机程序。


---

## 36. XBAR (交叉开关矩阵) 模块

XBAR (Crossbar) 模块是 C2000 芯片极具特色和灵活性的纯硬件数字信号路由网络。它就像早期的电话总机交换机，允许你将芯片内部几乎任何外设的输出信号（如比较器 CMPSS 跳闸信号、ADC 转换完成信号）甚至外部 GPIO 引脚的状态，不经过 CPU 直接用纯硬件导线动态连通到其它外设的输入端（如 EPWM 错误封锁引脚、外部中断源 XINT）。由于是纯硬件逻辑门连接，其延迟在纳秒级别，是实现功能安全和极限性能控制的骨架。

XBAR 宏观上分为三大独立网络：**Input XBAR（输入交叉开关）**、**Output XBAR（输出交叉开关）** 以及 **ePWM XBAR（PWM 专用交叉开关）**。

### 36.1 Input XBAR (输入交叉开关)

专门负责将芯片外部物理引脚（GPIO）捕捉到的数字信号，路由分发给芯片内部的各大外设。

#### `XBAR_setInputPin`
* **功能详细描述**：
  将任意一个物理 GPIO 管脚映射到内部逻辑的 `InputX` 节点上。比如，你可以将 GPIO15 映射为 `XBAR_INPUT1`，然后把这个 `XBAR_INPUT1` 作为信号源喂给外部中断（XINT）、eCAP 捕获模块，甚至是 ADC 的外部触发源。它打破了传统单片机外设功能必须死绑在固定管脚上的限制。
* **参数**：
  * `input`: 内部逻辑节点，如 `XBAR_INPUT1` 到 `XBAR_INPUT16`。
  * `pin`: 物理 GPIO 引脚编号（如 15）。
* **返回值**：无。

### 36.2 Output XBAR (输出交叉开关)

专门负责将芯片内部众多外设（比如 CMPSS 比较器、ADC 阈值越限标志、CPU 定时器溢出）产生的内部报警或同步信号，通过复用矩阵路由到芯片物理 GPIO 管脚上，向芯片外部（如外部驱动 IC 或故障记录仪）输出。

#### `XBAR_setOutputMuxConfig` / `XBAR_enableOutputMux`
* **功能详细描述**：
  配置 Output XBAR 的连线。
  * `setOutputMuxConfig`: 选择你要将哪一个内部信号源（比如 `XBAR_OUT_MUX01_CMPSS1_CTRIPH` 代表 CMPSS1 高侧比较器的跳闸信号）接到特定的输出大通道（如 `XBAR_OUTPUT1`）的那个MUX输入端上。
  * `enableOutputMux`: 打通这个特定的 MUX 通道，让信号真实流过。最后再配置对应的 GPIO 为 XBAR_OUTPUT1 功能即可将信号送出。
* **返回值**：无。

#### `XBAR_setOutputLatchMode` / `XBAR_clearOutputLatch`
* **功能详细描述**：
  很多内部报警信号（如 ADC 的偶然超限）可能只是个持续几十纳秒的极短尖刺。外部设备根本捕捉不到。此函数可在 XBAR 路由末端开启一个硬件锁存器（Latch）。一旦尖刺到来，输出引脚会被硬生生锁在高电平（或者低电平），直到 CPU 确认后调用 `clearOutputLatch` 才会松开。

### 36.3 ePWM XBAR (ePWM 专用交叉开关)

这是专为电机控制与数字电源打造的子网络。它负责把内部的各种灾难报警信号（主要是 CMPSS 比较器）快速汇总、逻辑组合（OR 门），然后直接砸给 EPWM 模块的 TZ（Trip Zone）引脚去封锁发波。

#### `XBAR_setEPWMMuxConfig` / `XBAR_enableEPWMMux`
* **功能详细描述**：
  高度类似于 Output XBAR 的配置过程，只不过它的目的地终点不是物理管脚，而是通往各大 EPWM 模块内部的跳闸信号源（如 TRIP4, TRIP5, TRIP7...）。你可以通过 MUX 极其灵活地配置：只有当 CMPSS1_High 或 CMPSS2_High 任意一个发生过流时，才触发 TRIP4 去关闭 EPWM1。
* **返回值**：无。

#### `XBAR_invertEPWMSignal` / `XBAR_invertOutputSignal`
* **功能详细描述**：
  如果在连线的最后一步，发现硬件信号极性与目标所需的极性相反（比如比较器送出的是高电平报警，而外部驱动芯片需要低电平断电），调用该函数即可在路由的末端硬件反相，省去外接非门的麻烦。

### 36.4 安全锁定

#### `XBAR_lockInput` / `XBAR_lockOutput` / `XBAR_lockEPWM`
* **功能详细描述**：
  锁死整个 XBAR 的路由矩阵。XBAR 掌管着极其危险的过流过压封锁信号网。一旦系统初始化连线完毕，强烈建议调用这些函数，将对应的配置寄存器彻底置为只读。以防软件越界跑飞后把比较器的保护网给“拔线”了，导致真正的灾难。锁定后直到芯片下一次硬重启前无法解开。

