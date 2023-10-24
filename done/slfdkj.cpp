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
  ll n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  vector<ll> l(k), r(k);
  cin >> l >> r;

  for (auto &x : l) x--;
  for (auto &x : r) x--;

  ll q;
  cin >> q;

  vector<ll> diff(n + 1);
  auto inc = [&](ll l, ll r) {
    if (l > r) swap(l, r);
    diff[l]++;
    diff[r + 1]--;
  };

  while (q--) {
    ll x;
    cin >> x;
    x--;

    ll idx = lower_bound(all(r), x) - begin(r);
    ll y = l[idx] + r[idx] - x;

    inc(x, y);
  }

  for (ll i = 1; i < n; ++i) diff[i] += diff[i - 1];

  for (ll i = 0; i < n; ++i) {
    if (diff[i] % 2 == 0) continue;

    ll idx = lower_bound(all(r), i) - begin(r);
    ll j = l[idx] + r[idx] - i;
    if (j > i) swap(s[i], s[j]);
  }

  cout << s << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
