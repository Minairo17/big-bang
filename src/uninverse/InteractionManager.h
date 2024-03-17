#pragma once
#include "ofMain.h"
#include "InputManager.h"
#include <random>
#include <unordered_set>
#include "ofxBox2d.h"

class InteractionManager {

    private:
    random_device rd;

    shared_ptr<InputManager> input;

    ofJson constants;
    ofJson allinteractions;
    ofJson interactions;
    ofJson settings;

    //energy universe
    double energyUniverse;
    string energyScaleUniverse;

    //energy process
	double setEnergyKinematic(b2Vec2 vel_a, b2Vec2 vel_b, string name_a, string name_b);
    string setEnergyScale(double energy);
	

    //check functions
    void setupParameters();
    void setupInteractions();
    void checkInteractions();

    public:
    // general functions
    void setup();
    void update();

    //getters
    double getEnergyUniverse();
    string getEnergyScaleUniverse();

    //Intereaction selection
    ofJson getInteraction(unordered_set<string> interactingParticles, b2Vec2 vel_a, b2Vec2 vel_b, string name_a, string name_b);

    InteractionManager(shared_ptr<InputManager> _input);
};