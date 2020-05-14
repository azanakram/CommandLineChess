#include <utility>
#include <locale>
#include <stdlib.h>

#include "queen.h"

using namespace std;

// Queen::Queen(){}

Queen::Queen(pair<int, int> coords, char type){

    this -> coords = coords;
    this -> type = type;
    
    if (islower(type))
        this -> colour = 'b';
    else
        this -> colour = 'w';
}

bool Queen::validMove(pair<int, int> start, pair<int, int> destination){

    if (this -> inBounds(start, destination) == false){
        return false;
    }
    
    int x1 = start.second;
    int y1 = start.first;

    int x2 = destination.second;
    int y2 = destination.first;

    // Horizontal move
    if (x1 == x2)
        return true;

    // Vertical move
    if (y1 == y2)
        return true;
    
    // Diagonal move
    if (x2 - x1 == y2 - y1)
        return true;

    return false;
}
