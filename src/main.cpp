#include "AsciiPaintApp.h"
#include "KeyboardInput.h"
#include <iostream>

int main() {
    std::cout << "ASCII Paint - Console ASCII Art Editor" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Press any key to start..." << std::endl;
    KeyboardInput::getKey();
    
    AsciiPaintApp app;
    app.run();
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}