#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include <utility>
#include <memory>

#include "piece.h"
#include "empty.h"
#include "knight.h"
#include "pawn.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"

#include "boarddisplay.h"
#include "board.h"
using namespace std;


Board::Board() {
    bd = make_shared<BoardDisplay>();
    whiteKing = pair<int,int>(-1, -1);
    blackKing = pair<int,int>(-1, -1);
    theBoard.resize(boardRowNum);
    for (int row = 0; row < boardRowNum; row++) {
        theBoard[row].resize(boardColNum);
        for (int col = 0; col < boardColNum; col++) {
            place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'e', 'e'); // fills board with empty pieces
        }
    }
}


void Board::clear() {
    theBoard.clear();
    bd = make_shared<BoardDisplay>();
    whiteKing = pair<int,int>(-1, -1);
    blackKing = pair<int,int>(-1, -1);
    theBoard.resize(boardRowNum);
    for (int row = 0; row < boardRowNum; row++) {
        theBoard[row].resize(boardColNum);
        for (int col = 0; col < boardColNum; col++) {
            place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'e', 'e'); // fills board with empty pieces
        }
    }
}


void Board::init() {
    whiteKing = pair<int,int>(7, 4);
    blackKing = pair<int,int>(0, 4);
    for (int row = 0; row < boardRowNum; row++) {
        for (int col = 0; col < boardColNum; col++) {
            if (row >= 2 && row <= 5) {                         // places empty pieces
                place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'e', 'e');
                continue;
            }
            if (row == 1) {                                     // places black pawns
                place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'b', 'p');
                continue;
            }
            if (row == 6) {                                     // places white pawns
                place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'w', 'P');
                continue;
            }
            if (col == 0 || col == 7) { 
                if (row == 0) {                                 // places black rooks
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'b', 'r');
                } else if (row == 7) {                          // places white rooks
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'w', 'R');
                }
                continue;
            }
            if (col == 1 || col == 6) { 
                if (row == 0) {                                 // places black knights
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'b', 'n');
                } else if (row == 7) {                          // places white knights
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'w', 'N');
                }
                continue;
            }
            if (col == 2 || col == 5) { 
                if (row == 0) {                                 // places black bishops
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'b', 'b');
                } else if (row == 7) {                          // places white bishops
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'w', 'B');
                }
                continue;
            }
            if (row == 0) {
                if (col == 3) {                                 // places black queen
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'b', 'q');
                } else if (col == 4) {                          // places black king
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'b', 'k');
                }
                continue;
            }
            if (row == 7) {
                if (col == 3) {                                 // places black queen
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'w', 'Q');
                } else if (col == 4) {                          // places black king
                    place(pair<int,int>(-1,-1), pair<int,int>(row,col), 'w', 'K');
                }
                continue;
            }
        }
    }
}


bool Board::spaceOccupied(pair<int,int> coord) {
    return (theBoard[coord.first][coord.second]->getType() != 'e');
}


bool Board::validBoard() {
    int blackKingCount = 0;
    int whiteKingCount = 0;
    bool pawnOnEnd = false;
    for (int row = 0; row < boardRowNum; row++) {
        for (int col = 0; col < boardColNum; col++) {
            char type = theBoard[row][col]->getType();
            if (type == 'k') {
                blackKingCount++;
            } else if (type == 'K') {
                whiteKingCount++;
            } else if (type == 'p' || type == 'P') {
                if (row == 0 || row == 7) {
                    pawnOnEnd = true;
                }
            }
        }
    }
    return (!pawnOnEnd && blackKingCount==1 && whiteKingCount==1 && !isCheck('b') && !isCheck('w'));
}


string Board::coordToBoard(int row, int col) {
    string pos = "";
    switch (col) {
        case 0: pos += "a";
            break;
        case 1: pos += "b";
            break;
        case 2: pos += "c";
            break;
        case 3: pos += "d";
            break;
        case 4: pos += "e";
            break;
        case 5: pos += "f";
            break;
        case 6: pos += "g";
            break;
        case 7: pos += "h";
            break;
    }
    switch (row) {
        case 0: pos += "8";
            break;
        case 1: pos += "7";
            break;
        case 2: pos += "6";
            break;
        case 3: pos += "5";
            break;
        case 4: pos += "4";
            break;
        case 5: pos += "3";
            break;
        case 6: pos += "2";
            break;
        case 7: pos += "1";
            break;
    }
    return pos;
}


void Board::move(pair<int,int> startCoord, pair<int,int> endCoord) {
    shared_ptr<Piece> mv = theBoard[startCoord.first][startCoord.second];

    string start = coordToBoard(startCoord.first, startCoord.second);
    string end = coordToBoard(endCoord.first, endCoord.second);
    string invalidMoveException = "move " + start + " " + end;                  // Make string to alert the user that they played an illegal move

    char colour = mv->getColour();
    char type = mv->getType();
    
    vector<pair<int,int>> moveList = findMoves(startCoord, colour, type);       // find all possible moves for the piece we want to move
    int size = moveList.size();
    
    for (int i = 0; i < size; i++) {
        if (moveList[i].first == endCoord.first && moveList[i].second == endCoord.second) {     // if where we want to move is amongst the legal moves the piece can make
            place(startCoord, endCoord, colour, type);                          // place the piece
            theBoard[endCoord.first][endCoord.second]->updateMoved();           // update hasMoved
            return;
        }
    }

    throw invalidMoveException;                                                 // Throw the error to Main
}


void Board::remove(pair<int,int> coord) {
    if (coord.first == -1) {
        return;
    }
    theBoard[coord.first][coord.second] = make_shared<Empty> (coord, 'e');
    bd->update(pair<int,int>(-1,-1), coord, 'e', 'e');
}


void Board::place(pair<int,int> coordOld, pair<int,int> coordNew, char colour, char piece) {
    if (coordOld.first == -1) {                                                                 // If we are placing a brand new piece
        if (piece == 'K' || piece == 'k') {                                                     
            theBoard[coordNew.first][coordNew.second] = make_shared<King>(coordNew, piece);     // places king
            if (colour == 'w') {
                whiteKing = coordNew;                                                           // update king position
            } else {
                blackKing = coordNew;                                                           // update king position
            }
        } else if (piece == 'Q' || piece == 'q') {
            theBoard[coordNew.first][coordNew.second] = make_shared<Queen>(coordNew, piece);    // places queen
        } else if (piece == 'N' || piece == 'n') {
            theBoard[coordNew.first][coordNew.second] = make_shared<Knight>(coordNew, piece);   // places knight
        } else if (piece == 'B' || piece == 'b') {                
            theBoard[coordNew.first][coordNew.second] = make_shared<Bishop>(coordNew, piece);   // places bishop
        } else if (piece == 'R' || piece == 'r') {              
            theBoard[coordNew.first][coordNew.second] = make_shared<Rook>(coordNew, piece);     // places rook
        } else if (piece == 'P' || piece == 'p') {                 
            theBoard[coordNew.first][coordNew.second] = make_shared<Pawn>(coordNew, piece);     // places pawn
        } else if (piece == 'e') {
            theBoard[coordNew.first][coordNew.second] = make_shared<Queen>(coordNew, piece);    // places empty pieces
        }
    } else {                                                                                    // We are moving a piece
        theBoard[coordNew.first][coordNew.second] = theBoard[coordOld.first][coordOld.second];
        theBoard[coordOld.first][coordOld.second] = make_shared<Empty>(coordOld, 'e');
    }
    shared_ptr<Piece> pce = theBoard[coordNew.first][coordNew.second];
    pce->updateCoords(coordNew);
    if (piece == 'K') {
        whiteKing = coordNew;
    } else if (piece == 'k') {
        blackKing = coordNew;
    }
    bd->update(coordOld, coordNew, colour, piece);
}

bool Board::inBound(pair<int,int> coord) {
    if (coord.first >= 0 && coord.first < boardRowNum && coord.second >= 0 && coord.second < boardColNum) {
        return true;
    }
    return false;
}


bool Board::isCheck(char colour) {
    if (blackKing.first < 0 || blackKing.first >= boardRowNum || blackKing.second < 0 || blackKing.second >= boardColNum ||
        whiteKing.first < 0 || whiteKing.first >= boardRowNum || whiteKing.second < 0 || whiteKing.second >= boardColNum) {
            return true;
        }
    pair<int,int> coord = blackKing;
    pair<int,int> p1 = pair<int,int>(coord.first+1, coord.second-1);        // check if a pawn can kill king
    pair<int,int> p2 = pair<int,int>(coord.first+1, coord.second+1);        // check if a pawn can kill king
    if (colour == 'w') {
        coord = whiteKing;
        p1 = pair<int,int>(coord.first-1, coord.second-1);
        p2 = pair<int,int>(coord.first-1, coord.second+1);
        if (inBound(p1) && theBoard[p1.first][p1.second]->getType() == 'p') {
            return true;
        }
        if (inBound(p2) && theBoard[p2.first][p2.second]->getType() == 'p') {
            return true;
        }
    } else {
        if (inBound(p1) && theBoard[p1.first][p1.second]->getType() == 'P') {
            return true;
        }
        if (inBound(p2) && theBoard[p2.first][p2.second]->getType() == 'P') {
            return true;
        }
    }

    pair<int,int> up = pair<int,int>(coord.first-1, coord.second);
    if (inBound(up) && (theBoard[up.first][up.second]->getType()=='K' || theBoard[up.first][up.second]->getType()=='k')) {
        return true;
    }
    while (up.first >= 0) {                                                 // checks vertically up for enemies than can kill king
        if (theBoard[up.first][up.second]->getType() != 'e') {              // encounter piece that is not empty
            if (theBoard[up.first][up.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[up.first][up.second]->getType();
                if (type == 'R' || type == 'r' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }
        up.first--;
    }
    pair<int,int> down = pair<int,int>(coord.first+1, coord.second);
    if (inBound(down) && (theBoard[down.first][down.second]->getType()=='K' || theBoard[down.first][down.second]->getType()=='k')) {
        return true;
    }
    while (down.first < boardRowNum) {                                                // checks vertically down for enemies than can kill king
        if (theBoard[down.first][down.second]->getType() != 'e') {          // encounter piece that is not empty
            if (theBoard[down.first][down.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[down.first][down.second]->getType();
                if (type == 'R' || type == 'r' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }
        down.first++;
    }
    pair<int,int> left = pair<int,int>(coord.first, coord.second-1);
    if (inBound(left) && (theBoard[left.first][left.second]->getType()=='K' || theBoard[left.first][left.second]->getType()=='k')) {
        return true;
    }
    while (left.second >= 0) {                                              // checks horizontally left for enemies than can kill king
        if (theBoard[left.first][left.second]->getType() != 'e') {          // encounter piece that is not empty
            if (theBoard[left.first][left.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[left.first][left.second]->getType();
                if (type == 'R' || type == 'r' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }
        left.second--;
    }
    pair<int,int> right = pair<int,int>(coord.first, coord.second+1);
    if (inBound(right) && (theBoard[right.first][right.second]->getType()=='K' || theBoard[right.first][right.second]->getType()=='k')) {
        return true;
    }
    while (right.second < boardColNum) {                                              // checks horizontally left for enemies than can kill king
        if (theBoard[right.first][right.second]->getType() != 'e') {        // encounter piece that is not empty
            if (theBoard[right.first][right.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[right.first][right.second]->getType();
                if (type == 'R' || type == 'r' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }
        right.second++;
    }

    pair<int,int> NE = pair<int,int>(coord.first-1, coord.second+1);
    if (inBound(NE) && (theBoard[NE.first][NE.second]->getType()=='K' || theBoard[NE.first][NE.second]->getType()=='k')) {
        return true;
    }
    while (NE.first >= 0 && NE.second < boardColNum) {                                // checks diagonally NE for possible moves
        if (theBoard[NE.first][NE.second]->getType() != 'e') {              // encounter piece that is not empty
            if (theBoard[NE.first][NE.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[NE.first][NE.second]->getType();
                if (type == 'B' || type == 'b' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }                                                                   // encounters an empty piece
        NE.first--;
        NE.second++;
    }
    pair<int,int> SW = pair<int,int>(coord.first+1, coord.second-1);
    if (inBound(SW) && (theBoard[SW.first][SW.second]->getType()=='K' || theBoard[SW.first][SW.second]->getType()=='k')) {
        return true;
    }
    while (SW.first < boardRowNum && SW.second >= 0) {                                // checks diagonally SW for possible moves
        if (theBoard[SW.first][SW.second]->getType() != 'e') {              // encounter piece that is not empty
            if (theBoard[SW.first][SW.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[SW.first][SW.second]->getType();
                if (type == 'B' || type == 'b' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }                                                                   // encounters an empty piece
        SW.first++;
        SW.second--;
    }
    pair<int,int> NW = pair<int,int>(coord.first-1, coord.second-1);
    if (inBound(NW) && (theBoard[NW.first][NW.second]->getType()=='K' || theBoard[NW.first][NW.second]->getType()=='k')) {
        return true;
    }
    while (NW.first >= 0 && NW.second >= 0) {                               // checks diagonally NW for possible moves
        if (theBoard[NW.first][NW.second]->getType() != 'e') {              // encounter piece that is not empty
            if (theBoard[NW.first][NW.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[NW.first][NW.second]->getType();
                if (type == 'B' || type == 'b' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }                                                               // encounters an empty piece
        NW.first--;
        NW.second--;
    }
    pair<int,int> SE = pair<int,int>(coord.first+1, coord.second+1);
    if (inBound(SE) && (theBoard[SE.first][SE.second]->getType()=='K' || theBoard[SE.first][SE.second]->getType()=='k')) {
        return true;
    }
    while (SE.first < boardRowNum && SE.second < boardColNum) {                                 // checks diagonaly SE for possible moves
        if (SE.first == coord.first) {
            SE.first++;
            SE.second++;
            continue;
        }
        if (theBoard[SE.first][SE.second]->getType() != 'e') {              // encounter piece that is not empty
            if (theBoard[SE.first][SE.second]->getColour() == colour) {
                break;
            } else {
                char type = theBoard[SE.first][SE.second]->getType();
                if (type == 'B' || type == 'b' || type == 'Q' || type == 'q') {
                    return true;
                }
                break;
            }
        }                                                                   // encounters an empty piece
        SE.first++;
        SE.second++;
    }

    pair<int,int> N1 = pair<int,int>(coord.first-2, coord.second+1);        // check if there is a Knight at N1
    if (inBound(N1) && theBoard[N1.first][N1.second]->getColour() != colour && (theBoard[N1.first][N1.second]->getType() == 'N' || theBoard[N1.first][N1.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N2 = pair<int,int>(coord.first-1, coord.second+2);        // check if there is a Knight at N2
    if (inBound(N2) && theBoard[N2.first][N2.second]->getColour() != colour && (theBoard[N2.first][N2.second]->getType() == 'N' || theBoard[N2.first][N2.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N3 = pair<int,int>(coord.first+1, coord.second+2);        // check if there is a Knight at N3
    if (inBound(N3) && theBoard[N3.first][N3.second]->getColour() != colour && (theBoard[N3.first][N3.second]->getType() == 'N' || theBoard[N3.first][N3.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N4 = pair<int,int>(coord.first+2, coord.second+1);        // check if there is a Knight at N4
    if (inBound(N4) && theBoard[N4.first][N4.second]->getColour() != colour && (theBoard[N4.first][N4.second]->getType() == 'N' || theBoard[N4.first][N4.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N5 = pair<int,int>(coord.first+2, coord.second-1);        // check if there is a Knight at N5
    if (inBound(N5) && theBoard[N5.first][N5.second]->getColour() != colour && (theBoard[N5.first][N5.second]->getType() == 'N' || theBoard[N5.first][N5.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N6 = pair<int,int>(coord.first+1, coord.second-2);        // check if there is a Knight at N6
    if (inBound(N6) && theBoard[N6.first][N6.second]->getColour() != colour && (theBoard[N6.first][N6.second]->getType() == 'N' || theBoard[N6.first][N6.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N7 = pair<int,int>(coord.first-1, coord.second-2);        // check if there is a Knight at N7
    if (inBound(N7) && theBoard[N7.first][N7.second]->getColour() != colour && (theBoard[N7.first][N7.second]->getType() == 'N' || theBoard[N7.first][N7.second]->getType() == 'n')) {
        return true;
    }
    pair<int,int> N8 = pair<int,int>(coord.first-2, coord.second-1);        // check if there is a Knight at N8
    if (inBound(N8) && theBoard[N8.first][N8.second]->getColour() != colour && (theBoard[N8.first][N8.second]->getType() == 'N' || theBoard[N8.first][N8.second]->getType() == 'n')) {
        return true;
    }
    return false;
}


bool Board::isCheckmate(char colour) {

    if (!isCheck(colour)) {                                                        // if the king isn't currently in check, return false
        return false;
    }
    if (colour == 'b') {
        vector<pair<int,int>> moveList = findMoves(blackKing, colour, 'k');         // find all possible legal moves for the black king
        int size = moveList.size();
        if (size == 0) {                                                            // if there are no moves, then we are in checkmate, so return true
            return true;
        }
    } else {
        vector<pair<int,int>> moveList = findMoves(whiteKing, colour, 'K');         // find all possible legal moves for the white king
        int size = moveList.size();
        if (size == 0) {                                                            // if there are no moves, then we are in checkmate, so return true
            return true;
        }
    }
    return false;                                                                   // there exists at least 1 legal move for king, so return false
}


void Board::promotePawn(pair<int, int> coord, char piece) {
    if (islower(piece)) {
        place(pair<int,int>(-1,-1), coord, 'b', piece);
    } else {
        place(pair<int,int>(-1,-1), coord, 'w', piece);
    }
}


bool Board::isStalemate(char colour) {
    if (isCheck(colour)) {
        return false;
    }
    for (int row = 0; row < boardRowNum; row++) {
        for (int col = 0; col < boardColNum; col++) {
            if (theBoard[row][col]->getColour() == colour) {
                vector<pair<int,int>> moveList = findMoves(pair<int,int>(row,col), colour, theBoard[row][col]->getType());
                if (moveList.size() != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}


void Board::setBoardPtr(std::pair<int,int> coord, std::shared_ptr<Piece> pce) {
    theBoard[coord.first][coord.second] = pce;
}


bool Board::addMove(pair<int,int> oldCoord, pair<int,int> newCoord, char colour, char piece) {
    bool add = false;
    shared_ptr<Piece> dest = theBoard[newCoord.first][newCoord.second];
    char colourDest = dest->getColour();
    char typeDest = dest->getType();
    place(oldCoord, newCoord, colour, piece);
    if (!isCheck(colour)) {                                             // if the move doesn't put your king in check, we want to add it
        add = true;
    }
    place(newCoord, oldCoord, colour, piece);                           // put pieces back where they were
    place(pair<int,int>(-1,-1), newCoord, colourDest, typeDest);        // so that bd updates
    theBoard[newCoord.first][newCoord.second] = dest;
    return add;
}


vector<pair<int,int>> Board::findMoves(pair<int,int> coord, char colour, char piece) {
    shared_ptr<Piece> pce = theBoard[coord.first][coord.second];
    vector<pair<int,int>> moves;
    pair<int,int> tempKingPos;
    if (colour=='b') {
        tempKingPos = blackKing;
    } else if (colour=='w') {
        tempKingPos = whiteKing;
    }
    
    if (piece == 'K' || piece == 'k') {                                                     // List of Moves for King
        pair<int,int> topL = pair<int,int>(coord.first-1, coord.second-1);                  // check top left
        pair<int,int> topM = pair<int,int>(coord.first-1, coord.second);                    // check top middle
        pair<int,int> topR = pair<int,int>(coord.first, coord.second-1);                    // check middle left
        pair<int,int> botL = pair<int,int>(coord.first+1, coord.second-1);                  // check bottom left
        pair<int,int> botM = pair<int,int>(coord.first+1, coord.second);                    // check bottom middle
        pair<int,int> botR = pair<int,int>(coord.first+1, coord.second+1);                  // check bottom right
        pair<int,int> midL = pair<int,int>(coord.first, coord.second+1);                    // check middle right
        pair<int,int> midR = pair<int,int>(coord.first-1, coord.second+1);                  // check top right
        if (colour == 'b') {
            blackKing = topL;
            if (inBound(topL) && (theBoard[topL.first][topL.second]->getColour()=='w' || theBoard[topL.first][topL.second]->getType()=='e')) {
                if (addMove(coord, topL, colour, piece)) {
                    moves.emplace_back(topL);
                }
            }
            blackKing = topM;
            if (inBound(topM) && (theBoard[topM.first][topM.second]->getColour()=='w' || theBoard[topM.first][topM.second]->getType()=='e')) {
                if (addMove(coord, topM, colour, piece)) {
                    moves.emplace_back(topM);
                }
            }
            blackKing = topR;
            if (inBound(topR) && (theBoard[topR.first][topR.second]->getColour()=='w' || theBoard[topR.first][topR.second]->getType()=='e')) {
                if (addMove(coord, topR, colour, piece)) {
                    moves.emplace_back(topR);
                }
            }
            blackKing = midL;
            if (inBound(midL) && (theBoard[midL.first][midL.second]->getColour()=='w' || theBoard[midL.first][midL.second]->getType()=='e')) {
                if (addMove(coord, midL, colour, piece)) {
                    moves.emplace_back(midL);
                }
            }
            blackKing = midR;
            if (inBound(midR) && (theBoard[midR.first][midR.second]->getColour()=='w' || theBoard[midR.first][midR.second]->getType()=='e')) {
                if (addMove(coord, midR, colour, piece)) {
                    moves.emplace_back(midR);
                }
            }
            blackKing = botL;
            if (inBound(botL) && (theBoard[botL.first][botL.second]->getColour()=='w' || theBoard[botL.first][botL.second]->getType()=='e')) {
                if (addMove(coord, botL, colour, piece)) {
                    moves.emplace_back(botL);
                }
            }
            blackKing = botM;
            if (inBound(botM) && (theBoard[botM.first][botM.second]->getColour()=='w' || theBoard[botM.first][botM.second]->getType()=='e')) {
                if (addMove(coord, botM, colour, piece)) {
                    moves.emplace_back(botM);
                }
            }
            blackKing = botR;
            if (inBound(botR) && (theBoard[botR.first][botR.second]->getColour()=='w' || theBoard[botR.first][botR.second]->getType()=='e')) {
                if (addMove(coord, botR, colour, piece)) {
                    moves.emplace_back(botR);
                }
            }
            blackKing = tempKingPos;                                                        // reset blackKing to original position
        } else {
            whiteKing = topL;
            if (inBound(topL) && (theBoard[topL.first][topL.second]->getColour()=='b' || theBoard[topL.first][topL.second]->getType()=='e')) {
                if (addMove(coord, topL, colour, piece)) {
                    moves.emplace_back(topL);
                }
            }
            whiteKing = topM;
            if (inBound(topM) && (theBoard[topM.first][topM.second]->getColour()=='b' || theBoard[topM.first][topM.second]->getType()=='e')) {
                if (addMove(coord, topM, colour, piece)) {
                    moves.emplace_back(topM);
                }
            }
            whiteKing = topR;
            if (inBound(topR) && (theBoard[topR.first][topR.second]->getColour()=='b' || theBoard[topR.first][topR.second]->getType()=='e')) {
                if (addMove(coord, topR, colour, piece)) {
                    moves.emplace_back(topR);
                }
            }
            whiteKing = midL;
            if (inBound(midL) && (theBoard[midL.first][midL.second]->getColour()=='b' || theBoard[midL.first][midL.second]->getType()=='e')) {
                if (addMove(coord, midL, colour, piece)) {
                    moves.emplace_back(midL);
                }
            }
            whiteKing = midR;
            if (inBound(midR) && (theBoard[midR.first][midR.second]->getColour()=='b' || theBoard[midR.first][midR.second]->getType()=='e')) {
                if (addMove(coord, midR, colour, piece)) {
                    moves.emplace_back(midR);
                }
            }
            whiteKing = botL;
            if (inBound(botL) && (theBoard[botL.first][botL.second]->getColour()=='b' || theBoard[botL.first][botL.second]->getType()=='e')) {
               if (addMove(coord, botL, colour, piece)) {
                    moves.emplace_back(botL);
                }
            }
            whiteKing = botM;
            if (inBound(botM) && (theBoard[botM.first][botM.second]->getColour()=='b' || theBoard[botM.first][botM.second]->getType()=='e')) {
                if (addMove(coord, botM, colour, piece)) {
                    moves.emplace_back(botM);
                }
            }
            whiteKing = botR;
            if (inBound(botR) && (theBoard[botR.first][botR.second]->getColour()=='b' || theBoard[botR.first][botR.second]->getType()=='e')) {
                if (addMove(coord, botR, colour, piece)) {
                    moves.emplace_back(botR);
                }
            }
            whiteKing = tempKingPos;                                                        // reset whiteKing to original position
        }
    } else if (piece == 'Q' || piece == 'q') {                                              // List of Moves for Queen
        moveStraight(coord, colour, piece, moves);
        moveDiag(coord, colour, piece, moves);
    } else if (piece == 'N' || piece == 'n') {                                              // List of Moves for Knight
        pair<int,int> p1 = pair<int,int>(coord.first - 2, coord.second - 1);
        pair<int,int> p2 = pair<int,int>(coord.first - 2, coord.second + 1);
        pair<int,int> p3 = pair<int,int>(coord.first - 1, coord.second - 2);
        pair<int,int> p4 = pair<int,int>(coord.first - 1, coord.second + 2);
        pair<int,int> p5 = pair<int,int>(coord.first + 2, coord.second - 1);
        pair<int,int> p6 = pair<int,int>(coord.first + 2, coord.second + 1);
        pair<int,int> p7 = pair<int,int>(coord.first + 1, coord.second - 2);
        pair<int,int> p8 = pair<int,int>(coord.first + 1, coord.second + 2);
        char opponent = 'b';
        if (opponent == colour) {
            opponent = 'w';
        }
        if (inBound(p1) && ((theBoard[p1.first][p1.second]->getColour()==opponent) || (theBoard[p1.first][p1.second]->getType()=='e'))) {
            if (addMove(coord, p1, colour, piece)) {
                moves.emplace_back(p1);
            }
        }
        if (inBound(p2) && ((theBoard[p2.first][p2.second]->getColour()==opponent) || (theBoard[p2.first][p2.second]->getType()=='e'))) {
            if (addMove(coord, p2, colour, piece)) {
                moves.emplace_back(p2);
            }
        }
        if (inBound(p3) && ((theBoard[p3.first][p3.second]->getColour()==opponent) || (theBoard[p3.first][p3.second]->getType()=='e'))) {
            if (addMove(coord, p3, colour, piece)) {
                moves.emplace_back(p3);
            }
        }
        if (inBound(p4) && ((theBoard[p4.first][p4.second]->getColour()==opponent) || (theBoard[p4.first][p4.second]->getType()=='e'))) {
            if (addMove(coord, p4, colour, piece)) {
                moves.emplace_back(p4);
            }
        }
        if (inBound(p5) && ((theBoard[p5.first][p5.second]->getColour()!=opponent) || (theBoard[p5.first][p5.second]->getType()=='e'))) {
            if (addMove(coord, p5, colour, piece)) {
                moves.emplace_back(p5);
            }
        }
        if (inBound(p6) && ((theBoard[p6.first][p6.second]->getColour()==opponent) || (theBoard[p6.first][p6.second]->getType()=='e'))) {
            if (addMove(coord, p6, colour, piece)) {
                moves.emplace_back(p6);
            }
        }
        if (inBound(p7) && ((theBoard[p7.first][p7.second]->getColour()==opponent) || (theBoard[p7.first][p7.second]->getType()=='e'))) {
            if (addMove(coord, p7, colour, piece)) {
                moves.emplace_back(p7);
            }
        }
        if (inBound(p8) && ((theBoard[p8.first][p8.second]->getColour()==opponent) || (theBoard[p8.first][p8.second]->getType()=='e'))) {
            if (addMove(coord, p8, colour, piece)) {
                moves.emplace_back(p8);
            }
        }
    } else if (piece == 'B' || piece == 'b') {                                              // List of Moves for Bishop
        moveDiag(coord, colour, piece, moves);
    } else if (piece == 'R' || piece == 'r') {                                              // List of Moves for Rook
        moveStraight(coord, colour, piece, moves);
    } else if (piece == 'P' || piece == 'p') {                                              // List of Moves for Pawn
        int step = 1;
        if (colour=='w') {
            step *= -1;
        }
        
            
        pair<int,int> diagLeft = pair<int,int>(coord.first + step, coord.second-1);
        if (inBound(diagLeft) && theBoard[diagLeft.first][diagLeft.second]->getColour()!=colour && theBoard[diagLeft.first][diagLeft.second]->getType()!='e') {      // Moves left diagonally to kill
            shared_ptr<Piece> dest = theBoard[diagLeft.first][diagLeft.second];
            char colourPce = pce->getColour();
            char typePce = pce->getType();
            char colourDest = dest->getColour();
            char typeDest = dest->getType();

            place(coord, diagLeft, colourPce, typePce);
            if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                moves.emplace_back(diagLeft);
            }
            place(diagLeft, coord, colourPce, typePce);                                       // put pieces back where they were
            place(pair<int,int>(-1,-1), diagLeft, colourDest, typeDest);                      // so that bd updates
            theBoard[diagLeft.first][diagLeft.second] = dest;
        }
            
        pair<int,int> diagRight = pair<int,int>(coord.first + step, coord.second+1);
        if (inBound(diagRight) && theBoard[diagRight.first][diagRight.second]->getColour()!=colour && theBoard[diagRight.first][diagRight.second]->getType()!='e') {   // Moves right diagonally to kill
            shared_ptr<Piece> dest = theBoard[diagRight.first][diagRight.second];
            char colourPce = pce->getColour();
            char typePce = pce->getType();
            char colourDest = dest->getColour();
            char typeDest = dest->getType();

            place(coord, diagRight, colourPce, typePce);
            if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                moves.emplace_back(diagRight);
            }
            place(diagRight, coord, colourPce, typePce);                                       // put pieces back where they were
            place(pair<int,int>(-1,-1), diagRight, colourDest, typeDest);                      // so that bd updates
            theBoard[diagRight.first][diagRight.second] = dest;
        }
            
        pair<int,int> snglStep = pair<int,int>(coord.first + step, coord.second);
        if (inBound(snglStep) && theBoard[snglStep.first][snglStep.second]->getType()=='e') {             // Check if pawn can move 1 step forward, and that snglStep is currently an Empty Piece
            char colourPce = pce->getColour();
            char typePce = pce->getType();
            place(coord, snglStep, colourPce, typePce);
            if(!isCheck(colour)) { 
                moves.emplace_back(snglStep);
            }                                                                                                           // if the move doesn't your king in check, add it to the list
            place(snglStep, coord, colourPce, typePce);
        }

        if ((pce->getColour()=='w' && coord.first==6 && !spaceOccupied(snglStep)) || (pce->getColour()=='b' && coord.first==1 && !spaceOccupied(snglStep))) {                                                                                         // Pawn can move 2 steps forward on first move
            pair<int,int> dbleStep = pair<int,int>(coord.first + step + step, coord.second);
            if (inBound(dbleStep) && theBoard[dbleStep.first][dbleStep.second]->getType()=='e') {         // Check if pawn can move 2 steps forward, and that dbleStep is currently an Empty Piece
                char colourPce = pce->getColour();
                char typePce = pce->getType();
                place(coord, dbleStep, colourPce, typePce);
                if(!isCheck(colour)) {
                    moves.emplace_back(dbleStep);
                }                                                                                                       // if the move doesn't your king in check, add it to the list
                place(dbleStep, coord, colourPce, typePce);                                                             // revert the board to its original state
            }
        }
    }
    return moves;
}


void Board::moveStraight(pair<int,int> coord, char colour, char piece, vector<pair<int,int>> &moves) {
    pair<int,int> up = coord;
    pair<int,int> down = coord;
    pair<int,int> left = coord;
    pair<int,int> right = coord;

    while (up.first >= 0) {                                     // checks vertically up for possible moves
        if (up.first == coord.first) {
            up.first--;
            continue;
        }
        if (theBoard[up.first][up.second]->getType() != 'e') {  // encounter piece that is not empty
            if (theBoard[up.first][up.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[up.first][up.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, up, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(up);
                }
                place(up, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), up, colourDest, typeDest);                      // so that bd updates
                theBoard[up.first][up.second] = dest;
                break;
            }
        } else {                                                // encounters an empty piece
            place(coord, up, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(up);
            }
            place(up, coord, colour, piece);
        }
        up.first--;
    }

    while (down.first < boardRowNum) {                                    // checks vertically down for possible moves
        if (down.first == coord.first) {
            down.first++;
            continue;
        }
        if (theBoard[down.first][down.second]->getType() != 'e') {  // encounter piece that is not empty
            if (theBoard[down.first][down.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[down.first][down.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, down, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(down);
                }
                place(down, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), down, colourDest, typeDest);                      // so that bd updates
                theBoard[down.first][down.second] = dest;
                break;
            }
        } else {                                                // encounters an empty piece
            place(coord, down, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(down);
            }
            place(down, coord, colour, piece);
        }
        down.first++;
    }

    while (left.second >= 0) {                                  // checks horizontally left for possible moves
        if (left.second == coord.second) {
            left.second--;
            continue;
        }
        if (theBoard[left.first][left.second]->getType() != 'e') {  // encounter piece that is not empty
            if (theBoard[left.first][left.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[left.first][left.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, left, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(left);
                }
                place(left, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), left, colourDest, typeDest);                      // so that bd updates
                theBoard[left.first][left.second] = dest;
                break;
            }
        } else {                                                // encounters an empty piece
            place(coord, left, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(left);
            }
            place(left, coord, colour, piece);
        }
        left.second--;
    }

    while (right.second < boardColNum) {                                  // checks horizontally right for possible moves
        if (right.second == coord.second) {
            right.second++;
            continue;
        }
        if (theBoard[right.first][right.second]->getType() != 'e') {  // encounter piece that is not empty
            if (theBoard[right.first][right.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[right.first][right.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, right, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(right);
                }
                place(right, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), right, colourDest, typeDest);                      // so that bd updates
                theBoard[right.first][right.second] = dest;
                break;
            }
        } else {                                                // encounters an empty piece
            place(coord, right, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(right);
            }
            place(right, coord, colour, piece);
        }
        right.second++;
    }
}


void Board::moveDiag(pair<int,int> coord, char colour, char piece, vector<pair<int,int>> &moves) {
    pair<int,int> NE = coord;
    pair<int,int> SW = coord;
    pair<int,int> NW = coord;
    pair<int,int> SE = coord;

    while (NE.first >= 0 && NE.second < boardColNum) {                                    // checks diagonally NE for possible moves
        if (NE.first == coord.first) {
            NE.first--;
            NE.second++;
            continue;
        }
        if (theBoard[NE.first][NE.second]->getType() != 'e') {                  // encounter piece that is not empty
            if (theBoard[NE.first][NE.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[NE.first][NE.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, NE, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(NE);
                }
                place(NE, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), NE, colourDest, typeDest);                      // so that bd updates
                theBoard[NE.first][NE.second] = dest;
                break;
            }
        } else {                                                                // encounters an empty piece
            place(coord, NE, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(NE);
            }
            place(NE, coord, colour, piece);
        }
        NE.first--;
        NE.second++;
    }

    while (SW.first < boardRowNum && SW.second >= 0) {                                    // checks diagonally SW for possible moves
        if (SW.first == coord.first) {
            SW.first++;
            SW.second--;
            continue;
        }
        if (theBoard[SW.first][SW.second]->getType() != 'e') {                  // encounter piece that is not empty
            if (theBoard[SW.first][SW.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[SW.first][SW.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, SW, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(SW);
                }
                place(SW, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), SW, colourDest, typeDest);                      // so that bd updates
                theBoard[SW.first][SW.second] = dest;
                break;
            }
        } else {                                                                // encounters an empty piece
            place(coord, SW, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(SW);
            }
            place(SW, coord, colour, piece);
        }
        SW.first++;
        SW.second--;
    }

    while (NW.first >= 0 && NW.second >= 0) {                                   // checks diagonally NW for possible moves
        if (NW.first == coord.first) {
            NW.first--;
            NW.second--;
            continue;
        }
        if (theBoard[NW.first][NW.second]->getType() != 'e') {                  // encounter piece that is not empty
            if (theBoard[NW.first][NW.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[NW.first][NW.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, NW, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(NW);
                }
                place(NW, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), NW, colourDest, typeDest);                      // so that bd updates
                theBoard[NW.first][NW.second] = dest;
                break;
            }
        } else {                                                                // encounters an empty piece
            place(coord, NW, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(NW);
            }
            place(NW, coord, colour, piece);
        }
        NW.first--;
        NW.second--;
    }

    while (SE.first < boardRowNum && SE.second < boardColNum) {                                     // checks diagonaly SE for possible moves
        if (SE.first == coord.first) {
            SE.first++;
            SE.second++;
            continue;
        }
        if (theBoard[SE.first][SE.second]->getType() != 'e') {                  // encounter piece that is not empty
            if (theBoard[SE.first][SE.second]->getColour() == colour) {
                break;
            } else {
                shared_ptr<Piece> dest = theBoard[SE.first][SE.second];
                char colourPce = colour;
                char typePce = piece;
                char colourDest = dest->getColour();
                char typeDest = dest->getType();

                place(coord, SE, colourPce, typePce);
                if(!isCheck(colour)) {                                                      // if the move doesn't your king in check, add it to the list
                    moves.emplace_back(SE);
                }
                place(SE, coord, colourPce, typePce);                                       // put pieces back where they were
                place(pair<int,int>(-1,-1), SE, colourDest, typeDest);                      // so that bd updates
                theBoard[SE.first][SE.second] = dest;
                break;
            }
        } else {                                                                // encounters an empty piece
            place(coord, SE, colour, piece);
            if (!isCheck(colour)) {
                moves.emplace_back(SE);
            }
            place(SE, coord, colour, piece);
        }
        SE.first++;
        SE.second++;
    }

}


shared_ptr<Piece> Board::getPiece(pair<int,int> coord) {

    int vals[4] = {coord.first, coord.second};

    for (int i = 0; i < 2; i++){

        if (vals[i] < 0 || vals[i] > 7) 
            throw "Out of bounds move.";
    }

    return theBoard[coord.first][coord.second];
}


void Board::toggleHints() {
    hints = !hints;
}


bool Board::isHintsOn() {
    return hints;
}


void Board::getHint(pair<int,int> coord) {
    shared_ptr<Piece> pce = theBoard[coord.first][coord.second];
    char colour = pce->getColour();
    char piece = pce->getType();
    vector<pair<int,int>> moveList = findMoves(coord, colour, piece);
    if (moveList.size() > 0) {
        cout << "Possible destinations for " << piece << " at " << coordToBoard(coord.first, coord.second) << ":  ";
        for (auto move : moveList) {
            cout << coordToBoard(move.first, move.second) << " ";
        }
    } else {
        cout << "No possible moves for " << piece << " at " << coordToBoard(coord.first, coord.second);
    }
    cout << endl;
    cout << endl;
}


bool Board::tryCastling(char colour, string direction) {
    bool success = false;
    string moveErr = "You cannot perform castling to the " + direction + " as your pieces have moved or are not present";
    string checkErr = "Your king will be checked if you do castling to the " + direction;
    string checkStart = "Unable to perform castling. Your King is currently in check!";
    string pieceErr = "Unable to perform castling as there are still pieces to the " + direction;

    if (isCheck(colour)) { // Check if the king is currently in check
        throw checkStart;
    }
    if (colour == 'w') {
        if (whiteKing.first != 7 || whiteKing.second != 4) { // Check if king has been moved
            throw moveErr;
        }
    } else {
        if (blackKing.first != 0 || blackKing.second != 4) { // Check if king has been moved
            throw moveErr;
        }
    }

    if (direction == "left") {
        if (colour == 'w') {
            if (theBoard[7][0]->getType() != 'R' || theBoard[7][0]->getMoved() == true) {   // check if Rooks have moved
                throw moveErr;
            }
            if (theBoard[7][1]->getType() != 'e' || theBoard[7][2]->getType() != 'e' || theBoard[7][3]->getType() != 'e') { // check if there are pieces inbetween
                throw pieceErr;
            }
            if (!addMove(pair<int,int>(7,4), pair<int,int>(7,3), colour, 'K') || !addMove(pair<int,int>(7,4), pair<int,int>(7,2), colour, 'K')) { // check if the king will be in check at final position and position inbetween
                throw checkErr;
            }
            place(pair<int,int>(7,4), pair<int,int>(7,2), colour, 'K');  // perform the castling
            place(pair<int,int>(7,0), pair<int,int>(7,3), colour, 'R');  // perform the castling
            success = true;

        } else {
            if (theBoard[0][0]->getType() != 'r' || theBoard[0][0]->getMoved() == true) {   // check if Rooks have moved
                throw moveErr;
            }
            if (theBoard[0][1]->getType() != 'e' || theBoard[0][2]->getType() != 'e' || theBoard[0][3]->getType() != 'e') { // check if there are pieces inbetween
                throw pieceErr;
            }
            if (!addMove(pair<int,int>(0,4), pair<int,int>(0,3), colour, 'k') || !addMove(pair<int,int>(0,4), pair<int,int>(0,2), colour, 'k')) { // check if the king will be in check at final position and position inbetween
                throw checkErr;
            }
            place(pair<int,int>(0,4), pair<int,int>(0,2), colour, 'k');  // perform the castling
            place(pair<int,int>(0,0), pair<int,int>(0,3), colour, 'r');  // perform the castling
            success = true;

        }
    } else if (direction == "right") {
        if (colour == 'w') {
            if (theBoard[7][7]->getType() != 'R' || theBoard[7][7]->getMoved() == true) {   // check if Rooks have moved
                throw moveErr;
            }
            if (theBoard[7][5]->getType() != 'e' || theBoard[7][6]->getType() != 'e') { // check if there are pieces inbetween
                throw pieceErr;
            }
            if (!addMove(pair<int,int>(7,4), pair<int,int>(7,5), colour, 'K') || !addMove(pair<int,int>(7,4), pair<int,int>(7,6), colour, 'K')) { // check if the king will be in check at final position and position inbetween
                throw checkErr;
            }
            place(pair<int,int>(7,4), pair<int,int>(7,6), colour, 'K');  // perform the castling
            place(pair<int,int>(7,7), pair<int,int>(7,5), colour, 'R');  // perform the castling
            success = true;

        } else {
            if (theBoard[0][7]->getType() != 'r' || theBoard[0][7]->getMoved() == true) {   // check if Rooks have moved
                throw moveErr;
            }
            if (theBoard[0][5]->getType() != 'e' || theBoard[0][6]->getType() != 'e') { // check if there are pieces inbetween
                throw pieceErr;
            }
            if (!addMove(pair<int,int>(0,4), pair<int,int>(0,5), colour, 'k') || !addMove(pair<int,int>(0,4), pair<int,int>(0,6), colour, 'k')) { // check if the king will be in check at final position and position inbetween
                throw checkErr;
            }
            place(pair<int,int>(0,4), pair<int,int>(0,6), colour, 'k');  // perform the castling
            place(pair<int,int>(0,7), pair<int,int>(0,5), colour, 'r');  // perform the castling
            success = true;

        }
    }
    return success;
}


ostream &operator<<(ostream &out, const Board &board) {
    out << *(board.bd);
    return out;
}
