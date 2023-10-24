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
  ll n;
  cin >> n;

  vector<ll> freq(n + 10);
  for (ll i = 0; i < n; ++i) {
    ll x;
    cin >> x;
    ckmin(x, n + 9);
    freq[x]++;
  }

  ll mex = 0;
  while (freq[mex] != 0) mex++;

  n = mex;

  if (mex == 0) {
    cout << 0 << endl;
    return;
  }

  vector<vector<ll>> dp(n, vector<ll>(n + 1));
  for (ll j = 0; j <= n; ++j) dp[0][j] = (freq[0] - 1) * j;

  for (ll i = 1; i < n; ++i) {
    for (ll j = 0; j <= n; ++j) {
      dp[i][j] = dp[i - 1][j];
      ll other = (freq[i] - 1) * j + i + dp[i - 1][i];
      ckmin(dp[i][j], other);
    }
  }
  cout << dp[n - 1][n] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
