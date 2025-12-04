#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

constexpr int JOLTAGE_SIZE = 12;
using J = unsigned long long;

int main() {
  ifstream infile("input.txt");
  string bank;
  J total_output = 0;

  while (getline(infile, bank)) {
    assert(bank.length() >= JOLTAGE_SIZE);

    J output = 0;
    int right_index = -1;

    for (int c = 0; c < JOLTAGE_SIZE; ++c) {
      int max_jolt = -1;

      for (int i = right_index + 1; i <= bank.length() - JOLTAGE_SIZE + c;
           ++i) {
        int joltage = bank[i] - '0';
        if (joltage > max_jolt) {
          max_jolt = joltage;
          right_index = i;
        }
      }

      output = output * 10 + max_jolt;
    }

    total_output += output;
  }
  cout << total_output;
  return 0;
}
