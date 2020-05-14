#ifndef COMPUTER
#define COMPUTER

#include "board.h"
#include "player.h"
#include <utility>

class Computer: public Player{

    int level;
    
    public:
    Computer() = delete;

    Computer(char type, int level);
    
    std::pair<std::pair<int, int>, std::pair<int, int>> generateMove(Board&) override;

    std::vector<std::pair<char, std::pair<int, int>>> getStartMoves(char, Board &);

    bool isComputer() const override;

    int getLevel();
};

#endif
