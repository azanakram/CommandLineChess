#include <utility>
#include <stdlib.h>
#include <locale>
#include <iostream>
#include "knight.h"

using namespace std;

// Knight::Knight(){}

Knight::~Knight(){}

Knight::Knight(pair<int, int> coords, char type){

    this -> coords = coords;
    this -> type = type;
    
    if (islower(type))
        this -> colour = 'b';
    else
        this -> colour = 'w';
}

bool Knight::validMove(pair<int, int> start, pair<int, int> destination){

    if (this -> inBounds(start, destination) == false){
        return false;
    }
    
    int x1 = start.second;
    int y1 = start.first;

    int x2 = destination.second;
    int y2 = destination.first;

    // First column to the right
    if (x1 == x2 - 1){

        if (y1 == y2 - 2 || y1 == y2 + 2)
            return true;
    }

    // Second column to the right
    if (x1 == x2 - 2){

        if (y1 == y2 -1 || y1 == y2 + 1)
            return true;
    }

    // First column to the left
    if (x1 == x2 + 1){

        if (y1 == y2 - 2 || y1 == y2 + 2)
            return true;
    }

    // Second column to the left
    if (x1 == x2 + 2){

        if (y1 == y2 -1 || y1 == y2 + 1)
            return true;
    }

    return false;
}
