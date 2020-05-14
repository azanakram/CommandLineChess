#ifndef ROOK
#define ROOK

#include "piece.h"
#include <utility>

class Rook: public Piece{
    
    public:

    ~Rook() override;

    Rook() = delete;

    Rook(std::pair<int, int>, char);

    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) override;
};

#endif
