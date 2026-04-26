#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>

class Canvas {
private:
    std::vector<std::vector<char>> grid;
    int width;
    int height;

public:
    Canvas(int w = 40, int h = 20);
    
    int getWidth() const;
    int getHeight() const;
    void setChar(int x, int y, char ch);
    char getChar(int x, int y) const;
    void clear(char fillChar = ' ');
    void drawLine(int x0, int y0, int x1, int y1, char ch);
    void drawRectangle(int x0, int y0, int x1, int y1, char ch, bool fill = false);
    void floodFill(int x, int y, char targetChar, char newChar);
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    void display(int cursorX, int cursorY, char currentChar) const;
    void showHelp() const;
};

#endif