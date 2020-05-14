#include "board.h"
#include "computer.h"
#include <stdlib.h>  
#include <time.h>  
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>

#include <ctime>
#include <cstdlib>

using namespace std;

// Computer::Computer() {}

Computer::Computer(char colour, int level){

    this -> setColour(colour);
    this -> level = level;
}

vector<pair<char, pair<int, int>>> Computer::getStartMoves(char colour, Board &b){

    vector<pair<char, pair<int, int>>> res;
    res.clear();

    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            
            shared_ptr<Piece> tmp = b.getPiece(pair<int, int>(i, j));

            if (tmp -> getColour() == colour && tmp -> getType() != 'e'){
                res.push_back(pair<char, pair<int, int>>(tmp -> getType(), pair<int, int>(i, j)));
            }
        }
    }

    return res;
}

int Computer::getLevel(){
    
    return this -> level;
}

pair<pair<int, int>, pair<int, int>> Computer::generateMove(Board &b){

    int computerLevel = this -> getLevel();

    // get list of starting moves from board, with the type of each starting piece.
    vector<pair<char, pair<int, int>>> startMoves = this -> getStartMoves(this -> getColour(), b);

    int startMovesSize = startMoves.size();

    // create a shuffled array of 1 ... startMoves.size()
    vector<int> indices;
    indices.clear();
    for (int i = 0; i < startMovesSize; i++)
        indices.push_back(i);
    
    std::random_shuffle(indices.begin(), indices.end(), [&](int x) { return std::rand() % x;});
    
    for (int i = 0; i < startMovesSize; i++){

        pair<int, int> currStartCoord = startMoves[indices[i]].second;
        char currPiece = startMoves[indices[i]].first;

        vector<pair<int, int>> endMoves;
        endMoves.clear();
        endMoves = b.findMoves(currStartCoord, this -> getColour(), currPiece);
        
        int endMovesSize = endMoves.size();
        
        if (endMovesSize < 1){
         
            if (i == startMovesSize - 1 && computerLevel == 2){
                computerLevel = 1;
                i = 0;
            }
            continue;
        }

        // level 1 computer. Return a random move.
        if (computerLevel == 1){

                int moveToGet = rand() % endMovesSize;
                return pair<pair<int, int>, pair<int, int>>(currStartCoord, endMoves[moveToGet]);
        }
        
        else if (computerLevel == 2){

            // level 2 computer. Return a random move, but give preference to moves that kill or check/checkmate.
            // randomly iterate over all possible moves. Then, check to see if the destination is occuppied.
            // If so, make the move. Otherwise, see if moving to destination causes a check. If so, make the move
            // Otherwise continue the loop. if the loop is exhausted, 
            // choose a random index from indices, and a random index from its endmoves

            // create a shuffled array of endMoves.size() indices
            vector<int> moveIndices;
            moveIndices.clear();
            for (int j = 0; j < endMovesSize; j++){
                moveIndices.push_back(j);
            }
            std::random_shuffle(moveIndices.begin(), moveIndices.end(), [&](int x) { return std::rand() % x;});

            // iterate over all end moves for the current pieece. If a suitable move is found
            // (ie.  if the destination is occupied, or if the move causes a check)
            for (int j = 0; j < endMovesSize; j++){

                pair<int, int> currEndMove = endMoves[moveIndices[j]];
                
                // if the destination has a killable target
                if (b.spaceOccupied(currEndMove) && b.getPiece(currEndMove) -> getColour() != this -> getColour()){
                    return pair<pair<int, int>, pair<int, int>>(currStartCoord, currEndMove);
                }

                // if the move results in a check
                // Make the move. see if it results in check.
                // Reverse the move.
                // If it did result in a check, return it. If not, do not.
                else{
                    
                    bool didCheck = false;
                    
                    shared_ptr<Piece> destPiece = b.getPiece(currEndMove);
                    char colourDest = destPiece -> getColour();
                    char typeDest = destPiece -> getType();

                    b.place(currStartCoord, currEndMove, this -> getColour(), currPiece);

                    char checkColour = this -> getColour();
                    
                    if (checkColour == 'w')
                        checkColour = 'b';
                    else
                        checkColour = 'w';

                    //see if the move you just made put the opposite side in check
                    if (b.isCheck(checkColour)) {
                        didCheck = true;
                    }
                    
                    b.place(currEndMove, currStartCoord, this -> getColour(), currPiece);
                    b.place(pair<int, int>(-1, -1), currEndMove, colourDest, typeDest);
                    b.setBoardPtr(currEndMove, destPiece);

                    if (didCheck){
                        return pair<pair<int, int>, pair<int, int>>(currStartCoord, currEndMove);
                    }
                }

            }
                
        }

        if (i == startMovesSize - 1){
            computerLevel = 1;
            i = 0;
        }
    }

    return pair<pair<int, int>, pair<int, int>>(pair<int, int>(0, 0), pair<int, int>(0, 0));
}

bool Computer::isComputer() const{
    
    return true;
}
