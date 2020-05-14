#include "empty.h"
#include <utility>

using namespace std;

// Empty::Empty(){}

Empty::~Empty(){}

Empty::Empty(pair<int, int> coords, char type){

    this -> coords = coords;
    this -> type = type;

    this -> colour = 'e';
}

bool Empty::validMove(pair<int, int> stat, pair<int, int> dest){

    return false;
}
