//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#include "BulletOpenGLApplication.h"
#include "BulletDynamics/btBulletDynamicsCommon.h"

class Synthetics : public BulletOpenGLApplication {
  public:
    Synthetics();
    virtual void initializePhysics() override;
    virtual void shutdownPhysics() override;

    void createObjects();

};
