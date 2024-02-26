#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define OUT(T) cout << "Case #" << T << ": "

#ifdef _DEBUG
#include "debugs.h"
#else
#define dbg(...)
#define endl '\n'
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
  vector<ll> h(n), a(n);
  cin >> h >> a;

  // vector<ll> dp(n + 1);
  // dp[0] = 0;

  // for (ll i = 1; i <= n; ++i) {
  //   dp[i] = 1;

  //   ll j = i - 1;
  //   for (ll t = 1; t < i; ++t) {
  //     ll time = h[i - 1] - h[t - 1];
  //     if (time >= a[i - 1]) {
  //       dp[i] = max(dp[i], 1 + dp[t]);
  //     }
  //   }
  // }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}