#include "ParticleManager.h"
#include <algorithm>
#include <cmath>

ParticleManager::ParticleManager(map<string, b2World *>  &_worlds, shared_ptr<InputManager> _input){
    worlds=_worlds;
    input=_input;
}

void ParticleManager::setup(){
	constants = input->dataManager->constants;
   	settings = input->dataManager->settings;

    setInitialParticles();
}

void ParticleManager::update(){
#pragma omp parallel sections
	{
#pragma omp section
		{removeBuffer(); }
#pragma omp section
		{ofRemove(particles, ofxBox2dBaseShape::shouldRemoveOffScreen); }
#pragma omp section
		{addBuffer(); }
#pragma omp section
		{gravity2(); }
	}
}

void ParticleManager::draw(){
    for(auto & particle : particles) {
		particle->draw();
	}
}

void ParticleManager::gravity2() {
	if (input->gui->gravity) {
#pragma omp parallel for
		for (size_t i = 0; i < particles.size(); ++i) {
			auto& particle1 = particles[i];
			auto* data1 = (ParticleData*)particle1->getData();
			double mass1 = constants["particles"][data1->name]["mass"];

			for (size_t j = i + 1; j < particles.size(); ++j) {
				auto& particle2 = particles[j];
				auto* data2 = (ParticleData*)particle2->getData();
				double mass2 = constants["particles"][data2->name]["mass"];

				ofVec2f pos1 = particle1->getPosition();
				ofVec2f pos2 = particle2->getPosition();
				double distanceSquared = pos1.squareDistance(pos2);

				double force = 100 * mass1 * mass2 / distanceSquared;
				ofVec2f direction = pos1 - pos2;
				direction.normalize();

#pragma omp critical
				{
					particle1->addForce(-direction, force);
					particle2->addForce(direction, force);
				}
			}
		}
	}
}

void ParticleManager::gravity() {
	if (input->gui->gravity) {
		const double centerX = ofGetWidth() / 2.0;
		const double centerY = ofGetHeight() / 2.0;
		const double meanPos = getMeanPosition();

		for (auto& particle : particles) {
			auto* particleData = static_cast<ParticleData*>(particle->getData());
			const std::string& name = particleData->name;
			const double mass = constants["particles"][name]["mass"];
			const double force = 10000 * mass / (pow(meanPos, 2));
			particle->addAttractionPoint(ofPoint(centerX, centerY), force);
		}
	}
}

double ParticleManager::calculateMean(const std::vector<double>& list) {
	double sum = 0.0;
	for (const double& elem : list) {
		sum += elem;
	}
	return sum / list.size();
}

double ParticleManager::getMeanPosition() {
	std::vector<double> distances;
	const double centerX = ofGetWidth() / 2.0;
	const double centerY = ofGetHeight() / 2.0;

	for (auto& particle : particles) {
		const ofVec2f& pos = particle->getPosition();
		const double relativeX = pos.x - centerX;
		const double relativeY = pos.y - centerY;
		distances.push_back(sqrt(pow(relativeX, 2) + pow(relativeY, 2)));
	}
	return calculateMean(distances);
}



void ParticleManager::draw_charged(){
    for(auto & particle : particles) {
		auto * theData = (ParticleData*)particle->getData();
		if (theData->charge!=0.0){
			particle->draw();
		}
	}
}

void ParticleManager::draw_neutral(){
	for(auto & particle : particles) {
		auto * theData = (ParticleData*)particle->getData();
		if (theData->charge==0.0 && theData->name!="gamma"){
			particle->draw();
		}
	}
}

void ParticleManager::draw_gamma(){
	for(auto & particle : particles) {
		auto * theData = (ParticleData*)particle->getData();
		if (theData->name=="gamma"){
			particle->draw();
		}
	}
}

void ParticleManager::setInitialParticles() {
	for (auto& element : settings["initialParticles"].items()) {
		for (int n = 0; n < element.value(); ++n) {
			ofVec2f position = getRandomPositionInsideEdge(input->gui->mappedradius);
			auto p = std::make_shared<Particle>(worlds, settings, constants, position.x, position.y, element.key());
			particles.push_back(p);
		}
	}
}

ofVec2f ParticleManager::getRandomPositionInsideEdge(float R){
	ofVec2f v;
	float r = R * sqrt(ofRandom(1));
	float theta = ofRandom(1) * 2 * 3.141592;
	float x = ofGetWindowWidth()/2 + r * cos(theta);
	float y = ofGetWindowHeight()/2 + r * sin(theta);

	v.set(x,y);

	return v;
//https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly
}

bool ParticleManager::toRemove(shared_ptr<Particle> p){
	auto * data = (ParticleData*) p->getData();
	return data->toRemove;
}

void ParticleManager::removeBuffer() {
	const int initialSize = particles.size();
	ofRemove(particles, toRemove);
	if (!particlesToRemoveId.empty()) {
		// Do whatever is necessary with particlesToRemoveId
		particlesToRemoveId.clear();
	}
}

void ParticleManager::remove(int id){
    particlesToRemoveId.push_back(id);
}

void ParticleManager::addBuffer() {
	const int initialSize = particles.size();
	for (auto& element : particlesToAdd) {
		auto p = std::make_shared<Particle>(worlds, settings, constants, element.position.x, element.position.y, element.name);
		particles.push_back(p);
	}
	particlesToAdd.clear();
}

void ParticleManager::add(ParticleTemplate p){
    particlesToAdd.push_back(p);
}

void ParticleManager::clearAll(){
    particlesToAdd.clear();
    particlesToRemoveId.clear();
    particles.clear();
    ofLog()<<"Cleared all particles";
}

int ParticleManager::getNumber(){
    return particles.size();
}


