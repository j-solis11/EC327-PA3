#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Point2D.h"
#include "Model.h"
#include "View.h"
using namespace std;

Model::Model() {
    time = 0;
    Point2D d1(5,1), d2(10,1), d3(1,20), d4(10,20), d5(0,0), d6(5,5);
    trainer_ptrs[0] = new Trainer("Ash",1,'T',1,d1);
    object_ptrs[0] = trainer_ptrs[0];
    trainer_ptrs[1] = new Trainer("Misty",2,'T',2,d2);
    object_ptrs[1] = trainer_ptrs[1];

    center_ptrs[0] = new PokemonCenter(1,1,100,d3);
    object_ptrs[2] = center_ptrs[0];
    center_ptrs[1] = new PokemonCenter(2,2,200,d4);
    object_ptrs[3] = center_ptrs[1];

    gym_ptrs[0] = new PokemonGym(10,1,2,3,1,d5);
    object_ptrs[4] = gym_ptrs[0];
    gym_ptrs[1] = new PokemonGym(20,5,7.5,4,2,d6);
    object_ptrs[5] = gym_ptrs[1];

    num_objects = 6;
    num_trainers = 2;
    num_centers = 2;
    num_gyms = 2;
    cout << "Model default constructed" << endl;
}

Model::~Model() {
    for (int i = 0; i < num_objects; i++) {
        delete object_ptrs[i];
    }
    cout << "Model destructed" << endl;
}

Trainer * Model::GetTrainerPtr(int id) {
    Trainer * return_ptr = 0;
    for (int i = 0; i < 10; i++) {
        if (trainer_ptrs[i]->GetId() == id) {
            return_ptr = trainer_ptrs[i];
            break;
        }
    }
    return return_ptr;
}

PokemonCenter * Model::GetPokemonCenterPtr(int id) {
    PokemonCenter * return_ptr = 0;
    for (int i = 0; i < 10; i++) {
        if (((center_ptrs[i])->GetId()) == id) {
            return_ptr = center_ptrs[i];
            break;
        }
    }
    return return_ptr;
}

PokemonGym * Model::GetPokemonGymPtr(int id) {
    PokemonGym * return_ptr = 0;
    for (int i = 0; i < 10; i++) {
        if ((gym_ptrs[i])->GetId() == id) {
            return_ptr = gym_ptrs[i];
            break;
        }
    }
    return return_ptr;
}

bool Model::Update() {
    time++;
    bool val = false;   //return
    bool b2 = true; //game over: battles done
    bool b3 = true;    //game over: all fainted
    for (int i = 0; i < num_objects; i++) {
        bool b1 = (*object_ptrs[i]).Update();
        if (b1 == true) {
            cout << i << endl;
            val = true;
        }    
    }
    for (int j = 0; j < num_gyms; j++) {
        unsigned int b1 = (*gym_ptrs[j]).GetNumBattlesRemaining();
        if (b1 != 0) {
            b2 = false;
        }
    }
    for (int k = 0; k < num_trainers; k++) {
        bool b4 = (*trainer_ptrs[k]).ShouldBeVisible();
        if (b4 == true) {
            b3 = false;
        }
    }
    if (b2 == true) {
        cout << "GAME OVER: You win! All battles done!" << endl;
        Model::~Model();
        exit(0);
    }
    if (b3 == true) {
        cout << "GAME OVER: You lose! All of your Trainers' pokemon have fainted!" << endl;
         Model::~Model();
        exit(0);
    }
    return val;
}

void Model::Display(View & view) {
    view.Clear();
    for (int i = 0; i < num_objects; i++) {
        view.Plot(object_ptrs[i]);   
    }
    view.Draw();
}

void Model::ShowStatus() {
    cout << "Time: " << time << endl;
    for (int i = 0; i < num_objects; i++) {
        (*object_ptrs[i]).ShowStatus();
    }
}