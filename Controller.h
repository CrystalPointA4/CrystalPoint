#pragma once

#include "Vector.h"

class Controller{
public:
    Controller(int controllerId);
    ~Controller();
    Vec3f ypr;
    Vec2f joystick;
    bool button, joystickButton, magnetSwitch;
    bool lastButton, lastJoystickButton, lastMagetSwitch;
    int controllerId;

    void setConnected(bool connected);
    bool isConnected(void);

    void rumble(int duration, int power);
private:
    bool connected = false;
};