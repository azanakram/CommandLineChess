#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include <utility>

#include "boarddisplay.h"

using namespace std;

BoardDisplay::BoardDisplay() {
    theDisplay.clear();
    bool white = true;
    for (int row = 0; row < 8; row++) {
        vector<char> newRow;
        for (int col = 0; col < 8; col++) {
            if (white) {
                newRow.emplace_back(' ');
                white = false;
            } else {
                newRow.emplace_back('-');
                white = true;
            }
        }
        white = !white;
        theDisplay.emplace_back(newRow);
        emptyDisplay.emplace_back(newRow);
    }
}

void BoardDisplay::update(pair<int,int> coordOld, pair<int,int> coordNew, char colour, char piece) {
    if (coordOld.first != -1) {
        theDisplay[coordOld.first][coordOld.second] = emptyDisplay[coordOld.first][coordOld.second];
    }
    switch (colour) {
        case 'w':
            switch (piece) {
                case 'K':
                    theDisplay[coordNew.first][coordNew.second] = 'K';
                    break;
                case 'Q':
                    theDisplay[coordNew.first][coordNew.second] = 'Q';
                    break;
                case 'B':
                    theDisplay[coordNew.first][coordNew.second] = 'B';
                    break;
                case 'R':
                    theDisplay[coordNew.first][coordNew.second] = 'R';
                    break;
                case 'N':
                    theDisplay[coordNew.first][coordNew.second] = 'N';
                    break;
                case 'P':
                    theDisplay[coordNew.first][coordNew.second] = 'P';
                    break;
            }
            break;
        case 'b':
            switch (piece) {
                case 'k':
                    theDisplay[coordNew.first][coordNew.second] = 'k';
                    break;
                case 'q':
                    theDisplay[coordNew.first][coordNew.second] = 'q';
                    break;
                case 'b':
                    theDisplay[coordNew.first][coordNew.second] = 'b';
                    break;
                case 'r':
                    theDisplay[coordNew.first][coordNew.second] = 'r';
                    break;
                case 'n':
                    theDisplay[coordNew.first][coordNew.second] = 'n';
                    break;
                case 'p':
                    theDisplay[coordNew.first][coordNew.second] = 'p';
                    break;
            }
            break;
        case 'e':
            theDisplay[coordNew.first][coordNew.second] = emptyDisplay[coordNew.first][coordNew.second];
            break;
    }
}

ostream &operator<<(std::ostream &out, const BoardDisplay &bd) {
    for (int row = 0; row < 8; row++) {
        out << 8 - row << ' ';
        for (int col = 0; col < 8; col++) {
            out << bd.theDisplay[row][col];
        }
        out << endl;
    }
    out << '\n' << "  abcdefgh" << endl;
    return out;
}
