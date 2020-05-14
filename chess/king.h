#ifndef KING
#define KING

#include "piece.h"
#include <utility>

class King: public Piece{

    public:

    ~King() override;

    King() = delete;

    King(std::pair<int, int>, char);

    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) override;

};

#endif
