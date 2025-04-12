#pragma once

#include "vex.h"

class Doinker {
    public:
        Doinker(vex::triport::port port);
        void toggle();
        void extend();
        void retract();
        bool is_extended();

    private:
        vex::digital_out port;
        bool extended;
};