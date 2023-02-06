#include "TrackingAction.hh"

#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4Track.hh"

#include "Celeritas.hh"
#include <accel/ExceptionConverter.hh>

#include <algorithm>

void TrackingAction::PreUserTrackingAction(G4Track const* track)
{
  static G4ParticleDefinition const* const allowed_particles[] = {
    G4Gamma::Gamma(),
    G4Electron::Electron(),
    G4Positron::Positron(),
  };

  if (std::find(std::begin(allowed_particles), std::end(allowed_particles),
        track->GetDefinition()) != std::end(allowed_particles))
  {
    // Celeritas is transporting this track
    celeritas::ExceptionConverter call_g4exception{"celer0003"};
    CELER_TRY_HANDLE(CelerLocalTransporter().Push(*track), call_g4exception);
    const_cast<G4Track*>(track)->SetTrackStatus(fStopAndKill);
  }
}
