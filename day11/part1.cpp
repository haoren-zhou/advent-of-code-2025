#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

template <typename T>
vector<T> topological_sort(unordered_map<T, unordered_set<T>> adj) {
  vector<T> result;
  result.reserve(adj.size());
  unordered_map<T, unordered_set<T>> adj_in;
  for (const auto &[source, outs] : adj) {
    for (const T &out : outs) {
      adj_in[out].insert(source);
    }
  }
  queue<T> no_in;
  for (const auto &[source, _] : adj) {
    if (adj_in[source].empty()) {
      no_in.push(source);
    }
  }

  while (!no_in.empty()) {
    T n = no_in.front();
    no_in.pop();
    result.push_back(n);

    const auto outs = adj[n];
    for (const T &out : outs) {
      adj[n].erase(out);
      adj_in[out].erase(n);
      if (adj_in[out].empty())
        no_in.push(out);
    }
  }

  for (const auto &[source, outs] : adj) {
    if (!outs.empty())
      throw invalid_argument("graph has cycle");
  }
  return result;
}

const string START = "you";
const string END = "out";

int main() {
  ifstream infile("input.txt");
  string line;

  unordered_map<string, unordered_set<string>> adj;

  while (getline(infile, line)) {
    stringstream ss(line);
    string source, out;

    ss >> source;
    source = source.substr(0, 3);

    while (ss >> out) {
      if (out == START) {
        adj.erase(source);
        break;
      }
      adj[source].insert(out);
    }
  }
  const vector<string> topo_order = topological_sort<string>(adj);
  unordered_map<string, int> ways;
  ways[START] = 1;

  for (const string &n : topo_order) {
    for (const string &out : adj[n]) {
      ways[out] += ways[n];
    }
  }

  cout << ways[END];

  return 0;
}
