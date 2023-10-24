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

const ll N = 2e5 + 10;
ll n, k, a[N], mx;

bool check(ll m) {
  if (m < mx) return false;
  ll cnt = 0, sum = 0;
  for (ll i = 0; i < n; ++i) {
    if (sum + a[i] > m) {
      sum = a[i];
      cnt++;
    } else {
      sum += a[i];
    }
  }
  if (sum != 0) cnt++;
  return cnt <= k;
}

void solve(ll _t) {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    ckmax(mx, a[i]);
  }

  ll lo = 0, hi = 1e16;
  while (hi - lo > 1) {
    ll m = (lo + hi) / 2;
    if (check(m))
      hi = m;
    else
      lo = m;
  }
  cout << hi << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
