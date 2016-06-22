//
// Created by janco on 5/23/16.
//

#include "ControllerHandler.h"
#include <iostream>

/*
 * String split helper functions
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

ControllerHandler::ControllerHandler(){
    readthread = std::thread(&ControllerHandler::BasestationReader, this);
};

Controller* ControllerHandler::getLeftController(void){
    for (int i = 0; i < 4; i++)
    {
        if(controllers[i] != nullptr && controllers[i]->isConnected()){
            return controllers[i];
        }
    }
    return nullptr;
}

Controller* ControllerHandler::getRightController(void){
    bool c1found = false;
    for (int i = 0; i < 4; i++)
    {
        if(controllers[i] != nullptr && controllers[i]->isConnected()){
            if(c1found){
                return controllers[i];
            }
            c1found = true;
        }
    }
    return nullptr;
}

void ControllerHandler::SearchBasestation(void){
    basestationFound = false;
    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();
    while( iter != devices_found.end() )
    {
        serial::PortInfo device = *iter++;
        if(device.hardware_id == "USB VID:PID=10c4:ea60 SNR=02133"){
            basestationFound = true;
            baseStation = new serial::Serial(device.port, BasestationBaudrate, serial::Timeout::simpleTimeout(1000));
            break;
        }
    }
}

void ControllerHandler::rumble(int idController, int duration, int power){
	if (basestationFound)
	{
		char sendbuffer[16];
		sprintf(sendbuffer, "1|%01d|%06d|%03d\n", idController, duration, power);
		baseStation->write(sendbuffer);
	}
}

/*
 * Reading from basestation
 */

void ControllerHandler::BasestationReader() {
    while(1){
        while(!basestationFound){
            SearchBasestation();
            if(basestationFound){
                baseStation ->write("stop\n");
                baseStation ->write("clientlist\n");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        while(baseStation->isOpen()){
            std::string basestationMessage = baseStation->readline();
            std::vector<std::string> basestationMessageSplit = split(basestationMessage, '|');
            if(basestationMessageSplit.size() > 1){ //Valid message
                std::cout << "DEBUG: Message received. Length: " << basestationMessageSplit.size() << " Type: " << basestationMessageSplit[0] << " Message: " << basestationMessage;
                int messageId = std::stoi(basestationMessageSplit[0]);
                switch(messageId){
                    //commandList[messageId](basestationMessageSplit);
                    case 0: commandDebug(basestationMessageSplit); break;  //Debug message
                    case 1: commandControllerData(basestationMessageSplit); break;  //Data from controller
                    case 2: commandControllerEvent(basestationMessageSplit); break;  //Controller events
                    case 3: commandControllerList(basestationMessageSplit); break;  //Connected controller list
                }
            }
        }
    }
}

void ControllerHandler::commandDebug(std::vector<std::string> data) {
    std::cout << "DEBUG: " << data[1];
}

void ControllerHandler::commandControllerData(std::vector<std::string> data) {
    if(data.size() == 10){
        Controller* c = controllers[std::stoi(data[1])];
        if(c != nullptr && c->isConnected()){
            c->ypr.x = std::stoi(data[5])/100.0f;
            c->ypr.y = std::stoi(data[6])/100.0f;
            c->ypr.z = std::stoi(data[7])/100.0f;

            c->joystick.x = std::stoi(data[2])/2000.0f;
            c->joystick.y = std::stoi(data[3])/2000.0f;
            c->joystickButton = !(data[4] == "0");

            c->magnetSwitch = !(data[9] == "0");
        }
    }
}

void ControllerHandler::commandControllerEvent(std::vector<std::string> data) {
    if(data.size() == 3){
        if(data[1] == "connected"){
            int controllerId = std::stoi(data[2]);
            controllers[controllerId] = new Controller(controllerId);
            controllers[controllerId]->setConnected(true);
        }else if(data[1] == "disconnected"){
         //   controllers.erase(*controllers[std::stoi(data[2])]);
        }
    }
}

void ControllerHandler::commandControllerList(std::vector<std::string> data) {
   for(unsigned int i = 1; i < data.size() - 1; i++){
       int controllerId = std::stoi(data[i]);
       controllers[controllerId] = new Controller(controllerId);
       rumble(controllerId, 100, 100);
   }
   if(basestationFound)
	 baseStation->write("start\n");
}




