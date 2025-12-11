#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

const string START = "svr";
const string FFT = "fft";
const string DAC = "dac";
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
      adj[source].insert(out);
    }
  }
  const vector<string> topo_order = topological_sort<string>(adj);
  string first = DAC, second = FFT;
  if (find(topo_order.begin(), topo_order.end(), FFT) <
      find(topo_order.begin(), topo_order.end(), DAC))
    swap(first, second);

  unordered_map<string, unsigned long long> ways;
  ways[START] = 1;

  for (const string &n : topo_order) {
    if (n == first)
      break;
    for (const string &out : adj[n]) {
      ways[out] += ways[n];
    }
  }
  const unsigned long long first_ways = ways[first];
  ways.clear();
  ways[first] = 1;

  for (const string &n : topo_order) {
    if (n == second)
      break;
    for (const string &out : adj[n]) {
      ways[out] += ways[n];
    }
  }
  const unsigned long long second_ways = ways[second];
  ways.clear();
  ways[second] = 1;

  for (const string &n : topo_order) {
    if (n == END)
      break;
    for (const string &out : adj[n]) {
      ways[out] += ways[n];
    }
  }

  cout << first_ways * second_ways * ways[END];

  return 0;
}
