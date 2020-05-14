#ifndef PLAYER
#define PLAYER

#include <utility>
#include "board.h"

class Player{

    private:
    char colour;

    public:
    Player();
    
    Player(char type);

    void setColour(char); 

    char getColour();

    virtual bool isComputer() const;

    virtual std::pair<std::pair<int, int>, std::pair<int, int>> generateMove(Board &);
};

#endif
