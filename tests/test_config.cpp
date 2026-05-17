#include <gtest/gtest.h>
#include "AppConfig.h"

class AppConfigTest : public ::testing::Test {
protected:
    void TearDown() override {
        // Сброс синглтона для чистоты тестов
        AppConfig* instance = AppConfig::getInstance();
        instance->setDrawChar('#');
        instance->setCanvasSize(40, 20);
        instance->setShowHelpOnStart(false);
    }
};

TEST_F(AppConfigTest, GetInstance_ReturnsSameInstance) {
    AppConfig* config1 = AppConfig::getInstance();
    AppConfig* config2 = AppConfig::getInstance();
    EXPECT_EQ(config1, config2);
}

TEST_F(AppConfigTest, GetDrawChar_ReturnsDefaultValue) {
    AppConfig* config = AppConfig::getInstance();
    EXPECT_EQ(config->getDrawChar(), '#');
}

TEST_F(AppConfigTest, SetDrawChar_ChangesValue) {
    AppConfig* config = AppConfig::getInstance();
    config->setDrawChar('@');
    EXPECT_EQ(config->getDrawChar(), '@');
    
    config->setDrawChar('.');
    EXPECT_EQ(config->getDrawChar(), '.');
}

TEST_F(AppConfigTest, SetDrawChar_SpecialSymbols) {
    AppConfig* config = AppConfig::getInstance();
    config->setDrawChar('*');
    EXPECT_EQ(config->getDrawChar(), '*');
    
    config->setDrawChar(' ');
    EXPECT_EQ(config->getDrawChar(), ' ');
}

TEST_F(AppConfigTest, GetCanvasWidth_ReturnsDefault) {
    AppConfig* config = AppConfig::getInstance();
    EXPECT_EQ(config->getCanvasWidth(), 40);
}

TEST_F(AppConfigTest, GetCanvasHeight_ReturnsDefault) {
    AppConfig* config = AppConfig::getInstance();
    EXPECT_EQ(config->getCanvasHeight(), 20);
}

TEST_F(AppConfigTest, SetCanvasSize_ChangesBothDimensions) {
    AppConfig* config = AppConfig::getInstance();
    config->setCanvasSize(60, 30);
    EXPECT_EQ(config->getCanvasWidth(), 60);
    EXPECT_EQ(config->getCanvasHeight(), 30);
}

TEST_F(AppConfigTest, SetCanvasSize_WithZeroValues) {
    AppConfig* config = AppConfig::getInstance();
    config->setCanvasSize(0, 0);
    EXPECT_EQ(config->getCanvasWidth(), 0);
    EXPECT_EQ(config->getCanvasHeight(), 0);
}

TEST_F(AppConfigTest, GetShowHelpOnStart_ReturnsDefaultFalse) {
    AppConfig* config = AppConfig::getInstance();
    EXPECT_FALSE(config->getShowHelpOnStart());
}

TEST_F(AppConfigTest, SetShowHelpOnStart_TogglesValue) {
    AppConfig* config = AppConfig::getInstance();
    config->setShowHelpOnStart(true);
    EXPECT_TRUE(config->getShowHelpOnStart());
    
    config->setShowHelpOnStart(false);
    EXPECT_FALSE(config->getShowHelpOnStart());
}