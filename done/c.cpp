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

  sort(all(a));

  ll ans = 0;
  ll c = 0;
  ll l = 0, r = n - 1;

  while (r >= l) {
    if (l == r) {
      if (c >= a[l]) {
        ans++;
        break;
      }

      if (a[l] == 1) {
        ans++;
        break;
      }

      ll x = (a[l] - c) / 2;

      ans += x + 1;
      c += x;

      a[l] -= (x + c);

      ans += a[l];

      break;
    }

    if (c + a[l] <= a[r]) {
      c += a[l];
      ans += a[l];
      l++;

      if (c == a[r]) {
        c = 0;
        r--;
        ans++;
      }

      continue;
    }

    ll need = a[r] - c;
    a[l] -= need;
    ans += need + 1;
    c = 0;

    if (a[l] == 0) l++;
    r--;
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}