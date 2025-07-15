# 控制方式修改说明

## 修改内容
将机器人的左右转向控制从右摇杆Y轴（Axis4）改为右摇杆X轴（Axis1），以提供更直观的操控体验。

## 修改前的控制方式
- **左摇杆Y轴（Axis3）**：前后移动
- **右摇杆Y轴（Axis4）**：左右转向
- **右摇杆Y轴（Axis2）**：壁桩手动控制

## 修改后的控制方式
- **左摇杆Y轴（Axis3）**：前后移动
- **右摇杆X轴（Axis1）**：左右转向 ⭐ **新的控制方式**
- **右摇杆Y轴（Axis2）**：壁桩手动控制（保持不变）

## 技术实现

### 修改的文件
- `src/main.cpp`

### 主要更改
1. **新增自定义控制函数**：`customDriveControl()`
   - 使用Axis1（右摇杆X轴）作为转向输入
   - 保持Axis3（左摇杆Y轴）作为前后移动输入
   - 内置deadband（死区）处理，避免摇杆飘移

2. **修改用户控制循环**：
   - 将 `chassis.control_arcade()` 替换为 `customDriveControl()`
   - 保持所有其他功能不变

### 控制逻辑
```cpp
// 获取控制器输入
float throttle_raw = Controller1.Axis3.value();  // 左摇杆Y轴
float turn_raw = Controller1.Axis1.value();      // 右摇杆X轴

// 死区处理
float throttle = (abs(throttle_raw) < 10) ? 0 : throttle_raw;
float turn = (abs(turn_raw) < 10) ? 0 : turn_raw;

// Arcade驱动控制
leftDriveMotors.spin(fwd, (throttle + turn) * 12.0 / 100.0, volt);
rightDriveMotors.spin(fwd, (throttle - turn) * 12.0 / 100.0, volt);
```

## 保持不变的功能
- ✅ 壁桩控制（Axis2）
- ✅ 所有按钮功能
- ✅ 自动程序
- ✅ 传感器功能
- ✅ 气动控制
- ✅ 环形物分拣

## 优势
1. **更直观的操控**：右摇杆左右推动对应机器人左右转向
2. **符合常见游戏习惯**：大多数游戏使用右摇杆X轴进行转向
3. **减少操作员学习成本**：更容易上手
4. **保持现有功能**：所有其他控制保持原样

## 测试建议
1. 确认前后移动响应正常
2. 确认左右转向方向正确
3. 确认壁桩控制功能正常
4. 确认所有按钮功能正常
5. 测试在比赛环境下的操控感受 