#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    std::cout << "Add: " << calc.Add(2, 3) << std::endl;
    std::cout << "Sub: " << calc.Sub(5, 2) << std::endl;
    return 0;
}

