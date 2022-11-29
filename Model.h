#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "Trainer.h"
#include "Point2D.h"
#include "View.h"
#ifndef MODEL_H
#define MODEL_H
using namespace std;

class Model {
    private:
        int time;
        GameObject * object_ptrs[10];
        int num_objects;
        Trainer * trainer_ptrs[10];
        int num_trainers;
        PokemonCenter * center_ptrs[10];
        int num_centers;
        PokemonGym * gym_ptrs[10];
        int num_gyms;
    public:
        Model();
        ~Model();
        Trainer * GetTrainerPtr(int);
        PokemonCenter * GetPokemonCenterPtr(int);
        PokemonGym * GetPokemonGymPtr(int);
        bool Update();
        void Display(View&);
        void ShowStatus();
        

};

#endif
