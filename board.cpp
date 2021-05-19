
#include <iostream>
#include <unistd.h>
#include <chrono>

#include "board.h"
#include "termfuncs.h"

using namespace std;


void Board::getcharthread() {
  while (!this->doneflag) {
    char c = getachar();
    if      (c == 'w' or c == 's') p1_moves.push_back(c);
    else if (c == 'o' or c == 'l') p2_moves.push_back(c);
  }
}

void Board::ballmovethread() {
  while (!this->doneflag) {
      // change the direction of the ball or continue it moving.  Mostly
      // this concerns not going out of bounds when the ball hits the top
      // or bottom of the board
      ball.change_dir(BOARD_H, BOARD_W, ball.get_xpos(), ball.get_ypos());
      std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
  } 
}

void Board::printboardthread() {
  while (!this->doneflag) {
        screen_clear();
        screen_home();
        print_score();
        print_board();
  }
}


Board::Board()
{
  printf("\e[?25l"); // hide the cursor
    for (int i = 0; i < BOARD_H; i++) {
        for (int j = 0; j < BOARD_W; j++) {
            board_arr[i][j] = ' ';
        }
    }
    player1.set_x(0);
    player1.set_y(4);
    player2.set_x(BOARD_W - 1);
    player2.set_y(BOARD_H - 4);

    ball.set_xpos(BOARD_W / 2);
    ball.set_ypos(BOARD_H / 2);
    ball.set_xvelos(1);
    ball.set_yvelos(1);

    doneflag = false;

    //funky syntax from stackoverflow
    //https://stackoverflow.com/questions/23594244/is-there-a-safe-way-to-have-a-stdthread-as-a-member-of-a-class
    getchars = std::thread(&Board::getcharthread, this);
    ballmove = std::thread(&Board::ballmovethread, this);
    pboard   = std::thread(&Board::printboardthread, this);
}

Board::~Board()
{
    // Nothing to do
}


void Board::run()
{
    while (player1.get_score() != 7 and player2.get_score() != 7) {

        // I think the bottle neck is here! With the getachar() function.
        char player1_move = p1_moves.pop_front(); //getachar();
	//if (player1_move == 'e') { continue; }
	char player2_move = p2_moves.pop_front(); //getachar();

	// check the input and move the paddle
	if (player1_move != 'e') {
	  
     	    if (player1_move == 'w') {
                player1.move_up();
            } else if (player1_move == 's') {
                player1.move_down(BOARD_H);
            }
	}
	if (player2_move != 'e') {
            if (player2_move == 'o') {
                player2.move_up();
            } else if (player2_move == 'l') {
                player2.move_down(BOARD_H);
            }
        }
	
        // check if the ball has passed the boundaries of the board. If so 
        // update the appropriate player score
        int score = ball.score(BOARD_W);	
        if (score == 0) {
            player1.set_score(1);
            reset_board();
        } else if (score == 1) {
            player2.set_score(1);
            reset_board();
        }

      // if the ball hits a paddle, change the x velocity of the ball to the
      // opposite direction.
	if (player1.get_x() == ball.get_xpos() and player1.get_y() == ball.get_ypos()) {
          ball.set_xvelos(1);
          ball.set_xpos(player1.get_x() + 1);
      }
      if (player2.get_x() == ball.get_xpos() and player2.get_y() == ball.get_ypos()) {
          ball.set_xvelos(-1);
          ball.set_xpos(player2.get_x() - 1);
      }

    }
    doneflag = true;
    this->getchars.join();
    this->ballmove.join();
    std::cout << "DONE" << std::endl;
    printf("\e[?25h"); // show the cursor
}

void Board::reset_board()
{
    boardlock.lock();
    player1.set_x(0);
    player1.set_y(4);
    player2.set_x(BOARD_W - 1);
    player2.set_y(BOARD_H - 4);

    ball.set_xpos(BOARD_W / 2);
    ball.set_ypos(BOARD_H / 2);
    ball.set_xvelos(1);
    ball.set_yvelos(1);

    p1_moves.empty();
    p2_moves.empty();
    boardlock.unlock();
}

void Board::print_score()
{
    cout << "Player 1: " << player1.get_score();
    for (int i = 0; i < BOARD_W - 24; i++) {
        cout << " ";
    }
    cout << "Player 2: " << player2.get_score() << endl;
}




void Board::print_board()
{
    for (int i = 0; i < BOARD_H; i++) {
        for (int j = 0; j < BOARD_W; j++) {
            if (i == player1.get_y() and j == player1.get_x()) {
                cout << player1.get_char();
            }
            else if (i == player2.get_y() and j == player2.get_x()) {
                cout << player2.get_char();
            }
            else if (i == ball.get_ypos() and j == ball.get_xpos()) {
                cout << ball;
            }
            else {
                cout << board_arr[i][j];
            }
        }
        cout << endl;
    }
}
