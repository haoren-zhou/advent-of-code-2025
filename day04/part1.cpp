#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr char EMPTY = '.';
constexpr char PAPER = '@';

inline bool check_range(const int index, const int size) {
  return index >= 0 && index < size;
}

int main() {
  ifstream infile("input.txt");
  string line;
  vector<vector<char>> grid;

  while (getline(infile, line)) {
    vector<char> row;
    row.reserve(line.length());
    for (const char &c : line) {
      assert(c == EMPTY || c == PAPER);
      row.push_back(c);
    }
    grid.push_back(row);
  }

  const int nrows = grid.size();
  assert(nrows > 0);
  const int ncols = grid[0].size();

  constexpr int adj[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                             {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  int result = 0;

  for (int r = 0; r < nrows; ++r) {
    for (int c = 0; c < ncols; ++c) {
      if (grid[r][c] == EMPTY)
        continue;
      int adj_paper = 0;
      for (const auto &[dr, dc] : adj) {
        const int adjr = r + dr, adjc = c + dc;
        if (check_range(adjr, nrows) && check_range(adjc, ncols)) {
          if (grid[adjr][adjc] == PAPER)
            ++adj_paper;
        }
      }

      if (adj_paper < 4)
        ++result;
    }
  }

  cout << result;

  return 0;
}
