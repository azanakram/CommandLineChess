#ifndef PAWN
#define PAWN

#include "piece.h"
#include <utility>

class Pawn: public Piece{

    public:
    
    ~Pawn() override;

    Pawn() = delete;

    Pawn(std::pair<int, int>, char);

    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) override;

};

#endif
