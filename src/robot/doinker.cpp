#include "robot/doinker.h"

Doinker::Doinker(digital_out *port) : port(port), extended(false) {}

void Doinker::toggle() {
  if (extended) {
    retract();
  } else {
    extend();
  }
}

void Doinker::extend() {
  port->set(true);
  extended = true;
}

void Doinker::retract() {
  port->set(false);
  extended = false;
}

bool Doinker::is_extended() { return extended; }