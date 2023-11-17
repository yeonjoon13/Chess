///////////////////////////////////
// IT IS OK TO MODIFY THIS FILE, //
// YOU WON'T HAND IT IN!!!!!     //
///////////////////////////////////
#ifndef MYSTERY_H
#define MYSTERY_H

#include <cmath>
#include "Piece.h"

namespace Chess
{
  class Mystery : public Piece {

  public:
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
      
      /**
      (void) start;//meaningless statement helps avoid unused parameter warning for now
      (void) end;  //meaningless statement helps avoid unused parameter warning for now
      
      **/
      int xdist = (int)end.first - (int)start.first;
      int ydist = (int)end.second - (int)start.second;

      return (std::abs(xdist) == 3 && std::abs(ydist) == 2) || (std::abs(ydist) == 3 && std::abs(xdist) == 2);

    }

    char to_ascii() const {
      return is_white() ? 'M' : 'm';
    }

  private:
    Mystery(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };
}
#endif // MYSTERY_H
