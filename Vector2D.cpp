#include <iostream>
#include "Vector2D.h"
using namespace std;

//Default Constructor
Vector2D::Vector2D() {    
    x = 0;
    y = 0;
}

//Constructor
Vector2D::Vector2D(double in_x, double in_y) {    
    x = in_x;
    y = in_y;
}

//Non-member overloaded operators
Vector2D operator*(const Vector2D& v1, const double d) {
    Vector2D v_return;
    v_return.x = v1.x * d;
    v_return.y = v1.y * d;
    return v_return;
}

Vector2D operator/(const Vector2D& v1, const double d) {
    Vector2D v_return;
    v_return.x = v1.x / d;
    v_return.y = v1.y / d;
    return v_return;
}

ostream& operator<<(ostream& os, const Vector2D& v1) {
    os << "<" << v1.x << ", " << v1.y << ">";
    return os;
}