#### 文件所有：STARRYSTONETECH

#### 文件名称：canfd_ex5_fifo_demo

#### 适用芯片：TMS320F280049/TMS320F280048

#### 功能说明：

此例程用于演示 F28004x CAN 模块的硬件 FIFO 功能，主要展示以下特性：

- 16 槽位 STB（Secondary Transmit Buffer）FIFO 批量发送
- 16 槽位 RB（Receive Buffer）FIFO 接收处理
- FIFO 发送模式（TSMODE=0，先进先出，非 ID 优先级）

#### 使用说明：

1. **FIFO 发送模式**（默认）
   - 主循环连续填充 16 个 STB 槽位
   - 使用 `CAN_fillMessage()` 依次填充，每次自动指向下一个槽位
   - 所有槽位填满后（TSFF 标志置位），调用 `CAN_startTx(CAN_TX_REQ_STB_ALL)` 一次性启动发送
   - 硬件按 FIFO 顺序（先进先出）发送，而非 ID 优先级
   - 每帧数据内容：Byte0=批次序号，Byte1=帧索引(0-15)，Bytes2-7=固定模式(0xAA~0xFF)
   - 发送完成后（TSIF 中断），等待 1 秒开始下一批次，批次序号自动递增

2. **接收功能**
   - 接收滤波器配置为接受标准 ID 范围 0x100 ~ 0x1FF
   - 接收中断（RIF）触发后，ISR 循环读取 RB FIFO 中所有可用帧
   - 支持 RB 满、警告、溢出等状态检测

3. **硬件连接**
   - CANFDB_RX: IO7
   - CANFDB_TX: IO6
   - 需要外部 CAN 节点配合，或在初始化时使能回环模式测试

#### 状态标志说明：

| 标志 | 说明 |
|------|------|
| TSFF | 发送缓存满标志，16 槽位全部填满后置位 |
| TSIF | 发送成功中断标志，每帧发送完成后置位 |
| RIF | 接收中断标志，RB 中有新数据时置位 |
| RAFIF | 接收缓存警告标志，填充槽位达到警告阈值 |
| RFIF | 接收缓存满标志，16 槽位全部填满 |
| RBOIF | 接收溢出标志，RB 满时又有新帧到达 |

#### 观察变量：

| 变量名 | 说明 |
|--------|------|
| txMsgCount | 发送成功帧计数，每批次应增加到 16 |
| rxMsgCount | 接收帧计数 |
| txSeqNumber | 当前批次序号，每完成一批自动加 1 |
| errorFlag | 错误标志，发生溢出或错误时置位 |

#### 注意事项：

- 确保 `CAN_init()` 中配置 STB 为 FIFO 模式（`CAN_STB_PRIO_MD_DISABLE`）
- 批量发送时需等待前一批次完成（txMsgCount == 16）再填充下一批
- 如需单帧发送测试，可改用 PTB（Primary Transmit Buffer）并调用 `CAN_TX_REQ_PTB`
