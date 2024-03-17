#include "InputManager.h"

InputManager::InputManager(shared_ptr<GuiApp> _gui){
    gui = _gui;
}

void InputManager::setup(){
    dataManager = make_shared<DataManager>();
	dataManager->setup();

    oscManager = make_shared<OscManager>(dataManager->settings);
	oscManager->setup();

    ofLog()<<"Ready from InputManager";
}


void InputManager::update(){

    oscManager->update();
    
}