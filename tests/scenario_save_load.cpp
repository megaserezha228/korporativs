// Сценарий 3: Сохранение и загрузка файла
// 1. Нарисовать крест: линия по горизонтали и вертикали
// 2. Нажать 's', сохранить в "cross.txt"
// 3. Очистить холст ('c')
// 4. Нажать 'o', загрузить "cross.txt"
// Ожидаемый результат: Крест восстановлен на холсте


#include "Canvas.h"
#include <iostream>

int main() {
    Canvas original(40, 20);
    
    // Рисуем крест
    original.drawLine(10, 10, 30, 10, '#');
    original.drawLine(20, 5, 20, 15, '#');
    
    // Сохраняем
    original.saveToFile("cross.txt");
    
    // Загружаем в новый холст
    Canvas loaded(40, 20);
    loaded.loadFromFile("cross.txt");
    
    // Проверяем совпадение
    bool success = true;
    for (int y = 0; y < 20 && success; y++) {
        for (int x = 0; x < 40 && success; x++) {
            if (original.getChar(x, y) != loaded.getChar(x, y)) {
                success = false;
            }
        }
    }
    
    std::cout << "Scenario 3: " << (success ? "PASSED" : "FAILED") << std::endl;
    return success ? 0 : 1;
}