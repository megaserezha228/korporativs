// Сценарий 6: Сохранение с неправильным путём
// 1. Нажать 's'
// 2. Ввести "/////invalid\\path/file.txt"
// Ожидаемый результат: Программа выводит сообщение об ошибке, не падает

#include "Canvas.h"
#include <iostream>

int main() {
    Canvas canvas(40, 20);
    canvas.setChar(5, 5, '#');
    bool result = canvas.saveToFile("\\\\?\\invalid|path.txt");
    bool success = !result;
    success = success && (canvas.getChar(5, 5) == '#');
    
    std::cout << "Scenario 6: " << (success ? "PASSED" : "FAILED") << std::endl;
    return success ? 0 : 1;
}