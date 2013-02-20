#include "dot.h"
#include <iostream>
#include <unistd.h>
#include <vector>


using namespace std;

int main() {
  srand(time(NULL));
  vector<Dot> dots;

  // create some dots
  for(unsigned int i = 0; i< 100; i++) {
    dots.push_back(Dot(rand() % 50));
  }

  // display all the dots...
  for (unsigned int i = 0; i < dots.size(); i++) {
    cout << dots[i].to_s() << endl;
  }

  return 0;
}
