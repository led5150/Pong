#ifndef _BALL_H_
#define _BALL_H_
#include <iostream>
#include <mutex>

using namespace std;
class Ball
{
    public:

        Ball();
        ~Ball();
        friend ostream &operator<<( ostream &output, const Ball &B ) { 
	    output << B.ball;
            return output; 
        }

        int  get_xpos();
        int  get_ypos();

        void set_xpos(int x);
        void set_ypos(int y);
        void set_xvelos(int x);
        void set_yvelos(int y);
        void change_dir(int height, int width, int x, int y);
        int  score(int width);
        void change_velos(int x);


    private:

        char ball;
        int  xpos;
        int  ypos;
        int  xvelos;
        int  yvelos;

        std::mutex ball_lock;
};


#endif
