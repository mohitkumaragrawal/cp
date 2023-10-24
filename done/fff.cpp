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

  if (m == 1) {
    cout << 0 << endl;
  } else {
    cout << min(n + 1, m) << endl;
  }

  vector<ll> def(m);
  def[0] = m - 1;
  for (ll i = 1; i < m; ++i) def[i] = i - 1;

  vector<vector<ll>> ans(n, def);

  for (ll i = 1; i < min(m - 1, n); ++i) {
    for (ll j = 1; j <= m; ++j) {
      ans[i][j % m] = ans[i - 1][j - 1];
    }
  }

  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < m; ++j) {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
