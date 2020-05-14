#ifndef QUEEN
#define QUEEN

#include "piece.h"
#include <utility>

class Queen: public Piece{

    public:
    
    Queen() = delete;

    Queen(std::pair<int, int>, char);

    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) override;

};

#endif
