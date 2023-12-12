#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace CBCT
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
 : fDetectorConstruction(det)
{
  fDirectory = new G4UIdirectory("/CBCT/");
  fDirectory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/CBCT/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fPhantomRotationCmd = new G4UIcmdWithADoubleAndUnit("/CBCT/det/setPhantomRotation",this);
  fPhantomRotationCmd->SetGuidance("Set.");
  fPhantomRotationCmd->SetParameterName("choice",false);
  fPhantomRotationCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fPhantomRotationCmd;
  delete fDirectory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == fPhantomRotationCmd ) {
    fDetectorConstruction->SetPhantomRotation(fPhantomRotationCmd->GetNewDoubleValue(newValue));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
