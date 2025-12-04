#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

using ID = unsigned long long;

vector<ID> construct_invalids(const int block, const int len) {
  assert(len % block == 0);
  int repeat_count = len / block;
  int limit = pow(10, block);

  vector<ID> result;

  for (int seq = pow(10, block - 1); seq < limit; ++seq) {
    ID invalid = 0;
    for (int i = 0; i < repeat_count; ++i) {
      invalid = invalid * limit + seq;
    }
    result.push_back(invalid);
  }

  return result;
}

int main() {
  ifstream infile("input.txt");
  ID low, high;
  char _sep;

  set<ID> invalid_ids;

  while (infile >> low) {
    infile >> _sep;
    infile >> high;
    infile >> _sep;

    string low_str = to_string(low);
    string high_str = to_string(high);

    for (int id_len = low_str.length(); id_len <= high_str.length(); ++id_len) {
      for (int block = 1; block < id_len; ++block) {
        if (id_len % block == 0) {
          vector<ID> candidates = construct_invalids(block, id_len);
          for (const ID &invalid : candidates) {
            if (invalid >= low and invalid <= high)
              invalid_ids.insert(invalid);
          }
        }
      }
    }
  }

  cout << accumulate(invalid_ids.begin(), invalid_ids.end(), 0ULL);

  return 0;
}
