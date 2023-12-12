#ifndef CBCTSteppingAction_h
#define CBCTSteppingAction_h 1

#include "G4UserSteppingAction.hh"

namespace CBCT
{
  class DetectorConstruction;
}

namespace CBCT
{

class EventAction;

/// Stepping action class.
///

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(const CBCT::DetectorConstruction* detConstruction,
                 EventAction* eventAction);
  ~SteppingAction() override = default;

  void UserSteppingAction(const G4Step* step) override;

private:
  const CBCT::DetectorConstruction* fDetConstruction = nullptr;
  EventAction* fEventAction = nullptr;
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
