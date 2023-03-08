
#include "ActionInitialization.hh"

#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

#include <corecel/io/Logger.hh>
#include <corecel/sys/Environment.hh>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const { SetUserAction(new MasterRunAction); }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);

  EventAction* eventAction = new EventAction();
  SetUserAction(eventAction);

  RunAction* runAction = new RunAction(eventAction);
  SetUserAction(runAction);

  SetUserAction(new SteppingAction(eventAction));

  if (! celeritas::getenv("CELER_DISABLE").empty()) {
    CELER_LOG(info) << "Disabling Celeritas offloading since the 'CELER_DISABLE' "
                       "environment variable is present and non-empty";
  }
  else {
    SetUserAction(new TrackingAction());
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
