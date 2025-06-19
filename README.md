# 🚗 ESP32 WiFi智能小车控制系统

[![PlatformIO](https://img.shields.io/badge/PlatformIO-Professional-blue)](https://platformio.org)
[![Arduino](https://img.shields.io/badge/Framework-Arduino-00979D)](https://www.arduino.cc/)

基于ESP32的物联网小车控制系统，通过Web界面实现远程运动控制。支持前进/后退/转向/急停，采用双电机差速转向算法。


## 主要功能
- 🖥️ 响应式网页控制界面（支持手机/PC访问）
- ⚙️ 双电机PWM调速控制（0-255级）
- ↕️ 差速转向算法实现灵活转弯
- 🔌 兼容TB6612FNG等常见电机驱动模块

## 硬件要求
| 组件          | 型号               |
|---------------|--------------------|
| 主控板        | ESP32开发板        |
| 电机驱动模块  | TB6612FNG或类似    |
| 直流电机      | 6V减速电机 x2      |
| 电源          | 18650电池组 x2     |
