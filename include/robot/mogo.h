#pragma once

#include "vex.h"

class Mogo {
    public:
        Mogo(digital_out* port);
        void toggle();
        void clamp();
        void release();
        bool is_clamped();

    private:
        digital_out* port;
        bool extended;
};