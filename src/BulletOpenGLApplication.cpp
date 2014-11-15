//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#include "Synthetics/BulletOpenGLApplication.h"

// Some constants for 3D math and the camera speed
#define RADIANS_PER_DEGREE 0.01745329f
#define CAMERA_STEP_SIZE 5.0f

// --------------------------------------------------------------------------
BulletOpenGLApplication::BulletOpenGLApplication() 
  : m_cameraPosition(10.0f, 5.0f, 0.0f),
    m_cameraTarget(0.0f, 0.0f, 0.0f),
    m_cameraDistance(15.0f),
    m_cameraPitch(20.0f),
    m_cameraYaw(0.0f),
    m_upVector(0.0f, 1.0f, 0.0f),
    m_nearPlane(1.0f),
    m_farPlane(1000.0f),
    m_pBroadphase(NULL),
    m_pCollisionConfiguration(NULL),
    m_pDispatcher(NULL),
    m_pSolver(NULL),
    m_pWorld(NULL),
    m_pPickedBody(NULL),
    m_pPickConstraint(NULL),
    m_selectedGameObj(NULL),
    m_grepObject(false)
{
  m_graphic = new Graphic();
}

// --------------------------------------------------------------------------
BulletOpenGLApplication::~BulletOpenGLApplication() 
{
  // shutdown the physics system
  shutdownPhysics();
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::initialize() 
{
  // initialize graphic system
  getGraphic()->initialize();

  // initialize physics system
  initializePhysics();

  // create the debug drawer
  m_pDebugDrawer = new DebugDrawer();
  // set the initial debug level to 0
  m_pDebugDrawer->setDebugMode(0);
  // add the debug drawer to the world
  m_pWorld->setDebugDrawer(m_pDebugDrawer);
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Keyboard(unsigned char key, int x, int y) 
{
  // This function is called by FreeGLUT whenever
  // generic keys are pressed down.
  switch(key) {
    // zooms in
    case 'y': zoomCamera(+CAMERA_STEP_SIZE); break;
              // zoom out
    case 'x': zoomCamera(-CAMERA_STEP_SIZE); break;
              // toggle wireframe debug drawing
    case 'w': m_pDebugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
              break;
              // toggle AABB debug drawing
    case 'b': m_pDebugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
              break;
              // release picked object
    case 'r': removePickingConstraint();
              m_grepObject = false;
              break;
              // quit the app
    case 'q': glutLeaveMainLoop();
              // destroy object
    case 'd': {
                // create a temp object to store the raycast result
                RayResult result;
                // perform the raycast
                if (!raycast(m_cameraPosition, getPickingRay(x, y), result))
                  return; // return if the test failed
                // destroy the corresponding game object
                destroyGameObject(result.pBody);
                break;
              }

  }
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::KeyboardUp(unsigned char key, int x, int y) {}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Special(int key, int x, int y) 
{
  // This function is called by FreeGLUT whenever special keys
  // are pressed down, like the arrow keys, or Insert, Delete etc.
  switch(key) {
    // the arrow keys rotate the camera up/down/left/right
    case GLUT_KEY_LEFT: 
      rotateCamera(m_cameraYaw, +CAMERA_STEP_SIZE); break;
    case GLUT_KEY_RIGHT:
      rotateCamera(m_cameraYaw, -CAMERA_STEP_SIZE); break;
    case GLUT_KEY_UP:	
      rotateCamera(m_cameraPitch, +CAMERA_STEP_SIZE); break;
    case GLUT_KEY_DOWN:	
      rotateCamera(m_cameraPitch, -CAMERA_STEP_SIZE); break;
  }
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::SpecialUp(int key, int x, int y) {}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Reshape(int w, int h) 
{
  // this function is called once during application intialization
  // and again every time we resize the window

  // grab the screen width/height
  m_screenWidth = w;
  m_screenHeight = h;
  // set the viewport
  getGraphic()->resizeScreen(w, h);
  // update the camera
  updateCamera();
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Idle() 
{
  // this function is called frequently, whenever FreeGlut
  // isn't busy processing its own events. It should be used
  // to perform any updating and rendering tasks

  // clear the backbuffer
  getGraphic()->prepareBuffer();

  // get the time since the last iteration
  float dt = m_clock.getTimeMilliseconds();
  // reset the clock to 0
  m_clock.reset();
  // update the scene (convert ms to s)
  updateScene(dt / 1000.0f);

  // update the camera
  updateCamera();

  // render the scene
  renderScene();

  // swap the front and back buffers
  getGraphic()->swapBuffer();
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Mouse(int button, int state, int x, int y) 
{
  switch(button) {
		case 0:  // left mouse button
      {
        if (state == 0) { // button down
          m_grepObject = true;
          // create the picking constraint when we click the LMB
          createPickingConstraint(x, y);
        } else { // button up
          m_grepObject = false;
        }
        break;
      }
    case 2: // right mouse button
      {
        if (state == 0) { // pressed down
          // select object
          if (m_selectedGameObj == NULL) {
            RayResult output;
            if (raycast(m_cameraPosition, getPickingRay(x, y), output)) {
              m_selectedGameObj = findGameObject(output.pBody);
              m_selectedGameObj->select();
            }
          }
          else {
            m_selectedGameObj->deselect();
            m_selectedGameObj = NULL;
          }
        }
        break;
      }
  }
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::PassiveMotion(int x, int y) {}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Motion(int x, int y) 
{
  // did we pick a body with the LMB?
  if (m_pPickedBody && m_grepObject) {
    btGeneric6DofConstraint* pickCon = static_cast<btGeneric6DofConstraint*>(m_pPickConstraint);
    if (!pickCon)
      return;

    // use another picking ray to get the target direction
    btVector3 dir = getPickingRay(x,y) - m_cameraPosition;
    dir.normalize();

    // use the same distance as when we originally picked the object
    dir *= m_oldPickingDist;
    btVector3 newPivot = m_cameraPosition + dir;

    // set the position of the constraint
    pickCon->getFrameOffsetA().setOrigin(newPivot);
  }
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::Display() {}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::updateCamera() 
{
  // exit in erroneous situations
  if (m_screenWidth == 0 && m_screenHeight == 0)
    return;

  // select the projection matrix
  glMatrixMode(GL_PROJECTION);
  // set it to the matrix-equivalent of 1
  glLoadIdentity();
  // determine the aspect ratio of the screen
  float aspectRatio = m_screenWidth / (float)m_screenHeight;
  // create a viewing frustum based on the aspect ratio and the
  // boundaries of the camera
  glFrustum (-aspectRatio * m_nearPlane, aspectRatio * m_nearPlane, -m_nearPlane, m_nearPlane, m_nearPlane, m_farPlane);
  // the projection matrix is now set

  // select the view matrix
  glMatrixMode(GL_MODELVIEW);
  // set it to '1'
  glLoadIdentity();

  // our values represent the angles in degrees, but 3D 
  // math typically demands angular values are in radians.
  float pitch = m_cameraPitch * RADIANS_PER_DEGREE;
  float yaw = m_cameraYaw * RADIANS_PER_DEGREE;

  // create a quaternion defining the angular rotation 
  // around the up vector
  btQuaternion rotation(m_upVector, yaw);

  // set the camera's position to 0,0,0, then move the 'z' 
  // position to the current value of m_cameraDistance.
  btVector3 cameraPosition(0,0,0);
  cameraPosition[2] = -m_cameraDistance;

  // create a Bullet Vector3 to represent the camera 
  // position and scale it up if its value is too small.
  btVector3 forward(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
  if (forward.length2() < SIMD_EPSILON) {
    forward.setValue(1.f,0.f,0.f);
  }

  // figure out the 'right' vector by using the cross 
  // product on the 'forward' and 'up' vectors
  btVector3 right = m_upVector.cross(forward);

  // create a quaternion that represents the camera's roll
  btQuaternion roll(right, - pitch);

  // turn the rotation (around the Y-axis) and roll (around 
  // the forward axis) into transformation matrices and 
  // apply them to the camera position. This gives us the 
  // final position
  cameraPosition = btMatrix3x3(rotation) * btMatrix3x3(roll) * cameraPosition;

  // save our new position in the member variable, and 
  // shift it relative to the target position (so that we 
  // orbit it)
  m_cameraPosition[0] = cameraPosition.getX();
  m_cameraPosition[1] = cameraPosition.getY();
  m_cameraPosition[2] = cameraPosition.getZ();
  m_cameraPosition += m_cameraTarget;

  // create a view matrix based on the camera's position and where it's
  // looking
  gluLookAt(m_cameraPosition[0], 
            m_cameraPosition[1], 
            m_cameraPosition[2], 
            m_cameraTarget[0], 
            m_cameraTarget[1], 
            m_cameraTarget[2], 
            m_upVector.getX(), 
            m_upVector.getY(), 
            m_upVector.getZ());
  // the view matrix is now set
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::rotateCamera(float &angle, float value) 
{
  // change the value (it is passed by reference, so we
  // can edit it here)
  angle -= value; 
  // keep the value within bounds
  if (angle < 0) angle += 360; 
  if (angle >= 360) angle -= 360;
  // update the camera since we changed the angular value
  updateCamera(); 
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::zoomCamera(float distance) {
  // change the distance value
  m_cameraDistance -= distance;
  // prevent it from zooming in too far
  if (m_cameraDistance < 0.1f) m_cameraDistance = 0.1f;
  // update the camera since we changed the zoom distance
  updateCamera();
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::renderScene() {
	// create an array of 16 floats (representing a 4x4 matrix)
	btScalar transform[16];

	// iterate through all of the objects in our world
	for(GameObjects::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		// get the object from the iterator
		GameObject* pObj = *i;

		// read the transform
		pObj->getTransform(transform);

		// get data from the object and draw it
		getGraphic()->drawShape(transform, pObj->getShape(), pObj->getColor());
	}

  // after rendering all game objects, perform debug rendering
  // Bullet will figure out what needs to be drawn then call to
  // our DebugDrawer class to do the rendering for us
  m_pWorld->debugDrawWorld();
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::updateScene(float dt) {
  // check if the world object exists
  if (m_pWorld) {
    // step the simulation through time. This is called
    // every update and the amount of elasped time was 
    // determined back in ::Idle() by our clock object.
    m_pWorld->stepSimulation(dt);

    // check for any new collisions/separations
    checkForCollisionEvents();
  }
}

// --------------------------------------------------------------------------
GameObject* BulletOpenGLApplication::createGameObject(
    btCollisionShape* pShape, 
    const float &mass, 
    const btVector3 &color, 
    const btVector3 &initialPosition, 
    short group, 
    short mask, 
    const btQuaternion &initialRotation
)
{
  // create a new game object
  GameObject* pObject = new GameObject(pShape, mass, color, initialPosition, initialRotation);

  // push it to the back of the list
  m_objects.push_back(pObject);

  // check if the world object is valid
  if (m_pWorld) {
    // add the object's rigid body to the world
    m_pWorld->addRigidBody(pObject->getRigidBody(), group, mask);
  }
  return pObject;
}

// --------------------------------------------------------------------------
btVector3 BulletOpenGLApplication::getPickingRay(int x, int y) {
  // calculate the field-of-view
  float tanFov = 1.0f / m_nearPlane;

  // get a ray pointing forward from the 
  // camera and extend it to the far plane
  btVector3 rayFrom = m_cameraPosition;
  btVector3 rayForward = (m_cameraTarget - m_cameraPosition);
  rayForward.normalize();
  rayForward*= m_farPlane;

  // find the horizontal and vertical vectors 
  // relative to the current camera view
  btVector3 ver = m_upVector;
  btVector3 hor = rayForward.cross(ver);
  hor.normalize();
  ver = hor.cross(rayForward);
  ver.normalize();
  hor *= 2.f * m_farPlane * tanFov;
  ver *= 2.f * m_farPlane * tanFov;

  // calculate the aspect ratio
  btScalar aspect = m_screenWidth / (btScalar)m_screenHeight;

  // adjust the forward-ray based on
  // the X/Y coordinates that were clicked
  hor*=aspect;
  btVector3 rayToCenter = rayFrom + rayForward;
  btVector3 dHor = hor * 1.f/float(m_screenWidth);
  btVector3 dVert = ver * 1.f/float(m_screenHeight);
  btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * ver;
  rayTo += btScalar(x) * dHor;
  rayTo -= btScalar(y) * dVert;

  // return the final result
  return rayTo;
}

// --------------------------------------------------------------------------
bool BulletOpenGLApplication::raycast(
    const btVector3 &startPosition, 
    const btVector3 &direction, 
    RayResult &output, 
    bool includeStatic
)
{
  if (!m_pWorld) 
    return false;

  // get the picking ray from where we clicked
  btVector3 rayTo = direction;
  btVector3 rayFrom = startPosition;

  // create our raycast callback object
  btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);

  // perform the raycast
  m_pWorld->rayTest(rayFrom,rayTo,rayCallback);

  // did we hit something?
  if (rayCallback.hasHit())
  {
    // if so, get the rigid body we hit
    btRigidBody* pBody = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
    if (!pBody)
      return false;

    // prevent us from picking objects 
    // like the ground plane
    if (!includeStatic) // skip this check if we want it to hit static objects
      if (pBody->isStaticObject() || pBody->isKinematicObject()) 
        return false;

    // set the result data
    output.pBody = pBody;
    output.hitPoint = rayCallback.m_hitPointWorld;
    return true;
  }

  // we didn't hit anything
  return false;
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::destroyGameObject(btRigidBody* pBody) {
  // we need to search through the objects in order to 
  // find the corresponding iterator (can only erase from 
  // an std::vector by passing an iterator)
  for (GameObjects::iterator iter = m_objects.begin(); iter != m_objects.end(); ++iter) {
    if ((*iter)->getRigidBody() == pBody) {
      GameObject* pObject = *iter;
      // remove the rigid body from the world
      m_pWorld->removeRigidBody(pObject->getRigidBody());
      // erase the object from the list
      m_objects.erase(iter);
      // delete the object from memory
      delete pObject;
      // done
      return;
    }
  }
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::createPickingConstraint(int x, int y) {
  if (!m_pWorld) 
    return;
  if (m_pPickedBody)
    return;

  // perform a raycast and return if it fails
  RayResult output;
  if (!raycast(m_cameraPosition, getPickingRay(x, y), output))
    return;

  // store the body for future reference
  m_pPickedBody = output.pBody;

  // prevent the picked object from falling asleep
  // else it could freeze
  m_pPickedBody->setActivationState(DISABLE_DEACTIVATION);

  // get the hit position relative to the body we hit 
  btVector3 localPivot = m_pPickedBody->getCenterOfMassTransform().inverse() * output.hitPoint;

  // create a transform for the pivot point
  btTransform pivot;
  pivot.setIdentity();
  pivot.setOrigin(localPivot);

  // create our constraint object
  btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*m_pPickedBody, pivot, true);
  dof6->setAngularLowerLimit(btVector3(0,0,0));
  dof6->setAngularUpperLimit(btVector3(0,0,0));

  // add the constraint to the world
  m_pWorld->addConstraint(dof6,true);

  // store a pointer to our constraint
  m_pPickConstraint = dof6;

  // define the 'strength' of our constraint (each axis)
  float cfm = 0.5f;
  dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,0);
  dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,1);
  dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,2);
  dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,3);
  dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,4);
  dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,5);

  // define the 'error reduction' of our constraint (each axis)
  float erp = 0.5f;
  dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,0);
  dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,1);
  dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,2);
  dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,3);
  dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,4);
  dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,5);

  // save this data for future reference
  m_oldPickingDist  = (output.hitPoint - m_cameraPosition).length();
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::removePickingConstraint() {
  // exit in erroneous situations
  if (!m_pPickConstraint || !m_pWorld) 
    return;

  // remove the constraint from the world
  m_pWorld->removeConstraint(m_pPickConstraint);

  // delete the constraint object
  delete m_pPickConstraint;

  // reactivate the body
  m_pPickedBody->forceActivationState(ACTIVE_TAG);
  m_pPickedBody->setDeactivationTime( 0.f );

  // clear the pointers
  m_pPickConstraint = NULL;
  m_pPickedBody = NULL;
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::checkForCollisionEvents() {
  // keep a list of the collision pairs we
  // found during the current update
  CollisionPairs pairsThisUpdate;

  // iterate through all of the manifolds in the dispatcher
  for (int i = 0; i < m_pDispatcher->getNumManifolds(); ++i) {

    // get the manifold
    btPersistentManifold* pManifold = m_pDispatcher->getManifoldByIndexInternal(i);

    // ignore manifolds that have 
    // no contact points.
    if (pManifold->getNumContacts() > 0) {
      // get the two rigid bodies involved in the collision
      const btRigidBody* pBody0 = static_cast<const btRigidBody*>(pManifold->getBody0());
      const btRigidBody* pBody1 = static_cast<const btRigidBody*>(pManifold->getBody1());

      // always create the pair in a predictable order
      // (use the pointer value..)
      bool const swapped = pBody0 > pBody1;
      const btRigidBody* pSortedBodyA = swapped ? pBody1 : pBody0;
      const btRigidBody* pSortedBodyB = swapped ? pBody0 : pBody1;

      // create the pair
      CollisionPair thisPair = std::make_pair(pSortedBodyA, pSortedBodyB);

      // insert the pair into the current list
      pairsThisUpdate.insert(thisPair);

      // if this pair doesn't exist in the list
      // from the previous update, it is a new
      // pair and we must send a collision event
      if (m_pairsLastUpdate.find(thisPair) == m_pairsLastUpdate.end()) {
        collisionEvent((btRigidBody*)pBody0, (btRigidBody*)pBody1);
      }
    }
  }

  // create another list for pairs that
  // were removed this update
  CollisionPairs removedPairs;

  // this handy function gets the difference beween
  // two sets. It takes the difference between
  // collision pairs from the last update, and this 
  // update and pushes them into the removed pairs list
  std::set_difference( m_pairsLastUpdate.begin(), m_pairsLastUpdate.end(),
      pairsThisUpdate.begin(), pairsThisUpdate.end(),
      std::inserter(removedPairs, removedPairs.begin()));

  // iterate through all of the removed pairs
  // sending separation events for them
  for (CollisionPairs::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); ++iter) {
    separationEvent((btRigidBody*)iter->first, (btRigidBody*)iter->second);
  }

  // in the next iteration we'll want to
  // compare against the pairs we found
  // in this iteration
  m_pairsLastUpdate = pairsThisUpdate;
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::collisionEvent(btRigidBody * pBody0, btRigidBody * pBody1) {
}

// --------------------------------------------------------------------------
void BulletOpenGLApplication::separationEvent(btRigidBody * pBody0, btRigidBody * pBody1) {
}

// --------------------------------------------------------------------------
GameObject* BulletOpenGLApplication::findGameObject(btRigidBody* pBody) {
  // search through our list of gameobjects finding
  // the one with a rigid body that matches the given one
  for (GameObjects::iterator iter = m_objects.begin(); iter != m_objects.end(); ++iter) {
    if ((*iter)->getRigidBody() == pBody) {
      // found the body, so return the corresponding game object
      return *iter;
    }
  }
  return 0;
}

