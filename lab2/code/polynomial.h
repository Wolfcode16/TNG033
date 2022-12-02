/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include "expression.h"
#include <vector>

class Polynomial : public Expression {
public:

	Polynomial(const std::vector<double>& arg);				//	vector of double to Polynomial
	Polynomial(double arg);									//	real constant to Polynomial
	Polynomial(const Polynomial&) = default;				//	Copy constructor that returns default 
															//	constructor of inserted Polynomial

	~Polynomial() = default;								// destructor to free up memory

	Polynomial& operator=(const Polynomial&) = default;		// Assignment operator: P1 = P2, similar to copy constructor

	Polynomial operator+=(const Polynomial& rhs);			// add-and-assign operator, P1+=P2

private:
	std::vector<double> coeff;
	void display(std::ostream os) const override;			// Overrides the virtual function display from base class
};
