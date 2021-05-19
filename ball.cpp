#include "ball.h"
#include <iostream>



Ball::Ball()
{
    ball = '.';
    xvelos = 1;
    yvelos = 1;
}

Ball::~Ball()
{
    // Nothing to do
}


int Ball::get_xpos()
{
    return xpos;
}

int Ball::get_ypos()
{
    return ypos;
}


void Ball::set_xpos(int x)
{
    xpos = x;
}


void Ball::set_ypos(int y)
{
    ypos = y;
}

void Ball::set_yvelos(int y)
{
    yvelos = y;
}

void Ball::set_xvelos(int x)
{
    xvelos = x;
}



void Ball::change_dir(int height, int width, int x, int y)
{
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
}


void Ball::change_velos(int x)
{
    xvelos = x;
}

int Ball::score(int width)
{
    if (xpos > width - 2) {
        return 0;
    } else if (xpos < 1) {
        return 1;
    } else {
        return 2;
    }
}
