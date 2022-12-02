/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "expression.h"

class Logarithm : public Expression {
  

public:
    Logarithm(); //default creat log2(x)
    Logarithm(const Expression& arg1, double arg2, double arg3, int arg4); //Klar
    Logarithm(const Logarithm& arg1);//Copy constructor

    ~Logarithm(); //destructor

    Logarithm* clone() const override;
    Logarithm& operator=(const Logarithm& rhs); // Assignment operator , P1 = P2;
    Logarithm& set_base(int arg);               // Sets the base for the logarithm

    double operator()(double d) const override; // for isRoot(double x) const override;

private:
    Expression* E;  // pointer for Polynomial or Logarithm
    int b;
    double c1, c2;

    void display(std::ostream& os) const override;
};
