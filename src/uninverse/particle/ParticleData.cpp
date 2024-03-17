#include "ParticleData.h"

int ParticleData::objectCount=0;

int ParticleData::setId() {
    ParticleData::objectCount++;
    return ParticleData::objectCount;
}

ParticleData::ParticleData(string _name, ofJson &constants ){
    name = _name;
    id = ParticleData::setId();
    color.setHex(ofHexToInt(constants["particles"][name]["settings"]["color"]));
    charge = float(constants["particles"][name]["charge"]);
}