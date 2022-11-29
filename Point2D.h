#include <iostream>
#include "Vector2D.h"
using namespace std;
#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
    public:
        double x;
        double y;
        Point2D();      //Default constructor
        Point2D(double, double);      //Constructor
};

//Non-member Function
double GetDistanceBetween(Point2D, Point2D);   

//Non-member overloaded operators
ostream& operator<<(ostream&, const Point2D&);      //using cout w/ Point2D
Point2D operator+(const Point2D&, const Vector2D&);     //adding a Point2D and Vector2D
Vector2D operator-(const Point2D&, const Point2D&);     //subtracting two Point2D's

#endif