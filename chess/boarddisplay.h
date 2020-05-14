#ifndef BOARDDISPLAY_H
#define BOARDDISPLAY_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <utility>

class Piece;

class BoardDisplay {
  std::vector<std::vector<char>> theDisplay;
  std::vector<std::vector<char>> emptyDisplay;
 public:
  BoardDisplay();
  void update(std::pair<int,int> coordOld, std::pair<int,int> coordNew, char colour, char piece);

  friend std::ostream &operator<<(std::ostream &out, const BoardDisplay &bd);
};

#endif
