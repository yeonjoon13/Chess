// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#include "Piece.h"
#include "Pawn.h"
#include <cmath>

namespace Chess {

bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  // Finds the distance traveled by the pawn in both directions
  int xdist = (int)end.first - (int)start.first;
  int ydist = (int)end.second - (int)start.second;

  //checks if proposed move would actualy move piece                                                                        
  if (xdist == 0 && ydist == 0) {
     return false;
  }

  
  //if the move indicates any horizontal motion, return false
  if (xdist) {
    return false;
  }

  if (this->is_white()) { 
  
  //if the pawn is in starting position
    if (start.second == '2') {
      //can move one or two spaces forwards
      return (ydist == 1 || ydist == 2);
    }
    else {
      return (ydist == 1 );
    }
  }
  //is black
  else {
    //if the pawn is in starting position
    if (start.second == '7') {
      //can move one or two spaces down
      return (ydist == -1 || ydist == -2);
    }
    else {
      return (ydist == -1);
    }
  }
}


bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  // Finds the distance traveled by the pawn in both directions
  int xdist = (int)end.first - (int)start.first;
  int ydist = (int)end.second - (int)start.second;

  // The change in y should always be positive for white pieces
  if (this->is_white()) {
    return (std::abs(xdist) == 1 && ydist == 1);
  } else { // Change in y should always be negative for black pieces
    return (std::abs(xdist) == 1 && ydist == -1);
  }
}

  
}
