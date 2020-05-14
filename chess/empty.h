#ifndef EMPTY
#define EMPTY

#include "piece.h"
#include <utility>

class Empty: public Piece{

    public:

    ~Empty() override;
    
    Empty() = delete;

    Empty(std::pair<int, int>, char);

    bool validMove(std::pair<int, int>, std::pair<int, int>) override;
    
};

#endif
