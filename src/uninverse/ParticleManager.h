#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "ParticleTemplate.h"
#include "InputManager.h"

#include "ofxBox2d.h"


class ParticleManager {

    public:
    map<string, b2World *> worlds;
    shared_ptr<InputManager> input;

	//setttings & constants
	ofJson settings;
	ofJson constants;

    vector<shared_ptr<Particle>> particles; //existing particles
    vector<ParticleTemplate> particlesToAdd; //particles to be created
    vector<int> particlesToRemoveId; //particles to remove

    void addBuffer(); //cretae particles in the buffer
    void removeBuffer(); //remove particles in the buffer
    
    void add(ParticleTemplate p); //add 1 particle
    void remove(int id); //remove 1 particle
    
    int getNumber();
    void clearAll();
	void gravity();
	void gravity2();
	double calculateMean(const std::vector<double>& lista);
	double getMeanPosition();

    void setup();
    void update();
    void draw();
    void draw_charged();
    void draw_neutral();
    void draw_gamma();

    void setInitialParticles();
    ofVec2f getRandomPositionInsideEdge(float R);

    static bool toRemove(shared_ptr<Particle> p);

    ParticleManager(map<string, b2World *>  &_worlds, shared_ptr<InputManager> _input);

};