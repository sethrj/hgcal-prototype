#ifndef RunAction_h
#define RunAction_h 1

#include "G4Accumulable.hh"
#include "G4AnalysisManager.hh"
#include "G4GenericMessenger.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

#include "EventAction.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class EventAction;

class RunAction : public G4UserRunAction
{
 public:
  RunAction(EventAction*);
  virtual ~RunAction();

  // virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

 private:
  EventAction* fEventAction;
  G4String fOutputFileDir;
  G4GenericMessenger* fMessenger;
};

class MasterRunAction : public G4UserRunAction
{
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
};

#endif
