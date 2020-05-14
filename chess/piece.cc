#include <utility>
#include <locale>
#include <iostream>

#include "piece.h"

using namespace std;

Piece::~Piece(){}

Piece::Piece(){}

Piece::Piece(pair<int, int> coords, char type): coords{coords}, type{type} {

    if (islower(type)){
        colour ='b';
    }
    else{
        colour = 'w';
    }
}

pair<int, int> Piece::getCoords(){
    return this -> coords;
}

char Piece::getColour() const{
    return this -> colour;
}

char Piece::getType() const {
    return this -> type;
}

bool Piece::getMoved() const{
    return this -> hasMoved;
}

void Piece::updateMoved(){
    this -> hasMoved = true;
}

void Piece::updateCoords(pair<int, int> newCoords){
    this -> coords = newCoords;
}

bool Piece::inBounds(pair<int, int> p1, pair<int, int> p2){

    int vals[4] = {p1.first, p1.second, p2.first, p2.second};

    for (int i = 0; i < 4; i++){

        if (vals[i] < 0 || vals[i] > 7) 
            return false;
    }

    return true;
}
