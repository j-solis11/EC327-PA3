#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

//Default Constructor
Point2D::Point2D() {    
    x = 0;
    y = 0;
}

//Constructor
Point2D::Point2D(double in_x, double in_y) {    
    x = in_x;
    y = in_y;
}

//non-member function
double GetDistanceBetween(Point2D p1, Point2D p2) {     
    return sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2));
}

//Non-member overloaded operators
ostream& operator<<(ostream& os, const Point2D& p1) {
    os << "(" << p1.x << ", " << p1.y << ")";
    return os;
}

Point2D operator+(const Point2D& p1, const Vector2D& v1) {
    Point2D p_return;
    p_return.x = p1.x + v1.x;
    p_return.y = p1.y + v1.y;
    return p_return;
}

Vector2D operator-(const Point2D& p1, const Point2D& p2) {
    Vector2D v_return;
    v_return.x = p1.x - p2.x;
    v_return.y = p1.y - p2.y;
    return v_return;
}
