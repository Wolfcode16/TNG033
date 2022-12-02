/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <iomanip>
#include <vector>

// Convert a vector of double into a Polynomial
Polynomial::Polynomial(const std::vector<double>& arg) {
	for (double i : arg) {		// for each element 
		coeff.push_back(i);		// push back into vector coeff
	}
}

// Convert real constant into a Polynomial
Polynomial::Polynomial(double arg) { coeff.push_back(arg); }	// Push back into vector coeff

Polynomial* Polynomial::clone() const {
    return new Polynomial(*this);
}

// add-and-assign operator
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {		
	for (std::size_t i = 0; i < rhs.coeff.size(); i++) {
		if (i >= coeff.size()) {								// If VL is done
			coeff.push_back(rhs.coeff[i]);						// Pushback rest of HL
		}		
		else coeff[i] += rhs.coeff[i];							// Add VL with HL
	}
	return *this;
}

// Display function
void Polynomial::display(std::ostream& os) const {

    for (std::size_t i = 0; i < coeff.size(); i++) {
        if (i == 0) {                                               // if its the first coeff
            os << std::fixed << std::setprecision(2) << coeff[i];   // Write it as a constant
        }
        else if (coeff[i] < 0) {                                                                // if coeff negative
            os << std::fixed << std::setprecision(2) << " - " << abs(coeff[i]) << " * X^" << i; // add negative sign infront
        }
        else {
            os << std::fixed << std::setprecision(2) << " + " << abs(coeff[i]) << " * X^" << i; // add positive sign infront
        }
    }
}

// Calculates value of polynomial
double Polynomial::operator()(double d) const {

    double sum = 0;

    for (std::size_t i = 0; i < coeff.size(); i++) {
        if (i == 0) sum += coeff[i];
        else {
            sum += coeff[i] * (pow(d, i));
        }
    }
    return sum;
}

// Operator[]
double& Polynomial::operator[](int arg) {
    return coeff[arg];                      // Return the coeff in place arg
}

double Polynomial::operator[](int arg) const {
    return coeff[arg];
}
