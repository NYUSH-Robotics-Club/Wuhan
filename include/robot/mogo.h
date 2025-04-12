#pragma once

#include "vex.h"

class Mogo {
    public:
        Mogo(vex::triport::port port);
        void toggle();
        void clamp();
        void release();
        bool is_clamped();

    private:
        vex::digital_out port;
        bool extended;
};