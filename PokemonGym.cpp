#include <iostream>
#include "PokemonGym.h"
#include "Building.h"
#include "Point2D.h"
using namespace std;

PokemonGym::PokemonGym() : Building() {
    display_code = 'G';
    state = NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    PokeDollar_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout << "PokemonGym default constructed" << endl;
}

PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc) : Building('G',in_id,in_loc) {
    state = NOT_DEFEATED;
    max_number_of_battles = max_battle;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = health_loss;
    experience_per_battle = exp_per_battle;
    PokeDollar_cost_per_battle = PokeDollar_cost;
    cout << "PokemonGym constructed" << endl;
}

PokemonGym::~PokemonGym() {
    cout << "PokemonGym destructed" << endl;
}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty) {
    return (battle_qty * PokeDollar_cost_per_battle);
}

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty) {
    return (battle_qty * health_cost_per_battle);
}

unsigned int PokemonGym::GetNumBattlesRemaining() {
    return num_battle_remaining;
}

bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health) {
    if ((health >= (health_cost_per_battle * battle_qty)) && (budget >= (PokeDollar_cost_per_battle * battle_qty))) {
        return true;
    }
    else {
        return false;
    }
}

unsigned int PokemonGym::TrainPokemon(unsigned int battle_units) {
    if (battle_units > num_battle_remaining) {
        unsigned int temp = (num_battle_remaining * experience_per_battle);
        num_battle_remaining = 0;
        return temp;
    } 
    else {
        unsigned int temp = (battle_units * experience_per_battle);
        num_battle_remaining = num_battle_remaining - battle_units;
        return temp;
    }
}

unsigned int PokemonGym::GetExperience(unsigned int battle_units) {
    return (battle_units * experience_per_battle);
}

unsigned int PokemonGym::GetExperiencePerBattle() {
    return experience_per_battle;
}
bool PokemonGym::Update() {
    if (num_battle_remaining == 0) {
        if (state != DEFEATED) {
            state = DEFEATED;
            display_code = 'g';
            cout << display_code << " " << id_num << " has been beaten" << endl;
            return DEFEATED;
        }
        else {
            cout << display_code << " " << id_num << " has been beaten" << endl;
            return false;
        }
    }
    else {
        return false;
    }
}

bool PokemonGym::passed() {
    if (num_battle_remaining == 0) {
        return true;
    } 
    else {
        return false;
    }
}

void PokemonGym::ShowStatus() {
    cout << "PokemonGymStatus: ";
    Building::ShowStatus();
    cout << "Max numbers of battles: " << max_number_of_battles << endl;
    cout << "Health cost per battle: " << health_cost_per_battle << endl;
    cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
    cout << "Experience per battle: " << experience_per_battle << endl;
    cout << num_battle_remaining << " battle(s) are remaining for this PokemonGym" << endl;
}