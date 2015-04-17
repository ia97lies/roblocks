//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_TESTS_POLY_CORE_MOCK_H
#define SYNTHETICS_CONSTRUCTOR_TESTS_POLY_CORE_MOCK_H

#include "PolyCore.h"
#include "PolyRendererMock.hpp"

class PolyCoreMock : public Polycode::Core {
  public:
    PolyCoreMock() : Core(400, 600, false, false, 0, 0, 0, 0) {
      services->setRenderer(new PolyRendererMock());
    }
    ~PolyCoreMock() {}

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


#endif

