#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define OUT(T) cout << "Case #" << T << ": "
#ifndef _DEBUG
#define endl '\n'
#endif
#ifdef _DEBUG
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
#define ckmin(x, y) x = min((x), (y))
#define ckmax(x, y) x = max((x), (y))

// clang-format off
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
// clang-format on

using ll = long long;
using lld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

void solve(ll _t) {
  int n, m;
  cin >> n >> m;
  vector<string> grid(n);
  for (int i = 0; i < n; ++i) cin >> grid[i];
  auto is_valid = [&](int i, int j) {
    if (i < 0 || i >= n) return false;
    if (j < 0 || j >= m) return false;
    if (grid[i][j] == '#') return false;
    return true;
  };
  int dx[] = {1, -1, 0, 0};
  int dy[] = {0, 0, 1, -1};
  char symbol[] = {'D', 'U', 'R', 'L'};
  vector<vector<int>> time(n, vector<int>(m, 1e6));
  queue<array<int, 3>> q;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'M') q.push({i, j, 0});
    }
  }
  while (!q.empty()) {
    auto [i, j, t] = q.front();
    q.pop();
    if (time[i][j] <= t) continue;
    time[i][j] = t;
    for (int dir = 0; dir < 4; ++dir) {
      int new_i = i + dx[dir], new_j = j + dy[dir];
      if (is_valid(new_i, new_j) && (t + 1) < time[new_i][new_j])
        q.push({new_i, new_j, t + 1});
    }
  }
  vector<vector<int>> direction(n, vector<int>(m, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'A') {
        direction[i][j] = 0;
        q.push({i, j, 0});
        break;
      }
    }
  }
  while (!q.empty()) {
    auto [i, j, tm] = q.front();
    q.pop();
    for (int dir = 0; dir < 4; ++dir) {
      int new_i = i + dx[dir], new_j = j + dy[dir];
      if (is_valid(new_i, new_j) && (tm + 1) < time[new_i][new_j] &&
          direction[new_i][new_j] == -1) {
        direction[new_i][new_j] = dir;
        q.push({new_i, new_j, tm + 1});
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] != '#' && (i == 0 || j == 0 || i == n - 1 || j == m - 1)) {
        if (direction[i][j] == -1) {
          continue;
        }
        string path;
        while (grid[i][j] != 'A') {
          int d = direction[i][j];
          path.push_back(symbol[d]);
          i = i - dx[d], j = j - dy[d];
        }
        reverse(all(path));
        cout << "YES" << endl;
        cout << path.size() << endl;
        cout << path << endl;
        return;
      }
    }
  }

  cout << "NO" << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
