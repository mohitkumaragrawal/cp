#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m;
  cin >> n >> m;

  const int INF = 1e8;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cin >> a[i][j];
  }

  vector<vector<int>> b(n + 1, vector<int>(m + 1, -INF));

  int ans = -INF;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      int v = max(b[i + 1][j], b[i][j + 1]);
      ans = max(ans, v - a[i][j]);

      b[i][j] = v;
      b[i][j] = max(b[i][j], a[i][j]);
    }
  }

  cout << ans << endl;
}