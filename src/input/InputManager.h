#pragma once

#include "DataManager.h"
#include "OscManager.h"
#include "GuiApp.h"


class InputManager {

public:

    shared_ptr<DataManager> dataManager;
    shared_ptr<OscManager> oscManager;
    shared_ptr<GuiApp> gui;

    void setup();
    void update();

    InputManager(shared_ptr<GuiApp> _gui);
};