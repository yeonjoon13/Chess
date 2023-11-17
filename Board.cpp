// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "CreatePiece.h"

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}	// Default constructor

  Board::Board(const Board& other) {	// Copy constructor
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = (other.occ).begin(); it != (other.occ).end(); it++) {
      add_piece(it->first,(*(it->second)).to_ascii());	// Adds all pieces in other to the current board
    }
  }

  Board::~Board() {	// Destructor
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      delete it->second;
    }
    occ.clear();
  }

  // Returns a pointer to a piece if it exists or a nullptr if it doesn't exist
  const Piece* Board::operator()(std::pair<char, char> position) const {
    typedef std::map<std::pair<char,char>, Piece*> board_map;
    board_map::const_iterator it = occ.find(position);	// Looks for the piece associated with the key
    if (it != occ.end()) {	// If a piece is found then it is returned
      return it->second;
    }
    else {	// No piece exists with that key
      return NULL;
    }
  }

  // Adds a piece in a specific location
  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    //specified location is occupied
    if ((*this)(position) != NULL) {
        return false;
    //the specified location is not on the board
    } else if (position.first < 'A' || position.first > 'H' || position.second < '1' || position.second > '8') {
        return false;
    //the designator is invalid
    } else if (piece_designator != 'K' && piece_designator != 'k' && piece_designator != 'Q' && piece_designator != 'q'
    && piece_designator != 'P' && piece_designator != 'p' && piece_designator != 'R' && piece_designator != 'r'
    && piece_designator != 'b' && piece_designator != 'B' && piece_designator != 'N' && piece_designator != 'n'
    && piece_designator != 'M' && piece_designator != 'm') {
        return false;
    }
    occ[position] = create_piece(piece_designator);	// If all of the above cases pass then create the piece
    return true;
  }

  // Checks if the board has a valid number of kings
  bool Board::has_valid_kings() const {
    int count = 0;
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
       if ((*(it->second)).to_ascii() == 'K' || (*(it->second)).to_ascii() == 'k') count++;	// Counts the number of black and white kings in the board
    }
    if (count != 2) return false;	// If there aren't 2 kings, then false
    return true;
  }

  // Displays a graphical representation of the chess game
  void Board::display() const {
    //print upper row of letters
    std::cout<<" ";
    for(char c = 'A'; c <= 'H'; c++) {
      std::cout<<" "<<c<<" ";
    }
    std::cout<<std::endl;

    for(char r = '8'; r >= '1'; r--) {
      //print the row number for each row
      std::cout << r;

      
      for(char c = 'A'; c <= 'H'; c++) {
	//set background to appropriate color depending on square 
	if (((int)c + (int)r) % 2 == 0) {
           Terminal::color_bg(Terminal::GREEN);
        }
        else {
           Terminal::color_bg(Terminal::YELLOW);
        }

	//store current piece in variable
	const Piece* piece = (*this)(std::pair<char, char>(c, r));
	//change text color depending on piece team
	if (piece) {
           if (piece->is_white()) {
              Terminal::color_fg(true, Terminal::WHITE);
           }
           else {
              Terminal::color_fg(true, Terminal::BLACK);
           }
	   //print out the piece's letter
           std::cout << " " << piece->to_ascii() << " ";
        } else {
          std::cout << "   ";
        }
      }
      //set the terminal to default colors and print out row number aain
      Terminal::set_default();
      std::cout<<r;
      std::cout<< std::endl;
    }
    //print top row of letters
    std::cout<<" ";
    for(char c = 'A'; c <= 'H'; c++) {
      std::cout<<" "<<c<<" ";
    }
    std::cout<<std::endl;
    
  }

  // Replaces the current board with the other board
  void Board::replace_board(const Board& other) {
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      delete it->second;
    }
    occ.clear();	// Clears the map containing the pieces and positions
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = (other.occ).begin(); it != (other.occ).end(); it++) {
      add_piece(it->first,(*(it->second)).to_ascii());	// Copies over the other board to the current board
    }
}

  // Equals override operator for copying boards
  Board& Board::operator=(const Board &other) {
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      delete it->second;
    }
    this->occ.clear();	// Clears the map containing the pieces and positions
    for (std::map<std::pair<char,char>, Piece*>::const_iterator it = (other.occ).begin(); it != (other.occ).end(); it++) {
      add_piece(it->first,(*(it->second)).to_ascii());	// Copies over the other board to the current board
    }
    return *this;
  }

  // Removes a piece at the specified position
  void Board::remove_piece(std::pair<char, char> position) {
    
    delete occ[position];
    occ.erase(position);
  }


  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }

}
