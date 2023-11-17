// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#ifndef KING_H
#define KING_H

#include "Piece.h"

namespace Chess
{

  class King : public Piece {

  public:
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const override;

    
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    char to_ascii() const override{
      return is_white() ? 'K' : 'k';
    }

  private:
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    King(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };

}
#endif // KING_H
