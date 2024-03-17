#include "UniverseManager.h"
#include "ParticleData.h"
#include "ofxBox2d.h"
#include <unordered_set>


UniverseManager::UniverseManager(shared_ptr<InputManager> _input){
    input = _input;
}

void UniverseManager::setup(){
    box2d.init();
	box2d.setGravity(0, 0);
    box2d.setFPS(60.0);
    box2d.enableEvents();
    ofAddListener(box2d.contactStartEvents, this, &UniverseManager::contactStart); //listener
	ofAddListener(box2d.contactEndEvents, this, &UniverseManager::contactEnd); //listener
	ofAddListener(box2d.contactPreSolveEvents, this, &UniverseManager::preSolve); //listener

	interactionManager = make_shared<InteractionManager>(input);
    interactionManager->setup();

	worlds["general"]=box2d.getWorld();

	box2d_neutrinos.init();
    box2d_neutrinos.setGravity(0, 0);
    box2d_neutrinos.setFPS(60.0);

	worlds["neutrinos"]=box2d_neutrinos.getWorld();

    edgeManager = make_shared<EdgeManager>(box2d.getWorld());
    edgeManager->setup(input->gui->mappedradius);
    particleManager = make_shared<ParticleManager>(worlds, input);
    particleManager->setup();

	interactionManager = make_shared<InteractionManager>(input);
    interactionManager->setup();

	statisticsManager = make_shared<StatisticsManager>(input, particleManager);
    statisticsManager->setup();

    ofLog()<<"Ready from UniverseManager";
}

void UniverseManager::update() {
	box2d.update();
	box2d_neutrinos.update();

#pragma omp parallel sections
	{
#pragma omp section
		{ particleManager->update(); }

#pragma omp section
		{ edgeManager->update(input->gui->mappedradius); }

#pragma omp section
		{ statisticsManager->update(); }

#pragma omp section
		{ interactionManager->update(); }
	}

	if (input->gui->reset) {
		input->gui->interactions = false;
		input->gui->gravity = false;
		particleManager->clearAll();
		particleManager->setInitialParticles();
	}
}


void UniverseManager::draw(){

    particleManager->draw();    
}

void UniverseManager::contactStart(ofxBox2dContactArgs &e) {
	if (input->gui->interactions==true){
		if(e.a != NULL && e.b != NULL) { 
			if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {

				ParticleData * aData = (ParticleData*)e.a->GetBody()->GetUserData();
				ParticleData * bData = (ParticleData*)e.b->GetBody()->GetUserData();

				b2Vec2 aVel = e.a->GetBody()->GetLinearVelocity();
				b2Vec2 bVel = e.b->GetBody()->GetLinearVelocity();

				string aName = aData->name;
				string bName = bData->name;

				if (aData->ready==true && bData->ready==true && aData->toRemove==false && bData->toRemove==false){
					aData->ready=false;
					bData->ready=false;

					unordered_set<string> interactingParticles={aData->name,bData->name};
					ofJson selectedInteraction = interactionManager->getInteraction(interactingParticles, aVel, bVel, aName, bName);

					if (selectedInteraction.size()>0){
						string interactionText= aData->name+" + "+bData->name+ " -> ";
						ofVec2f interactionPosition=ofxBox2d::toOf(e.a->GetBody()->GetPosition());
						for (auto finalParticle : selectedInteraction["final"]){
							//here we create new particles in random positions
							ofVec2f position =particleManager->getRandomPositionInsideEdge(input->gui->mappedradius);
							//try to assign real positions to new particles
							ofVec2f interactionPosition=ofxBox2d::toOf(e.a->GetBody()->GetPosition());
							auto p = ParticleTemplate(finalParticle,position);
                            particleManager->add(p);
							interactionText.append(finalParticle.dump() + " ");
						}
                        particleManager->remove(aData->id);
                        particleManager->remove(bData->id);

						aData->toRemove=true;
						bData->toRemove=true;
						//ofLog()<<interactionText;
					}
				}
			}
		}
	}
}

void UniverseManager::contactEnd(ofxBox2dContactArgs &e) {
	if (input->gui->interactions==true){
		if(e.a != NULL && e.b != NULL) { 
			
			ParticleData * aData = (ParticleData*)e.a->GetBody()->GetUserData();
			ParticleData * bData = (ParticleData*)e.b->GetBody()->GetUserData();
			
			if(aData) {
				aData->ready=true;
			}
			
			if(bData) {
				bData->ready=true;
			}
		}
	}
}

void UniverseManager::preSolve(b2Contact* &contact) {
	if (input->gui->interactions==true){
		static ofxBox2dContactArgs e;
		e.a = contact->GetFixtureA();
		e.b = contact->GetFixtureB();
		if(e.a != NULL && e.b != NULL) { 
			ParticleData * aData = (ParticleData*)e.a->GetBody()->GetUserData();
			ParticleData * bData = (ParticleData*)e.b->GetBody()->GetUserData();

			double energyUniverse = input->gui->energy;
			bool disableCollision = false;

			float eneryGamma = input->dataManager->settings["edges"]["gamma"]["energyMin"];

/* 			unordered_set<b2Shape> interactingContacts={e.a->GetType(),e.b->GetType()};
			unordered_set<b2Shape> edgeContacts={b2Shape::e_edge,b2Shape::e_circle }; */

			if(e.a->GetType()==b2Shape::e_edge && e.b->GetType()==b2Shape::e_circle ) {
				ParticleData * pData = (ParticleData*)e.b->GetBody()->GetUserData();
				if (energyUniverse<eneryGamma && pData->name=="gamma"){
					disableCollision = true;
				}
			}

			if(e.b->GetType()==b2Shape::e_edge && e.a->GetType()==b2Shape::e_circle ) {
				ParticleData * pData = (ParticleData*)e.a->GetBody()->GetUserData();
				if (energyUniverse<eneryGamma && pData->name=="gamma"){
					disableCollision = true;
				}
			}

		 	if (disableCollision) {
				contact->SetEnabled(false);
			}
		}
	}
}





