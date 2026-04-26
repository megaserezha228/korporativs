#ifndef APP_CONFIG_H
#define APP_CONFIG_H

class AppConfig {
private:
    static AppConfig* instance;
    
    char currentDrawChar;
    int canvasWidth;
    int canvasHeight;
    bool showHelpOnStart;
    
    AppConfig();
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
    
public:
    static AppConfig* getInstance();
    
    char getDrawChar() const;
    void setDrawChar(char ch);
    
    int getCanvasWidth() const;
    int getCanvasHeight() const;
    void setCanvasSize(int w, int h);
    
    bool getShowHelpOnStart() const;
    void setShowHelpOnStart(bool value);
};

#endif