#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#ifndef BUILDING_H
#define BUILDING_H
using namespace std;

class Building: public GameObject {
    private:
        unsigned int trainer_count;
    public:
        Building();
        Building(char, int, Point2D);
        void AddOneTrainer();
        void RemoveOneTrainer();
        void ShowStatus();
        bool ShouldBeVisible();
};



#endif