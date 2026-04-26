#ifndef ASCII_PAINT_APP_H
#define ASCII_PAINT_APP_H

#include "Canvas.h"
#include <string>

class AsciiPaintApp {
private:
    Canvas canvas;
    int cursorX, cursorY;
    char currentDrawChar;
    bool running;
    
    void getCoordinatesFromUser(const std::string& prompt, int& x, int& y);
    void handlePoint();
    void handleLine();
    void handleRectangle();
    void handleFloodFill();
    void handleEraser();
    void handleClear();
    void handleSave();
    void handleLoad();
    void moveCursor(int dx, int dy);
    
public:
    AsciiPaintApp();
    void run();
};

#endif