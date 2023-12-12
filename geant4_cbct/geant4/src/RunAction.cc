#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace CBCT
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Creating ntuple
  analysisManager->CreateNtuple("CBCT", "Edep");
  analysisManager->CreateNtupleIColumn("EventID");
  analysisManager->CreateNtupleDColumn("PosX");
  analysisManager->CreateNtupleDColumn("PosY");
  analysisManager->CreateNtupleDColumn("PosZ");
  analysisManager->CreateNtupleDColumn("Edep");

  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  // G4String fileName = "data.root";
  // G4String fileName = "data.csv";
  // analysisManager->OpenFile(fileName);
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  auto analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
