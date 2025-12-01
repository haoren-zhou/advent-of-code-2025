#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
  ifstream infile("input.txt");
  string line;

  int dial = 50;
  char direction;
  int distance, zero_count = 0;
  constexpr char LEFT = 'L';
  constexpr char RIGHT = 'R';

  while (getline(infile, line)) {
    stringstream ss(line);

    ss >> direction;
    ss >> distance;

    zero_count += distance / 100;
    distance %= 100;

    const int multiplier = direction == LEFT ? 1 : -1;

    if (dial == 0) {
      dial = multiplier * distance;
    } else {
      dial += multiplier * distance;
      if (dial >= 100 || dial <= 0)
        ++zero_count;
    }
    dial = (dial + 100) % 100;
  }

  cout << zero_count;
  return 0;
}
