#include <utility>
#include <stdlib.h>
#include <ctype.h>

#include "king.h"

using namespace std;

// King::King(){}

King::~King(){}

King::King(pair<int, int> coords, char type){

    this -> coords = coords;
    this -> type = type;
    
    if (islower(type))
        this -> colour = 'b';
    else
        this -> colour = 'w';
}

bool King::validMove(pair<int, int> start, pair<int, int> destination){

    if (this -> inBounds(start, destination) == false){
        return false;
    }
    
    int x1 = start.second;
    int y1 = start.first;

    int x2 = destination.second;
    int y2 = destination.first;

    return (abs(x1 - x2) <= 1 && abs(y2 - y1) <= 1);
}
