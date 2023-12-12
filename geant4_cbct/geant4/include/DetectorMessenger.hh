#ifndef CBCTDetectorMessenger_h
#define CBCTDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

namespace CBCT
{

class DetectorConstruction;

/// Messenger class that defines commands for DetectorConstruction.

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction* );
    ~DetectorMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    DetectorConstruction *fDetectorConstruction = nullptr;

    G4UIdirectory *fDirectory = nullptr;
    G4UIdirectory *fDetDirectory = nullptr;

    G4UIcmdWithADoubleAndUnit *fPhantomRotationCmd = nullptr;
};

}

#endif
