#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Distance = double;
using PointId = int;

class Point3D {
private:
  int x, y, z;

public:
  Point3D(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Distance distance(Point3D &other) const {
    return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) +
                pow(this->z - other.z, 2));
  }
  int getX() { return x; }
};

class DSU {
private:
  vector<int> size;
  vector<int> parent;

public:
  DSU(int n) {
    size.resize(n, 1);
    parent.resize(n, 0);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find_set(int v) {
    if (parent[v] == v)
      return v;
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b)
      return;

    if (size[b] > size[a])
      swap(a, b);

    parent[b] = a;
    size[a] += size[b];
  }

  int get_set_size(int v) {
    v = find_set(v);
    return size[v];
  }
};

int main() {
  ifstream infile("input.txt");
  string line;
  int x, y, z;
  char _sep;

  vector<Point3D> points;
  /*
   * order pairs of points by their distance in priority_queue
   * store actual points in vector
   */
  priority_queue<pair<Distance, pair<PointId, PointId>>,
                 vector<pair<Distance, pair<PointId, PointId>>>, greater<>>
      pq;

  while (getline(infile, line)) {
    stringstream ss(line);
    ss >> x >> _sep >> y >> _sep >> z;

    Point3D point(x, y, z);
    PointId id = points.size();

    for (PointId i = 0; i < points.size(); ++i) {
      Distance d = points[i].distance(point);
      pq.push({d, {i, id}});
    }

    points.push_back(point);
  }

  /*
   * Use disjoint set union to join circuits and calculate size (union by size)
   */
  DSU circuits(points.size());

  pair<int, int> last_x;

  while (!pq.empty()) {
    PointId a = pq.top().second.first;
    PointId b = pq.top().second.second;
    pq.pop();

    if (circuits.find_set(a) == circuits.find_set(b))
      continue;

    circuits.union_sets(a, b);
    last_x = {points[a].getX(), points[b].getX()};
  }

  cout << last_x.first * last_x.second;

  return 0;
}
