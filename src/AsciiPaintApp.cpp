#include "AsciiPaintApp.h"
#include "KeyboardInput.h"
#include "AppConfig.h"
#include <iostream>
#include <cctype>

AsciiPaintApp::AsciiPaintApp() 
    : canvas(40, 20), cursorX(0), cursorY(0), currentDrawChar('#'), running(true) {}

void AsciiPaintApp::getCoordinatesFromUser(const std::string& prompt, int& x, int& y) {
    std::cout << prompt << " (x y): ";
    std::cin >> x >> y;
    std::cin.ignore();
}

void AsciiPaintApp::handlePoint() {
    canvas.setChar(cursorX, cursorY, currentDrawChar);
}

void AsciiPaintApp::handleLine() {
    int x1, y1, x2, y2;
    getCoordinatesFromUser("Enter start point", x1, y1);
    getCoordinatesFromUser("Enter end point", x2, y2);
    canvas.drawLine(x1, y1, x2, y2, currentDrawChar);
}

void AsciiPaintApp::handleRectangle() {
    int x1, y1, x2, y2;
    getCoordinatesFromUser("Enter first corner", x1, y1);
    getCoordinatesFromUser("Enter second corner", x2, y2);
    std::cout << "Fill rectangle? (y/n): ";
    char fillChoice;
    std::cin >> fillChoice;
    std::cin.ignore();
    canvas.drawRectangle(x1, y1, x2, y2, currentDrawChar, fillChoice == 'y' || fillChoice == 'Y');
}

void AsciiPaintApp::handleFloodFill() {
    char targetChar = canvas.getChar(cursorX, cursorY);
    if (targetChar == currentDrawChar) {
        std::cout << "Target character is the same as fill character!" << std::endl;
        std::cout << "Press any key to continue...";
        KeyboardInput::getKey();
        return;
    }
    canvas.floodFill(cursorX, cursorY, targetChar, currentDrawChar);
}

void AsciiPaintApp::handleEraser() {
    canvas.setChar(cursorX, cursorY, ' ');
}

void AsciiPaintApp::handleClear() {
    canvas.clear(' ');
}

void AsciiPaintApp::handleSave() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    if (canvas.saveToFile(filename)) {
        std::cout << "Saved successfully!" << std::endl;
    } else {
        std::cout << "Error saving file!" << std::endl;
    }
    std::cout << "Press any key to continue...";
    KeyboardInput::getKey();
}

void AsciiPaintApp::handleLoad() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    if (canvas.loadFromFile(filename)) {
        cursorX = std::min(cursorX, canvas.getWidth() - 1);
        cursorY = std::min(cursorY, canvas.getHeight() - 1);
        std::cout << "Loaded successfully!" << std::endl;
    } else {
        std::cout << "Error loading file!" << std::endl;
    }
    std::cout << "Press any key to continue...";
    KeyboardInput::getKey();
}

void AsciiPaintApp::moveCursor(int dx, int dy) {
    cursorX = std::max(0, std::min(cursorX + dx, canvas.getWidth() - 1));
    cursorY = std::max(0, std::min(cursorY + dy, canvas.getHeight() - 1));
}

void AsciiPaintApp::run() {
    while (running) {
        canvas.display(cursorX, cursorY, currentDrawChar);
        
        char key = KeyboardInput::getKey();
        
        switch (key) {
            case 'U': moveCursor(0, -1); break;
            case 'D': moveCursor(0, 1); break;
            case 'L': moveCursor(-1, 0); break;
            case 'R': moveCursor(1, 0); break;
            default:
                char lowerKey = tolower(key);
                switch (lowerKey) {
                    case 'p': handlePoint(); break;
                    case 'l': handleLine(); break;
                    case 'r': handleRectangle(); break;
                    case 'f': handleFloodFill(); break;
                    case 'e': handleEraser(); break;
                    case 'c': handleClear(); break;
                    case 's': handleSave(); break;
                    case 'o': handleLoad(); break;
                    case 'h': canvas.showHelp(); break;
                    case 'q': running = false; break;
                    default: break;
                }
                break;
        }
    }
}