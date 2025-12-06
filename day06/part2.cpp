#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream infile("input.txt");
  string line, operations;

  vector<string> lines;

  unsigned long long total = 0;

  while (getline(infile, line)) {
    if (line[0] == '*' || line[0] == '+') {
      operations = line;
      break;
    }
    lines.push_back(line);
  }

  const int math_rows = lines.size();
  char current_operation;
  unsigned long long acc = 0;

  for (int i = 0; i < operations.length(); ++i) {
    // loop through columns of input
    if (operations[i] == '*') {
      total += acc;
      acc = 1;
      current_operation = '*';
    } else if (operations[i] == '+') {
      total += acc;
      acc = 0;
      current_operation = '+';
    }

    unsigned long long n = 0;
    bool blank_column =
        true; // flag to check if column is empty to prevent multiplication by 0

    for (int r = 0; r < math_rows; ++r) {
      if (isdigit(lines[r][i])) {
        blank_column = false;
        n = n * 10 + lines[r][i] - '0'; // build input number from column
      }
    }

    if (blank_column)
      continue;

    if (current_operation == '*') {
      acc *= n;
    } else {
      acc += n;
    }
  }

  total += acc;

  cout << total;

  return 0;
}
