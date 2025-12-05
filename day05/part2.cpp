#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using ID = unsigned long long;

int main() {
  ifstream infile("input.txt");
  string line;
  vector<pair<ID, ID>> ranges;

  while (getline(infile, line)) {
    if (line.length() == 0)
      break;
    stringstream ss(line);
    ID start, end;
    char _sep;

    ss >> start;
    ss >> _sep;
    ss >> end;

    ranges.emplace_back(start, end);
  }

  sort(ranges.begin(), ranges.end());

  unsigned long long fresh = 0;
  ID right = 0;

  for (const auto &[start, end] : ranges) {
    if (end <= right)
      continue;
    if (start > right) {
      fresh += (end - start + 1);
    } else {
      fresh += (end - right);
    }
    right = end;
  }

  cout << fresh;

  return 0;
}
