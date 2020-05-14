#include <utility>
#include <stdlib.h>
#include <locale>
#include <iostream>

#include "pawn.h"

using namespace std;

// Pawn::Pawn(){}

Pawn::~Pawn(){}

Pawn::Pawn(pair<int, int> coords, char type){

    this -> coords = coords;
    this -> type = type;
    
    if (islower(type))
        this -> colour = 'b';
    else
        this -> colour = 'w';
}

bool Pawn::validMove(pair<int, int> start, pair<int, int> destination){

    if (this -> inBounds(start, destination) == false){
        return false;
    }
    
    // int x1 = start.second;
    int y1 = start.first;

    // int x2 = destination.second;
    int y2 = destination.first;

    if (this -> hasMoved == false){

        if (abs(y2 - y1) > 2)
            return false;
        else
            return true;
    }
    else if (abs(y2 - y1) == 1)
        return true;
    else
        return false;
}
