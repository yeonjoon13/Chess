// William Chung, Kenny Chung, Alexandra Augur
// wchung17, kchung31, aaugur1

#include "Game.h"
#include <cmath>

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
      board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

    // Add the knights
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

    // Add the bishops
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

    // Add the kings and queens
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
  }

  void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {
	check_move(start, end);
	//remove piece being captured, if necessary
	if (this->board(end) != NULL) {
	    this->board.remove_piece(end);
	}
        this->board.add_piece(end, (this->board(start))->to_ascii());
        this->board.remove_piece(start);
	if (is_white_turn) is_white_turn = false;
        else is_white_turn = true;
	
	if (end.second == '8' && board(end)->to_ascii() == 'P') {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        } else if (end.second == '1' && board(end)->to_ascii() == 'p') {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
    }

void Game::check_move(std::pair<char, char> start, std::pair<char, char> end) const {
       //throw exceptions for invalid coordinates
        if (start.first < 'A' || start.first > 'H' || start.second < '1' || start.second > '8') {
            throw Exception("start position is not on board");
        }
        if (end.first < 'A' || end.first > 'H' || end.second < '1' || end.second > '8') {
            throw Exception("end position is not on board");
        }
        if (board(start) == NULL) {
            throw Exception("no piece at start position");
        }
	if (is_white_turn != (this->board(start)->to_ascii() < 'a')) {
            throw Exception("piece color and turn do not match");
        }

	//if move is intended non-capure
	if (board(end) == NULL) {
	  if (!(board(start)->legal_move_shape(start, end))) {
	    throw Exception("illegal move shape");
	  }
	}

	//if move is intended capture
	if (board(end) != NULL) {
	  if (islower(board(start)->to_ascii()) == islower(board(end)->to_ascii())) {                     
            throw Exception("Cannot capture own piece");
	  }
	  if (!(board(start)->legal_capture_shape(start, end))) {
	    throw Exception("illegal capture shape");
	    
	  }
	}

       
	if (!check_path(start, end)) {
	  throw Exception("path is not clear");
	}

	

	//create a temporary game to evalute whether move will cause check
        Game* temp = new Game();
        temp->board = this->board;
	if (temp->board(end) != NULL) {
	  temp->board.remove_piece(end);
	}
	//add correct piece at specified place 
        temp->board.add_piece(end, (temp->board(start))->to_ascii());

	//remove the piece from its starting position
        temp->board.remove_piece(start);
	if (temp->in_check(is_white_turn)) {
            throw Exception("move exposes check");
        }

	//free the memory occupied by the temporary board
	delete temp;
}

    
    bool Game::in_check(bool white) const {
	std::pair<char, char> king_pos;

	//iterate through board to find the specified king
	for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::pair<char, char> pos('A' + j, '1' + i);
		if (board(pos) == NULL) continue;
		//store king coordinates if correct color
                if (board(pos)->to_ascii() == 'K') {
                    if (white) king_pos = pos;
                } else if (board(pos)->to_ascii() == 'k') {
                    if (!white) king_pos = pos;
                }
            }
        }

	//iterate through chess board
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::pair<char, char> pos('A' + j, '1' + i);

		//return true if piece can move to king space
		if (board(pos) == NULL) continue;
		else if ((board(pos)->to_ascii() >= 'a') == !(white)) continue;
		if (!(check_path(pos, king_pos))) continue;
		if (board(pos)->legal_capture_shape(pos, king_pos)) {
		    return true;
		}
	       
	    }
	}
        return false;
    }


    bool Game::check_path(std::pair<char, char> start, std::pair<char, char> end) const {
 
      //if the piece is either moving horiz/vertical or diagonaly, cleared path does not matter
      if (!(start.first == end.first || start.second == end.second)) {
	if (!(std::abs(end.first - start.first) == std::abs(end.second - start.second))) {
	  return true;
	}
      }
      

      //Checks south
        if (start.first == end.first && start.second > end.second) {
            for (int i = start.second - 1; i > end.second; i--) {
	      if (board(std::pair<char, char>(start.first,(char)i)) != NULL) {
                    return false;
                }
            }
        }
        //Checks north
        else if (start.first == end.first && start.second < end.second) {
            for (int i = start.second + 1; i < end.second; i++) {
	      if (board(std::pair<char, char>(start.first, (char)i)) != NULL) {
                    return false;
                }
            }
        }
        //Checks horizontal east
        else if (start.first < end.first && start.second == end.second) {
            for (int i = start.first + 1; i < end.first; i++) {
	      if (board(std::pair<char, char>((char)i, start.second)) != NULL) {
                    return false;
                }
            }
        }
        //Checks horizontal west
        else if (start.first > end.first && start.second == end.second) {
            for (int i = start.first - 1; i > end.first; i--) {
	      if (board(std::pair<char, char>((char)i, start.second)) != NULL) {
                    return false;
                }
            }
        }
        //Checks diagonal northeast
        else if (start.first < end.first && start.second < end.second) {
	  for (int i = start.first + 1, j = start.second + 1;i < end.first; ++i, ++j) {
	    if (board(std::pair<char, char>(i, j)) != NULL) {
                    return false;
                }
            }
        }
        //Checks diagonal northwest
        else if (start.first > end.first && start.second < end.second) {
            for (int i = start.first - 1, j = start.second + 1; i > end.first; --i, ++j) {
                if (board(std::pair<char, char>(i, j)) != NULL) {
                    return false;
                }
            }
            
        }
        //Checks diagonal southeast
        else if (start.first < end.first && start.second > end.second) {
	  for (int i = start.first + 1, j = start.second - 1; i < end.first; ++i, --j) {
                if (board(std::pair<char, char>(i, j)) != NULL) {
                    return false;
                }
            }
        }
        //Checks diagonal southwest
        else if (start.first > end.first && start.second > end.second) {
            for (int i = start.first - 1, j = start.second - 1; i > end.first; --i, --j) {
                if (board(std::pair<char, char>(i, j)) != NULL) {
                    return false;
                }
            }
        }

        return true;
    }

  
bool Game::in_mate(bool white) const {
    if (!(in_check(white))) return false;

    //iterate through chess board squares for pieces to move
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::pair<char, char> start('A' + j, '1' + i);
	    //if player occupies square, determine whether it can move the board to a non checked pos
            if (board(start) != NULL) {
	      //check if piece on square is same color as player with turn
		if ((board(start)->to_ascii() >= 'a') == !(white)) {
		  //for each square the piece could move to
		    for (int u = 0; u < 8; u++) {
                        for (int v = 0; v < 8; v++) {
                            std::pair<char, char> end('A' + v, '1' + u);

			    //if check_move does not trigger an exception, player is not in mate
			    try {
                                check_move(start, end);
                            }
                            catch (Exception&) {
				continue;
                            }
                            return false;
			}
		    }
		}
	    }
	}
    }
    return true;
}

bool Game::in_stalemate(bool white) const {
    //iterate through chess board squares for pieces to move
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::pair<char, char> start('A' + j, '1' + i);
	    //if player occupies square, determine whether it can complete a legal move
            if (board(start) != NULL) {
	        //check if piece on square is same color as player with turn
		if ((board(start)->to_ascii() >= 'a') == !(white)) {
		    for (int u = 0; u < 8; u++) {
                        for (int v = 0; v < 8; v++) {
                            std::pair<char, char> end('A' + v, '1' + u);
			    //if check_move does not trigger exception, legal move can be made
			    try {
                                check_move(start, end);
                            }
                            catch (Exception&) {
				continue;
                            }
                            return false;
			}
		    }
		}
	    }
	}
    }
    return true;
}

  std::istream& operator>> (std::istream& is, Game& game) {
    char character;
    Board tempBoard;

    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
	    is >> character;
	    //add piece if character doesn't indicate blank space
            if (character != '-') {
                tempBoard.add_piece(std::pair<char, char> ('A' + j, '8'- i), character);
            }
        }
    }
    //replace current game's board with the board scanned in
    game.board.replace_board(tempBoard);
    //read in the char that indicates character's turn
    is >> character;
    std::cout << character;
    game.make_turn(character);
    return is;
  }

  // Sets the turn equal to the color
  void Game::make_turn(char color) {
      if (color == 'w') is_white_turn = true;
      else is_white_turn = false;
  }


  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
  }
}
