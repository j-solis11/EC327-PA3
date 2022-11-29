#include <iostream>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Point2D.h"
#include "Vector2D.h"
#ifndef TRAINER_H
#define TRAINER_H
using namespace std;

enum TrainerStates {
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2,
    AT_CENTER = 3,
    IN_GYM = 4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};

class Trainer: public GameObject {
    public:
        Trainer();
        Trainer(char);
        Trainer(string, int, char, unsigned int, Point2D);
        virtual ~Trainer();
        void StartMoving(Point2D);
        void StartMovingToGym(PokemonGym*);
        void StartMovingToCenter(PokemonCenter*);
        void StartBattling(unsigned int);
        void StartRecoveringHealth(unsigned int);
        void Stop();
        bool HasFainted();
        bool ShouldBeVisible();
        void ShowStatus();
        bool Update();
        string GetName();
    protected:
        bool UpdateLocation();
        void SetupDestination(Point2D);
    private:
        double speed;
        bool is_at_center;
        bool is_IN_GYM;
        unsigned int health;
        unsigned int experience;
        double PokeDollars;
        unsigned int battles_to_buy;
        unsigned int potions_to_buy;
        string name;
        PokemonCenter* current_center;
        PokemonGym* current_gym;
        Point2D destination;
        Vector2D delta;
};

double GetRandomAmountOfPokeDollars();

#endif