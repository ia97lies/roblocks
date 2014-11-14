#include "Synthetics/Synthetics.h"
#include "Synthetics/FreeGLUTCallbacks.h"

int main(int argc, char** argv)
{
  Synthetics app;
  return glutmain(argc, argv, 768, 500, "Introduction to Game Physics with Bullet Physics and OpenGL", &app);
}
