#include "Particle.h"

Particle::Particle(map<string, b2World *> &worlds, ofJson &settings, ofJson &constants, float x, float y, string _name) {

        setPhysics(settings["box2d"]["physics"]["density"], settings["box2d"]["physics"]["bounce"], settings["box2d"]["physics"]["friction"]);
		if ((_name == "nu_e") || (_name == "nu_e_bar") ){
        	setup(worlds["neutrinos"], x, y, constants["particles"][_name]["settings"]["radius"]);

		} else {
			setup(worlds["general"], x, y, constants["particles"][_name]["settings"]["radius"]);			
		};
        setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
		setData(new ParticleData(_name, constants));
		

		// we are using a Data pointer because 
		// box2d needs to have a pointer not 
		// a referance
		//setData(new ParticleData());
		//auto * theData = (ParticleData*)getData();
		//theData->id = ofRandom(0, 100);
		//theData->name += abc[(int)ofRandom(0, abc.size())];
		//theData->color.setHex(colors[(int)ofRandom(0, 3)]);
		//printf("setting the custom data!\n");
}

//implement Particle class destructor
Particle::~Particle()
{
	destroy();
}

void Particle::draw() {
		
        auto * theData = (ParticleData*)getData();
        
		if(theData) {
			
			// Evan though we know the data object lets just 
			// see how we can get the data out from box2d
			// you would use this when using a contact listener
			// or tapping into box2d's solver.
			
			float radius = getRadius();
			ofPushMatrix();
			ofTranslate(getPosition());
			ofRotateDeg(getRotation());
			ofSetColor(theData->color);
			ofFill();
			ofDrawCircle(0, 0, radius);
			
/*             float textSize = radius/10;
            ofPushMatrix();
            ofScale(textSize, textSize);
			ofSetColor(255);
			ofDrawBitmapString(theData->name, -textSize, textSize);
            ofPopMatrix(); */
            
			ofPopMatrix();
		}
}


