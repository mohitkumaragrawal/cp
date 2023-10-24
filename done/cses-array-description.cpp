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
  ll n, m;
  cin >> n >> m;

  vector<ll> a(n);
  cin >> a;

  const ll MOD = 1e9 + 7;

  vector<vector<ll>> dp(n, vector<ll>(m + 2, 0));
  if (a[0] == 0) {
    fill(all(dp[0]), 1LL);
    dp[0][0] = 0;
    dp[0][m + 1] = 0;
  } else {
    dp[0][a[0]] = 1;
  }

  for (ll i = 1; i < n; ++i) {
    if (a[i] == 0) {
      for (ll j = 1; j <= m; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i - 1][j + 1] + dp[i - 1][j - 1];
        dp[i][j] %= MOD;
      }
    } else {
      ll x = a[i];
      dp[i][x] = dp[i - 1][x] + dp[i - 1][x + 1] + dp[i - 1][x - 1];
      dp[i][x] %= MOD;
    }
  }

  ll ans = 0;
  for (ll j = 1; j <= m; ++j) {
    ans = (ans + dp[n - 1][j]) % MOD;
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}
