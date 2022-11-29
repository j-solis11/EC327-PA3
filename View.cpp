#include <iostream>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "View.h"
using namespace std;

bool View::GetSubscripts(int & out_x, int & out_y, Point2D location) {
    out_x = (location.x - origin.x) / scale;
    out_y = (location.y - origin.y) / scale;
    if ((out_x <= view_maxsize) && (out_y <= view_maxsize)) {
        return true;
    }
    else {
        cout << "An object is outside the display" << endl;
        return false;
    }
}

View::View() {
    size = 11;
    scale = 2;
    origin.x = 0;
    origin.y = 0;
}

void View::Clear() {
    for (int i = 0; i < view_maxsize; i++) {
        for (int j = 0; j < view_maxsize; j++) {
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject * ptr) {
    int x, y;
    bool z = GetSubscripts(x,y,ptr->GetLocation());
    if (z == true) {
        if ((grid[y][x][0] == '.') && ((*ptr).ShouldBeVisible() == true)) {
            ptr->DrawSelf(&grid[x][y][0]);
        }
        else {
            grid[x][y][0] = '*';
            grid[x][y][1] = ' ';
        }
    }
}
void View::Draw() {
    for (int j = size-1; j >= -1; j--) {
        for (int i = -1; i <= size-1; i++) {
            //grid axis
            if (i == -1 && j%2 == 0) {
                cout << j*2;
                if (j/5 == 0) {
                    cout << " ";
                }
                }
            else if (i == -1 && j%2 != 0) {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0) {
                cout << i*2;
                if (i/5 == 0) {
                    cout << " ";
                }
                cout << "  ";
            }
//draw objects
            if (i >= 0 && j >=0) {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}
