// Сценарий 1: Создание простого рисунка
// 1. Запустить программу
// 2. Переместить курсор в позицию (10, 5)
// 3. Нажать 'p' для рисования точки
// 4. Переместить курсор в позицию (20, 5)
// 5. Нажать 'p' для рисования второй точки
// 6. Нажать 'l' и нарисовать линию между точками
// 7. Нажать 's' и сохранить рисунок в "simple.txt"
// Ожидаемый результат: Линия соединяет две точки


#include "Canvas.h"
#include <iostream>

int main() {
    Canvas canvas(40, 20);
    canvas.setChar(10, 5, '#');
    canvas.setChar(20, 5, '#');
    canvas.drawLine(10, 5, 20, 5, '#');
    bool success = true;
    for (int x = 10; x <= 20; x++) {
        if (canvas.getChar(x, 5) != '#') {
            success = false;
            break;
        }
    }
    
    canvas.saveToFile("simple.txt");
    
    std::cout << "Scenario 1: " << (success ? "PASSED" : "FAILED") << std::endl;
    return success ? 0 : 1;
}