#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"

class TrackingAction : public G4UserTrackingAction
{
  void PreUserTrackingAction(G4Track const* track);
};

#endif
