//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#include "Synthetics/Graphic.h"

// --------------------------------------------------------------------------
Graphic::Graphic() 
{
}

// --------------------------------------------------------------------------
Graphic::~Graphic() 
{
}

// --------------------------------------------------------------------------
void Graphic::initialize()
{
  // create some floats for our ambient, diffuse, specular and position
  GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // dark grey
  GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white
  GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white
  GLfloat position[] = { 5.0f, 10.0f, 1.0f, 0.0f };

  // set the ambient, diffuse, specular and position for LIGHT0
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glEnable(GL_LIGHTING); // enables lighting
  glEnable(GL_LIGHT0); // enables the 0th light
  glEnable(GL_COLOR_MATERIAL); // colors materials when lighting is enabled

  // enable specular lighting via materials
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMateriali(GL_FRONT, GL_SHININESS, 100);

  // enable smooth shading
  glShadeModel(GL_SMOOTH);

  // enable depth testing to be 'less than'
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // transparent
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // set the backbuffer clearing color to a lightish blue
  glClearColor(0.6, 0.65, 0.85, 0);
}

//----------------------------------------------------------------------------
void Graphic::DrawBox(const btVector3 &halfSize)
{
  // push the transform onto the stack
  float halfWidth = halfSize.x();
  float halfHeight = halfSize.y();
  float halfDepth = halfSize.z();

  // create the vertex positions
  btVector3 vertices[8]={	
    btVector3(halfWidth,halfHeight,halfDepth),
    btVector3(-halfWidth,halfHeight,halfDepth),
    btVector3(halfWidth,-halfHeight,halfDepth),	
    btVector3(-halfWidth,-halfHeight,halfDepth),	
    btVector3(halfWidth,halfHeight,-halfDepth),
    btVector3(-halfWidth,halfHeight,-halfDepth),	
    btVector3(halfWidth,-halfHeight,-halfDepth),	
    btVector3(-halfWidth,-halfHeight,-halfDepth)};

  // create the indexes for each triangle, using the 
  // vertices above. Make it static so we don't waste 
  // processing time recreating it over and over again
  static int indices[36] = {
    0,1,2,
    3,2,1,
    4,0,6,
    6,0,2,
    5,1,4,
    4,1,0,
    7,3,1,
    7,1,5,
    5,4,7,
    7,4,6,
    7,2,3,
    7,6,2};

  // start processing vertices as triangles
  glBegin (GL_TRIANGLES);

  // increment the loop by 3 each time since we create a 
  // triangle with 3 vertices at a time.

  for (int i = 0; i < 36; i += 3) {
    // get the three vertices for the triangle based
    // on the index values set above
    // use const references so we don't copy the object
    // (a good rule of thumb is to never allocate/deallocate
    // memory during *every* render/update call. This should 
    // only happen sporadically)
    const btVector3 &vert1 = vertices[indices[i]];
    const btVector3 &vert2 = vertices[indices[i+1]];
    const btVector3 &vert3 = vertices[indices[i+2]];

    // create a normal that is perpendicular to the 
    // face (use the cross product)
    btVector3 normal = (vert3-vert1).cross(vert2-vert1);
    normal.normalize ();

    // set the normal for the subsequent vertices
    glNormal3f(normal.getX(),normal.getY(),normal.getZ());

    // create the vertices
    glVertex3f (vert1.x(), vert1.y(), vert1.z());
    glVertex3f (vert2.x(), vert2.y(), vert2.z());
    glVertex3f (vert3.x(), vert3.y(), vert3.z());
  }

  // stop processing vertices
  glEnd();
}

void Graphic::DrawShape(
    btScalar* transform, 
    const btCollisionShape* pShape, 
    const btVector3 &color,
    bool transparent
)
{
  // set the color
  glColor3f(color.x(), color.y(), color.z());

  // push the matrix stack
  glPushMatrix();
  glMultMatrixf(transform);
  if (transparent) {
    glTranslatef(0.15, 0.15, -0.8);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
  }

  // make a different draw call based on the object type
  switch(pShape->getShapeType()) {
    // an internal enum used by Bullet for boxes
    case BOX_SHAPE_PROXYTYPE:
      {
        // assume the shape is a box, and typecast it
        const btBoxShape* box = static_cast<const btBoxShape*>(pShape);
        // get the 'halfSize' of the box
        btVector3 halfSize = box->getHalfExtentsWithMargin();
        // draw the box
        DrawBox(halfSize);
        break;
      }
		case SPHERE_SHAPE_PROXYTYPE:
			{
				// assume the shape is a sphere and typecast it
				const btSphereShape* sphere = static_cast<const btSphereShape*>(pShape);
				// get the sphere's size from the shape
				float radius = sphere->getMargin();
				// draw the sphere
				DrawSphere(radius);
				break;
			}
    case CYLINDER_SHAPE_PROXYTYPE:
      {
        // assume the object is a cylinder
        const btCylinderShape* pCylinder = static_cast<const btCylinderShape*>(pShape);
        // get the relevant data
        float radius = pCylinder->getRadius();
        float halfHeight = pCylinder->getHalfExtentsWithMargin()[1];
        // draw the cylinder
        DrawCylinder(radius,halfHeight);

        break;
      }
    case CONVEX_HULL_SHAPE_PROXYTYPE:
      {
        // draw the convex hull shape...whatever it is
        DrawConvexHull(pShape);
        break;
      }
    case COMPOUND_SHAPE_PROXYTYPE:
      {
        // get the shape
        const btCompoundShape* pCompound = static_cast<const btCompoundShape*>(pShape);
        // iterate through the children
        for (int i = 0; i < pCompound->getNumChildShapes(); ++i) {
          // get the transform of the sub-shape
          btTransform thisTransform = pCompound->getChildTransform(i);
          btScalar thisMatrix[16];
          thisTransform.getOpenGLMatrix(thisMatrix);
          // call drawshape recursively for each child. The matrix
          // stack takes care of positioning/orienting the object for us
          DrawShape(thisMatrix, pCompound->getChildShape(i), color);
        }
        break;
      }
    default:
      // unsupported type
      break;
  }

  // pop the stack
  if (transparent) {
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
  }
  glPopMatrix();
}

//----------------------------------------------------------------------------
void Graphic::DrawSphere(const btScalar &radius) {
  // some constant values for more many segments to build the sphere from
  static int lateralSegments = 25;
  static int longitudinalSegments = 25;

  // iterate laterally
  for(int i = 0; i <= lateralSegments; i++) {
    // do a little math to find the angles of this segment
    btScalar lat0 = SIMD_PI * (-btScalar(0.5) + (btScalar) (i - 1) / lateralSegments);
    btScalar z0  = radius*sin(lat0);
    btScalar zr0 =  radius*cos(lat0);

    btScalar lat1 = SIMD_PI * (-btScalar(0.5) + (btScalar) i / lateralSegments);
    btScalar z1 = radius*sin(lat1);
    btScalar zr1 = radius*cos(lat1);

    // start rendering strips of quads (polygons with 4 poins)
    glBegin(GL_QUAD_STRIP);
    // iterate longitudinally
    for(int j = 0; j <= longitudinalSegments; j++) {
      // determine the points of the quad from the lateral angles
      btScalar lng = 2 * SIMD_PI * (btScalar) (j - 1) / longitudinalSegments;
      btScalar x = cos(lng);
      btScalar y = sin(lng);
      // draw the normals and vertices for each point in the quad
      // since it is a STRIP of quads, we only need to add two points
      // each time to create a whole new quad

      // calculate the normal
      btVector3 normal = btVector3(x*zr0, y*zr0, z0);
      normal.normalize();
      glNormal3f(normal.x(), normal.y(), normal.z());
      // create the first vertex
      glVertex3f(x * zr0, y * zr0, z0);

      // calculate the next normal
      normal = btVector3(x*zr1, y*zr1, z1);
      normal.normalize();
      glNormal3f(normal.x(), normal.y(), normal.z());
      // create the second vertex
      glVertex3f(x * zr1, y * zr1, z1);

      // and repeat...
    }
    glEnd();
  }
}

//----------------------------------------------------------------------------
void Graphic::DrawCylinder(const btScalar &radius, const btScalar &halfHeight) {
  static int slices = 15;
  static int stacks = 10;
  // tweak the starting position of the
  // cylinder to match the physics object
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, -halfHeight);
  // create a quadric object to render with
  GLUquadricObj *quadObj = gluNewQuadric();
  // set the draw style of the quadric
  gluQuadricDrawStyle(quadObj, (GLenum)GLU_FILL);
  gluQuadricNormals(quadObj, (GLenum)GLU_SMOOTH);
  // create a disk to cap the cylinder
  gluDisk(quadObj, 0, radius, slices, stacks);
  // create the main hull of the cylinder (no caps)
  gluCylinder(quadObj, radius, radius, 2.f*halfHeight, slices, stacks);
  // shift the position and rotation again
  glTranslatef(0.0f, 0.0f, 2.f*halfHeight);
  glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
  // draw the cap on the other end of the cylinder
  gluDisk(quadObj, 0, radius, slices, stacks);
  // don't need the quadric anymore, so remove it
  // to save memory
  gluDeleteQuadric(quadObj);
}

//----------------------------------------------------------------------------
void Graphic::DrawConvexHull(const btCollisionShape* shape) {
  // get the polyhedral data from the convex hull
  const btConvexPolyhedron* pPoly = shape->isPolyhedral() ? ((btPolyhedralConvexShape*) shape)->getConvexPolyhedron() : 0;
  if (!pPoly) return;

  // begin drawing triangles
  glBegin (GL_TRIANGLES);

  // iterate through all faces
  for (int i = 0; i < pPoly->m_faces.size(); i++) {
    // get the indices for the face
    int numVerts = pPoly->m_faces[i].m_indices.size();
    if (numVerts>2)	{
      // iterate through all index triplets
      for (int v = 0; v <pPoly->m_faces[i].m_indices.size()-2;v++) {
        // grab the three vertices
        btVector3 v1 = pPoly->m_vertices[pPoly->m_faces[i].m_indices[0]];
        btVector3 v2 = pPoly->m_vertices[pPoly->m_faces[i].m_indices[v+1]];
        btVector3 v3 = pPoly->m_vertices[pPoly->m_faces[i].m_indices[v+2]];
        // calculate the normal
        btVector3 normal = (v3-v1).cross(v2-v1);
        normal.normalize ();
        // draw the triangle
        glNormal3f(normal.getX(),normal.getY(),normal.getZ());
        glVertex3f (v1.x(), v1.y(), v1.z());
        glVertex3f (v2.x(), v2.y(), v2.z());
        glVertex3f (v3.x(), v3.y(), v3.z());
      }
    }
  }
  // done drawing
  glEnd ();
}

