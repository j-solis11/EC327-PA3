#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

//Public member functions
GameObject::GameObject(char in_code) {
    id_num = 1;
    display_code = in_code;
    state = '0';
    cout << "GameObject constructed" << endl;
}

GameObject::GameObject(const Point2D in_loc, int in_id, char in_code) {
    location = in_loc;
    id_num = in_id;
    display_code = in_code;
    state = '0';
    cout << "GameObject constructed" << endl;
}     

GameObject::~GameObject()  {
    cout << "GameObject destructed" << endl;
}

Point2D GameObject::GetLocation() {
    Point2D p_return;
    p_return = location;
    return p_return;
}  

int GameObject::GetId() {
    int id_return;
    id_return = id_num;
    return id_return;
}   

char GameObject::GetState() {
    int state_return;
    state_return = state;
    return state_return;
}    

void GameObject::ShowStatus() {
    cout << display_code << " " << id_num << " at " << location << endl;
}

void GameObject::DrawSelf(char * ptr) {
    *ptr = GetDisplayCode();
    *(ptr + 1) = '0' + GetId();
}

char GameObject::GetDisplayCode() {
    return display_code;
}