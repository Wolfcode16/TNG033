/*********************************************
 * Lab 3: exercise 3                         *
 * Program to compute an approximation of PI *
 * STL-algorithms should be used             *
 *********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <format>


// Calculates formula
double calculate(double k) {
    double const factor{ 8.0 * k };
    double const init{ 4.0 / (factor + 1.0) - 1.0 / (factor + 4.0) };

    std::vector<double> other_factors{ 4.0, 5.0, 6.0 };

    // Instead of for-loop: transform( start range , end range, destination start range, operation)
    // Takes in : double d (values from "other_factors"
    //            factor (reference to the double const "factor"
    // Proceeds to execture the same math function as in "exerc3_given.cpp"
    std::transform(other_factors.begin(), other_factors.end(), other_factors.begin(), [&factor](double d) { return -1.0 / (factor + d); } );

    // Starts variable result with intialized values
    double result = init; //******* BYTTE ********

    // std::accumulate ( start range, end range , initial value of sum)
    // Adds together all "other_factors" + initial value
    result = std::accumulate(other_factors.begin(), other_factors.end(), init);
    return result;
}


int main() {
    std::cout << "Enter number of terms: ";
    int n;
    std::cin >> n;

    // Create a vector called "terms" holding variable n
    std::vector<double> terms(n);

    // starts from zero, and sequentially increases value for each value until terms.end
    std::iota(terms.begin(), terms.end(), 0);

    std::vector<double> power_terms{ terms };
    // Instead of for-loop: transform( start range , end range, destination start range, operation)
    // Use the calculate function on all terms
    std::transform(terms.begin(), terms.end(), terms.begin(), calculate);

    // return (1/16)^(every value in "power_term")
    std::transform(power_terms.begin(), power_terms.end(), power_terms.begin(), [](int i) { return std::pow(16.0, -i); });

    double result = 0.0;
    // std::inner_product(start range, end range, destination start range, initial value)
    result = std::inner_product(terms.begin(), terms.end(), power_terms.begin(), 0.0);

    std::cout << std::format("{:.15f}\n", result);
}
