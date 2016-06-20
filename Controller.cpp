//
// Created by janco on 5/24/16.
//

#include "Controller.h"

Controller::Controller(int controllerId) {
    this->controllerId = controllerId;
    this->ypr = Vec3f();
    this->joystick = Vec2f();
    this->setConnected(true);
}

Controller::~Controller() { }

void Controller::rumble(int duration, int power){
  //  controllerhandler->rumble(controllerId, duration, power);
}

void Controller::setConnected(bool connected) {
    if(connected){
        this->connected = true;
    }else{
        this->connected = false;
        this->ypr = Vec3f(0,0,0);
        this->joystick = Vec2f(0,0);
        this->button = false;
        this->magnetSwitch = false;
        this ->joystickButton = false;
    }
}

bool Controller::isConnected(void) {
    return connected;
}






