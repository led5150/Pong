
#ifndef _PADDLE_H_
#define _PADDLE_H_


class Paddle
{
    public:
        Paddle();
        Paddle(int x, int y);
        ~Paddle();
        int get_x();
        int get_y();
        void set_x(int x);
        void set_y(int y);
        char get_char();
        void move_up();
        void move_down(int height);
        void set_score(int add);
        int get_score();
    private:
        char pad;
        int xpos;
        int ypos;
        int score;
};


#endif 

