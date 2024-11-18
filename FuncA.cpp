#include "FuncA.h"
#include <cmath>

// Конструктор класу FuncA
FuncA::FuncA() {

}

// Функція для обчислення факторіала заданого числа
long long factorial(int num) {
    // факторіал 0 або 1 дорівнює 1
    if (num == 0 || num == 1)
        return 1;
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

// Функція для обчислення суми ряду на основі вхідного x і кількості членів
double FuncA::count(double x, int terms) {
    double sum = 0.0; // Ініціалізуємо суму

    for (int n = 0; n < terms; n++) {
        long long numerator = factorial(2 * n); // чисельник (2n)!
        long long denominator = std::pow(4, n) * std::pow(factorial(n), 2) * (2 * n + 1); // знаменник
        double term = (static_cast<double>(numerator) / denominator) * std::pow(x, 2 * n + 1); // обчислення члена ряду
        sum += term; // Додаємо поточний член до суми
    }

    return sum; // Повертаємо остаточну обчислену суму
}

