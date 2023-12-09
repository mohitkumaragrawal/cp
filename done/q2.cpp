#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> parent, siz;
  int components;
  void init(int n) {
    parent.resize(n);
    siz.resize(n);
    components = n;
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      siz[i] = 1;
    }
  }
  int find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find(parent[x]);
  }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    components--;
    if (siz[x] < siz[y]) swap(x, y);
    parent[y] = x;
    siz[x] += siz[y];
  }
};

const int MOD = 1e9 + 7;

int solution(int len, int p, vector<vector<int>> substrings) {
  DSU dsu;
  dsu.init(len);

  for (auto x : substrings) {
    int l = x[0] - 1, r = x[1] - 1;
    while (r > l) {
      dsu.merge(l, r);
      r--;
      l++;
    }
  }

  int power = dsu.components;
  long long ans = 1;

  for (int i = 0; i < power; ++i) {
    ans = (ans * 26) % MOD;
  }
  return int(ans);
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  int n;
  cin >> n;

  int p;
  cin >> p;

  vector<vector<int>> s;
  for (int i = 0; i < p; ++i) {
    int l, r;
    cin >> l >> r;
    vector<int> v = {l, r};
    s.push_back(v);
  }
  cout << solution(n, p, s) << endl;
}