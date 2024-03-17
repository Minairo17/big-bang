#pragma once
#include "ofMain.h"
#include "ParticleManager.h"
#include "InputManager.h"

class StatisticsManager {
    shared_ptr<ParticleManager> particleManager;
    shared_ptr<InputManager> input;

    ofJson checkParticles;
    ofJson	plotParticles;
	ofJson plotAtoms;
	ofJson plotNuclei;
    ofJson plotNeutrinos;
public:

    map<std::string, int> numParticles;

    vector<float>numAtoms;
    vector<float>numNuclei;
    vector<float>numParts;
    vector<float>numNeutrinos;

    void setup();
    void update ();

    void updateParticleNumbers();

    void updateVectors();

    StatisticsManager(shared_ptr<InputManager> _input, shared_ptr<ParticleManager> _particleManager);

};