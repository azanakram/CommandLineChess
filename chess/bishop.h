#ifndef BISHOP
#define BISHOP

#include "piece.h"
#include <utility>

class Bishop: public Piece{

    public:
    
    ~Bishop() override;
    
    Bishop() = delete;

    Bishop(std::pair<int, int>, char);

    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) override;

};

#endif
