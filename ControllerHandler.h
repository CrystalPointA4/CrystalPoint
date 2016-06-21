#pragma once
//
// Created by janco on 5/23/16.
//

#define BasestationBaudrate 115200
#include <thread>

#ifdef WIN32
#include "include/serial.h"
#else
#include "lib/serial/include/serial.h"
#endif


#include "Controller.h"

class ControllerHandler{
public:
    ControllerHandler();
    Controller* getLeftController(void);
    Controller* getRightController(void);
    void rumble(int idController, int duration, int power);
private:
    void SearchBasestation(void);
    void BasestationReader(void);

    bool basestationFound;
    serial::Serial *baseStation;
    std::thread readthread;
    Controller* controllers[4];

    //Command functions
    void commandDebug(std::vector<std::string> data);
    void commandControllerData(std::vector<std::string> data);
    void commandControllerEvent(std::vector<std::string> data);
    void commandControllerList(std::vector<std::string> data);

    //void(*commandList [1])(std::vector<std::string> data);
};

