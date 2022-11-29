#include <iostream>
using namespace std;
#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
    public: 
        double x;
        double y;
        Vector2D();     //Default constructor
        Vector2D(double, double);       //Constructor
};

//Non-member overloaded operators
ostream& operator<<(ostream&, const Vector2D&);      //using cout w/ Vector2D
Vector2D operator*(const Vector2D&, const double);
Vector2D operator/(const Vector2D&, const double);

#endif