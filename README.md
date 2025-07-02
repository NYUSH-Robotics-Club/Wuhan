# NYUSH-VEX-HighStake 🤖

## 项目简介

这是NYUSH（上海纽约大学）VEX机器人团队为2025年HighStake武汉赛区开发的机器人控制程序。本项目是基于[CPSLO VexCode 2024-2025](https://github.com/CalPolyVEX/VEXCODE-2024-2025)的私有分支开发。

### 赛季信息
- **比赛**: VEX HighStake 2025
- **地区**: 武汉赛区
- **团队**: NYUSH VEX机器人团队
- **平台**: VEX V5 系统

## 目录结构

```
NYUSH-VEX-HighStake/
├── src/                    # 源代码目录
│   ├── main.cpp           # 主程序文件
│   ├── autons.cpp         # 自动程序文件
│   ├── robot-config.cpp   # 机器人配置
│   └── JAR-Template/      # JAR模板库
│       ├── PID.cpp        # PID控制算法
│       ├── drive.cpp      # 底盘驱动控制
│       ├── odom.cpp       # 里程计定位
│       └── util.cpp       # 工具函数
├── include/               # 头文件目录
│   ├── main.h            # 主程序头文件
│   ├── autons.h          # 自动程序头文件
│   ├── robot-config.h    # 机器人配置头文件
│   ├── vex.h             # VEX系统头文件
│   └── JAR-Template/     # JAR模板头文件
├── vex/                  # VEX构建系统
│   ├── mkenv.mk          # 环境配置
│   └── mkrules.mk        # 构建规则
├── .vscode/              # VS Code配置
├── wheels.ipynb          # 轮子校准计算
├── makefile              # 构建配置文件
└── HS_18-2_WorldsGreen.v5code  # VEX代码项目文件
```

## 机器人配置

此项目支持两种不同的机器人配置：

### GREEN配置（主要配置 - 已适配Python端口）
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

## 功能特性

### 🎯 自动程序 (Autonomous)
项目包含多种自动程序策略：

#### GREEN配置自动程序
- `redGreenAutonCenter()` - 红方中央抢攻略
- `blueGreenAutonCenter()` - 蓝方中央抢攻略  
- `redGreenAutonOther()` - 红方备用策略
- `blueGreenAutonOther()` - 蓝方备用策略

#### GOLD配置自动程序
- `redGoldAuton()` - 金色机器人红方策略
- `blueGoldAuton()` - 金色机器人蓝方策略

#### 特殊程序
- `Prog_Skills()` - 技能挑战最大化得分策略
- `worlds_auton()` - 世界赛优化策略
- `safe_worlds_auton()` - 安全备用方案

### 🎮 手动控制 (User Control)
- **双摇杆坦克驱动**: 精确的机器人移动控制
- **智能环形物分拣**: 基于颜色传感器的自动分拣
- **多种控制模式**: 
  - 精准控制模式
  - 快速移动模式
  - 壁柱专用控制

### 🧠 智能系统

#### 环形物颜色分拣
```cpp
// 自动检测并分拣正确颜色的环形物
void colorSort() {
    // 基于光学传感器的颜色检测
    ringColor = colorDetect.hue();
    bool ringIsRed = ringColor > 360 || ringColor < 20;
    bool ringIsBlue = ringColor > 180 && ringColor < 260;
    // 自动排除错误颜色的环形物
}
```

#### PID控制系统
- **驱动PID**: 精确的直线和转向控制
- **壁柱PID**: 精确的壁柱位置控制
- **自适应参数**: 根据不同情况调整PID参数

#### 里程计定位 (Odometry)
- **双轮编码器系统**: 高精度位置跟踪
- **陀螺仪辅助**: 准确的朝向控制
- **实时坐标显示**: 在Brain屏幕上显示当前位置

## 控制器映射

### 主要控制
- **左摇杆 (Axis3)**: 左侧驱动控制
- **右摇杆 (Axis2)**: 右侧驱动控制 + 壁柱手动控制
- **L1**: 进料系统正转
- **L2**: 进料系统反转
- **R1**: 壁柱机构状态循环 (装载→预得分→得分)
- **R2**: 移动目标机构开关

### 辅助控制
- **A**: 自动进料至检测到环形物
- **B**: 戳击器(右)开关
- **X**: 锁定自动程序选择
- **Y**: 解锁自动程序选择
- **上**: 设置为红方颜色分拣
- **下**: 戳击器(左)开关
- **左**: 设置为蓝方颜色分拣
- **右**: 翻转器开关

## 自动程序适配状态

✅ **已完成适配**

所有自动程序已成功适配新的端口配置：

### 适配详情
1. 电机组定义已统一为 `wallStakeMain`，与主程序保持一致
2. 所有驱动电机、进料系统、壁桩系统调用已更新
3. 传感器配置（距离传感器、颜色传感器）正确映射
4. 气动装置控制适配新端口配置
5. 清理了旧的注释代码和过时的电机定义

### 可用的自动选择
使用控制器按钮可以选择不同的自动程序，程序会根据当前编译配置（GREEN/GOLD）显示相应的选项。

## 开发与部署

### 构建项目
```bash
# 编译GREEN配置 (默认)
make

# 编译GOLD配置
make GOLD=1

# 清理构建文件
make clean
```

### 部署到机器人
1. 将VEX V5 Brain连接到电脑
2. 运行编译命令
3. 通过VEX Coding Studio或VS Code上传程序

### 开发环境
- **推荐IDE**: VS Code with VEX Extension
- **编译器**: VEX GCC工具链
- **调试**: VEX V5 Brain终端输出

## 团队贡献

### 项目维护者
- **NYUSH VEX Team** - 主要开发和维护

### 鸣谢
- **CPSLO VEX Team** - 原始代码库和JAR模板
- **VEX Robotics** - 硬件平台和开发工具

## 许可证

本项目基于原始CPSLO项目进行开发，遵循相应的开源协议。

---

**Good luck in the competition! 🏆**
