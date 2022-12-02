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

	Polynomial* clone() const override;

	Polynomial& operator=(const Polynomial&) = default;		// Assignment operator: P1 = P2, similar to copy constructor

	Polynomial& operator+=(const Polynomial& rhs);			// add-and-assign operator, P1+=P2

	//P3 = P1 + P2, addition of two polynomials
	//we are not using *this, so not a member function, but we need to have access to private coeff
	// Converting inputs into class of Polynomial
	friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
		return (lhs += rhs); //using += operator
	}

	double operator()(double d) const override;	// Calculates value of polynomial
	double& operator[](int arg);				// Subscript operator, to be able to assign
	double operator[](int arg) const;			// Subscript operator, to be able to compare

private:
	std::vector<double> coeff;
	void display(std::ostream& os) const override;
};
