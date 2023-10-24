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

  vector<ll> idx(n + 1);
  for (ll i = 0; i < n; ++i) idx[a[i]] = i;

  ll ans = 1;
  for (ll i = 1; i < n; ++i) {
    if (idx[i + 1] < idx[i]) ans++;
  }

  while (m--) {
    ll i, j;
    cin >> i >> j;
    i--, j--;

    set<ll> st = {a[i], a[j], a[i] - 1, a[j] - 1};
    for (ll t : st) {
      if (t < 1 || t >= n) continue;
      if (idx[t + 1] < idx[t]) ans--;
    }

    swap(a[i], a[j]);

    idx[a[i]] = i;
    idx[a[j]] = j;

    for (ll t : st) {
      if (t < 1 || t >= n) continue;
      if (idx[t + 1] < idx[t]) ans++;
    }

    cout << ans << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
