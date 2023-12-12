#ifndef CBCTEventAction_h
#define CBCTEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

namespace CBCT
{

  /// Event action class
  ///
  /// It defines data members to hold the energy deposit and track lengths
  /// of charged particles in Absober and Gap layers:
  /// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
  /// which are collected step by step via the functions
  /// - AddAbs(), AddGap()

  class EventAction : public G4UserEventAction
  {
  public:
    EventAction() = default;
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *event) override;
    void EndOfEventAction(const G4Event *event) override;

    void AddPos(G4double edep, G4ThreeVector pos);

  private:
    G4double fEdep;
    G4ThreeVector fPos;
  };

  // inline functions
  inline void EventAction::AddPos(G4double edep, G4ThreeVector pos)
  {
    fPos = (edep * pos + fEdep * fPos) / (fEdep + edep);
    fEdep += edep;
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
