#include "EdgeManager.h"

EdgeManager::EdgeManager(b2World * _world){
    world = _world;
     ofLog()<<"EdgeManager constructor";

    //we need to get access to the input
}

void EdgeManager::setup(double radius){
    //double initial_radius = 200.0;
    buildEdge(radius);
    ofLog()<<"Ready from EdgeManager";
}

void EdgeManager::update(double radius){
    //here we get the new radius - energy
    buildEdge(radius);
}

void EdgeManager::draw(){
    //edgeLine.draw();

}

void EdgeManager::buildEdge(double radius){
    int resolution = 40;
    //float endAngle = 360.0 - 360.0/resolution;
    float endAngle = 360.0;

    ofPoint center(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
    //float radius = 200.0;
    edgeLine.clear();
    edgeLine.arc(center, radius, radius, 0, endAngle, resolution);
    edgeLine.setClosed(true);
    edge.clear();  //this complains in setup
    edge.addVertexes(edgeLine);
    edge.create(world);
}