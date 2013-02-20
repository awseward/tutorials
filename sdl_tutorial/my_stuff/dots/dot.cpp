#include "dot.h"

Dot::Dot() {
  x = 0;
  y = 0;
  w = 50;
  h = 50;
  name = 'Unnamed dot';
}

Dot::Dot(int pos_x, int pos_y) {
  x = pos_x;
  y = pos_y;
  w = 50;
  h = 50;
  name = 'Unnamed dot';
}

string Dot::get_name() {
  return name;
}

int Dot::get_x() {
  return x;
}
int Dot::get_y() {
  return y;
}
int Dot::get_w() {
  return w;
}
int Dot::get_h() {
  return h;
}

