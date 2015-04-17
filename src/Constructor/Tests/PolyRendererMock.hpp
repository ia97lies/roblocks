//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_TESTS_POLY_RENDERER_MOCK_H
#define SYNTHETICS_CONSTRUCTOR_TESTS_POLY_RENDERER_MOCK_H

#include "PolyRenderer.h"
#include "PolyCoreServices.h"

using namespace Polycode;

class PolyRendererMock : public Polycode::Renderer {
  public:
    PolyRendererMock() {}
    ~PolyRendererMock() {}
    virtual bool Init() {}
    virtual void Resize(int xRes, int yRes) {} 
    virtual void BeginRender() {}
    virtual void EndRender() {}
    virtual Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) { return NULL; }   
    virtual Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type=Image::IMAGE_RGBA) { return NULL; }
    virtual void destroyTexture(Texture *texture) {} 
    virtual void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer) {} 
    virtual Texture *createFramebufferTexture(unsigned int width, unsigned int height) {} 
    virtual void bindFrameBufferTexture(Texture *texture) {}
    virtual void bindFrameBufferTextureDepth(Texture *texture) {}
    virtual void unbindFramebuffers() {}
    virtual Image *renderScreenToImage() {}
    virtual Image *renderBufferToImage(Texture *texture) {} 
    virtual void resetViewport() {} 
    virtual Polycode::Rectangle getViewport() { return Rectangle(); } 
    virtual void loadIdentity() {} 
    virtual void setProjectionOrtho(Number xSize=0.0f, Number ySize=0.0f, Number near=-256.0f, Number far=256.0f, bool centered = false) {} 
    virtual void setPerspectiveDefaults() {} 
    virtual void setProjectionMatrix(Matrix4 matrix) {} 
    virtual void setTexture(Texture *texture) {} 
    virtual void enableBackfaceCulling(bool val) {} 
    virtual void setClearColor(Number r, Number g, Number b, Number a = 1.0) {}
    virtual void setClearColor(Color color) {}
    virtual void setAmbientColor(Number r, Number g, Number b) {}
    virtual void clearScreen(bool clearColor = true, bool clearDepth = true) {} 
    virtual void translate2D(Number x, Number y) {} 
    virtual void rotate2D(Number angle) {} 
    virtual void scale2D(const Vector2 &scale) {} 
    virtual void setVertexColor(Number r, Number g, Number b, Number a) {} 
    virtual void pushRenderDataArray(RenderDataArray *array) {} 
    virtual void drawArrays(int drawType, IndexDataArray *indexArray) {} 
    virtual void translate3D(const Vector3 &position) {} 
    virtual void translate3D(Number x, Number y, Number z) {} 
    virtual void scale3D(const Vector3 &scale) {} 
    virtual void pushMatrix() {} 
    virtual void popMatrix() {} 
    virtual void setLineSmooth(bool val) {} 
    virtual void setLineSize(Number lineSize) {} 
    virtual void setPointSize(Number pointSize) {} 
    virtual void setPointSmooth(bool val) {} 
    virtual void enableLighting(bool enable) {}
    virtual void enableFog(bool enable) {}
    virtual void setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth) {} 
    virtual void multModelviewMatrix(Matrix4 m) {} 
    virtual void setModelviewMatrix(Matrix4 m) {} 
    virtual void setBlendingMode(int blendingMode) {} 
    virtual void applyMaterial(Material *material, ShaderBinding *localOptions, unsigned int shaderIndex, bool forceMaterial) {}
    virtual void clearShader() {} 
    virtual void setDepthFunction(int depthFunction) {} 
    virtual void createVertexBufferForMesh(Mesh *mesh) {}
    virtual void drawVertexBuffer(VertexBuffer *buffer, bool enableColorBuffer) {} 
    virtual void enableDepthTest(bool val) {} 
    virtual void enableDepthWrite(bool val) {} 
    virtual void setWireframePolygonMode(bool val) {} 
    virtual void setProjectionFromFrustum(Number left, Number right, Number bottom, Number top, Number front, Number back) {} 
    virtual void setProjectionFromFoV(Number fov, Number near, Number far) {} 
    virtual void enableAlphaTest(bool val) {} 
    virtual void clearBuffer(bool colorBuffer, bool depthBuffer) {} 
    virtual void drawToColorBuffer(bool val) {} 
    virtual void drawScreenQuad(Number qx, Number qy) {} 
    virtual void enableScissor(bool val) {}
    virtual void setScissorBox(Polycode::Rectangle box) {}
    virtual void cullFrontFaces(bool val) {} 
    virtual Vector3 projectRayFrom2DCoordinate(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) { return 0; } 
    virtual Vector2 Project(const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport, const Vector3 &coordiante) const { return Vector2(0, 0); } 
    virtual Matrix4 getProjectionMatrix() { return 0; } 
    virtual Matrix4 getModelviewMatrix() { return 0; } 
    virtual Vector3 Unproject(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) { return 0; } 
    virtual void initOSSpecific() {} 
};


#endif

