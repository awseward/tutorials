#include <string>

class Dot {
 private:
  int x, y, w, h;
  std::string name;

 public:
  Dot();
  Dot(int);
  Dot(int, int);
  Dot(int, int, int, int);
  Dot(std::string);
  Dot(std::string, int);
  Dot(std::string, int, int);
  Dot(std::string, int, int, int, int);
  

  std::string get_name();
  std::string to_s();
  int pseudo_timestamp();
  int get_x();
  int get_y();
  int get_w();
  int get_h();
  void set_x(int);
  void set_y(int);
  void set_w(int);
  void set_h(int);
};
