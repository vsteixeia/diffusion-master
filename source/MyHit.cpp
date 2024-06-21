#include "MyHit.h"
#include "G4UnitsTable.hh"

MyHit::MyHit(G4Step*aStep) : 
    m_TrackID( aStep->GetTrack()->GetTrackID() ),
    m_PID(  aStep->GetTrack()->GetParticleDefinition()->GetParticleName() ),
    m_EnDep( aStep->GetTotalEnergyDeposit() ),
    m_Position( aStep->GetPreStepPoint()->GetPosition() ),
    m_Direction( aStep->GetPreStepPoint()->GetMomentumDirection() ),
    m_Time( aStep->GetPreStepPoint()->GetGlobalTime() )


{}

void MyHit::Print(){

    G4cout 
    << "TrackID: " <<   m_TrackID 
    << " PID: "    <<   m_PID
    << " EnDep: "  <<   std::setw(7) << G4BestUnit( m_EnDep, "Energy" )
    << " Position: " << std::setw(7) << G4BestUnit( m_Position, "Length" )
    << " Direction: " << std::setw(7) << m_Direction
    << " Time: " << std::setw(7) << G4BestUnit (m_Time, "Time")
    << G4endl;

    std::ofstream outFile("output2.dat", std::ios::app);
    //outFile << "Energy Deposit: " << m_EnDep / CLHEP::MeV << " MeV" << G4endl;
    //outFile << "Time of Arrival: " << m_Time / CLHEP::ns << " ns" << G4endl;
    
    outFile << m_Time / CLHEP::ns << G4endl;
    outFile.close();
    
}