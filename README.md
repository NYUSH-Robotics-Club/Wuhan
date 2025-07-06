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

## 🎮 遥控器操作键位

### **肩部按键**
| 按键 | 功能 | 详细说明 |
|------|------|----------|
| **L1** | 进料系统正转 | 启动滚轮和传送带正转，同时启用环检测覆盖 |
| **L2** | 进料系统反转 | 按下时反转，释放时停止 |
| **R1** | 壁桩状态切换 | 循环切换：装载(14°) → 预得分(68°) → 得分(60°) |
| **R2** | 移动目标机构 | 开关移动目标抓取机构，带震动反馈 |

### **方向键**
| 按键 | 功能 | 详细说明 |
|------|------|----------|
| **⬆️ Up** | 蓝方模式 | 设置为蓝方机器人，丢弃红色环 |
| **⬇️ Down** | 左推杆 | 切换左侧推杆气动装置 |
| **⬅️ Left** | 红方模式 | 设置为红方机器人，丢弃蓝色环 |
| **➡️ Right** | 翻转器 | 切换翻转器气动装置 |

### **面部按键**
| 按键 | 功能 | 详细说明 |
|------|------|----------|
| **A** | 自动进料 | 持续进料直到检测到环，带震动提示 |
| **B** | 右推杆 | 切换右侧推杆气动装置 |

### **摇杆控制**
| 摇杆 | 功能 | 详细说明 |
|------|------|----------|
| **左摇杆** | 底盘驱动 | 街机式控制（前进后退+转向） |
| **右摇杆Y轴** | 手动壁桩 | 直接控制壁桩电机，覆盖自动控制 |

### **壁桩系统角度设置**
| 状态 | GREEN角度 | GOLD角度 | 功能 |
|------|-----------|----------|------|
| **装载** | 14° | 14° | 装载环的位置 |
| **预得分** | 68° | 68° | 准备得分位置 |
| **得分** | 60° | 60° | 最终得分位置 |

### **颜色检测系统**
- **LED亮度**: 25%（节能优化）
- **红色检测**: 350-10度色调范围
- **蓝色检测**: 205-225度色调范围
- **自动分拣**: 根据阵营设置自动丢弃错误颜色的环

### **自动程序选择**
- **Brain屏幕点击**: 循环切换自动程序
- **X键**: 锁定选择并校准陀螺仪
- **Y键**: 解锁自动程序选择
