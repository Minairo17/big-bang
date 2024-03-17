#pragma once
#include "ofMain.h"

#include "ofxBox2d.h"

class EdgeManager {

ofxBox2dEdge edge;
ofPolyline edgeLine;
b2World * world;

public:
    void setup(double radius);
    void update (double radius);
    void draw();

    void buildEdge(double radius);

    EdgeManager(b2World * _world);

};