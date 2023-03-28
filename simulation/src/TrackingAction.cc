#include "TrackingAction.hh"

#include "Celeritas.hh"

void TrackingAction::PreUserTrackingAction(G4Track const* track)
{
  CelerSimpleOffload().PreUserTrackingAction(const_cast<G4Track*>(track));
}
