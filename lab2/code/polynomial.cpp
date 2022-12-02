/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <vector>

// Convert a vector of double into a Polynomial
Polynomial::Polynomial(const std::vector<double>& arg) {
	for (double i : arg) {		// for each element 
		coeff.push_back(i);		// push back into vector coeff
	}
}

// Convert real constant into a Polynomial
Polynomial::Polynomial(double arg) { coeff.push_back(arg); }

// add-and-assign operator
Polynomial Polynomial::operator+=(const Polynomial& rhs) {
	for (std::size_t i = 0; i < rhs.coeff.size(); i++) {
		if (i >= coeff.size()) {
			coeff.push_back(rhs.coeff[i]);
		}
		else coeff[i] += rhs.coeff[i];
	}
	return *this;
}