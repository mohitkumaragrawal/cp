#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<int>> v(n + 1, vector<int>(m + 1));
  vector<pair<int, int>> f;
  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    f.push_back({x, y});
  }

  int R;
  cin >> R;

  int T;
  cin >> T;

  long long r = R * 1LL * T;

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      long long min_dist = 1e10;

      for (auto [x, y] : f) {
        long long d = (x - i) * 1LL * (x - i) + (y - j) * 1LL * (y - j);
        min_dist = min(min_dist, d);
      }

      if (min_dist <= r * r) {
        v[i][j] = 1;
      }
    }
  }

  int ans = 0;

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (v[i][j] == 0) ans++;
    }
  }

  cout << ans << endl;
}