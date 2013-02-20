#include "dot.h"
#include <string>
#include <ctime>
#include <sstream>

const int DEFAULT_SIZE = 50;
const int DEFAULT_START = 0;

Dot::Dot() {
  x = DEFAULT_START;
  y = DEFAULT_START;
  w = DEFAULT_SIZE;
  h = DEFAULT_SIZE;
  name = "anon:"+std::to_string(pseudo_timestamp());
}
Dot::Dot(int n) {
  x = DEFAULT_START;
  y = DEFAULT_START;
  w = n;
  h = n;
  name = "anon:"+std::to_string(pseudo_timestamp());
}
Dot::Dot(int siz_w, int siz_h) {
  x = DEFAULT_START;
  y = DEFAULT_START;
  w = siz_w;
  h = siz_h;
  name = "anon:"+std::to_string(pseudo_timestamp());
}
Dot::Dot(int siz_w, int siz_h, int pos_x, int pos_y) {
  x = pos_x;
  y = pos_y;
  w = siz_w;
  h = siz_h;
  name = "anon:"+std::to_string(pseudo_timestamp());
}
Dot::Dot(std::string dname) {
  x = DEFAULT_START;
  y = DEFAULT_START;
  w = DEFAULT_SIZE;
  h = DEFAULT_SIZE;
  name = dname;
}
Dot::Dot(std::string dname, int n) {
  x = DEFAULT_START;
  y = DEFAULT_START;
  w = n;
  h = n;
  name = dname;
}
Dot::Dot(std::string dname, int siz_w, int siz_h) {
  x = DEFAULT_START;
  y = DEFAULT_START;
  w = siz_w;
  h = siz_h;
  name = dname;
}
Dot::Dot(std::string dname, int siz_w, int siz_h, int pos_x, int pos_y) {
  x = pos_x;
  y = pos_y;
  w = siz_w;
  h = siz_h;
  name = dname;
}
std::string Dot::get_name() {
  return name;
}
int Dot::pseudo_timestamp() {
  time_t t;
  return (time(&t) % 10000);
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
void Dot::set_x(int pos_x) {
  x = pos_x;
}
void Dot::set_y(int pos_y) {
  y = pos_y;
}
void Dot::set_w(int siz_w) {
  w = siz_w;
}
void Dot::set_h(int siz_h) {
  h = siz_h;
}
std::string Dot::to_s() {
  std::stringstream description;
  description << name << "\n" << x << "\n" << y << "\n" << w << "\n" << h << "\n";
  return description.str();
}
