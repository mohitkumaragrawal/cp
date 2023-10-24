#include <bits/stdc++.h>

#include <algorithm>
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

  vector<array<ll, 3>> v(n);
  vector<ll> comp;
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < 3; ++j) {
      cin >> v[i][j];
      if (j != 2) comp.push_back(v[i][j]);
    }
  }

  sort(all(comp));
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < 2; ++j)
      v[i][j] = lower_bound(all(comp), v[i][j]) - begin(comp);
  }

  ll mx = comp.size();

  vector<ll> dp(mx + 1);

  sort(all(v), [](auto &x, auto &y) { return x[1] < y[1]; });
  ll j = 0;

  for (ll day = 0; day <= mx; ++day) {
    if (day > 0) dp[day] = dp[day - 1];
    while (j < n && v[j][1] == day) {
      auto [s, e, p] = v[j];
      j++;
      if (s > 0)
        ckmax(dp[e], p + dp[s - 1]);
      else
        ckmax(dp[e], p);
    }
  }

  cout << dp[mx] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}
