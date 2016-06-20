#pragma once
//
// Created by janco on 5/23/16.
//

#define BasestationBaudrate 115200
#include <thread>
#include "include/serial.h"
#include "Controller.h"

class ControllerHandler{
public:
    ControllerHandler();
    Controller* getLeftController(void);
    void rumble(int idController, int duration, int power);
private:
    void SearchBasestation(void);
    void BasestationReader(void);

    bool basestationFound;
    serial::Serial *baseStation;
    std::thread readthread;
    std::vector<Controller*> controllers {0};

    //Command functions
    void commandDebug(std::vector<std::string> data);
    void commandControllerData(std::vector<std::string> data);
    void commandControllerEvent(std::vector<std::string> data);
    void commandControllerList(std::vector<std::string> data);

    //void(*commandList [1])(std::vector<std::string> data);
};

