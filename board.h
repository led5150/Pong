
#ifndef _BOARD_H_
#define _BOARD_H_

#define BOARD_W 40
#define BOARD_H 10

#include "paddle.h"
#include "ball.h"



class Board {

    public:
        Board();
        ~Board();
        void run();
        void print_board();
        void print_score();

    private:
        char board_arr[BOARD_H][BOARD_W];
        Paddle player1;
        Paddle player2;
        Ball   ball;
        void   reset_board();



};

#endif
