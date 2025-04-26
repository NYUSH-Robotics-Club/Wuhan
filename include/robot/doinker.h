#pragma once

#include "vex.h"

class Doinker {
    public:
        Doinker(digital_out* port);
        void toggle();
        void extend();
        void retract();
        bool is_extended();

    private:
        digital_out* port;
        bool extended;
};