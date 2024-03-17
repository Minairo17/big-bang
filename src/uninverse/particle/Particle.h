#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ParticleData.h"

class Particle : public ofxBox2dCircle {
    public:
	    Particle(map<string, b2World *>  &worlds, ofJson &settings, ofJson &constants, float x, float y, string _name);
		~Particle();

	    void draw();
};


