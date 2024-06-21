#include "MyPrimaryGenerator.h"
#include "G4GeneralParticleSource.hh"

MyPrimaryGenerator::MyPrimaryGenerator() : 
    G4VUserPrimaryGeneratorAction(), 
    gps(new G4GeneralParticleSource())
{

};

MyPrimaryGenerator::~MyPrimaryGenerator() {
    delete gps;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {
    gps->GeneratePrimaryVertex(anEvent);
};