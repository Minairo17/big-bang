#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(shared_ptr<InputManager> _input, shared_ptr<ParticleManager> _particleManager){
    particleManager = _particleManager;
    input= _input;
}

void StatisticsManager::setup(){
    checkParticles = input->dataManager->settings["allParticles"];

	plotParticles = input->dataManager->settings["graph"]["particles"];
	plotAtoms= input->dataManager->settings["graph"]["light_elements"];
	plotNuclei=input->dataManager->settings["graph"]["heavy_elements"];
	plotNeutrinos=input->dataManager->settings["graph"]["neutrinos"];

    ofLog()<<"Ready from StatisticsManager";
}

void StatisticsManager::update(){
    updateParticleNumbers();
	updateVectors();
}

void StatisticsManager::updateParticleNumbers(){
	for(const string &particle_name : checkParticles){
		int counter = 0;
		for (auto & particle : particleManager->particles) {
			auto * theData = (ParticleData*)particle->getData();
			if (theData->name== particle_name){
				counter++;
			}
		}
		numParticles[particle_name]=float(counter);
	}
}

void StatisticsManager::updateVectors(){
	numParts.clear();
	numAtoms.clear();
	numNuclei.clear();
	numNeutrinos.clear();

	for(const string &particle_name : plotParticles) {
		numParts.push_back(float(numParticles[particle_name]));
	}
	for(const string &particle_name : plotAtoms) {
		numAtoms.push_back(float(numParticles[particle_name]));
	}
	for(const string &particle_name : plotNuclei) {
		numNuclei.push_back(float(numParticles[particle_name]));
	}
	for(const string &particle_name : plotNeutrinos) {
		numNeutrinos.push_back(float(numParticles[particle_name]));
	}
}