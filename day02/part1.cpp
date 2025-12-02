#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

using ID = unsigned long long;

ID range_invalid(ID low, ID high) {
  if (high < low)
    return 0;
  string low_str = to_string(low);
  string high_str = to_string(high);

  if (high_str.length() <= 1)
    return 0;
  if (low_str.length() % 2)
    return range_invalid(pow(10, low_str.length()), high);
  assert(low_str.length() % 2 == 0);

  if (high_str.length() % 2)
    return range_invalid(low, stoi(string(high_str.length() - 1, '9')));
  assert(high_str.length() % 2 == 0);

  int low_halflength = low_str.length() / 2;
  int high_halflength = high_str.length() / 2;

  ID first = low / (ID)pow(10, low_halflength);
  ID last = high / (ID)pow(10, high_halflength);
  ID range_sum = 0LL;

  ID i = first;
  for (int p = low_halflength; p <= high_halflength; ++p) {
    ID limit = pow(10, p);
    while (i < limit && i <= last) {
      ID id = i * (limit + 1);
      if (id >= low && id <= high)
        range_sum += id;
      ++i;
    }
  }

  return range_sum;
}

int main() {
  ifstream infile("input.txt");
  ID low, high;
  char _sep;
  ID sum_invalid = 0LL;

  while (infile >> low) {
    infile >> _sep;
    infile >> high;
    infile >> _sep;

    sum_invalid += range_invalid(low, high);
  }
  cout << sum_invalid;

  return 0;
}
