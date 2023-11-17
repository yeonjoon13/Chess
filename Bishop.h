// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

namespace Chess
{
  class Bishop : public Piece {

  public:
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const override;

    
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    char to_ascii() const override{
      return is_white() ? 'B' : 'b';
    }

  private:
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    Bishop(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };
}
#endif // BISHOP_H
