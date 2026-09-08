# Structure Refresh Stress Test

本示例基于原来的 ADC 软件触发工程改造而来，当前用途是验证 IDE 实时刷新时，复杂结构体成员是否能持续正确更新。

程序会在主循环中不断更新以下对象：`gDbgFrame`、`gMirror`、`gHeartbeat`。

建议在 Watch 中重点观察这些成员：

- `gDbgFrame.packed.a` / `b` / `c` / `d` / `e` / `f`
- `gDbgFrame.window.channels.raw[]`
- `gDbgFrame.window.channels.filtered[]`
- `gDbgFrame.window.channels.sum`
- `gDbgFrame.window.channels.energy`
- `gDbgFrame.window.history[]`
- `gDbgFrame.stats.tick`
- `gDbgFrame.stats.runningMax`
- `gDbgFrame.stats.runningMin`
- `gDbgFrame.stats.runningAvg`
- `gDbgFrame.stats.gain`
- `gDbgFrame.stats.offset`
- `gDbgFrame.phase`
- `gDbgFrame.crcLike`
- `gMirror.accumulator`
- `gMirror.transform`
- `gHeartbeat`

判断方式很直接：

1. `gHeartbeat` 应持续递增。
2. `gDbgFrame` 内部多个成员应同步变化，但变化幅度不同。
3. `gMirror.transform` 和 `gDbgFrame.crcLike` 应保持连续变化。
4. 如果 Watch 里展开结构体后某些成员长期停留在旧值，而 `gHeartbeat` 在变，通常就能复现实时刷新问题。

这个工程仍保留原来的板级初始化流程，但 ADC 转换逻辑已不再是主测试内容。
