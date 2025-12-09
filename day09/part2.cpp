#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Tile {
  int x;
  int y;
  Tile(int x, int y) : x{x}, y{y} {}
};

struct Edge {
  Tile start;
  Tile end;
  Edge(Tile start, Tile end) : start{start}, end{end} {}
};

long long area(const Tile &a, const Tile &b) {
  int width = abs(a.x - b.x) + 1;
  int height = abs(a.y - b.y) + 1;
  return 1LL * width * height;
}

/*
 * Checks if value v is within range (low, high), returning an int representing
 * which segment of the number line v lies in.
 *
 * @param range The range of values (low, high) to check
 * @param v The value to check
 * @return -1 if v <= low, 0 if v in (low, high), 1 if v >= high
 */
int compare_range(const pair<int, int> &range, const int v) {
  if (v <= range.first)
    return -1;
  if (v >= range.second)
    return 1;
  return 0;
}

bool check_rectangle(const Tile &a, const Tile &b, const Edge &e) {
  auto x_range =
      a.x > b.x ? pair<int, int>(b.x, a.x) : pair<int, int>(a.x, b.x);
  auto y_range =
      a.y > b.y ? pair<int, int>(b.y, a.y) : pair<int, int>(a.y, b.y);

  // check if edge vertices are within rectangle
  if (compare_range(x_range, e.start.x) == 0 &&
      compare_range(y_range, e.start.y) == 0)
    return false;
  if (compare_range(x_range, e.end.x) == 0 &&
      compare_range(y_range, e.end.y) == 0)
    return false;

  // check if edge cuts rectangle vertically
  if (compare_range(x_range, e.start.x) == 0 &&
      compare_range(x_range, e.end.x) == 0) {
    return compare_range(y_range, e.start.y) == compare_range(y_range, e.end.y);
  }

  // check if edge cuts rectangle horizontally
  if (compare_range(y_range, e.start.y) == 0 &&
      compare_range(y_range, e.end.y) == 0) {
    return compare_range(x_range, e.start.x) == compare_range(x_range, e.end.x);
  }

  return true;
}

int main() {
  ifstream infile("input.txt");
  string line;

  int x, y;
  char _sep;

  vector<Tile> tiles;
  vector<Edge> edges;
  long long max_area = 0;

  while (getline(infile, line)) {
    stringstream ss(line);
    ss >> x >> _sep >> y;
    Tile tile(x, y);
    if (!tiles.empty())
      edges.emplace_back(tiles.back(), tile);
    tiles.push_back(tile);
  }
  // join last and first tile
  edges.emplace_back(tiles.back(), tiles[0]);

  const int num_tiles = tiles.size();

  for (int i = 1; i < num_tiles; ++i) {
    for (int j = 0; j < i; ++j) {
      Tile a = tiles[i];
      Tile b = tiles[j];

      bool valid = true;
      for (const auto &e : edges) {
        if (!check_rectangle(a, b, e)) {
          valid = false;
          break;
        }
      }
      if (valid)
        max_area = max(max_area, area(a, b));
    }
  }

  cout << max_area;

  return 0;
}
