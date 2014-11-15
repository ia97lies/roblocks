//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#ifndef _BULLETOPENGLAPP_H_
#define _BULLETOPENGLAPP_H_

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
// includes for convex hulls
#include "BulletCollision/CollisionShapes/btConvexPolyhedron.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

// include our custom Motion State object
#include "Synthetics/Graphic.h"
#include "Synthetics/OpenGLMotionState.h"
#include "Synthetics/GameObject.h"
#include "Synthetics/DebugDrawer.h"
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

// Collision groups for different types of objects. Each value
// is represented by a single bit
enum CollisionGroups {
  COLGROUP_NONE  = 0,
  COLGROUP_STATIC = 1 << 0,
  COLGROUP_BOX  = 1 << 1,
  COLGROUP_SPHERE = 1 << 2
};

// a convenient typedef to reference an STL vector of GameObjects
typedef std::vector<GameObject*> GameObjects;

// convenient typedefs for collision events
typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;
typedef std::set<CollisionPair> CollisionPairs;

// struct to store our raycasting results
struct RayResult {
  btRigidBody* pBody;
  btVector3 hitPoint;
};

class BulletOpenGLApplication {
  public:
    BulletOpenGLApplication();
    ~BulletOpenGLApplication();
    void initialize();
    // FreeGLUT callbacks //
    virtual void Keyboard(unsigned char key, int x, int y);
    virtual void KeyboardUp(unsigned char key, int x, int y);
    virtual void Special(int key, int x, int y);
    virtual void SpecialUp(int key, int x, int y);
    virtual void Reshape(int w, int h);
    virtual void Idle();
    virtual void Mouse(int button, int state, int x, int y);
    virtual void PassiveMotion(int x, int y);
    virtual void Motion(int x, int y);
    virtual void Display();

    // rendering. Can be overrideen by derived classes
    virtual void renderScene();

    // scene updating. Can be overridden by derived classes
    virtual void updateScene(float dt);

    // physics functions. Can be overriden by derived classes (like BasicDemo)
    virtual void initializePhysics() {};
    virtual void shutdownPhysics() {};

    // camera functions
    void updateCamera();
    void rotateCamera(float &angle, float value);
    void zoomCamera(float distance);

    Graphic *getGraphic() { return m_graphic; }

    // object functions
    GameObject* createGameObject(btCollisionShape* pShape, 
        const float &mass, 
        const btVector3 &color = btVector3(1.0f,1.0f,1.0f), 
        const btVector3 &initialPosition = btVector3(0.0f,0.0f,0.0f), 
        short int group = -1,
        short int mask = -1,
        const btQuaternion &initialRotation = btQuaternion(0,0,1,1));

    void destroyGameObject(btRigidBody* pBody);
    GameObject* findGameObject(btRigidBody* pBody);

    // picking functions
    btVector3 getPickingRay(int x, int y);
    bool raycast(const btVector3 &startPosition, const btVector3 &direction, RayResult &output, bool includeStatic = false);
	

    // constraint functions
    void createPickingConstraint(int x, int y);
    void removePickingConstraint();

    // collision event functions
    void checkForCollisionEvents();
    virtual void collisionEvent(btRigidBody* pBody0, btRigidBody * pBody1);
    virtual void separationEvent(btRigidBody * pBody0, btRigidBody * pBody1);

  protected:
    // camera control
    btVector3 m_cameraPosition; // the camera's current position
    btVector3 m_cameraTarget;	 // the camera's lookAt target
    float m_nearPlane; // minimum distance the camera will render
    float m_farPlane; // farthest distance the camera will render
    btVector3 m_upVector; // keeps the camera rotated correctly
    float m_cameraDistance; // distance from the camera to its target
    float m_cameraPitch; // pitch of the camera 
    float m_cameraYaw; // yaw of the camera

    int m_screenWidth;
    int m_screenHeight;

    // core Bullet components
    btBroadphaseInterface* m_pBroadphase;
    btCollisionConfiguration* m_pCollisionConfiguration;
    btCollisionDispatcher* m_pDispatcher;
    btConstraintSolver* m_pSolver;
    btDynamicsWorld* m_pWorld;

    // our custom motion state
    OpenGLMotionState* m_pMotionState;

    // a simple clock for counting time
    btClock m_clock;

    // an array of our game objects
    GameObjects m_objects;
    GameObject *m_selectedGameObj;

    // debug renderer
    DebugDrawer* m_pDebugDrawer;

    // constraint variables
    btRigidBody* m_pPickedBody;				// the body we picked up
    btTypedConstraint*  m_pPickConstraint;	// the constraint the body is attached to
    btScalar m_oldPickingDist;				// the distance from the camera to the hit point (so we can move the object up, down, left and right from our view)

    // collision event variables
    CollisionPairs m_pairsLastUpdate;

    // grep an object with mouse
    bool m_grepObject;

    // grapic abstraction
    Graphic *m_graphic;
};
#endif

