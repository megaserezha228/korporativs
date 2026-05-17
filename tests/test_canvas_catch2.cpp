#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Canvas.h"
#include <fstream>
#include <cstdio>

TEST_CASE("Canvas constructor creates correct size", "[canvas]") {
    Canvas canvas(15, 25);
    REQUIRE(canvas.getWidth() == 15);
    REQUIRE(canvas.getHeight() == 25);
}

TEST_CASE("Canvas constructor fills with spaces", "[canvas]") {
    Canvas canvas(10, 10);
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            REQUIRE(canvas.getChar(x, y) == ' ');
        }
    }
}

TEST_CASE("setChar and getChar work correctly", "[canvas]") {
    Canvas canvas(10, 10);
    
    SECTION("Valid position") {
        canvas.setChar(5, 5, '@');
        REQUIRE(canvas.getChar(5, 5) == '@');
    }
    
    SECTION("Invalid positions are ignored") {
        canvas.setChar(-1, 5, '#');
        canvas.setChar(10, 10, '#');
        REQUIRE(canvas.getChar(-1, 5) == ' ');
        REQUIRE(canvas.getChar(10, 10) == ' ');
    }
}

TEST_CASE("drawLine draws horizontal line correctly", "[canvas]") {
    Canvas canvas(20, 20);
    canvas.drawLine(5, 10, 15, 10, '=');
    
    for (int x = 5; x <= 15; ++x) {
        REQUIRE(canvas.getChar(x, 10) == '=');
    }
    REQUIRE(canvas.getChar(4, 10) == ' ');
    REQUIRE(canvas.getChar(16, 10) == ' ');
}

TEST_CASE("drawLine draws vertical line correctly", "[canvas]") {
    Canvas canvas(20, 20);
    canvas.drawLine(10, 5, 10, 15, '|');
    
    for (int y = 5; y <= 15; ++y) {
        REQUIRE(canvas.getChar(10, y) == '|');
    }
}

TEST_CASE("drawLine draws diagonal line correctly", "[canvas]") {
    Canvas canvas(20, 20);
    canvas.drawLine(2, 2, 6, 6, '/');
    
    for (int i = 0; i <= 4; ++i) {
        REQUIRE(canvas.getChar(2 + i, 2 + i) == '/');
    }
}

TEST_CASE("drawRectangle draws outline correctly", "[canvas]") {
    Canvas canvas(20, 20);
    canvas.drawRectangle(5, 5, 10, 10, '#', false);
    for (int x = 5; x <= 10; ++x) {
        REQUIRE(canvas.getChar(x, 5) == '#');
        REQUIRE(canvas.getChar(x, 10) == '#');
    }
    for (int y = 6; y <= 9; ++y) {
        REQUIRE(canvas.getChar(5, y) == '#');
        REQUIRE(canvas.getChar(10, y) == '#');
    }
    REQUIRE(canvas.getChar(7, 7) == ' ');
}

TEST_CASE("drawRectangle fills correctly", "[canvas]") {
    Canvas canvas(20, 20);
    canvas.drawRectangle(5, 5, 10, 10, '*', true);
    
    for (int y = 5; y <= 10; ++y) {
        for (int x = 5; x <= 10; ++x) {
            REQUIRE(canvas.getChar(x, y) == '*');
        }
    }
}

TEST_CASE("floodFill fills connected area", "[canvas]") {
    Canvas canvas(10, 10);
    canvas.setChar(5, 5, '#');
    canvas.floodFill(5, 5, '#', '@');
    REQUIRE(canvas.getChar(5, 5) == '@');
}

TEST_CASE("floodFill does nothing if target equals new char", "[canvas]") {
    Canvas canvas(10, 10);
    canvas.setChar(5, 5, '#');
    canvas.floodFill(5, 5, '#', '#');
    REQUIRE(canvas.getChar(5, 5) == '#');
}

TEST_CASE("clear resets canvas with default space", "[canvas]") {
    Canvas canvas(10, 10);
    canvas.drawRectangle(2, 2, 7, 7, '*', true);
    canvas.clear();
    
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            REQUIRE(canvas.getChar(x, y) == ' ');
        }
    }
}

TEST_CASE("clear resets canvas with custom char", "[canvas]") {
    Canvas canvas(10, 10);
    canvas.drawRectangle(2, 2, 7, 7, '*', true);
    canvas.clear('.');
    
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            REQUIRE(canvas.getChar(x, y) == '.');
        }
    }
}

TEST_CASE("saveToFile and loadFromFile work correctly", "[canvas]") {
    Canvas original(10, 10);
    original.drawRectangle(2, 2, 7, 7, 'X', false);
    std::string filename = "test_save.txt";
    
    REQUIRE(original.saveToFile(filename) == true);
    
    Canvas loaded;
    REQUIRE(loaded.loadFromFile(filename) == true);
    REQUIRE(loaded.getWidth() == 10);
    REQUIRE(loaded.getHeight() == 10);
    REQUIRE(loaded.getChar(2, 2) == 'X');
    REQUIRE(loaded.getChar(7, 7) == 'X');
    REQUIRE(loaded.getChar(5, 5) == ' ');
    
    std::remove(filename.c_str());
}

TEST_CASE("loadFromFile returns false for nonexistent file", "[canvas]") {
    Canvas canvas;
    bool result = canvas.loadFromFile("nonexistent_file_12345.txt");
    REQUIRE(result == false);
}