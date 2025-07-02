# VEXCODE-2024-2025
CPSLO VexCode 2024-2025

## 机器人配置

此项目支持两种不同的机器人配置：

### GREEN配置（已更新为匹配Python代码端口）
- **驱动电机**: 
  - 左侧: PORT1-PORT4 (比例 6:1)
  - 右侧: PORT5-PORT8 (比例 6:1)
- **进料系统**: 
  - 滚轮: PORT11 (比例 18:1)
  - 传送带: PORT12 (比例 18:1)
- **壁桩系统**: 
  - 左电机: PORT13 (比例 36:1)
  - 右电机: PORT14 (比例 36:1)
  - 旋转传感器: PORT15
- **气动系统**:
  - 移动目标机构: Brain.ThreeWirePort.H
  - 推杆右: Brain.ThreeWirePort.G
  - 推杆左: Brain.ThreeWirePort.F

### GOLD配置（备用配置）
- 金色机器人的备用端口配置

## 编译配置

在 `makefile` 中默认使用GREEN配置：
```makefile
CPPFLAGS += -DGREEN
# CPPFLAGS += -DGOLD
```

## 端口映射对照表（Python -> C++）

| Python设备 | Python端口 | C++变量名 | C++端口 |
|------------|-------------|-----------|---------|
| motor1 | PORT1 | L1 | PORT1 |
| motor2 | PORT2 | L2 | PORT2 |
| motor3 | PORT3 | L3 | PORT3 |
| motor4 | PORT4 | L4 | PORT4 |
| motor5 | PORT5 | R1 | PORT5 |
| motor6 | PORT6 | R2 | PORT6 |
| motor7 | PORT7 | R3 | PORT7 |
| motor8 | PORT8 | R4 | PORT8 |
| roller | PORT11 | roller | PORT11 |
| conveyor | PORT12 | conveyor | PORT12 |
| wall_stake_left | PORT13 | wallStake1 | PORT13 |
| wall_stake_right | PORT14 | wallStake2 | PORT14 |
| wall_stake_rotation | PORT15 | rotationWallStake | PORT15 |
| mogo_mech | ThreeWirePort.H | mogoMech | ThreeWirePort.H |
| arm_grip | ThreeWirePort.G | doinker_right | ThreeWirePort.G |
| arm_extend | ThreeWirePort.F | doinker_left | ThreeWirePort.F |

## 控制器映射

现有的控制器映射保持不变，所有遥控器操作功能都已保留。

## 自动程序适配状态

✅ **已完成适配**

所有自动程序已成功适配新的端口配置：

### GREEN配置自动程序
- `redGreenAutonCenter()` - 红方中央抢攻略
- `blueGreenAutonCenter()` - 蓝方中央抢攻略  
- `redGreenAutonOther()` - 红方备用策略
- `blueGreenAutonOther()` - 蓝方备用策略

### GOLD配置自动程序
- `redGoldAuton()` - 金色机器人红方策略
- `blueGoldAuton()` - 金色机器人蓝方策略

### 适配详情
1. 电机组定义已统一为 `wallStakeMain`，与主程序保持一致
2. 所有驱动电机、进料系统、壁桩系统调用已更新
3. 传感器配置（距离传感器、颜色传感器）正确映射
4. 气动装置控制适配新端口配置
5. 清理了旧的注释代码和过时的电机定义

### 可用的自动选择
使用控制器按钮可以选择不同的自动程序，程序会根据当前编译配置（GREEN/GOLD）显示相应的选项。
