#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr char SOURCE = 'S';
constexpr char EMPTY = '.';
constexpr char SPLITTER = '^';

int main() {
  ifstream infile("input.txt");
  string line;

  vector<string> grid;

  while (getline(infile, line)) {
    grid.push_back(line);
  }

  set<int> beam_idx;
  const int width = grid[0].length();

  int split_count = 0;

  for (const string &line : grid) {
    set<int> next_beam_idx;

    for (int i = 0; i < width; ++i) {
      if (line[i] == EMPTY) {
        if (beam_idx.count(i))
          next_beam_idx.insert(i);
      } else if (line[i] == SOURCE) {
        next_beam_idx.insert(i);
        break;
      } else {
        // SPLITTER
        if (beam_idx.count(i)) {
          ++split_count;
          if (i > 0)
            next_beam_idx.insert(i - 1);
          if (i < width - 1)
            next_beam_idx.insert(i + 1);
        }
      }
    }

    swap(next_beam_idx, beam_idx);
  }

  cout << split_count;
  return 0;
}
