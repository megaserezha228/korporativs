// Сценарий 4: Обработка ошибок ввода
// 1. Нажать 'l' (линия)
// 2. Ввести нечисловые координаты (например, "abc def")
// Ожидаемый результат: Программа не падает, предлагает ввести координаты заново


#include "Canvas.h"
#include <iostream>
#include <sstream>

// ошибочный ввод
int main() {
    Canvas canvas(40, 20);
    bool result = canvas.loadFromFile("nonexistent_12345.txt");
    
    bool success = !result;
    std::ofstream file("broken.txt");
    file << "not a number" << std::endl;
    file.close();
    
    result = canvas.loadFromFile("broken.txt");
    success = success && !result;
    
    std::cout << "Scenario 4: " << (success ? "PASSED" : "FAILED") << std::endl;
    return success ? 0 : 1;
}