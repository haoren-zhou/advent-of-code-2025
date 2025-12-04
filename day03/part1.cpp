#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
  ifstream infile("input.txt");
  string bank;
  int total_output = 0;
  while (getline(infile, bank)) {
    int first = 0, first_index = -1, second = 0;
    for (int i = 0; i < bank.length() - 1; ++i) {
      int joltage = bank[i] - '0';
      if (joltage > first) {
        first = joltage;
        first_index = i;
      }
    }
    for (int i = first_index + 1; i < bank.length(); ++i) {
      int joltage = bank[i] - '0';
      second = max(second, joltage);
    }

    int output = first * 10 + second;
    total_output += output;
  }
  cout << total_output;
  return 0;
}
