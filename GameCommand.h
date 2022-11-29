#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Point2D.h"
#include "Model.h"
#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
using namespace std;

void DoMoveCommand(Model&, int, Point2D);
void DoMoveToCenterCommand(Model&, int, int);
void DoMoveToGymCommand(Model&, int, int);
void DoStopCommand(Model&, int);
void DoBattleCommand(Model&, int, unsigned int);
void DoRecoverInCenterCommand(Model &, int, unsigned int);
void DoAdvanceCommand(Model&, View&);
void DoRunCommand(Model&, View&);
void CommandGame(char, Model&);     //a, r, q



#endif