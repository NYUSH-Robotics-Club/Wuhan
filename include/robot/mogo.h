#include "vex.h"
#include "globals.h"

class Mogo{
    public :
        Mogo();
        int toggle();
        int release();
        int clamp();
    private:
        vex::digital_out piston;
};


Mogo mogo;