#include "robot/mogo.h"

Mogo::Mogo(digital_out *port) : port(port), extended(false) {}

void Mogo::toggle() {
  if (extended) {
    release();
  } else {
    clamp();
  }
}

void Mogo::clamp() {
  printf("clamp\n");
  port->set(true);
  extended = true;
}

void Mogo::release() {
  printf("release\n");
  port->set(false);
  extended = false;
}

bool Mogo::is_clamped() { return extended; }