#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
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

  /*
   * Instead of using a set to store particle indices,
   * use a map to store number of ways of particle reaching each point.
   */

  unordered_map<int, unsigned long long> beam_idx;
  const int width = grid[0].length();

  for (const string &line : grid) {
    unordered_map<int, unsigned long long> next_beam_idx;

    for (int i = 0; i < width; ++i) {
      if (line[i] == EMPTY) {
        next_beam_idx[i] += beam_idx[i];
      } else if (line[i] == SOURCE) {
        next_beam_idx[i] = 1;
        break;
      } else {
        // SPLITTER
        if (i > 0)
          next_beam_idx[i - 1] += beam_idx[i];
        if (i < width - 1)
          next_beam_idx[i + 1] += beam_idx[i];
      }
    }

    swap(next_beam_idx, beam_idx);
  }

  unsigned long long total_timelines = 0;

  // sum total timelines in final row

  for (const auto &[_, timelines] : beam_idx) {
    total_timelines += timelines;
  }

  cout << total_timelines;

  return 0;
}
