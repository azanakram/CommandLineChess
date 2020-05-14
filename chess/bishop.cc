#include <utility>
#include <stdlib.h>
#include <locale>

#include "bishop.h"

using namespace std;

// Bishop::Bishop(){}

Bishop::~Bishop(){}

Bishop::Bishop(pair<int, int> coords, char type){

    this -> coords = coords;
    this -> type = type;
    
    if (islower(type))
        this -> colour = 'b';
    else
        this -> colour = 'w';
}

bool Bishop::validMove(pair<int, int> start, pair<int, int> destination){

    if (this -> inBounds(start, destination) == false){
        return false;
    }
    
    int x1 = start.second;
    int y1 = start.first;

    int x2 = destination.second;
    int y2 = destination.first;

    // Diagonal move
    if (x2 - x1 == y2 - y1)
        return true;

    return false;
}
