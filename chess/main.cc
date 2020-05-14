#include "board.h"
#include "player.h"
#include "computer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include <memory>

using namespace std;

// prints score of both players
void printScore(double bScore, double wScore){

    cout << "White: " << wScore << endl;
    cout << "Black: " << bScore << endl;
}

// checks to see if a string corresponds to a valid type of piece
bool isValidPiece(char piece){

    return (piece == 'K' || piece == 'k' ||
        piece == 'Q' || piece == 'q' ||
        piece == 'N' || piece == 'n' ||
        piece == 'P' || piece == 'p' ||
        piece == 'B' || piece == 'b' ||
        piece == 'R' || piece == 'r');
}

// converts a letter coordinate to a numerical one
// returns -1 if it is an invalid character
int getColumn(char c){
    
    switch (c){

        case 'a':
            return 7;
        break;
        
        case 'b':
            return 6;
        break;
        
        case 'c':
            return 5;
        break;
        
        case 'd':
            return 4;
        break;
        
        case 'e':
            return 3;
        break;
        
        case 'f':
            return 2;
        break;
        
        case 'g':
            return 1;
        break;
        
        case 'h':
            return 0;
        break;

        default:
            return -1;
        break;
    }

    return -1;
}

// determines if the string form of a coordinate is within bounds
bool isValidCoordinate(string coord){

    transform(coord.begin(), coord.end(), coord.begin(), ::tolower); 

    if (coord.length() != 2){
        return false;
    }

    int x, y;
    x = 7 - getColumn(coord[0]);
    y = 7 - (coord[1] - '0' - 1);

    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        return true;
    
    return false;
}

// converts a string coordinate to a numerical, pair form
pair<int, int> convertCoord(string convert){

    transform(convert.begin(), convert.end(), convert.begin(), ::tolower); 

    int x, y;
    x = 7 - getColumn(convert[0]);
    y = 7 - (convert[1] - '0' - 1);

    return pair<int,int>(y,x);
}

int main(){

    double blackScore = 0;
    double whiteScore = 0;
    char turn = 'w';
    string winner = "WHITE";

    // boolean to see if eof has been reached
    bool eof = false;

    shared_ptr<Player> white;
    shared_ptr<Player> black;

    cout << "Welcome to Chess" << endl;

    Board board = Board();
    board.init();
    
    string input = "";
    
    // print default board and present default options
    cout << board << endl;
    
    cout << "-MAIN MENU-" << endl; 
    cout << "SETUP MODE:\t\tsetup" << endl;
    cout << "GAME:\t\t\tgame <white-player> <black-player>" << endl << "\t\t\tAdd 'hints=on' when starting game to enable hints" << endl << endl;
    
    bool once = true;

    // wrapping command interpreter
    while (getline(cin, input)){
        
        if (once == false){
            cout << endl << "-MAIN MENU-" << endl; 
            cout << "SETUP MODE:\t\tsetup" << endl;
            cout << "GAME:\t\t\tgame <white-player> <black-player>" << endl << "\t\t\tAdd 'hints=on' when starting game to enable hints" << endl << endl;

        }
        once = false;

        cout << board << endl << endl;

        if (cin.eof()){
            eof = true;
            break;
        }

        transform(input.begin(), input.end(), input.begin(), ::tolower); 

        stringstream commandCheck(input);
        string commandWord;
        commandCheck >> commandWord;

        if (commandWord != "game" && commandWord != "setup"){
            
            cout << "Invalid command." << endl << "Please enter 'setup' or 'game' to continue." << endl;
            continue;
        }

        else if (commandWord == "setup"){

            cout << "Entering setup mode..." << endl;
            
            board.clear();

            cout << "-SETUP COMMANDS-:" << endl << endl;
            cout << "PLACE:\t\t\t+ <piece> <coordinates>" << endl;
            cout << "REMOVE:\t\t\t- <coordinates> " << endl;
            cout << "CHANGE TURN:\t\t= <colour>" << endl;
            cout << "DONE:\t\t\tdone" << endl << endl;

            string command = "";

            cout << "Current board:" << endl;
            cout << board << endl << endl;
            
            while (getline(cin, command)){    
                
                cout << command << endl;
                
                stringstream line(command);
                string word = "";
                char piece;

                bool invalid = false;

                //get primary command (+, -, =, done)
                line >> word;

                if (word == "+"){
                    
                    // get piece
                    line >> piece;
                    
                    if (isValidPiece(piece)){
                        
                        // get coordinate
                        line >> word;
                        
                        // if a valid coordinate, construct coordinate and place piece
                        if (isValidCoordinate(word)){

                            pair<int, int> coord = convertCoord(word);
                            cout << "FIRST: " << coord.first << endl << "SECOND: " << coord.second << endl;
                            if (islower(piece)) {
                                board.place(pair<int,int>(-1,-1), coord, 'b', piece);
                            } else {
                                board.place(pair<int,int>(-1,-1), coord, 'w', piece);
                            }
                        }
                        
                        else
                            invalid = true;
                    }

                    else{
                        invalid = true;
                    }
                }
                
                else if (word == "-"){
                        
                    // get coordinate
                    line >> word;

                    // if a valid coordinate, construct coordinate and remove piece
                    if (isValidCoordinate(word)){
                        
                        pair<int, int> coord = convertCoord(word);
                        board.remove(coord);
                    }
                    
                    else
                        invalid = true;
                }

                else if (word == "="){
                    
                    // get colour
                    line >> word;

                    transform(word.begin(), word.end(), word.begin(), ::tolower); 
                    
                    if (word == "black")
                        turn = 'b';
                    else if (word == "white")
                        turn = 'w';
                    else
                        invalid = true;
                }

                else if (word == "done"){

                    if (board.validBoard()){
                        cout << "Custom board is valid." << endl;
                    }

                    else{
                        cout << "Custom board is invalid. Resetting board to default configuration." << endl;
                        
                        // reset board to default
                        board.clear();
                        board.init();
                    }

                    cout << endl << "Exiting setup mode..." << endl;
                    cout << endl << "-MAIN MENU-" << endl; 
                    cout << "SETUP MODE:\t\tsetup" << endl;
                    cout << "GAME:\t\t\tgame <white-player> <black-player>" << endl << "\t\t\tAdd 'hints=on' when starting game to enable hints" << endl << endl;
                    
                    once = true;

                    break;
                }

                else{
                    invalid = true;
                }

                if (invalid){

                    cout << "Invalid command." << endl << endl;
                    cout << "-SETUP COMMANDS-:" << endl << endl;
                    cout << "PLACE:\t\t\t + <piece> <coordinates>" << endl;
                    cout << "REMOVE:\t\t\t - <coordinates> " << endl;
                    cout << "CHANGE TURN:\t\t\t = <black OR white>" << endl;
                    cout << "DONE:\t\t\tdone" << endl << endl;
                    continue;
                }

                else{
                    cout << "Current board:" << endl;
                    cout << board << endl << endl;
                
                }
                if (eof){
                    break;
                }
            }

            if (cin.eof()){
                eof = true;
            }
        }

        if (commandWord == "game"){

            cout << "Starting game..." << endl;
            
            // white player
            commandCheck >> commandWord;

            if (commandWord == "human"){
                white = make_shared<Player>('w');
            }
            else if (commandWord.find("computer[") != string::npos && commandWord.length() == 11 && commandWord[10] == ']' && isdigit(commandWord[9])){
                
                int computerLevel = 1;

                if (commandWord[9] == '1'){
                    computerLevel = 1;
                }
                else if (commandWord[9] == '2'){
                    computerLevel = 2;
                } 

                white = make_shared<Computer>('w', computerLevel);
            }
            else{
                cout << "Invalid White Player expression." << endl;
                continue;
            }            

            // black player
            commandCheck >> commandWord;
            
            if (commandWord == "human"){
                black = make_shared<Player>('b');
            }
            else if (commandWord.find("computer[") != string::npos && commandWord.length() == 11 && commandWord[10] == ']' && isdigit(commandWord[9])){
                
                int computerLevel = 1;

                if (commandWord[9] == '1'){
                    computerLevel = 1;
                }
                else if (commandWord[9] == '2'){
                    computerLevel = 2;
                } 

                black = make_shared<Computer>('b', computerLevel);
            }
            else{
                cout << "Invalid Black Player expression.";
                continue;
            }            

            bool game = true;

            // game command interpreter

            cout << "Game started." << endl;
        
            commandCheck >> commandWord;

            if (commandWord == "hints=on"){
                board.toggleHints();
            }
            
            while (game){
                

                cout << board << endl;

                cout << "-GAME COMMANDS-" << endl;
                cout << "MOVE:\t\tmove <start> <destination>" << endl;
                cout << "RESIGN:\t\tresign" << endl;
                cout << "CASTLE:\t\tcastle <direction>" << endl;
                if (board.isHintsOn())
                    cout << "HINT:\t\thint <coordinate>" << endl <<endl;
                else
                    cout << endl;

                string gameCommand;

                // starting and ending coordinates of an ending move
                pair<int, int> startCoord, endCoord;

                // pre-turn checks: check, checkmate, stalemate

                if (board.isCheckmate('w')){
                    cout << "White is checkmated" << endl;
                    winner = "BLACK";
                    blackScore++;
                    break;
                }
                else if (board.isCheckmate('b')){
                    cout << "Black is checkmated" << endl;
                    winner = "WHITE";
                    whiteScore++;
                    break;
                }

                if (board.isStalemate('w') || board.isStalemate('b')){
                    winner = "STALEMATE";
                }

                if (board.isCheck('b')){
                    cout << "BLACK is in check." << endl << endl;
                }

                if (board.isCheck('w')){
                    cout << "WHITE is in check." << endl << endl;
                }


                cout << endl << "It is currently ";

                switch (turn){
                    case 'w':
                        cout << "WHITE";
                    break;
                    case 'b':
                        cout << "BLACK";
                    break;
                }

                cout << "\'s turn. Enter your move." << endl << endl; 
                    
                getline(cin, gameCommand);

                if (cin.eof()){
                    eof = true;
                    game = false;
                    continue;
                }
                
                char promoType = ' ';

                promoType = gameCommand[gameCommand.length() - 1];
                
                transform(gameCommand.begin(), gameCommand.end(), gameCommand.begin(), ::tolower); 

                stringstream command(gameCommand);

                string action;
                command >> action;

                if (action == "resign"){
                    
                    switch (turn){
                    case 'w':
                        cout << "WHITE";
                        winner = "BLACK";
                        blackScore++;
                    break;
                    case 'b':
                        cout << "BLACK";
                        winner = "WHITE";
                        whiteScore++;
                    break;
                    }

                    cout << " Player has resigned." << endl;
                    break;
                }
                
                // entire command is "move" indicating a computer move
                else if (gameCommand == "move"){
                    
                    if (turn == 'w'){
                        
                        if (white -> isComputer()){
                            
                            try{
                                pair<pair<int, int>, pair<int, int>> computerMove = white -> generateMove(board);
                                startCoord = computerMove.first;
                                endCoord = computerMove.second;
                                board.move(startCoord, endCoord);

                                switch(turn){
                                    case 'w':
                                        turn = 'b';
                                    break;
                                    case 'b':
                                        turn = 'w';
                                    break;
                                }
                            }
                            catch (string s){
                                cout << "Computer move error: " << s << endl;
                            }
                        }
                        
                        else{
                            cout << endl << "Invalid command. No coordinates entered for move." << endl; 
                            continue;
                        }
                    }


                    else if (turn == 'b'){
                        if (black -> isComputer()){
                            
                            try{

                            pair<pair<int, int>, pair<int, int>> computerMove = black -> generateMove(board);
                            startCoord = computerMove.first;
                            endCoord = computerMove.second;
                            board.move(startCoord, endCoord);

                            switch(turn){
                                case 'w':
                                    turn = 'b';
                                break;
                                case 'b':
                                    turn = 'w';
                                break;
                            }

                            }
                            catch (string s){
                                cout << "Computer move error: " << s << endl;
                            }
                        }

                        else{
                            cout << "Invalid command. No coordinates entered for move." << endl; 
                            continue;
                        }
                    }
                }

                // normal move
                else if (action == "move"){

                    bool invalidMove = false;

                    // grab starting and ending coordinates
                    for (int i = 0; i < 2; i++){
                        
                        string coord;
                        command >> coord;
                        
                        if (coord.length() != 2){
                            invalidMove = true;
                            break;
                        }

                        int x = 7 - getColumn(coord[0]);
                        int y = 8 - (coord[1] - '0'); 
                        
                        if (x < 0 || x > 7 || y < 0 || y > 7){
                            invalidMove = true;
                            break;
                        }

                        switch(i){
                            case 0:
                                startCoord.first = y;
                                startCoord.second = x;
                            break;

                            case 1:
                                endCoord.first = y;
                                endCoord.second = x;
                            break;
                        }
                    }

                    if (invalidMove){
                        cout << endl << "Invalid move entered. Try again." << endl << endl;
                        continue;
                    }

                    else{

                        try{

                            shared_ptr<Piece> pieceCheck = board.getPiece(startCoord);
                            
                            if (pieceCheck -> getColour() != turn){
                                string err = "You cannot attempt moves on pieces that aren't yours.";
                                throw err;
                            }

                            board.move(startCoord, endCoord);


                            shared_ptr<Piece> pieceMoved = board.getPiece(endCoord);
                            if (pieceMoved -> getType() == 'p' || pieceMoved -> getType() == 'P'){

                                if (endCoord.first == 0 || endCoord.first == 7){
                                    
                                    switch (turn){

                                        case 'w':
                                            if (!(promoType == 'Q' || promoType == 'N' || promoType == 'R' || promoType == 'B')){
                                                promoType = ' ';
                                            }
                                        break;

                                        case 'b':
                                            if (!(promoType == 'q' || promoType == 'n' || promoType == 'r' || promoType == 'b')){
                                                promoType = ' ';
                                            }
                                        break;
                                    }

                                    while (promoType == ' '){
                                        
                                        cout << endl << "Invalid piece entered for pawn promotion." << endl;
                                        
                                        cout << "Please enter the piece you would like to promote your pawn to." << endl;
                                        
                                        if (turn == 'b'){
                                            cout << "Enter one of the following: q, n, r, b" << endl;
                                            cin >> promoType;
                                            if (!(promoType == 'q' || promoType == 'n' || promoType == 'r' || promoType == 'b')){
                                                promoType = ' ';
                                            }
                                        }
                                        else{
                                            cout << "Enter one of the following: Q, N, R, B" << endl;
                                            cin >> promoType;
                                            if (!(promoType == 'Q' || promoType == 'N' || promoType == 'R' || promoType == 'B')){
                                                promoType = ' ';
                                            }
                                        }
                                    }

                                    board.promotePawn(endCoord, promoType);
                                }
                            }

                            switch(turn){
                                case 'w':
                                    turn = 'b';
                                break;
                                case 'b':
                                    turn = 'w';
                                break;
                            }
                        }

                        catch(string invalidMoveException){
                            
                            cout << endl << "Invalid move: " << endl << invalidMoveException << endl << "Try again." << endl << endl;
                            continue;
                        }
                    }
                }
            
                else if (action == "hint"){
                    
                    if (board.isHintsOn()){
                        
                        bool invalidCoord = false;

                        for(int i = 0; i < 1; i++){

                            string coord;
                            command >> coord;
                            
                            if (coord.length() != 2){
                                invalidCoord = true;
                                break;
                            }

                            int x = 7 - getColumn(coord[0]);
                            int y = 8 - (coord[1] - '0'); 
                            
                            if (x < 0 || x > 7 || y < 0 || y > 7){
                                invalidCoord = true;
                                break;
                            }

                            startCoord.first = y;
                            startCoord.second = x;

                            shared_ptr<Piece> hintPiece = board.getPiece(startCoord);

                            if (hintPiece -> getColour() == turn){
                                board.getHint(startCoord);
                            }
                            else{
                                cout << "You cannot get a hint for pieces that aren't your own." << endl << endl;
                            }

                        }
                        
                        if (invalidCoord){
                            cout << "Invalid coordinate accessed for hint." << endl << endl;
                        }
                    }

                    else{
                        cout << "Hints are disabled. Enter a move or resign." << endl << endl;
                    }
                }

                else if (action == "castle"){
                    
                    string direction = "";

                    command >> direction;

                    if (direction != "left" && direction != "right"){
                        cout << "Invalid direction given for castling." << endl << endl;
                    }

                    try {

                        if (board.tryCastling(turn, direction)){
                            
                            cout << "Successfully performed castle to the " << direction << "." << endl << endl;

                            switch(turn){
                                case 'w':
                                    turn = 'b';
                                break;
                                case 'b':
                                    turn = 'w';
                                break;
                            }
                        }
                    }
                    catch (string castleError){
                        
                        cout << "Invalid castle attempted:" << endl;
                        cout << castleError << endl << endl;
                    }
                }

                else{
                        
                    cout << "Invalid command." << endl << endl;

                    cout << "-GAME COMMANDS-" << endl;
                    cout << "MOVE:\t\tmove <start> <destination>" << endl;
                    cout << "RESIGN:\t\tresign" << endl;
                    cout << "CASTLE:\t\tcastle <direction>" << endl;
                    if (board.isHintsOn())
                        cout << "HINT:\t\thint <coordinate>" << endl <<endl;
                    else
                        cout << endl;
                    continue;
                }

            }

            if (game){
                if (winner != "STALEMATE"){
                    cout << winner << " wins!" << endl << endl; 
                }
                else{
                    cout << "STALEMATE: Draw!" << endl << endl;
                    blackScore += 0.5;
                    whiteScore += 0.5;
                }

                // reset board to default and display
                board.clear();
                board.init();
                if (board.isHintsOn()){
                    cout << "Hints are being disabled." << endl << endl;
                    board.toggleHints();
                }

                turn = 'w';

                cout << endl << "-MAIN MENU-" << endl; 
                cout << "SETUP MODE:\t\tsetup" << endl;
                cout << "GAME:\t\t\tgame <white-player> <black-player>" << endl << "\t\t\tAdd 'hints=on' when starting game to enable hints" << endl << endl;
                once = true;
            }
            else{
                break;
            }
            
        }
    }

    cout << endl << "Final Score:" << endl;
    printScore(blackScore, whiteScore);
    
    cout << endl << endl << "Thank you for playing." << endl;
    exit(0);
}
