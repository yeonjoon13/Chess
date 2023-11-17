// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#include "Piece.h"
#include "King.h"
#include <cmath>

namespace Chess {

bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  // Finds the ABSOLUTE VALUE distance traveled and takes the absolute value of it
  int xdist = std::abs((int)end.first - (int)start.first);
  int ydist = std::abs((int)end.second - (int)start.second);

  				   
  if ((xdist == 0 && ydist == 0) || xdist > 1 || ydist > 1) return false;
  
  return true;

}
}
