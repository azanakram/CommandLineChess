#ifndef PIECE
#define PIECE

#include <utility>

class Piece{

    protected:

    std::pair<int, int> coords = std::pair<int, int>(0, 0);
    char colour = 'b';
    char type = 'k';
    bool hasMoved = false;

    public:

    virtual ~Piece();
    
    Piece();

    Piece(std::pair<int, int>, char);
    
    virtual bool validMove(std::pair<int, int>, std::pair<int, int>) = 0;

    std::pair<int, int> getCoords();

    char getType() const;

    char getColour() const;

    bool getMoved() const;

    void updateMoved();

    void updateCoords(std::pair<int, int>);
    
    bool inBounds(std::pair<int, int>, std::pair<int, int>);
};

#endif
