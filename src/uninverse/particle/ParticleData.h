#pragma once
#include "ofMain.h"
#include <random>

class ParticleData {
    public:

        //ids and counters
        static int objectCount;
        static int setId();
        int		id;

        //info
        string  name;
        float charge;
		ofVec2f vel;

        //appearance
        ofColor color;

        //flags
        bool    toRemove{false};
        bool    ready{true};

        //constructor
        ParticleData(string _name, ofJson &constants);
};


