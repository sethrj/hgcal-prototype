#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4FieldManager.hh"
#include "G4GenericMessenger.hh"
#include "G4LogicalVolume.hh"
#include "G4ProductionCuts.hh"
#include "G4RunManager.hh"
#include "G4TransportationManager.hh"
#include "G4UImanager.hh"
#include "G4UniformMagField.hh"
#include "G4UserLimits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "SiPMSD.hh"
#include "SiliconPixelSD.hh"
#include "materials.hh"

#include <vector>

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();

  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  /// Get field vector in native units
  static G4ThreeVector GetMagneticField();

 protected:
  G4LogicalVolume* fScoringVolume;

 private:
  G4LogicalVolume* logicWorld;
  std::vector<std::pair<std::string, G4double>> dz_map;
  G4double default_viewpoint;
  void DefineCommands();
  G4GenericMessenger* fMessenger;
  void SelectConfiguration(G4int val);
  void SetStepSizeSilicon(G4double val);
  void SetMagneticFieldStrength(G4double val);
  G4int _configuration;

  G4MagneticField* magField;
  HGCalTBMaterials* materials;

  static double fFieldStrength;

  void ConstructHGCal();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
