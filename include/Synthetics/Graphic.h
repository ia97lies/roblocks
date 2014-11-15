//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#ifndef _SYNTHETICS_GRAPHIC_H_
#define _SYNTHETICS_GRAPHIC_H_

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
// includes for convex hulls
#include "BulletCollision/CollisionShapes/btConvexPolyhedron.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

// include our custom Motion State object
#include "Synthetics/OpenGLMotionState.h"
#include "Synthetics/GameObject.h"
#include "Synthetics/DebugDrawer.h"
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

class Graphic {
  public:
    Graphic();
    ~Graphic();

    void initialize();
    void resizeScreen(int width, int hight);
    void prepareBuffer();
    void swapBuffer();

    void drawBox(const btVector3 &halfSize); 
    void drawSphere(const btScalar &radius);
    void drawCylinder(const btScalar &radius, const btScalar &halfHeight);
    void drawConvexHull(const btCollisionShape* shape);
    void drawShape(
        btScalar* transform, 
        const btCollisionShape* pShape, 
        const btVector3 &color,
        bool transparent = false
    );
};
#endif

