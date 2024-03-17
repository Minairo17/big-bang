#include "DataManager.h"

void DataManager::setup(){
    // read settings
    ofFile file_settings("settings_2.json");
    if(file_settings.exists()){
		file_settings >> settings;  
	}

	// read constants
    ofFile file_constants("constants_2.json");
    if(file_constants.exists()){
		file_constants >> constants;  
	}

    // read interactions
    ofFile file_interactions("interactions_2.json");
    if(file_interactions.exists()){
		file_interactions >> interactions;  
	}

  ofLog()<<"Ready from DataManager";

}