#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int MAX_LIGHTS = 64;

using namespace std;
int main() {
  ifstream infile("input.txt");
  string line;
  int total_press = 0;

  while (getline(infile, line)) {
    stringstream ss(line);
    string lights, button;
    char _sep;
    int light;

    ss >> lights;
    const int num_lights = lights.length() - 2;
    lights = lights.substr(1, num_lights);

    bitset<MAX_LIGHTS> target;
    for (int i = 0; i < num_lights; ++i) {
      if (lights[i] == '#')
        target.set(i);
    }

    vector<vector<int>> buttons;
    while (ss >> button) {
      if (button[0] != '(')
        continue;
      stringstream button_stream(button);
      vector<int> toggles;
      while (button_stream >> _sep >> light) {
        toggles.push_back(light);
      }
      buttons.push_back(toggles);
    }

    const int num_buttons = buttons.size();
    int min_press = num_buttons;

    for (int bitmask = 0; bitmask < pow(2, num_buttons); ++bitmask) {
      bitset<MAX_LIGHTS> tlights;
      int press_count = 0;
      for (int b = 0; b < num_buttons; ++b) {
        if ((bitmask >> b) & 1) {
          ++press_count;
          for (const int &l : buttons[b])
            tlights.flip(l);
        }
      }
      if (tlights == target)
        min_press = min(min_press, press_count);
    }

    total_press += min_press;
  }

  cout << total_press;

  return 0;
}
