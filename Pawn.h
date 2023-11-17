// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

namespace Chess
{
  class Pawn : public Piece {

  public:
    // Returns true if the move is a legal move for a pawn
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const override;

    // Returns true if the move is a legal capture move for a pawn
    bool legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const override;

    
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    char to_ascii() const override{
      return is_white() ? 'P' : 'p';
    }

  private:
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    Pawn(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };
}
#endif // PAWN_H
