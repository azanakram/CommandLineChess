#ifndef KNIGHT
#define KNIGHT

#include "piece.h"
#include <utility>

class Knight: public Piece{

    public:
    
    ~Knight() override;

    Knight() = delete;

    Knight(std::pair<int, int>, char);

    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) override;

};

#endif
