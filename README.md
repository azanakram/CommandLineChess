# CommandLineChess
Playable Command Line Chess Game with Computer AI and Setup Mode, C++

This is a completed chess game, with 2 levels of AI for computer players.

The game features a Setup Mode, within which players are able to setup their own initial
board configurations, as well as a Hint feature give the player a list of coordinates a
specified piece can move to.


----------------- Display -----------------

    8 rnbqkbnr 
    7 pppppppp 
    6  _ _ _ _ 
    5 _ _ _ _ 
    4  _ _ _ _ 
    3 _ _ _ _ 
    2 PPPPPPPP 
    1 RNBQKBNR
      abcdefgh

Captial letters denote white pieces, lower case letters denote black pieces.
Unoccupied squares are denoted by a blank space for white squares, and an 
underscore character for dark squares.


----------------- Rules for Pieces -----------------

King (K/k) Moves one square in any direction.

Queen (Q/q) Moves in any of the eight possible directions, any distance, but cannot move
past any piece that blocks its path.

Bishop (B/b) Moves in any of the four diagonal directions, any distance, but cannot move
past any piece that blocks its path.

Rook (R/r) Moves in any of the four vertical/horizontal directions, any distance, but cannot
move past any piece that blocks its path.

Knight (N/n) If it sits on square (x,y), it can move to square (x+-2,y+-1) or (x+-1,y+-2)
as long as the destination is within the board, and not occupied by a piece of the same colour.

Pawn (P/p) Moves one square forward. Can move two steps forward if the pawn is being moved from
row-2 (White) or row-7 (Black). Moves one square diagonally forward when attempting to kill 
opposing piece.


----------------- Players -----------------

The game supports both Human and Computer players, in particular, Human vs. Human, Human vs.
Computer, Computer vs. Computer games are all possible.


----------------- Computer AI -----------------

    Level 1: Random Legal Moves
    Level 2: Prefers Capturing Moves and Checks over other moves
    

----------------- Commands -----------------

### <setup>
    Enter Setup Mode, within which you can set up your own initial board configurations.
    This can only be done when a game is not currently running.
    
    Within setup mode, the following commands is used:
    
          <+ piece coordinate>             Ex: <+ K e4>
                Places piece at the specified coordinate. If a piece is already on that
                square, it is replaced.
                
          <- coordinate>                      Ex: <- e4>
                Removes the piece (if any) at the specified coordinate.
                
          <= colour>                          Ex: <= black>
                Makes it <colour>'s turn to make the first move.
                
          done
                Exits setup mode.
                
    Upon completion of setup mode, you must verify that the board contains exactly one white
    king and exactly one black king; that no pawns are on the first or last row of the board; and
    that neither king is in check. The user cannot leave setup mode until these conditions are
    satisfied.

### <game white-player black-player>   or   <game white-player black-player hints=on>
    Starts a new game, the parameters <white-player> and <black-player> can either be human
    or computer[1] or computer[2]. If you want hints to be enabled in your game, you must do
    so now.
    
    Within the game, the following commands is used:
    
          <move start-coordinate end-coordinate>             Ex: <move e2 e4>
                Attempts to move piece at start-coordinate to end-coordinate
                
          <move start-coordinate end-coordinate piece>             Ex: <move e7 e8 Q>
                Attempts to perform pawn promotion by moving a pawn at start-coordinate
                to end-coordinate, and turning it into a new piece
                
          <move>
                Move command for computer
                
          <resign>
                Resign the game. The opposing player gets 1 point
                
          <castle direction>                          Ex: <castle left>
                Attempts to perform caslting by moving the King in the specified
                direction
                
          <hint coordinate>                          Ex: <hint e2>
                Get a hint for the piece at coordinate.
    
    
------------------------------------------------------------------------------------------------    

