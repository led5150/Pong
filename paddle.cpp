
#include <iostream>
#include "paddle.h"


Paddle::Paddle()
{
    pad   = '|';
    xpos  = 0;
    ypos  = 0;
    score = 0;
}

Paddle::Paddle(int x, int y)
{
    pad  = '|';
    xpos = x;
    ypos = y;
}

Paddle::~Paddle()
{
    // Nothing to do
}

int Paddle::get_x()
{
    return xpos;
}

int Paddle::get_y()
{
    return ypos;
}

void Paddle::set_x(int x)
{
    xpos = x;
}

void Paddle::set_y(int y)
{
    ypos = y;
}

char Paddle::get_char()
{
    return pad;
}

void Paddle::move_up()
{
    if (ypos > 0) {
        ypos--;
    }
}

void Paddle::move_down(int height)
{
    if (ypos < height - 1) {
        ypos++;
    }
}

int Paddle::get_score()
{
    return score;
}

void Paddle::set_score(int add)
{
    score += add;
}
