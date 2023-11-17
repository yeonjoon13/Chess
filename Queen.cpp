// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#include "Piece.h"
#include "Queen.h"
#include <cmath>

namespace Chess {

bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //piece functions as a rook and a bishop

  //distances in both directions                                                                                                 
  int xdist = std::abs((int)end.first - (int)start.first);
  int ydist = std::abs((int)end.second - (int)start.second);

  if (xdist == 0 && ydist == 0) {
    return false;
  }

  //bools represented whether the move is diagnolly or in one direction
  bool diagonal = (xdist == ydist);
  bool one_direction = !(xdist && ydist);

  return diagonal || one_direction;

}
}
