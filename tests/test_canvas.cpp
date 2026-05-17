#include <gtest/gtest.h>
#include "Canvas.h"
#include <fstream>

class CanvasTest : public ::testing::Test {
protected:
    void SetUp() override {
        canvas = new Canvas(10, 10);
    }
    
    void TearDown() override {
        delete canvas;
    }
    
    Canvas* canvas;
};

//  Тесты конструктора и базовых методов 

TEST_F(CanvasTest, Constructor_CreatesCorrectSize) {
    EXPECT_EQ(canvas->getWidth(), 10);
    EXPECT_EQ(canvas->getHeight(), 10);
}

TEST_F(CanvasTest, Constructor_InitializesWithSpaces) {
    for (int y = 0; y < canvas->getHeight(); y++) {
        for (int x = 0; x < canvas->getWidth(); x++) {
            EXPECT_EQ(canvas->getChar(x, y), ' ');
        }
    }
}

TEST_F(CanvasTest, Constructor_DefaultSize_40x20) {
    Canvas defaultCanvas;
    EXPECT_EQ(defaultCanvas.getWidth(), 40);
    EXPECT_EQ(defaultCanvas.getHeight(), 20);
}

//  Тесты setChar и getChar 

TEST_F(CanvasTest, SetChar_SetsCharacterAtValidPosition) {
    canvas->setChar(3, 4, '#');
    EXPECT_EQ(canvas->getChar(3, 4), '#');
}

TEST_F(CanvasTest, SetChar_DoesNothingAtInvalidPosition_XNegative) {
    canvas->setChar(-1, 5, '#');
    EXPECT_EQ(canvas->getChar(-1, 5), ' ');
}

TEST_F(CanvasTest, SetChar_DoesNothingAtInvalidPosition_YNegative) {
    canvas->setChar(5, -1, '#');
    EXPECT_EQ(canvas->getChar(5, -1), ' ');
}

TEST_F(CanvasTest, SetChar_DoesNothingAtInvalidPosition_XTooLarge) {
    canvas->setChar(10, 5, '#');
    EXPECT_EQ(canvas->getChar(10, 5), ' ');
}

TEST_F(CanvasTest, SetChar_DoesNothingAtInvalidPosition_YTooLarge) {
    canvas->setChar(5, 10, '#');
    EXPECT_EQ(canvas->getChar(5, 10), ' ');
}

TEST_F(CanvasTest, GetChar_ReturnsSpaceForInvalidPosition) {
    EXPECT_EQ(canvas->getChar(-1, -1), ' ');
    EXPECT_EQ(canvas->getChar(100, 100), ' ');
}

// Тесты clear 

TEST_F(CanvasTest, Clear_ResetsAllCellsToSpace) {
    canvas->setChar(0, 0, '#');
    canvas->setChar(5, 5, '@');
    canvas->setChar(9, 9, '*');
    
    canvas->clear();
    
    for (int y = 0; y < canvas->getHeight(); y++) {
        for (int x = 0; x < canvas->getWidth(); x++) {
            EXPECT_EQ(canvas->getChar(x, y), ' ');
        }
    }
}

TEST_F(CanvasTest, Clear_WithCustomFillChar_UsesProvidedChar) {
    canvas->setChar(0, 0, '#');
    canvas->clear('.');
    
    EXPECT_EQ(canvas->getChar(0, 0), '.');
    EXPECT_EQ(canvas->getChar(5, 5), '.');
}

//  Тесты drawLine 

TEST_F(CanvasTest, DrawLine_HorizontalLine_DrawsCorrectly) {
    canvas->drawLine(2, 5, 7, 5, '#');
    
    for (int x = 2; x <= 7; x++) {
        EXPECT_EQ(canvas->getChar(x, 5), '#');
    }
    EXPECT_EQ(canvas->getChar(1, 5), ' ');
    EXPECT_EQ(canvas->getChar(8, 5), ' ');
}

TEST_F(CanvasTest, DrawLine_VerticalLine_DrawsCorrectly) {
    canvas->drawLine(5, 2, 5, 7, '#');
    
    for (int y = 2; y <= 7; y++) {
        EXPECT_EQ(canvas->getChar(5, y), '#');
    }
}

TEST_F(CanvasTest, DrawLine_DiagonalLine_DrawsCorrectly) {
    canvas->drawLine(2, 2, 6, 6, '#');
    
    for (int i = 0; i <= 4; i++) {
        EXPECT_EQ(canvas->getChar(2 + i, 2 + i), '#');
    }
}

TEST_F(CanvasTest, DrawLine_ReverseOrder_DrawsSameLine) {
    canvas->drawLine(7, 5, 2, 5, '#');
    
    for (int x = 2; x <= 7; x++) {
        EXPECT_EQ(canvas->getChar(x, 5), '#');
    }
}

TEST_F(CanvasTest, DrawLine_SinglePoint_DrawsPoint) {
    canvas->drawLine(5, 5, 5, 5, '#');
    EXPECT_EQ(canvas->getChar(5, 5), '#');
}

TEST_F(CanvasTest, DrawLine_OutOfBounds_OnlyDrawsInside) {
    canvas->drawLine(-5, 5, 15, 5, '#');
    
    for (int x = 0; x < canvas->getWidth(); x++) {
        EXPECT_EQ(canvas->getChar(x, 5), '#');
    }
}

// ========== Тесты drawRectangle ==========

TEST_F(CanvasTest, DrawRectangle_Outline_DrawsOnlyBorder) {
    canvas->drawRectangle(2, 2, 7, 6, '#', false);
    
    for (int x = 2; x <= 7; x++) {
        EXPECT_EQ(canvas->getChar(x, 2), '#');
        EXPECT_EQ(canvas->getChar(x, 6), '#');
    }
    for (int y = 3; y <= 5; y++) {
        EXPECT_EQ(canvas->getChar(2, y), '#');
        EXPECT_EQ(canvas->getChar(7, y), '#');
    }
    
    EXPECT_EQ(canvas->getChar(3, 3), ' ');
}

TEST_F(CanvasTest, DrawRectangle_Filled_DrawsAllCells) {
    canvas->drawRectangle(2, 2, 5, 5, '#', true);
    
    for (int y = 2; y <= 5; y++) {
        for (int x = 2; x <= 5; x++) {
            EXPECT_EQ(canvas->getChar(x, y), '#');
        }
    }
}

TEST_F(CanvasTest, DrawRectangle_SingleCell_DrawsPoint) {
    canvas->drawRectangle(5, 5, 5, 5, '#', false);
    EXPECT_EQ(canvas->getChar(5, 5), '#');
}

TEST_F(CanvasTest, DrawRectangle_ReversedCorners_WorksCorrectly) {
    canvas->drawRectangle(7, 6, 2, 2, '#', false);
    
    EXPECT_EQ(canvas->getChar(2, 2), '#');
    EXPECT_EQ(canvas->getChar(7, 6), '#');
    EXPECT_EQ(canvas->getChar(2, 6), '#');
    EXPECT_EQ(canvas->getChar(7, 2), '#');
}

// Тесты floodFill

TEST_F(CanvasTest, FloodFill_FillsConnectedArea) {
    canvas->setChar(5, 5, '.');
    canvas->floodFill(5, 5, '.', '#');
    EXPECT_EQ(canvas->getChar(5, 5), '#');
}

TEST_F(CanvasTest, FloodFill_DoesNotFillIfTargetEqualsNew) {
    canvas->setChar(5, 5, '#');
    canvas->floodFill(5, 5, '#', '#');
    EXPECT_EQ(canvas->getChar(5, 5), '#');
}

TEST_F(CanvasTest, FloodFill_StopsAtDifferentSymbol) {
    for (int i = 0; i < 10; i++) {
        canvas->setChar(i, 5, '.');
    }
    canvas->setChar(5, 5, '#');
    
    canvas->floodFill(0, 5, '.', '@');
    
    EXPECT_EQ(canvas->getChar(4, 5), '@');
    EXPECT_EQ(canvas->getChar(5, 5), '#');
    EXPECT_EQ(canvas->getChar(6, 5), '@');
}

TEST_F(CanvasTest, FloodFill_HandlesEmptyCanvas) {
    canvas->floodFill(5, 5, ' ', '#');
    EXPECT_EQ(canvas->getChar(5, 5), '#');
}

TEST_F(CanvasTest, FloodFill_DoesNothingOnInvalidStart) {
    canvas->floodFill(-1, -1, ' ', '#');
    SUCCEED();
}

//  Тесты saveToFile и loadFromFile

TEST_F(CanvasTest, SaveAndLoad_PreservesCanvasState) {
    canvas->setChar(0, 0, '#');
    canvas->setChar(5, 5, '@');
    canvas->setChar(9, 9, '*');
    
    std::string filename = "test_save.txt";
    canvas->saveToFile(filename);
    
    Canvas newCanvas(10, 10);
    newCanvas.loadFromFile(filename);
    
    EXPECT_EQ(newCanvas.getChar(0, 0), '#');
    EXPECT_EQ(newCanvas.getChar(5, 5), '@');
    EXPECT_EQ(newCanvas.getChar(9, 9), '*');
    
    std::remove(filename.c_str());
}

TEST_F(CanvasTest, LoadFromFile_ReturnsFalseForInvalidFile) {
    Canvas newCanvas;
    bool result = newCanvas.loadFromFile("nonexistent_file.txt");
    EXPECT_FALSE(result);
}

TEST_F(CanvasTest, LoadFromFile_HandlesWrongFormat) {
    std::ofstream file("bad_format.txt");
    file << "not a number" << std::endl;
    file.close();
    
    Canvas newCanvas;
    bool result = newCanvas.loadFromFile("bad_format.txt");
    EXPECT_FALSE(result);
    
    std::remove("bad_format.txt");
}

TEST_F(CanvasTest, SaveToFile_CreatesFileWithCorrectFormat) {
    canvas->setChar(0, 0, 'A');
    canvas->saveToFile("format_test.txt");
    
    std::ifstream file("format_test.txt");
    int w, h;
    file >> w >> h;
    EXPECT_EQ(w, 10);
    EXPECT_EQ(h, 10);
    
    std::string line;
    std::getline(file, line); // skip newline
    std::getline(file, line);
    EXPECT_EQ(line[0], 'A');
    
    std::remove("format_test.txt");
}