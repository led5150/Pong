#include "ball.h"
#include <iostream>



Ball::Ball()
{
<<<<<<< HEAD
    ball_lock.lock();
    ball = '.';
=======
    ball   = '.';
>>>>>>> a94bfe9c0bf0fb83fb77813e8061d01617cbaa26
    xvelos = 1;
    yvelos = 1;
    ball_lock.unlock();
}

Ball::~Ball()
{
    // Nothing to do
}


int Ball::get_xpos()
{
   ball_lock.lock();
   int retval = xpos;
   ball_lock.unlock();
   return retval;
}

int Ball::get_ypos()
{
   ball_lock.lock();
   int retval = ypos;
   ball_lock.unlock();
   return retval;
}


void Ball::set_xpos(int x)
{
    ball_lock.lock();
    xpos = x;
    ball_lock.unlock();
}


void Ball::set_ypos(int y)
{
    ball_lock.lock();
    ypos = y;
    ball_lock.unlock();
}

void Ball::set_yvelos(int y)
{
    ball_lock.lock();
    yvelos = y;
    ball_lock.unlock();
}

void Ball::set_xvelos(int x)
{
    ball_lock.lock();
    xvelos = x;
    ball_lock.unlock();
}



void Ball::change_dir(int height, int width, int x, int y)
{
    ball_lock.lock();
    if (y >= height - 1) {
        yvelos = -1;
        ypos += yvelos;
    } else if ( y < 1 ) {
        yvelos = 1;
        ypos += yvelos;
    } 
    else {
        ypos += yvelos;
    }
    if (x >= width - 1) {
        xvelos = -1;
        xpos   += xvelos;
    } else if (x < 1){
        xvelos = 1;
        xpos   += xvelos;
    }  else {
        xpos += xvelos;
    }
    ball_lock.unlock();
}


void Ball::change_velos(int x)
{
    ball_lock.lock();
    xvelos = x;
    ball_lock.unlock();
}

int Ball::score(int width)
{
    ball_lock.lock();
    if (xpos > width - 2) {
        ball_lock.unlock();
        return 0;
    } else if (xpos < 1) {
        ball_lock.unlock();
        return 1;
    } else {
        ball_lock.unlock();
        return 2;
    }
}
