/* ========================================================================

    This is a series of tutorials on Geant4

    Compile it with
    source compile.sh

    or take a look inside compile.sh to see the command line.

    Where YOU have to define ${G4INCLUDES} to point to the include files in 
    your local installation.

    Gustavo Valdiviesso 2020

   ======================================================================== */

#include <iostream>

// The Detector
#include "source/MyDetector.h"

// The Action Initialization (particle source)
#include "source/MyActionInitialization.h"

// The User's Actions
#include "source/MyRunAction.h"
#include "source/MyEventAction.h"

// The Physics List
#include "G4VUserPhysicsList.hh"
#include "G4PhysListFactory.hh"
// We are going to import a pre-made physics list called "Shielding"
// You can find other options at https://geant4.web.cern.ch/node/302

// The Manager
#include "G4RunManager.hh"

// This is the User Interface
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"

#define G4VIS_USE_OPENGLX
#define G4VIS_USE_OPENGLQT

// This is the Visualization Engine
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

// Optical Physics
#include "G4OpticalPhysics.hh"

// Step limits
//#include "G4StepLimiterPhysics.hh"

//G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
//stepLimitPhys->SetApplyToAll(true); // activates step limit for ALL particles
//RegisterPhysics(stepLimitPhys);

// This is the Main code.
int main(int argc, char** argv){

    auto *runManager = new G4RunManager();

    auto *factory = new G4PhysListFactory();
    auto *physicsList = factory->GetReferencePhysList("Shielding");
    physicsList->RegisterPhysics( new G4OpticalPhysics() );

    runManager->SetUserInitialization( new MyDetector() );
    runManager->SetUserInitialization( physicsList );
    runManager->SetUserInitialization( new MyActionInitialization() );
    runManager->SetUserAction( new MyRunAction() );
    runManager->SetUserAction( new MyEventAction() );
    runManager->Initialize();

    
    auto *visManager = new G4VisExecutive();
    visManager->Initialise();

	//auto *uiExecutive = new G4UIExecutive(argc,argv,"Qt");
    auto *uiExecutive = new G4UIExecutive(argc,argv,"csh");


	if (argc == 1){
        uiExecutive->SessionStart();
	} else {
		auto *uiManager = G4UImanager::GetUIpointer();
		uiManager->ApplyCommand("/control/execute " + G4String(argv[1]) );
        //uiExecutive->SessionStart();
	}

    //const G4double timeStep = 1.0 * CLHEP::ns;  // Time step for time-lapse simulation
    //const G4double totalTime = 100.0 * CLHEP::ns;  // Total time for simulation

    // Perform the time-lapse simulation
    //G4double currentTime = 0.0;
    //while (currentTime < totalTime) {
    //    runManager->BeamOn(1);
    //    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    //    UImanager->ApplyCommand("/run/beamOn 10");
    //    currentTime += timeStep;
    //}

    delete runManager; // The runManager will delete all other pointers owned by it.
	delete uiExecutive;
    delete visManager;
};