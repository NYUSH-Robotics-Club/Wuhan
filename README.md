# NYUSH-VEX-HighStake 🤖

## 项目简介

这是NYUSH（上海纽约大学）VEX机器人团队为2025年HighStake武汉赛区开发的机器人控制程序。本项目是基于[CPSLO VexCode 2024-2025](https://github.com/CalPolyVEX/VEXCODE-2024-2025)的分支开发。

### 赛季信息
- **比赛**: VEX HighStake 2025
- **地区**: 武汉赛区
- **团队**: NYUSH VEX机器人团队
- **平台**: VEX V5 系统
- **开发语言**: C++
- **构建系统**: Make + VEX GCC工具链

### 项目特色
- 🎯 **多策略自动程序**: 针对不同比赛场景的优化策略
- 🧠 **智能颜色分拣**: 基于光学传感器的自动环形物分拣
- 📍 **高精度定位**: 双轮编码器 + 陀螺仪里程计系统
- ⚡ **PID控制优化**: 精确的驱动和机构控制
- 🎮 **多模式手动控制**: 适应不同操作需求的控制模式

## 目录结构

```
NYUSH-VEX-HighStake/
├── src/                    # 源代码目录
│   ├── main.cpp           # 主程序文件 - 程序入口和初始化
│   ├── autons.cpp         # 自动程序文件 - 所有自动策略实现
│   ├── robot-config.cpp   # 机器人配置 - 硬件端口映射和初始化
│   └── JAR-Template/      # JAR模板库 - 核心算法库
│       ├── PID.cpp        # PID控制算法 - 精确控制实现
│       ├── drive.cpp      # 底盘驱动控制 - 移动和转向控制
│       ├── odom.cpp       # 里程计定位 - 位置跟踪和导航
│       └── util.cpp       # 工具函数 - 通用辅助函数
├── include/               # 头文件目录
│   ├── main.h            # 主程序头文件 - 全局变量和函数声明
│   ├── autons.h          # 自动程序头文件 - 自动策略函数声明
│   ├── robot-config.h    # 机器人配置头文件 - 硬件定义
│   ├── vex.h             # VEX系统头文件 - VEX API
│   └── JAR-Template/     # JAR模板头文件 - 算法库接口
│       ├── drive.h       # 驱动控制接口
│       ├── odom.h        # 里程计接口
│       ├── PID.h         # PID控制接口
│       └── util.h        # 工具函数接口
├── vex/                  # VEX构建系统
│   ├── mkenv.mk          # 环境配置 - 编译环境设置
│   └── mkrules.mk        # 构建规则 - 编译规则定义
├── .vscode/              # VS Code配置 - 开发环境设置
├── wheels.ipynb          # 轮子校准计算 - 轮子参数优化
├── makefile              # 构建配置文件 - 项目编译配置
└── HS_18-2_WorldsGreen.v5code  # VEX代码项目文件 - VEX Studio项目
```

## 机器人配置

此项目支持两种不同的机器人配置，通过编译时宏定义进行切换：

### 🟢 GREEN配置（主要配置 - 已适配Python端口）
**驱动系统**:
- **左侧驱动**: PORT1-PORT4 (比例 6:1) - 4个电机并联
- **右侧驱动**: PORT5-PORT8 (比例 6:1) - 4个电机并联
- **编码器**: 左轮编码器用于里程计定位

**进料系统**:
- **滚轮电机**: PORT11 (比例 18:1) - 环形物收集
- **传送带电机**: PORT12 (比例 18:1) - 环形物传输

**壁桩系统**:
- **左壁桩电机**: PORT13 (比例 36:1) - 高扭矩壁桩控制
- **右壁桩电机**: PORT14 (比例 36:1) - 高扭矩壁桩控制
- **旋转传感器**: PORT15 - 壁桩角度反馈

**气动系统**:
- **移动目标机构**: Brain.ThreeWirePort.H - 目标抓取
- **推杆右**: Brain.ThreeWirePort.G - 右侧戳击器
- **推杆左**: Brain.ThreeWirePort.C - 左侧戳击器
- **推杆**: Brain.ThreeWirePort.F - 壁桩推杆
- **翻转器**: Brain.ThreeWirePort.D - 环形物翻转器
- **夹爪**: Brain.ThreeWirePort.E - 戳击器夹爪

**传感器系统**:
- **光学传感器**: PORT19 - 环形物颜色检测
- **距离传感器**: PORT18 - 障碍物检测和定位
- **陀螺仪**: PORT21 - 朝向控制和里程计辅助
- **壁桩旋转传感器**: PORT16 - 壁桩角度反馈
- **戳击器开关**: Brain.ThreeWirePort.A - 戳击器位置检测
- **里程计编码器**: PORT9 (垂直), PORT10 (水平) - 位置跟踪

### 🟡 GOLD配置（备用配置）
**驱动系统**:
- **左侧驱动**: PORT7-PORT10 (比例 6:1) - 4个电机并联
- **右侧驱动**: PORT1-PORT4 (比例 6:1) - 4个电机并联
- **编码器**: 左轮编码器用于里程计定位

**进料系统**:
- **滚轮电机**: PORT20 (比例 6:1) - 环形物收集
- **传送带电机**: PORT18 (比例 18:1) - 环形物传输

**壁桩系统**:
- **左壁桩电机**: PORT11 (比例 36:1) - 高扭矩壁桩控制
- **右壁桩电机**: PORT12 (比例 36:1) - 高扭矩壁桩控制
- **旋转传感器**: PORT15 - 壁桩角度反馈

**气动系统**:
- **移动目标机构**: Brain.ThreeWirePort.B - 目标抓取
- **推杆右**: Brain.ThreeWirePort.C - 右侧戳击器
- **翻转器**: Brain.ThreeWirePort.A - 环形物翻转器
- **推杆左**: Brain.ThreeWirePort.D - 左侧戳击器

**传感器系统**:
- **光学传感器**: PORT19 - 环形物颜色检测
- **距离传感器**: PORT16 - 障碍物检测和定位
- **陀螺仪**: PORT21 - 朝向控制和里程计辅助
- **戳击器开关**: Brain.ThreeWirePort.H - 戳击器位置检测
- **里程计编码器**: PORT5 (垂直), PORT6 (水平) - 位置跟踪

## 编译配置

在 `makefile` 中通过宏定义控制配置选择：

```makefile
# 默认使用GREEN配置
CPPFLAGS += -DGREEN

# 如需使用GOLD配置，取消注释下行并注释上行
# CPPFLAGS += -DGOLD
```

### 编译命令
```bash
# 编译GREEN配置 (默认)
make

# 编译GOLD配置
make GOLD=1

# 清理构建文件
make clean

# 重新编译
make rebuild
```

## 端口映射对照表（Python ↔ C++）

| Python设备 | Python端口 | C++变量名 | C++端口 | 功能描述 |
|------------|-------------|-----------|---------|----------|
| motor1 | PORT1 | L1 | PORT1 | 左驱动电机1 |
| motor2 | PORT2 | L2 | PORT2 | 左驱动电机2 |
| motor3 | PORT3 | L3 | PORT3 | 左驱动电机3 |
| motor4 | PORT4 | L4 | PORT4 | 左驱动电机4 |
| motor5 | PORT5 | R1 | PORT5 | 右驱动电机1 |
| motor6 | PORT6 | R2 | PORT6 | 右驱动电机2 |
| motor7 | PORT7 | R3 | PORT7 | 右驱动电机3 |
| motor8 | PORT8 | R4 | PORT8 | 右驱动电机4 |
| roller | PORT11 | roller | PORT11 | 进料滚轮 |
| conveyor | PORT12 | conveyor | PORT12 | 传送带 |
| wall_stake_left | PORT13 | wallStake1 | PORT13 | 左壁桩电机 |
| wall_stake_right | PORT14 | wallStake2 | PORT14 | 右壁桩电机 |
| wall_stake_rotation | PORT16 | rotationWallStake | PORT16 | 壁桩旋转传感器 |
| mogo_mech | ThreeWirePort.H | mogoMech | ThreeWirePort.H | 移动目标机构 |
| arm_grip | ThreeWirePort.G | doinker_right | ThreeWirePort.G | 右侧戳击器 |
| arm_extend | ThreeWirePort.C | doinker_left | ThreeWirePort.C | 左侧戳击器 |
| pusher | ThreeWirePort.F | pusher | ThreeWirePort.F | 壁桩推杆 |
| tipper | ThreeWirePort.D | tipper | ThreeWirePort.D | 环形物翻转器 |
| doinker_clamp | ThreeWirePort.E | doinker_clamp | ThreeWirePort.E | 戳击器夹爪 |
| ring_dist | PORT18 | ringDist | PORT18 | 环形物距离传感器 |
| color_detect | PORT19 | colorDetect | PORT19 | 环形物颜色传感器 |
| inertial | PORT21 | inertialSensor | PORT21 | 陀螺仪传感器 |

**注意**: 以下设备在代码中定义但当前未使用:
- `ringChuck` (ThreeWirePort.C) - 环形物夹爪
- `ringSwitch` (ThreeWirePort.B) - 环形物开关
- `doinkerSwitches` (ThreeWirePort.A/H) - 戳击器开关

## 功能特性

### 🎯 自动程序 (Autonomous)

项目包含多种自动程序策略，针对不同比赛场景进行优化：

#### GREEN配置自动程序
- **`redGreenAutonCenter()`** - 红方中央抢攻略
  - 快速抢占中央区域
  - 优先收集高分环形物
  - 优化路径规划减少时间浪费
  
- **`blueGreenAutonCenter()`** - 蓝方中央抢攻略
  - 镜像红方策略适配蓝方
  - 考虑场地对称性优化
  
- **`redGreenAutonOther()`** - 红方备用策略
  - 当中央策略不可行时的备选方案
  - 侧边区域得分策略
  
- **`blueGreenAutonOther()`** - 蓝方备用策略
  - 蓝方侧边得分策略

#### GOLD配置自动程序
- **`redGoldAuton()`** - 金色机器人红方策略
- **`blueGoldAuton()`** - 金色机器人蓝方策略

#### 特殊程序
- **`Prog_Skills()`** - 技能挑战最大化得分策略
  - 60秒内最大化得分
  - 优化环形物收集和放置顺序
  
- **`worlds_auton()`** - 世界赛优化策略
  - 针对高水平比赛的优化策略
  
- **`safe_worlds_auton()`** - 安全备用方案
  - 保守但可靠的得分策略

### 🎮 手动控制 (User Control)

#### 驱动控制
- **双摇杆坦克驱动**: 精确的机器人移动控制
  - 左摇杆控制左侧驱动
  - 右摇杆控制右侧驱动
  - 支持精确控制和快速移动模式切换

#### 智能环形物分拣
```cpp
// 自动检测并分拣正确颜色的环形物
void colorSort() {
    // 基于光学传感器的颜色检测
    ringColor = colorDetect.hue();
    bool ringIsRed = ringColor > 360 || ringColor < 20;
    bool ringIsBlue = ringColor > 180 && ringColor < 260;
    
    // 自动排除错误颜色的环形物
    if (isRedSide && !ringIsRed) {
        // 红方时排除蓝环
        rejectRing();
    } else if (!isRedSide && !ringIsBlue) {
        // 蓝方时排除红环
        rejectRing();
    }
}
```

#### 多种控制模式
- **精准控制模式**: 适合精细操作
- **快速移动模式**: 适合快速移动和位置调整
- **壁柱专用控制**: 专门针对壁柱操作的优化控制

### 🧠 智能系统

#### PID控制系统
- **驱动PID**: 精确的直线和转向控制
  - 直线行驶PID参数: P=0.8, I=0.0, D=0.1
  - 转向PID参数: P=1.2, I=0.0, D=0.15
  
- **壁柱PID**: 精确的壁柱位置控制
  - 位置控制PID参数: P=0.6, I=0.0, D=0.05
  
- **自适应参数**: 根据不同情况调整PID参数

#### 里程计定位 (Odometry)
- **双轮编码器系统**: 高精度位置跟踪
  - 左轮编码器: 距离测量
  - 右轮编码器: 距离测量
  - 陀螺仪: 朝向测量
  
- **实时坐标显示**: 在Brain屏幕上显示当前位置
  - X坐标: 前后位置
  - Y坐标: 左右位置
  - 朝向: 角度信息

#### 传感器融合
- **光学传感器**: 环形物颜色和距离检测
- **距离传感器**: 障碍物检测和精确定位
- **陀螺仪**: 朝向控制和稳定性保证

## 控制器映射

### 主要控制
| 控制器输入 | 功能 | 详细说明 |
|------------|------|----------|
| **左摇杆 (Axis3)** | 左侧驱动控制 | 控制左侧4个驱动电机 |
| **右摇杆 (Axis2)** | 右侧驱动控制 + 壁柱手动控制 | 控制右侧4个驱动电机，长按进入壁柱控制模式 |
| **L1** | 进料系统正转 | 启动环形物收集和传输 |
| **L2** | 进料系统反转 | 反向传输环形物 |
| **R1** | 壁柱机构状态循环 | 装载→预得分→得分 循环切换 |
| **R2** | 移动目标机构开关 | 控制移动目标抓取机构 |

### 辅助控制
| 控制器输入 | 功能 | 详细说明 |
|------------|------|----------|
| **A** | 自动进料至检测到环形物 | 智能进料控制 |
| **B** | 戳击器(右)开关 | 控制右侧戳击器 |
| **X** | 锁定自动程序选择 | 防止意外切换自动程序 |
| **Y** | 夹爪开关 | 控制戳击器夹爪 |
| **上** | 设置为红方颜色分拣 | 自动分拣红色环形物 |
| **下** | 推杆开关 | 控制壁桩推杆 |
| **左** | 设置为蓝方颜色分拣 | 自动分拣蓝色环形物 |
| **右** | 翻转器开关 | 控制环形物翻转机构 |
| **Y** | 夹爪开关 | 控制戳击器夹爪 |

## 自动程序适配状态

✅ **已完成适配**

所有自动程序已成功适配新的端口配置，确保与主程序的一致性：

### 适配详情
1. **电机组定义统一**: 所有自动程序使用统一的 `wallStakeMain` 电机组定义
2. **驱动系统更新**: 所有驱动电机调用已更新为新的端口配置
3. **进料系统适配**: 滚轮和传送带电机正确映射
4. **壁桩系统优化**: 壁桩电机和传感器配置正确
5. **传感器配置**: 距离传感器、颜色传感器正确映射
6. **气动装置控制**: 所有气动装置适配新端口配置
7. **代码清理**: 清理了旧的注释代码和过时的电机定义

### 可用的自动选择
使用控制器按钮可以选择不同的自动程序，程序会根据当前编译配置（GREEN/GOLD）显示相应的选项：

- **按钮组合**: 不同按钮组合选择不同自动程序
- **配置感知**: 自动识别当前编译配置
- **实时切换**: 比赛前可快速切换自动程序

## 开发与部署

### 环境要求
- **操作系统**: Windows 10/11, macOS, Linux
- **开发工具**: VS Code with VEX Extension
- **编译器**: VEX GCC工具链
- **硬件**: VEX V5 Brain + 控制器

### 构建项目
```bash
# 克隆项目
git clone [repository-url]
cd NYUSH-VEX-HighStake

# 编译GREEN配置 (默认)
make

# 编译GOLD配置
make GOLD=1

# 清理构建文件
make clean

# 重新编译
make rebuild
```

### 部署到机器人
1. **硬件连接**: 将VEX V5 Brain通过USB连接到电脑
2. **编译程序**: 运行相应的make命令
3. **上传程序**: 通过VEX Coding Studio或VS Code上传程序
4. **测试验证**: 在测试场地验证程序功能

### 开发环境配置
```json
// .vscode/settings.json
{
    "vex.includePath": [
        "${workspaceFolder}/include",
        "${workspaceFolder}/include/JAR-Template"
    ],
    "vex.buildPath": "${workspaceFolder}",
    "vex.outputPath": "${workspaceFolder}/build"
}
```

### 调试技巧
- **Brain终端输出**: 使用 `printf()` 进行调试信息输出
- **控制器显示**: 在控制器屏幕上显示关键信息
- **传感器监控**: 实时监控传感器数据
- **PID调参**: 通过修改PID参数优化控制效果

## 性能优化

### 代码优化
- **内存管理**: 优化变量使用和内存分配
- **循环优化**: 减少不必要的循环和计算
- **函数优化**: 内联关键函数提高执行效率

### 控制优化
- **PID调参**: 根据不同情况调整PID参数
- **路径规划**: 优化自动程序路径减少时间浪费
- **传感器融合**: 提高定位和检测精度

## 团队贡献

### 项目维护者
- **NYUSH VEX Team** - 主要开发和维护
  - 自动程序开发和优化
  - 硬件配置和端口映射
  - 控制系统调参和优化

### 鸣谢
- **CPSLO VEX Team** - 原始代码库和JAR模板
  - 提供了优秀的代码架构和算法库
  - 为项目开发奠定了坚实基础
  
- **VEX Robotics** - 硬件平台和开发工具
  - 提供了稳定可靠的硬件平台
  - 完善的开发工具链支持

### 贡献指南
1. **代码规范**: 遵循C++编码规范
2. **注释要求**: 关键函数和算法需要详细注释
3. **测试验证**: 新功能需要充分测试
4. **文档更新**: 及时更新相关文档

## 许可证

本项目基于原始CPSLO项目进行开发，遵循相应的开源协议。具体许可证信息请参考原始项目。

## 更新日志

### v1.0.0 (2025-01-XX)
- ✅ 完成GREEN配置自动程序适配
- ✅ 实现智能颜色分拣系统
- ✅ 优化PID控制参数
- ✅ 完善里程计定位系统
- ✅ 添加多模式手动控制

### 计划更新
- 🔄 进一步优化自动程序策略
- 🔄 添加更多传感器融合算法
- 🔄 实现自适应PID控制
- 🔄 优化代码结构和性能

---

**Good luck in the competition! 🏆**

*愿我们的机器人在HighStake武汉赛区取得优异成绩！*
