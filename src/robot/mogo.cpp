#include "robot/mogo.h"

Mogo::Mogo(vex::triport::port port)
    : port(vex::digital_out(port)), extended(false) {}

void Mogo::toggle() {
  if (extended) {
    release();
  } else {
    clamp();
  }
}

void Mogo::clamp() {
  port.set(true);
  extended = true;
}

void Mogo::release() {
  port.set(false);
  extended = false;
}

bool Mogo::is_clamped() { return extended; }