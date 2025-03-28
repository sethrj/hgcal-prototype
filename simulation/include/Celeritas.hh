#ifndef Celeritas_h
#define Celeritas_h 1

#include <accel/SimpleOffload.hh>

// Global shared setup options
celeritas::SetupOptions& CelerSetupOptions();
// Shared data and GPU setup
celeritas::SharedParams& CelerSharedParams();
// Thread-local transporter
celeritas::LocalTransporter& CelerLocalTransporter();
// Thread-local offload
celeritas::SimpleOffload& CelerSimpleOffload();

#endif
