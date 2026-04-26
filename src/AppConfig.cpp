#include "AppConfig.h"

AppConfig* AppConfig::instance = nullptr;

AppConfig::AppConfig() 
    : currentDrawChar('#'), canvasWidth(40), canvasHeight(20), showHelpOnStart(false) {}

AppConfig* AppConfig::getInstance() {
    if (instance == nullptr) {
        instance = new AppConfig();
    }
    return instance;
}

char AppConfig::getDrawChar() const { return currentDrawChar; }
void AppConfig::setDrawChar(char ch) { currentDrawChar = ch; }

int AppConfig::getCanvasWidth() const { return canvasWidth; }
int AppConfig::getCanvasHeight() const { return canvasHeight; }
void AppConfig::setCanvasSize(int w, int h) { canvasWidth = w; canvasHeight = h; }

bool AppConfig::getShowHelpOnStart() const { return showHelpOnStart; }
void AppConfig::setShowHelpOnStart(bool value) { showHelpOnStart = value; }