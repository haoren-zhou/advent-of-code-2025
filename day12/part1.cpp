#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream infile("input.txt");
  string id;
  vector<int> areas;

  for (int s = 0; s < 6; ++s) {
    infile >> id;
    vector<string> shape;
    shape.resize(3);
    infile >> shape[0] >> shape[1] >> shape[2];
    int area = 0;
    for (const auto &row : shape) {
      for (const auto &c : row)
        if (c == '#')
          ++area;
    }
    areas.push_back(area);
  }

  string line;
  int trivially_possible = 0, impossible = 0, unknown = 0;

  while (getline(infile, line)) {
    if (line.length() == 0)
      continue;
    int w, h;
    char _sep;
    stringstream ss(line);
    ss >> w >> _sep >> h >> _sep;

    vector<int> shape_quantity(6, 0);
    int total_shapes = 0, area_required = 0;
    for (int s = 0; s < 6; ++s) {
      ss >> shape_quantity[s];
      total_shapes += shape_quantity[s];
      area_required += shape_quantity[s] * areas[s];
    }

    if (total_shapes <= (w / 3) * (h / 3)) {
      trivially_possible++;
      continue;
    }
    if (area_required > w * h) {
      impossible++;
      continue;
    }
    unknown++;
  }

  cout << "Trivilly Possible: " << trivially_possible << "\n";
  cout << "Impossible: " << impossible << "\n";
  cout << "Unknown: " << unknown << "\n";
  return 0;
}
