#include "ofMain.h"
#include "ofApp.h"
#include "PlotApp.h"
#include "ofAppGLFWWindow.h" //

//========================================================================
int main( ){

	ofGLFWWindowSettings settings;

    settings.setSize(1280, 1280);
	settings.setPosition(glm::vec2(50,50));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.setSize(870, 200);
	settings.setPosition(glm::vec2(1330,1000));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	settings.setSize(870, 950);
	settings.setPosition(glm::vec2(1330,50));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> plotWindow = ofCreateWindow(settings);

	shared_ptr<GuiApp> guiApp(new GuiApp);
	shared_ptr<ofApp> mainApp = make_shared<ofApp>(guiApp);
	shared_ptr<PlotApp> plotApp = make_shared<PlotApp>(mainApp);

	ofRunApp(guiWindow, guiApp);
	ofRunApp(plotWindow, plotApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();	
};