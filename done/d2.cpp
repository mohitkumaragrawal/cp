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

ll f(vector<ll> a, vector<ll> b) {
  sort(all(a));
  sort(all(b));
  ll n = a.size();
  ll j = 0;

  ll ans = 0;
  for (ll i = 0; i < n; ++i) {
    while (j < n && b[j] <= a[i]) j++;
    if (j >= n) break;
    ans++;
    j++;
  }
  return ans;
}

void solve(ll _t) {
  ll n, m;
  cin >> n >> m;
  vector<ll> a(n), b(n);
  a[0] = 1e16;

  for (ll i = 1; i < n; ++i) cin >> a[i];
  cin >> b;
  sort(all(b));

  ll t = f(a, b);

  a[0] = m;
  ll tt = f(a, b);
  if (tt == t + 1) {
    ll ans = (n - t - 1) * m;
    cout << ans << endl;
    return;
  }

  ll lo = 1, hi = m;
  while (hi > lo) {
    ll mid = (lo + hi) / 2;

    a[0] = mid;
    ll k = f(a, b);

    dbg(mid, k);

    if (k == t) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  dbg(hi, t);
  ll tot = n * m;
  ll ans = (t + 1) * (hi - 1) + (t * (m - hi + 1));
  ans = tot - ans;
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
