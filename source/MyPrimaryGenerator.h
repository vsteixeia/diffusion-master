#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction {
private:
    G4GeneralParticleSource* gps; // Replace G4ParticleGun with G4GeneralParticleSource

public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event* anEvent) override;
};