#include "BulletOpenGLApplication.hpp"
#include "FreeGLUTCallbacks.hpp"

int main(int argc, char** argv)
{
  BulletOpenGLApplication demo;
  return glutmain(argc, argv, 1024, 768, "Introduction to Game Physics with Bullet Physics and OpenGL", &demo);
}
