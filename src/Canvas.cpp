#include "Canvas.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

Canvas::Canvas(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<char>(width, ' '));
}

int Canvas::getWidth() const { return width; }
int Canvas::getHeight() const { return height; }

void Canvas::setChar(int x, int y, char ch) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x] = ch;
    }
}

char Canvas::getChar(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y][x];
    }
    return ' ';
}

void Canvas::clear(char fillChar) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = fillChar;
        }
    }
}

void Canvas::drawLine(int x0, int y0, int x1, int y1, char ch) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (true) {
        setChar(x0, y0, ch);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void Canvas::drawRectangle(int x0, int y0, int x1, int y1, char ch, bool fill) {
    int left = std::min(x0, x1);
    int right = std::max(x0, x1);
    int top = std::min(y0, y1);
    int bottom = std::max(y0, y1);
    
    if (fill) {
        for (int y = top; y <= bottom; y++) {
            for (int x = left; x <= right; x++) {
                setChar(x, y, ch);
            }
        }
    } else {
        for (int x = left; x <= right; x++) {
            setChar(x, top, ch);
            setChar(x, bottom, ch);
        }
        for (int y = top + 1; y < bottom; y++) {
            setChar(left, y, ch);
            setChar(right, y, ch);
        }
    }
}

void Canvas::floodFill(int x, int y, char targetChar, char newChar) {
    if (targetChar == newChar) return;
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    if (getChar(x, y) != targetChar) return;
    
    std::vector<std::pair<int,int>> stack;
    stack.push_back({x, y});
    
    while (!stack.empty()) {
        auto [cx, cy] = stack.back();
        stack.pop_back();
        
        if (cx < 0 || cx >= width || cy < 0 || cy >= height) continue;
        if (getChar(cx, cy) != targetChar) continue;
        
        setChar(cx, cy, newChar);
        
        stack.push_back({cx + 1, cy});
        stack.push_back({cx - 1, cy});
        stack.push_back({cx, cy + 1});
        stack.push_back({cx, cy - 1});
    }
}

bool Canvas::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << width << " " << height << std::endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file << grid[y][x];
        }
        file << std::endl;
    }
    return true;
}

bool Canvas::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    int newWidth, newHeight;
    file >> newWidth >> newHeight;
    file.ignore();
    
    if (newWidth <= 0 || newHeight <= 0 || newWidth > 200 || newHeight > 100) {
        return false;
    }
    
    std::vector<std::vector<char>> newGrid(newHeight, std::vector<char>(newWidth, ' '));
    
    for (int y = 0; y < newHeight; y++) {
        std::string line;
        std::getline(file, line);
        for (int x = 0; x < newWidth && x < (int)line.length(); x++) {
            newGrid[y][x] = line[x];
        }
    }
    
    width = newWidth;
    height = newHeight;
    grid = std::move(newGrid);
    return true;
}

void Canvas::display(int cursorX, int cursorY, char currentChar) const {
    CLEAR_SCREEN();
    
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    
    for (int y = 0; y < height; y++) {
        std::cout << "|";
        for (int x = 0; x < width; x++) {
            if (x == cursorX && y == cursorY) {
                std::cout << '[' << grid[y][x] << ']';
            } else {
                std::cout << grid[y][x];
            }
        }
        std::cout << "|" << std::endl;
    }
    
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    std::cout << "Pos: (" << cursorX << "," << cursorY << ") ";
    std::cout << "Char: '" << currentChar << "' ";
    std::cout << "Size: " << width << "x" << height << std::endl;
    std::cout << std::endl;
    std::cout << "p=Point l=Line r=Rect f=Fill e=Eraser ";
    std::cout << "c=Clear s=Save o=Load h=Help q=Quit" << std::endl;
    std::cout << "Use ARROW KEYS to move cursor" << std::endl;
}

void Canvas::showHelp() const {
    CLEAR_SCREEN();
    std::cout << "================== ASCII PAINT - HELP ==================" << std::endl;
    std::cout << std::endl;
    std::cout << "NAVIGATION:" << std::endl;
    std::cout << "  Arrow Keys - Move cursor around the canvas" << std::endl;
    std::cout << std::endl;
    std::cout << "DRAWING TOOLS:" << std::endl;
    std::cout << "  p - Draw point at cursor position" << std::endl;
    std::cout << "  l - Draw line (enter start and end coordinates)" << std::endl;
    std::cout << "  r - Draw rectangle (enter two corners, then fill choice)" << std::endl;
    std::cout << "  f - Flood fill (fill connected area with current char)" << std::endl;
    std::cout << "  e - Eraser (delete character at cursor)" << std::endl;
    std::cout << std::endl;
    std::cout << "FILE OPERATIONS:" << std::endl;
    std::cout << "  s - Save canvas to file" << std::endl;
    std::cout << "  o - Load canvas from file" << std::endl;
    std::cout << std::endl;
    std::cout << "OTHER:" << std::endl;
    std::cout << "  c - Clear entire canvas" << std::endl;
    std::cout << "  h - Show this help" << std::endl;
    std::cout << "  q - Quit program" << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    
    std::cin.get();
}