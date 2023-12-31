// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

namespace Chess
{
  class Knight : public Piece {

  public:
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const override;

    
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    char to_ascii() const override {
      return is_white() ? 'N' : 'n';
    }

  private:
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    Knight(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };
}

#endif // KNIGHT_H
