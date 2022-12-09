/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

/* Key word explanation :
*   "virtual":  - Function could be called under same name but overridden by other subclasses
*               - Only named in base class
*               - Later overridden and declared in subclass
*               - Needs to have "const = 0"
*                   - A "pure virtual" will not be used in current base class
*                   - Will be declared later in subclasses
*                   - Must be overloaded return 0
* 
*   "friend":   - Has access to member functions as well as subclasses of base class
* 
*   "Dynamic binding":  - When using virtual functions
*                       - Takes place at runtime (late binding)
*                       - function call is only resolved at runtime and not compile time (static binding)
*
*/


#pragma once

#include <iostream>

constexpr double Epsilon = 1.0e-5;

class Expression {
public:
    // Destructor
    virtual ~Expression() {
        --count_expressions;
    }

    // ADD OTHER MEMBER FUNCTIONS
    bool isRoot(double x) const;

    // Use virtual here as this is the base class
    virtual double operator()(double d) const = 0;  // must be overloaded return 0 

    // Use friend to have access to members and subclasses
    friend std::ostream& operator<<(std::ostream& os, const Expression&);

    virtual Expression* clone() const = 0;

    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();


protected:
    // Default constructor
    Expression() {
        ++count_expressions;
    }

    // Copy constructor
    Expression(const Expression&) {
        ++count_expressions;
    }
    
    Expression& operator=(const Expression&) = default;

    // Total number of existing expressions -- to help to detect bugs in the code
    static std::size_t count_expressions;

    virtual void display(std::ostream&) const = 0; // if overloaded return 0
};
