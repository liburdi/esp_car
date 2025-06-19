#include "MotorDriver.h"

MotorDriver::MotorDriver(int ain1, int ain2, int pwm, int stby, int pwmChannel)
  : _ain1Pin(ain1), _ain2Pin(ain2), _pwmPin(pwm), _stbyPin(stby), _pwmChannel(pwmChannel) {}

void MotorDriver::begin() {
    pinMode(_ain1Pin, OUTPUT);
    pinMode(_ain2Pin, OUTPUT);
    pinMode(_stbyPin, OUTPUT);

    digitalWrite(_stbyPin, HIGH); // 使能驱动模块

    ledcSetup(_pwmChannel, 1000, 8);      // 1kHz, 8-bit
    ledcAttachPin(_pwmPin, _pwmChannel);
    stop();
}

void MotorDriver::forward(int speed) {
    digitalWrite(_ain1Pin, HIGH);
    digitalWrite(_ain2Pin, LOW);
    setPwm(speed);
}

void MotorDriver::backward(int speed) {
    digitalWrite(_ain1Pin, LOW);
    digitalWrite(_ain2Pin, HIGH);
    setPwm(speed);
}

void MotorDriver::stop() {
    digitalWrite(_ain1Pin, LOW);
    digitalWrite(_ain2Pin, LOW);
    setPwm(0);
}

void MotorDriver::setPwm(int speed) {
    speed = constrain(speed, 0, 255);
    ledcWrite(_pwmChannel, speed);
}
