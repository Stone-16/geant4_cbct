#include "EventAction.hh"
#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>


namespace CBCT
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // initialisation per event
  fPos = G4ThreeVector(0, 0, 0);
  fEdep = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //
  if (fEdep > 0)
  {
    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    
    auto eventID = event->GetEventID();

    // fill ntuple
    analysisManager->FillNtupleIColumn(0, eventID);
    analysisManager->FillNtupleDColumn(1, fPos[0]/mm);
    analysisManager->FillNtupleDColumn(2, fPos[1]/mm);
    analysisManager->FillNtupleDColumn(3, fPos[2]/mm);
    analysisManager->FillNtupleDColumn(4, fEdep/keV);
    analysisManager->AddNtupleRow();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
