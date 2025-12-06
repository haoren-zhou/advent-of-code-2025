#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream infile("input.txt");
  string line;

  vector<vector<unsigned long long>> numbers;

  unsigned long long total = 0;

  while (getline(infile, line)) {
    if (line[0] == '*' || line[0] == '+') {
      int i = 0;
      for (char &c : line) {
        if (c == '*') {
          total += accumulate(numbers[i].begin(), numbers[i].end(), 1ULL,
                              multiplies<>());
        } else if (c == '+') {
          total += accumulate(numbers[i].begin(), numbers[i].end(), 0ULL);
        } else
          continue;

        ++i;
      }
      break;
    }
    stringstream ss(line);

    int i = 0;
    unsigned long long n;

    while (ss >> n) {
      if (i >= numbers.size())
        numbers.push_back({n});
      else
        numbers[i].push_back(n);

      ++i;
    }
  }

  cout << total;

  return 0;
}
