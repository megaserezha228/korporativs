#include <gtest/gtest.h>
#include "KeyboardInput.h"

TEST(KeyboardInputTest, GetKey_ReturnsCharType) {
    char result = KeyboardInput::getKey();
    SUCCEED();
}

TEST(KeyboardInputTest, KeyPressed_ReturnsBoolType) {
    bool result = KeyboardInput::keyPressed();
    SUCCEED();
}