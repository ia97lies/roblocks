//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestMenuEntry
#include <boost/test/unit_test.hpp>
#include "PolyCore.h"
#include "PolyRenderer.h"
#include "PolyCoreServices.h"
#include "PolyEntity.h"
#include "PolySceneLabel.h"
#include "Constructor/MenuEntry.hpp"
#include "Constructor/CommandNone.hpp"

using namespace Polycode;
using namespace Synthetics::Constructor;

class MockRenderer : public Polycode::Renderer {
  public:
    MockRenderer() {}
    ~MockRenderer() {}
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

class MockCore : public Polycode::Core {
  public:
    MockCore() : Core(400, 600, false, false, 0, 0, 0, 0) {
      services->setRenderer(new MockRenderer());
    }
    ~MockCore() {}

    virtual void Render() {} 
    virtual bool systemUpdate() { return false; }
    virtual void enableMouse(bool newval) {}
    virtual void captureMouse(bool newval) {}
    virtual void setCursor(int cursorType) {}
    virtual void lockMutex(CoreMutex *mutex) {}
    virtual void unlockMutex(CoreMutex *mutex) {}
    virtual CoreMutex *createMutex() { return NULL; }
    virtual void copyStringToClipboard(const String& str) {}
    virtual String getClipboardString() { return ""; }
    virtual void createFolder(const String& folderPath) {} 
    virtual void copyDiskItem(const String& itemPath, const String& destItemPath) {} 
    virtual void moveDiskItem(const String& itemPath, const String& destItemPath) {}
    virtual void removeDiskItem(const String& itemPath) {}
    virtual String openFolderPicker() { return ""; }
    virtual std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) { return files; }
    virtual String saveFilePicker(std::vector<CoreFileExtension> extensions) { return ""; }
    virtual void setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, bool retinaSupport=true) {}
    virtual void resizeTo(int xRes, int yRes) {} 
    virtual void openURL(String url) {} 
    virtual unsigned int getTicks() { return 0; }
    virtual String executeExternalCommand(String command, String args, String inDirectory) { return ""; } 

    std::vector<String> files;
};

class MyEntity : public Polycode::Entity {
  public:
    MyEntity(bool *_deleted = NULL) {
      deleted = _deleted;
    }
    ~MyEntity() {
      if (deleted) {
        *deleted = true;
      }
    }
    bool *deleted;
};

class MyCommand : public Command {
  public:
    MyCommand(bool *_deleted = NULL) {
      deleted = _deleted;
    }
    ~MyCommand() {
      if (deleted) {
        *deleted = true;
      }
    }

    bool execute() { return true; }
    void undo() { }
    bool *deleted;
};

//----------------------------------------------------------------------------
class MenuEntryInstantiateFixture {
  public:
    MenuEntryInstantiateFixture() {
      MockCore *core = new MockCore();
    }
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryInstantiate, MenuEntryInstantiateFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_instantiate) {
    MenuEntry menuEntry;
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_command) {
    MenuEntry menuEntry;
    BOOST_CHECK(dynamic_cast<CommandNone *>(menuEntry.getCommand()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_label) {
    MenuEntry menuEntry;
    BOOST_CHECK(dynamic_cast<Polycode::SceneLabel *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_label_position) {
    MenuEntry menuEntry;
    BOOST_CHECK(menuEntry.getLabel()->getPosition() == Vector3(1, 0, 0));
  }

BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
class MenuEntryCommandFixture {
  public:
    MenuEntryCommandFixture() {
      deleted = false;
      Command *command = new MyCommand(&deleted);
      menuEntry.setCommand(command);
    }
    MenuEntry menuEntry;
    bool deleted;
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryCommand, MenuEntryCommandFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_my_command) {
    BOOST_CHECK(dynamic_cast<MyCommand *>(menuEntry.getCommand()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_set_null_command) {
    menuEntry.setCommand(NULL);
    BOOST_CHECK(dynamic_cast<MyCommand *>(menuEntry.getCommand()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_delete_on_overwrite) {
    menuEntry.setCommand(new MyCommand());
    BOOST_CHECK(deleted);
  }
BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
class MenuEntryLabelFixture {
  public:
    MenuEntryLabelFixture() {
      deleted = false;
      MockCore *core = new MockCore();
      menuEntry.setLabel(new MyEntity(&deleted)); 
    }
    MenuEntry menuEntry;
    bool deleted;
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryLabel, MenuEntryLabelFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_custom_label) {
    BOOST_CHECK(dynamic_cast<MyEntity *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_overwrite_label) {
    menuEntry.setLabel(new Entity); 
    BOOST_CHECK(dynamic_cast<Entity *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_label_delete_on_overwrite) {
    menuEntry.setLabel(new Entity); 
    BOOST_CHECK(deleted);
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_label_overwrite_null) {
    menuEntry.setLabel(NULL); 
    BOOST_CHECK(dynamic_cast<MyEntity *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_custom_label_pos) {
    BOOST_CHECK(menuEntry.getLabel()->getPosition() == Vector3(1,0,0));
  }

BOOST_AUTO_TEST_SUITE_END()

