#include "OscManager.h"

OscManager::OscManager(ofJson &settings){
    portIn = settings["OSC"]["portIn"];
	//portIn = 12345;
}

void OscManager::setup(){
    // listen on the given port
	//ofLog() << "listening for osc messages on port: " << portIn;
	receiver.setup(portIn);

      ofLog()<<"Ready from OscManager";

}

void OscManager::update (){
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
        // get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        ofLog() << "message: " << m;
    }
}