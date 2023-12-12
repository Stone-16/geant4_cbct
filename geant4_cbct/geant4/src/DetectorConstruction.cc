#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4SubtractionSolid.hh"
#include "G4TessellatedSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RotationMatrix.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

namespace CBCT
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  DetectorConstruction::DetectorConstruction()
  {
    fMessenger = new DetectorMessenger(this);
    phantomRotation = 0. * deg;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  DetectorConstruction::~DetectorConstruction()
  {
    delete fMessenger;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4VPhysicalVolume *DetectorConstruction::Construct()
  {
    // Define materials
    DefineMaterials();

    // Define volumes
    return DefineVolumes();
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::DefineMaterials()
  {

    G4NistManager *man = G4NistManager::Instance();
    G4bool isotopes = false;

    G4Element *Fe = man->FindOrBuildElement("Fe", isotopes);
    G4Element *Al = man->FindOrBuildElement("Al", isotopes);
    G4Element *Cd = man->FindOrBuildElement("Cd", isotopes);
    G4Element *Zn = man->FindOrBuildElement("Zn", isotopes);
    G4Element *Te = man->FindOrBuildElement("Te", isotopes);
    G4Element *Pb = man->FindOrBuildElement("Pb", isotopes);
    G4Element *H = man->FindOrBuildElement("H", isotopes);
    G4Element *O = man->FindOrBuildElement("O", isotopes);
    G4Element *N = man->FindOrBuildElement("N", isotopes);
    G4Element *C = man->FindOrBuildElement("C", isotopes);
    G4Element *Na = man->FindOrBuildElement("Na", isotopes);
    G4Element *Mg = man->FindOrBuildElement("Mg", isotopes);
    G4Element *P = man->FindOrBuildElement("P", isotopes);
    G4Element *S = man->FindOrBuildElement("S", isotopes);
    G4Element *Cl = man->FindOrBuildElement("Cl", isotopes);
    G4Element *K = man->FindOrBuildElement("K", isotopes);
    G4Element *Ca = man->FindOrBuildElement("Ca", isotopes);
    G4Element *Sr = man->FindOrBuildElement("Sr", isotopes);
    G4Element *Zr = man->FindOrBuildElement("Zr", isotopes);
    G4Element *Si = man->FindOrBuildElement("Si", isotopes);
    G4Element *Ge = man->FindOrBuildElement("Ge", isotopes);
    G4Element *Lu = man->FindOrBuildElement("Lu", isotopes);
    G4Element *Y = man->FindOrBuildElement("Y", isotopes);
    G4Element *Ce = man->FindOrBuildElement("Ce", isotopes);
    G4Element *Bi = man->FindOrBuildElement("Bi", isotopes);
    G4Element *Gd = man->FindOrBuildElement("Gd", isotopes);
    G4Element *W = man->FindOrBuildElement("W", isotopes);
    G4Element *Mn = man->FindOrBuildElement("Mn", isotopes);
    G4Element *Cu = man->FindOrBuildElement("Cu", isotopes);
    G4Element *Cr = man->FindOrBuildElement("Cr", isotopes);
    G4Element *Ni = man->FindOrBuildElement("Ni", isotopes);
    G4Element *Ga = man->FindOrBuildElement("Ga", isotopes);
    G4Element *Cs = man->FindOrBuildElement("Cs", isotopes);
    G4Element *I = man->FindOrBuildElement("I", isotopes);
    G4Element *La = man->FindOrBuildElement("La", isotopes);
    G4Element *Br = man->FindOrBuildElement("Br", isotopes);

    // Water H2o
    man->FindOrBuildMaterial("G4_WATER");
    
    // PMMA C5H8O2
    G4Material *PMMA = new G4Material("PMMA", 1.19 * g / cm3, 3);
    PMMA->AddElement(H, 8);
    PMMA->AddElement(C, 5);
    PMMA->AddElement(O, 2);

    // PVC
    man->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");

    // Al
    man->FindOrBuildMaterial("G4_Al");

    // C
    man->FindOrBuildMaterial("G4_C");

    // CsI
    G4Material *CsI = new G4Material("CsI", 4.51 * g / cm3, 2);
    CsI->AddElement(Cs, 1);
    CsI->AddElement(I, 1);

    // Air
    man->FindOrBuildMaterial("G4_AIR");

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4VPhysicalVolume *DetectorConstruction::DefineVolumes()
  {
    // Geometry parameters
    G4double worldSizeXY = 500. * mm;
    G4double worldSizeZ = 500. * mm;

    // 模体
    G4double phantomSize = 20. * mm;
    G4ThreeVector phantomPos = G4ThreeVector(0, 0, 0);
    G4double ballSizeR = 4. * mm;
    G4ThreeVector ballPos = G4ThreeVector(5.0 * mm, 0.0 * mm, 0. * mm);
    G4double boxSize = 6. * mm;
    G4ThreeVector boxPos = G4ThreeVector(-3.0 * mm, 0.0 * mm, 0. * mm);

    // 探测器
    G4double detectorSizeX = 50. * mm;
    G4double detectorSizeY = 50. * mm;
    G4double detectorSizeZ = 1.0 * mm;
    G4ThreeVector detectorPos = G4ThreeVector(0. * mm, 0. * mm, 150. * mm);

    // Get materials
    auto defaultMaterial = G4Material::GetMaterial("G4_AIR");

    auto phantomMaterial = G4Material::GetMaterial("G4_AIR");
    auto ballMaterial = G4Material::GetMaterial("G4_Al");
    auto boxMaterial = G4Material::GetMaterial("G4_C");

    auto detectorMaterial = G4Material::GetMaterial("CsI");

    //
    // World
    //
    auto worldS = new G4Box("World",                                                 // its name
                            0.5 * worldSizeXY, 0.5 * worldSizeXY, 0.5 * worldSizeZ); // its size

    auto worldLV = new G4LogicalVolume(worldS,          // its solid
                                       defaultMaterial, // its material
                                       "World");        // its name

    auto worldPV = new G4PVPlacement(nullptr,         // no rotation
                                     G4ThreeVector(), // at (0,0,0)
                                     worldLV,         // its logical volume
                                     "World",         // its name
                                     nullptr,         // its mother  volume
                                     false,           // no boolean operation
                                     0,               // copy number
                                     fCheckOverlaps); // checking overlaps

    //
    // Phantom
    //
    auto phantomS = new G4Box("Phantom",                                                // its name
                              0.5 * phantomSize, 0.5 * phantomSize, 0.5 * phantomSize); // its size

    auto phantomLV = new G4LogicalVolume(phantomS,        // its solid
                                         phantomMaterial, // its material
                                         "Phantom");      // its name

    G4RotationMatrix *rotation = new G4RotationMatrix();
    rotation->rotateY(phantomRotation);

    new G4PVPlacement(rotation,        // rotation
                      phantomPos,      // at (0,0,0)
                      phantomLV,       // its logical volume
                      "Phantom",       // its name
                      worldLV,         // its mother  volume
                      false,           // no boolean operation
                      0,               // copy number
                      fCheckOverlaps); // overlaps checking

    //
    // Ball
    //
    auto ballS = new G4Orb("Ball",                                                     // its name
                            ballSizeR); // its size

    auto ballLV = new G4LogicalVolume(ballS,        // its solid
                                       ballMaterial, // its material
                                       "Ball1");      // its name

    new G4PVPlacement(nullptr,         // no rotation
                      ballPos,        // at (0,0,0)
                      ballLV,         // its logical volume
                      "Ball",         // its name
                      phantomLV,       // its mother  volume
                      false,           // no boolean operation
                      0,               // copy number
                      fCheckOverlaps); // overlaps checking
    
    //
    // Box
    //
    auto boxS = new G4Box("Box",                                        // its name
                          0.5 * boxSize, 0.5 * boxSize, 0.5 * boxSize); // its size

    auto boxLV = new G4LogicalVolume(boxS,        // its solid
                                     boxMaterial, // its material
                                     "Box");      // its name

    new G4PVPlacement(nullptr,         // no rotation
                      boxPos,          // at (0,0,0)
                      boxLV,           // its logical volume
                      "Box",           // its name
                      phantomLV,       // its mother  volume
                      false,           // no boolean operation
                      0,               // copy number
                      fCheckOverlaps); // overlaps checking

    //
    // Detector
    //
    auto detectorS = new G4Box("Detector",                                                     // its name
                               detectorSizeX * 0.5, detectorSizeY * 0.5, detectorSizeZ * 0.5); // its size

    auto detectorLV = new G4LogicalVolume(detectorS,        // its solid
                                          detectorMaterial, // its material
                                          "Detector");      // its name

    new G4PVPlacement(nullptr,         // no rotation
                      detectorPos,     // at (0,0,0)
                      detectorLV,      // its logical volume
                      "Detector",      // its name
                      worldLV,         // its mother  volume
                      false,           // no boolean operation
                      0,               // copy number
                      fCheckOverlaps); // checking overlaps

    //
    // Visualization attributes
    //
    // worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());

    auto simpleBoxVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    simpleBoxVisAtt->SetVisibility(true);
    boxLV->SetVisAttributes(simpleBoxVisAtt);
    ballLV->SetVisAttributes(simpleBoxVisAtt);
    detectorLV->SetVisAttributes(simpleBoxVisAtt);
    //
    // Always return the physical World
    //
    return worldPV;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  void DetectorConstruction::SetPhantomRotation(G4double val)
  {
    phantomRotation = val;
  }

}

  
