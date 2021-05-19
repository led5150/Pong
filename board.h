
#ifndef _BOARD_H_
#define _BOARD_H_

#define BOARD_W 40
#define BOARD_H 10

#include <queue>
#include <mutex>
#include <thread>
#include "paddle.h"
#include "ball.h"

// a thread-safe queue class. 
class TSQueue {
public:
  void push_back(char c) {
    l.lock();
    this->q.push(c);
    l.unlock();
  };
  char pop_front() {
    l.lock();
    if (this->q.empty()) {
      l.unlock();
      return 'e';
    }
    char c = this->q.front();
    this->q.pop();
    l.unlock();
    return c;
  };

  void empty() {
    this->l.lock();
    while(!this->q.empty()) {
      this->q.pop();
    }
    this->l.unlock();
  };
private:
  std::mutex l;
  std::queue<char> q;
};


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
  
        // our thread objects
        std::thread getchars;
        std::thread ballmove;
        std::thread pboard;
  
        // functions that the threads are running 
        void    getcharthread();
        void    ballmovethread();
        void    printboardthread();

        // these queues keep track of the moves to be made for each player
        TSQueue p1_moves;
        TSQueue p2_moves;
  
        bool doneflag;  // keeps track of whether the game is over

        std::mutex boardlock; // locks the board when resetting the game
};

#endif
