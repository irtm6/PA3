#include "FuncA.h"
#include <cmath>
#include <chrono>
#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>

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
void FuncA::testServerSimulation() {
    FuncA func;
    int n = 10; // кількість елементів для обчислення
    int x = 1;
    std::vector<double> results;
    
    auto start_time = std::chrono::high_resolution_clock::now();

    // Генерація результатів
    for (int i = 0; i < 100000; ++i) {
        results.push_back(func.count(x, n));
    }

    // Сортування
    for(int i=0; i<7000; i++){
    		std::sort(results.begin(), results.end(), [](const auto &a, const auto &b) {
        	return std::abs(a) < std::abs(b);
    	});
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

   // Виведення часу на консоль (імітація відповіді сервера)
    std::cout << "Elapsed time (ms): " << elapsed.count() << std::endl;

    // Перевірка часу виконання
    assert(elapsed.count() >= 5000 && elapsed.count() <= 20000 && "Test failed: Elapsed time is out of bounds!");
    }
