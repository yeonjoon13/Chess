// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#include "Piece.h"
#include "Rook.h"
#include <cmath>

namespace Chess {
bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //distances in both directions                                                                                                 
  int xdist = (int)end.first - (int)start.first;
  int ydist = (int)end.second - (int)start.second;

  //checks if proposed move would actualy move piece                                                                             
  if (xdist == 0 && ydist == 0)	{
    return false;
  }

  //return true if the distance is only changed in one direction 
  return !(xdist && ydist);
}
}
