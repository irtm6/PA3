#include "../FuncA.h"
#include <iostream>
#include <cmath>


bool verifySum(double x, int terms, double expected_result, double tolerance) {
    FuncA func;
    double result = func.count(x, terms);


    return std::abs(result - expected_result) < tolerance;
}

int main() {

    double x = 1.0;    
    int terms = 3;      
    double tolerance = 3.0; 

  
    double expected_result = (1.0 / 1) * std::pow(x, 1) + 
                             (2.0 / 3) * std::pow(x, 3) +
                             (24.0 / 15) * std::pow(x, 5);

  
    if (verifySum(x, terms, expected_result, tolerance)) {
        std::cout << "The series sum is correct!" << std::endl;
        return 0;
    } else {
        std::cout << "The series sum is incorrect!" << std::endl;
        return 1;
    }
}

