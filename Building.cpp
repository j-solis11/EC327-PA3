#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#include "Building.h"
using namespace std;

//Constructors
Building::Building() : GameObject('B') {
    trainer_count = 0;
    cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_Id, Point2D in_loc) : GameObject(in_loc,in_Id,in_code) {
    trainer_count = 0;
    cout << "Building constructed" << endl;
}

//Public member functions
void Building::AddOneTrainer() {
    trainer_count++;
}

void Building::RemoveOneTrainer() {
    trainer_count--;
}

void Building::ShowStatus() {
    cout << display_code << " " << id_num << " located at " << location << endl;
    cout << trainer_count;
    if (trainer_count == 1) {
        cout << " trainer is in this buiding" << endl;
    }
    else {
        cout << " trainers are in this building" << endl;
    }
}

bool Building::ShouldBeVisible() {
    return true;
}
