#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Tile {
  int x;
  int y;
  Tile(int x, int y) : x{x}, y{y} {}
};

long long area(const Tile &a, const Tile &b) {
  int width = abs(a.x - b.x) + 1;
  int height = abs(a.y - b.y) + 1;
  return 1LL * width * height;
}

int main() {
  ifstream infile("input.txt");
  string line;

  int x, y;
  char _sep;

  vector<Tile> tiles;
  long long max_area = 0;

  while (getline(infile, line)) {
    stringstream ss(line);
    ss >> x >> _sep >> y;
    Tile tile(x, y);
    for (const auto &t : tiles)
      max_area = max(max_area, area(t, tile));

    tiles.push_back(tile);
  }

  cout << max_area;

  return 0;
}
