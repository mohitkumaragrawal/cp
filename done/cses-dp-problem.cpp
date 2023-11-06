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
  string a, b;
  cin >> a >> b;
  int n = a.size(), m = b.size();

  // dp[i][j] = minimum number of moves

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e7));

  // if last character matches dp[i][j] = dp[i-1][j-1]
  // else
  //  we can replace the last character dp[i][j] = 1 + dp[i-1][j-1]
  //  we can insert a new character same as last character, dp[i][j] =
  //  dp[i][j-1] + 1
  //  we can delete the last character, dp[i][j] = 1 + dp[i-1][j]

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0 && j == 0) {
        dp[i][j] = 0;
        continue;
      }
      if (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = 1 + dp[i - 1][j - 1];
        }
      }
      if (j > 0) {
        ckmin(dp[i][j], dp[i][j - 1] + 1);
      }
      if (i > 0) {
        ckmin(dp[i][j], 1 + dp[i - 1][j]);
      }
    }
  }

  cout << dp[n][m] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}