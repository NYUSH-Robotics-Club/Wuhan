#include "robot/doinker.h"

Doinker::Doinker(vex::triport::port port)
    : port(vex::digital_out(port)), extended(false) {}

void Doinker::toggle() {
  if (extended) {
    retract();
  } else {
    extend();
  }
}

void Doinker::extend() {
  port.set(true);
  extended = true;
}

void Doinker::retract() {
  port.set(false);
  extended = false;
}

bool Doinker::is_extended() { return extended; }