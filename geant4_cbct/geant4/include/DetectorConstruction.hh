#ifndef CBCTDetectorConstruction_h
#define CBCTDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

namespace CBCT
{

class DetectorMessenger;
/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;
  
  public:
    void SetPhantomRotation (G4double);

  public:
    G4VPhysicalVolume* Construct() override;

  private:
    G4double phantomRotation;
  
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    DetectorMessenger* fMessenger = nullptr; // messenger

    G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

