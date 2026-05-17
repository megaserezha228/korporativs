#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../src/Canvas.h"
#include <fstream>
#include <cstdio> 


TEST_CASE("Canvas can be created with custom size", "[canvas][constructor]") {
    Canvas canvas(15, 25);
    REQUIRE(canvas.getWidth() == 15);
    REQUIRE(canvas.getHeight() == 25);
}

TEST_CASE("Canvas constructor fills with spaces", "[canvas][initialization]") {
    Canvas canvas(10, 10);
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            REQUIRE(canvas.getChar(x, y) == ' ');
        }
    }
}


TEST_CASE("setChar and getChar work correctly", "[canvas][basics]") {
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


TEST_CASE("drawLine draws a horizontal line", "[canvas][drawLine]") {
    Canvas canvas(20, 20);
    canvas.drawLine(5, 10, 15, 10, '=');
    for (int x = 5; x <= 15; ++x) {
        REQUIRE(canvas.getChar(x, 10) == '=');
    }
    REQUIRE(canvas.getChar(4, 10) == ' ');
    REQUIRE(canvas.getChar(16, 10) == ' ');
}


TEST_CASE("floodFill fills a connected area", "[canvas][floodFill]") {
    Canvas canvas(10, 10);
    canvas.setChar(5, 5, '#');
    canvas.floodFill(5, 5, '#', '@');
    REQUIRE(canvas.getChar(5, 5) == '@');
}


TEST_CASE("clear resets the canvas", "[canvas][clear]") {
    Canvas canvas(10, 10);
    canvas.drawRectangle(2, 2, 7, 7, '*', true);
    canvas.clear('.');
    
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            REQUIRE(canvas.getChar(x, y) == '.');
        }
    }
}


TEST_CASE("saveToFile and loadFromFile work correctly", "[canvas][fileIO]") {
    Canvas original(10, 10);
    original.drawRectangle(2, 2, 7, 7, 'X', false);
    std::string filename = "test_catch_save.txt";
    
    REQUIRE(original.saveToFile(filename) == true);
    
    Canvas loaded;
    REQUIRE(loaded.loadFromFile(filename) == true);
    REQUIRE(loaded.getWidth() == 10);
    REQUIRE(loaded.getHeight() == 10);
    REQUIRE(loaded.getChar(2, 2) == 'X');
    REQUIRE(loaded.getChar(5, 5) == ' ');
    REQUIRE(loaded.getChar(7, 7) == 'X');
    
    std::remove(filename.c_str());
}