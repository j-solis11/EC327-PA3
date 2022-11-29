#include <iostream>
#include "Point2D.h"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
using namespace std;

class GameObject {
    protected: 
        Point2D location;
        int id_num;
        char display_code;
        char state;
    public:
        GameObject(char);   //initalizes variables
        GameObject(Point2D, int, char);     //initalizes gameobject with inputted variables
        virtual ~GameObject();
        Point2D GetLocation();  //Returns location
        int GetId();    //returns (int) id
        char GetState();    //returns the (char) state 
        virtual void ShowStatus();  //outputs information in class
        virtual bool Update() = 0;
        virtual bool ShouldBeVisible() = 0;
        void DrawSelf(char *);
        char GetDisplayCode();
};

#endif