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
#include "View.h"
using namespace std;

int main () {
    Model model;
    View view;
    char arg;
    view.Clear();
    while (true) {
        cout << "Enter command and parameters: ";
        cin >> arg;
        switch (arg) {
            case 'a':
                DoAdvanceCommand(model,view);
                break;
            case 'r':
                DoRunCommand(model,view);
                break;
            default:
            CommandGame(arg,model);
        }
    }
}