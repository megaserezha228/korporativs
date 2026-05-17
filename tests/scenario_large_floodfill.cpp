// Сценарий 5: Заливка большой области
// 1. Нарисовать прямоугольник размером 30×15
// 2. Переместить курсор внутрь
// 3. Нажать 'f' для заливки
// Ожидаемый результат: Заливка выполнена без переполнения стека

#include "Canvas.h"
#include <iostream>
#include <chrono>

int main() {
    Canvas canvas(100, 50);
    canvas.drawRectangle(10, 10, 90, 40, '#', false);
    auto start = std::chrono::high_resolution_clock::now();
    canvas.floodFill(50, 25, ' ', '@');
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    bool success = (canvas.getChar(50, 25) == '@');
    bool noOverflow = (duration.count() < 1000); // менее секунды
    
    std::cout << "Scenario 5: " << (success ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Time: " << duration.count() << "ms" << std::endl;
    
    return success ? 0 : 1;
}