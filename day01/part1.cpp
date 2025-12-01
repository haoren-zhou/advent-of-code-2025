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

    if (direction == LEFT) {
      dial -= distance;
    } else {
      dial += distance;
    }

    dial = (dial + 100) % 100;

    if (dial == 0)
      ++zero_count;
  }

  cout << zero_count;
  return 0;
}
