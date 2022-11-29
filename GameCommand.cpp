#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "GameCommand.h"
using namespace std;

void DoMoveCommand(Model& model, int trainer_id, Point2D p1) {
    cout << "b";
    if (model.GetTrainerPtr(trainer_id) == 0) {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else {
        Trainer * t1 = model.GetTrainerPtr(trainer_id);
        cout << "Moving " << (*t1).GetName() << " to "  << p1 << endl;
        (*t1).StartMoving(p1);
    }
}

void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id) {
    if ((model.GetTrainerPtr(trainer_id) != 0) && (model.GetPokemonCenterPtr(center_id) != 0)) {
        Trainer * t1 = model.GetTrainerPtr(trainer_id);
        PokemonCenter * c1 = model.GetPokemonCenterPtr(center_id);
        cout << "Moving " << (*t1).GetName() << " to pokemon center " << (*(c1)).GetId() << endl;
        (*t1).StartMovingToCenter(c1);
    }
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id) {
    if ((model.GetTrainerPtr(trainer_id) != 0) && (model.GetPokemonGymPtr(gym_id) != 0)) {
        Trainer * t1 = model.GetTrainerPtr(trainer_id);
        PokemonGym * g1 = model.GetPokemonGymPtr(gym_id);
        cout << "Moving " << (*t1).GetName() << " to gym  " << (*g1).GetId() << endl;
        (*t1).StartMovingToGym(g1);
    }
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoStopCommand(Model& model, int trainer_id) {
    if (model.GetTrainerPtr(trainer_id) == 0) {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else {
        Trainer * t1 = model.GetTrainerPtr(trainer_id);
        cout << "Stopping " << (*t1).GetName() << endl;
        (*t1).Stop();
    }
}

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles) {
    if ((model.GetTrainerPtr(trainer_id) != 0) && (battles > 0)) {
        Trainer * t1 = model.GetTrainerPtr(trainer_id);
        cout << (*t1).GetName() << " is battling" << endl;
        t1->StartBattling(battles);
    }
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoRecoverInCenterCommand(Model & model, int trainer_id, unsigned int potions_needed) {
    if ((model.GetTrainerPtr(trainer_id) != 0) && (potions_needed > 0)) {
        Trainer * t1 = model.GetTrainerPtr(trainer_id);
        cout << "Recovering " << (*t1).GetName() << "'s Pokemon's health" << endl;
        (*t1).StartRecoveringHealth(potions_needed);
    }
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}



void DoAdvanceCommand(Model& model, View& view) {
    bool b1;
    cout << "Advancing one tick" << endl;
    b1 = model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model& model, View& view) {
    cout << "Advancing to next event" << endl;
    bool b_up;
    for (int j = 0; j < 5; j++) {
        b_up = model.Update();
        if (b_up != 0) {
            break;
        }
    }
    model.ShowStatus();
    model.Display(view);
}

void CommandGame(char command, Model& model) {
    switch (command) {
        int in_id, in_id1, in_id2;
        double x, y;
        unsigned int num;
        bool b1;
        case 'm': {
            cin >> in_id;
            cin >> x;
            cin >> y;
            Point2D p(x,y);
            DoMoveCommand(model,in_id,p);
            break; }
        case 'c': 
            cin >> in_id1;
            cin >> in_id2;
            DoMoveToCenterCommand(model,in_id1,in_id2);
            break;
        case 'g': 
            cin >> in_id1;
            cin >> in_id2;
            DoMoveToGymCommand(model,in_id1,in_id2);
            break;
        case 's':
            cin >> in_id;
            DoStopCommand(model, in_id);
            break;
        case 'p':
            cin >> in_id;
            cin >> num;
            DoRecoverInCenterCommand(model, in_id, num);
            break;
        case 'b': 
            cin >> in_id;
            cin >> num;
            DoBattleCommand(model, in_id, num);
            break;
        case 'q':
        model.~Model();
            exit(0);
            break;
    }
}