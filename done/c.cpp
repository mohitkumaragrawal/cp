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

  vector<ll> a(n);
  cin >> a;

  map<ll, ll> left_idx, right_idx;
  for (ll i = 0; i < n; ++i) {
    ll x = a[i];

    if (left_idx.count(x)) {
      left_idx[x] = min(left_idx[x], i);
      right_idx[x] = max(right_idx[x], i);
    } else {
      left_idx[x] = i;
      right_idx[x] = i;
    }
  }

  ll cnt = 0;
  ll ans = 0;

  for (ll i = 0; i < n; ++i) {
    if (i == left_idx[a[i]]) {
      cnt++;
    }
    if (i == right_idx[a[i]]) {
      ans += cnt;
    }
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
