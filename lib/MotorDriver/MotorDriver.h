#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

class MotorDriver {
public:
    MotorDriver(int ain1, int ain2, int pwm, int stby, int pwmChannel);

    void begin();
    void forward(int speed);   // 正转
    void backward(int speed);  // 反转
    void stop();               // 停止

private:
    int _ain1Pin;
    int _ain2Pin;
    int _pwmPin;
    int _stbyPin;
    int _pwmChannel;

    void setPwm(int speed);
};

#endif // MOTOR_DRIVER_H
