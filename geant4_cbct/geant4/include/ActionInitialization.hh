#ifndef CBCTActionInitialization_h
#define CBCTActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


namespace CBCT
{
  class DetectorConstruction;
}

namespace CBCT
{

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(CBCT::DetectorConstruction*);
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;

  private:
    CBCT::DetectorConstruction* fDetConstruction = nullptr;
};

}

#endif


