#include <iostream>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Point2D.h"
#include "Vector2D.h"
#ifndef VIEW_H
#define VIEW_H
using namespace std;

const int view_maxsize = 20;

class View {
    private:
        int size;
        double scale;
        Point2D origin;
        char grid[view_maxsize][view_maxsize][2];
        bool GetSubscripts(int &, int &, Point2D);
    public:
        View();
        void Clear();
        void Plot(GameObject *);
        void Draw();
};

#endif