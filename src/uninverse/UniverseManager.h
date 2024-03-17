#pragma once

#include "ofMain.h"
#include "EdgeManager.h"
#include "ParticleManager.h"
#include "InteractionManager.h"
#include "StatisticsManager.h"
#include "Particle.h"

#include "InputManager.h"

#include "ofxBox2d.h"
#include "ofxBloom.h"


class ofxBox2d2 : public ofxBox2d {
    public:
    
    ofEvent <b2Contact*> contactPreSolveEvents;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) { 
/*         static ofxBox2dContactArgs args;
        args.a = contact->GetFixtureA();
        args.b = contact->GetFixtureB(); */
        ofNotifyEvent( contactPreSolveEvents, contact, this);
    }
};


class UniverseManager {
public:

    shared_ptr<InputManager> input;

    shared_ptr<ParticleManager> particleManager;
    shared_ptr<EdgeManager> edgeManager;
    shared_ptr<InteractionManager> interactionManager;

	vector<shared_ptr<Particle>> particles; //existing particles

    shared_ptr<StatisticsManager> statisticsManager;

    ofxBox2d2 box2d;
    ofxBox2d2 box2d_neutrinos;

    map<string, b2World *> worlds;

    void contactStart(ofxBox2dContactArgs &e); //callback
    void contactEnd(ofxBox2dContactArgs &e); //callback
    void preSolve(b2Contact* &contact); //callback



    void setup();
    void update();
    void draw();

    UniverseManager(shared_ptr<InputManager> _input);

};
