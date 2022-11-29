#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "Trainer.h"
using namespace std;

//Public
Trainer::Trainer() : GameObject('T') {
    speed = 5;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    cout << "Trainer default constructed" << endl;
}

Trainer::Trainer(char in_code) : GameObject(in_code) {
    speed = 5;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    state = STOPPED;
    cout << "Trainer constructed" << endl;
}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc,in_id,in_code) {
    speed = in_speed;
    name = in_name;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    state = STOPPED;
    cout << "Trainer constructed" << endl;
}

Trainer::~Trainer() {
    cout << "Trainer destructed" << endl;
}

void Trainer::StartMoving(Point2D dest) {
    if (GetDistanceBetween(dest,location) == 0) {
        cout << display_code << id_num << ": I'm already there, See?" << endl;
    }
    else if (HasFainted() == 1) {
        cout << display_code << id_num << ": My pokemon have fainted. I may move but you cannot see me." << endl;
    }
    else {
        if ((is_at_center = true) && (current_center != NULL)) {
            current_center->RemoveOneTrainer();
            is_at_center = false;
            current_center = NULL;
        }
        if ((is_IN_GYM = true) && (current_gym != NULL)) {
            current_gym->RemoveOneTrainer();
            is_IN_GYM = false;
            current_gym = NULL;
        }
        SetupDestination(dest);
        state = MOVING;
        cout << display_code << id_num << ": On my way." << endl;
    }
}

void Trainer::StartMovingToGym(PokemonGym* gym) {
    int temp_id = (*gym).GetId();
    if (GetDistanceBetween((*gym).GetLocation(),location) == 0) {
        cout << display_code << id_num << ": I'm already there, See?" << endl;
    }
    else if (state == FAINTED) {
        cout << display_code << id_num << ": My pokemon have fainted so I can't move to gym..." << endl;
    }
    else {
        if ((is_at_center = true) && (current_center != NULL)) {
            current_center->RemoveOneTrainer();
            is_at_center = false;
            current_center = NULL;
        }
        if ((is_IN_GYM = true) && (current_gym != NULL)) {
            current_gym->RemoveOneTrainer();
            is_IN_GYM = false;
        }
        SetupDestination((*gym).GetLocation());
        state = MOVING_TO_GYM;
        current_gym = gym;
        cout << display_code << id_num << ": on my way to gym " << temp_id << endl;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter* center) {
    int temp_id = (*center).GetId();
    if (GetDistanceBetween((center->GetLocation()),location) == 0) {
        cout << display_code << id_num << ": I am already at the center!" << endl;
    }
    else if (HasFainted() == 1) {
        cout << display_code << id_num << ": My pokemon have fainted so I should've gone to the center..." << endl;
    }
    else {
        if ((is_at_center = true) && (current_center != NULL)) {
            current_center->RemoveOneTrainer();
            is_at_center = false;
        }
        if ((is_IN_GYM = true) && (current_gym != NULL)) {
            current_gym->RemoveOneTrainer();
            is_IN_GYM = false;
            current_gym = NULL;
        }
        SetupDestination(center->GetLocation());
        state = MOVING_TO_CENTER;
        current_center = center;
        cout << display_code << id_num << ": on my way to Center " << temp_id << endl;
    }
}

void Trainer::StartBattling(unsigned int num_battles) {
    if (HasFainted() == 1) {
        cout << display_code << " " << id_num << ": My Pokemon have fainted so no more battles for me..." << endl;
    }
    else if (is_IN_GYM == false) {
            cout << display_code << " " << id_num << ": I can only battle in a PokemonGym!" << endl;
        }
    else if (((*current_gym).GetPokeDollarCost(num_battles)) > PokeDollars ) {
        cout << display_code << " " << id_num << ": Not enough money or health for battles" << endl;
    }
    else if ((*current_gym).GetNumBattlesRemaining() == 0) {
        cout << display_code << " " << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
    } 
    else {
        state = BATTLING_IN_GYM;
        battles_to_buy = num_battles;
        unsigned int waste = (*current_gym).TrainPokemon(num_battles);
        cout << display_code << " Started to battle at the PokemonGym "  << (*current_gym).GetId()<< " with " << num_battles << " battles" << endl;
    }
}
void Trainer::StartRecoveringHealth(unsigned int num_potions) {
    if (HasFainted() == 1) {
        cout << display_code << " " << id_num << ": My Pokemon have fainted so no more healing for me..." << endl;
    }
    else if (is_at_center == false) {
        cout << display_code << " " << id_num << ": I can only recover health at a Pokemon Center!" << endl;
    }
    else if (((*current_center).HasPotions()) == false) {
        cout << display_code << " " << id_num << ": Cannot recover! No potion remaining in this Pokemon Center" << endl;
    }
    else if (((*current_center).CanAffordPotion(num_potions,PokeDollars)) == false) {
        cout << display_code << " " << id_num << ": Not enough money to recover health." << endl;
    }
    else {
        int center_id = ((*current_center).GetId());
        state = RECOVERING_HEALTH;
        unsigned int potions = (*current_center).DistributePotion(num_potions);
        cout << display_code << " " << id_num << ": Started recovering " << potions << " potions at Pokemon Center " << center_id << endl;
        potions_to_buy = potions;
    }
}

void Trainer::Stop() {
    state = STOPPED;
    cout << display_code << " " << id_num << ": Stopping..." << endl;
}

bool Trainer::HasFainted() {
    if (health == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Trainer::ShouldBeVisible() {
    if (HasFainted() == true) {
        return false;
    }
    else {
        return true;
    }
}

void Trainer::ShowStatus() {
    cout << name << " status: ";
    GameObject::ShowStatus();
    switch (state) {
        case STOPPED:
            cout << " stopped" << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case MOVING:
            cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case MOVING_TO_GYM:
            cout << " heading to PokemonGym " << (*current_gym).GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case MOVING_TO_CENTER:
            cout << " heading to PokemonCenter " << (*current_center).GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case IN_GYM:
            cout << " inside PokemonGym " << (*current_gym).GetId() << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case AT_CENTER:
            cout << "inside PokemonCenter " << (*current_center).GetId() << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case BATTLING_IN_GYM:
            cout << " battling in PokemonGym " << (*current_gym).GetId() << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        case RECOVERING_HEALTH:
            cout << " recovering health in PokemonCenter " << (*current_center).GetId() << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
        default: 
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;
            break;
    }
}

bool Trainer::Update() {
    bool arrived;
    if (HasFainted() == true) {
        state = FAINTED;
    }
    switch (state) {
        case STOPPED: {
            return false;
            break;
        }
        case MOVING: {
            arrived = UpdateLocation();
            if (arrived == true) {
                state = STOPPED;
                return true;
            }
            else {
                health = health - 1;
                PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
                return false;
            }
            break;
        }
        case MOVING_TO_GYM: {
            arrived = UpdateLocation();
            if ((arrived == true) && (state != FAINTED)) {
                current_gym->AddOneTrainer();
                is_IN_GYM = true;
                state = IN_GYM;
                return true;
            }
            else {
                health = health - 1;
                PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
                return false;
            }
            break;
        }
        case MOVING_TO_CENTER: {
            arrived = UpdateLocation();
            if ((arrived == true) && (state != FAINTED)) {
                current_center->AddOneTrainer();
                is_at_center = true;
                state = AT_CENTER;
                return true;
            }
            else {
                health = health - 1;
                PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
                return false;
            }
            break;
        }
        case IN_GYM: {
            return false;
            break;
        }
        case AT_CENTER: {
            return false;
            break;
        }
        case BATTLING_IN_GYM: {
            health = health - (*current_gym).GetHealthCost(battles_to_buy);
            PokeDollars = PokeDollars - (*current_gym).GetPokeDollarCost(battles_to_buy);
            experience = experience + (*current_gym).GetExperience(battles_to_buy);
            cout << "** " << name << " completed " << battles_to_buy << " battle(s)! **" << endl;
            cout << "** " << name << " gained " << (*current_gym).GetExperience(battles_to_buy) << " experience! **" << endl;
            state = IN_GYM;
            return true;
            break;
        }
        case RECOVERING_HEALTH: {
            unsigned int health_recovered = potions_to_buy * 5;
            health = health + health_recovered;
            PokeDollars = PokeDollars - ((*current_center).GetPokeDollarCost(potions_to_buy));
            cout << "** " << name << " recovered " << health_recovered << " health! **" << endl;
            cout << "** " << name << " bought " << potions_to_buy << " potion(s)! **" << endl;
            state = AT_CENTER;
            return true;
        }
        default:
            return false;
    }
}

string Trainer::GetName() {
    return name;
}

//Protected
bool Trainer::UpdateLocation() {
    if ((delta.x >= 0) && (delta.y >= 0)) {
        if (((location.x + delta.x) >= destination.x) && ((location.y + delta.y) >= destination.y)) {
            location = destination;
            cout << display_code << " " << id_num << ": I'm there!" << endl;    //if there
            return true;
        }
        else {
            location = location + delta;
            cout << display_code << " " << id_num << ": step..." << endl;   //if not there
            return false;
        }
    }
    else if ((delta.x >= 0) && (delta.y <= 0)) {
        if (((location.x + delta.x) >= destination.x) && ((location.y + delta.y) <= destination.y)) {
            location = destination;
            cout << display_code << " " << id_num << ": I'm there!" << endl;    //if there
            return true;
        }
        else {
            location = location + delta;
            cout << display_code << " " << id_num << ": step..." << endl;   //if not there
            return false;
        }
    }
    else if ((delta.x <= 0) && (delta.y >= 0)) {
        if (((location.x + delta.x) <= destination.x) && ((location.y + delta.y) >= destination.y)) {
            location = destination;
            cout << display_code << " " << id_num << ": I'm there!" << endl;    //if there
            return true;
        }
        else {
            location = location + delta;
            cout << display_code << " " << id_num << ": step..." << endl;   //if not there
            return false;
        }
    }
    else if ((delta.x <= 0) && (delta.y <= 0)) {
        if (((location.x + delta.x) <= destination.x) && ((location.y + delta.y) <= destination.y)) {
            location = destination;
            cout << display_code << " " << id_num << ": I'm there!" << endl;    //if there
            return true;
        }
        else {
            location = location + delta;
            cout << display_code << " " << id_num << ": step..." << endl;   //if not there
            return false;
        }
    }
    else {
        cout << display_code << " " << id_num << ": I'm there!" << endl;
        return false;
    }
}

void Trainer::SetupDestination(Point2D dest) {
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

//Non-member
double GetRandomAmountOfPokeDollars() {
    return (double(rand()) / (double(RAND_MAX)) * 2); 
}