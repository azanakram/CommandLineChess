#include "player.h"
#include <utility>
#include "board.h"

using namespace std;

Player::Player() {}

Player::Player(char colour): colour{colour} {}

void Player::setColour(char newColour){
    this -> colour = newColour;
} 

char Player::getColour(){
    return this -> colour;
}

bool Player::isComputer() const{
    return false;
}

pair<pair<int, int>, pair<int, int>> Player::generateMove(Board &b) {
    
    return std::pair<std::pair<int, int>, std::pair<int, int>>(std::pair<int, int>(0,0), std::pair<int, int>(0,0));
}
