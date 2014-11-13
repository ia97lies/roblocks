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
    virtual void InitializePhysics() override;
    virtual void ShutdownPhysics() override;

    void CreateObjects();

};
