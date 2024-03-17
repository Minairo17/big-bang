#include "InteractionManager.h"
#include <cmath>

InteractionManager::InteractionManager(shared_ptr<InputManager> _input){
      input = _input;
};

void InteractionManager::setup(){
   //read the files
   setupParameters();

   //check conservations
   //checkInteractions();

   //calculate mass defects & energy scales
   setupInteractions();

   ofLog()<<"Ready from Interaction Manager";

}

void InteractionManager::update(){
   energyUniverse = input->gui->energy;
   energyScaleUniverse = setEnergyScale(energyUniverse);
}

void InteractionManager::setupParameters() {
	constants = input->dataManager->constants;
	settings = input->dataManager->settings;
	allinteractions = input->dataManager->interactions;

	// Convert interaction names to unordered set for faster lookup
	unordered_set<string> selectedInteractions(settings["interactions"].begin(), settings["interactions"].end());

	for (auto& originalInteraction : allinteractions) {
		if (selectedInteractions.find(originalInteraction["name"]) != selectedInteractions.end()) {
			interactions.push_back(originalInteraction);
		}
	}
}


void InteractionManager::setupInteractions() {
#pragma omp parallel for
	for (auto& interaction : interactions) {
		double initialMass = 0.0, finalMass = 0.0;
		for (string particle : interaction["initial"]) {
			initialMass += constants["particles"][particle]["mass"];
		}
		for (string particle : interaction["final"]) {
			finalMass += constants["particles"][particle]["mass"];
		}
		double massDefect = finalMass - initialMass;
		interaction["massDefect"] = massDefect;
		interaction["scale"] = setEnergyScale(massDefect);
	}
}


double InteractionManager::setEnergyKinematic(b2Vec2 vel_a, b2Vec2 vel_b, string name_a, string name_b) {
#pragma omp parallel for
	if (name_a == "gamma" && name_b == "gamma") {
		return 1000000 / (vel_a.LengthSquared() + vel_b.LengthSquared());
	}
	else {
		double mass_a = constants["particles"][name_a]["mass"];
		double mass_b = constants["particles"][name_b]["mass"];
		return 0.5 * mass_a * vel_a.LengthSquared() / 5000 + 0.5 * mass_b * vel_b.LengthSquared() / 5000;
	}
}

string InteractionManager::setEnergyScale(double energy){
      string scale = "";
      if (energy < 0.0001){scale="electro";}
      else if (energy < 30){scale="weak";}
      else {scale="strong";}

      return scale;
}

double InteractionManager::getEnergyUniverse() {
   return energyUniverse;
}

string InteractionManager::getEnergyScaleUniverse() {
   return energyScaleUniverse;
}

/*
1. Possible interactions for given energy & energy scale: interaction["massDefect"] < energy && interaction["scale"]== scale 
2. Matching interaction for given initial particles: interactionParticles == possibleInteraction["initial"]
3. Selected interaction that will produce final particles: random selection
*/

ofJson InteractionManager::getInteraction(unordered_set<string> interactingParticles, b2Vec2 vel_a, b2Vec2 vel_b, string name_a, string name_b){
#pragma omp parallel for
	//here the random energy of the process is set
   double energyProcess= setEnergyKinematic(vel_a, vel_b, name_a, name_b);
   //double energyProcess = setEnergyProcess();
   string energyScaleProcess =setEnergyScale(energyProcess);

   ofJson matchingInteractions;

   // the selection takes place
   for (ofJson interaction: interactions){
      unordered_set<string> interactionParticles=interaction["initial"];
      if (  interaction["massDefect"] < energyProcess && 
            interactionParticles == interactingParticles
      ){
         ofLog() <<energyProcess << ":  " <<  interaction["name"] << " " <<interaction["initial"] <<" -> " << interaction["final"]<< " massDefect: " << interaction["massDefect"] << " Kinematic: " << energyProcess;
         matchingInteractions.push_back(interaction);
      }
   }
   ofJson returnInteractions;
   if (matchingInteractions.size()>1){
      auto urbg = mt19937 {rd()}; 
      auto dist = uniform_int_distribution<int>(0, matchingInteractions.size() - 1);
      returnInteractions = matchingInteractions[dist(urbg)];
   }
   else {returnInteractions = matchingInteractions[0];}

   return returnInteractions;
}