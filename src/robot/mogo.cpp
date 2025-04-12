#include "mogo.h"
#include "vex.h"
#include "globals.h"
#include "robot-config.h"

class Mogo {
    public:
        Mogo() : piston(mogoMech) {
        }
    
        int toggle() {
        piston.set(!piston.value());
        return 0;
        }
    
        int release() {
        piston.set(false);
        return 0;
        }
    
        int clamp() {
        piston.set(true);
        return 0;
        }
    
    private:
        vex::digital_out piston;
};
