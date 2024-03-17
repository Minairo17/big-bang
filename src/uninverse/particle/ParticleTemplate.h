#pragma once
#include "ofMain.h"

class ParticleTemplate {
    public:
        string name;
        ofVec2f position;
        ParticleTemplate(string _name, ofVec2f _positon);
};