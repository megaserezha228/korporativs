// Сценарий 2: Рисование и заливка прямоугольника
// 1. Очистить холст ('c')
// 2. Нажать 'r' и ввести координаты (5,5) и (15,10)
// 3. Выбрать 'n' (не заливать)
// 4. Переместить курсор внутрь прямоугольника
// 5. Нажать 'f' для заливки
// 6. Нажать 's' и сохранить в "filled_rect.txt"
// Ожидаемый результат: Прямоугольник залит текущим символом внутри

#include "Canvas.h"
#include <iostream>

int main() {
    Canvas canvas(40, 20);
    
    canvas.drawRectangle(5, 5, 15, 10, '#', false);
    canvas.floodFill(10, 7, ' ', '@');
    bool success = (canvas.getChar(10, 7) == '@');
    
    success = success && (canvas.getChar(5, 5) == '#');
    success = success && (canvas.getChar(15, 10) == '#');
    
    canvas.saveToFile("filled_rect.txt");
    
    std::cout << "Scenario 2: " << (success ? "PASSED" : "FAILED") << std::endl;
    return success ? 0 : 1;
}