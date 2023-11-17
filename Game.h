// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

  class Game {

  public:
    // This default constructor initializes a board with the standard
    // piece positions, and sets the state to white's turn
    Game();

    // Returns a constant reference to the board
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    const Board& get_board() const { return board; }

    // Returns true if it is white's turn
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    bool turn_white() const { return is_white_turn; }

    // Attemps to make a move. If successful, the move is made and
    // the turn is switched white <-> black. Otherwise, an exception is thrown
    void make_move(std::pair<char, char> start, std::pair<char, char> end);

    // Helper function for make_move to check exceptions
    void check_move(std::pair<char, char> start, std::pair<char, char> end) const;

    // Returns true if the designated player is in check
    bool in_check(bool white) const;

    // Returns true if the designated player is in mate
    bool in_mate(bool white) const;

    // Returns true if the designated player is in mate
    bool in_stalemate(bool white) const;

    // Sets the turn equal to the color
    void make_turn(char color);

    // Checks whether the path between two positions is clear
    bool check_path(std::pair<char, char> start, std::pair<char, char> end) const;

    // Writes the board out to a stream
    friend std::ostream& operator<< (std::ostream& os, const Game& game);

    // Reads the board in from a stream
    friend std::istream& operator>> (std::istream& is, Game& game);

  private:
    // The board
    Board board;

    // Is it white's turn?
    bool is_white_turn;

    
  };

}
#endif // GAME_H
