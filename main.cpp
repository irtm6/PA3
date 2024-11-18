#include <iostream>
#include "FuncA.h"

int main() {
    FuncA function;
    double x;
    int n;

    std::cout << "Введіть значення x: ";
    std::cin >> x;

    std::cout << "Введіть кількість членів ряду: ";
    std::cin >> n;

    std::cout << "Result: " << function.count(x, n) << "\n";

    return 0;
}

