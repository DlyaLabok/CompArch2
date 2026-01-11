#include <iostream>
#include "calculator.h"
int main() {
    Calculator calc;
    std::cout << "3.0 + 4.0 = " << calc.Add(3.0, 4.0) << std::endl;
    std::cout << "3.0 - 4.0 = " << calc.Sub(3.0, 4.0) << std::endl;
    return 0;
}
