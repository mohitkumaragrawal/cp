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

int solve(int n, vector<int> a) {
  int ans = 0;
  int f[20];
  for (int j = 0; j < (1 << n); ++j) {
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; ++i) {
      if (!(j & (1 << i))) continue;
      for (int j = 0; j < 20; ++j) {
        if (a[i] & (1 << j)) {
          f[j]++;
        }
      }
    }

    int mx = 0;
    for (int j = 0; j < 20; ++j) mx = max(mx, f[j]);
    ans += mx;
  }
  return ans;
}

void solve(ll _t) {
  int n;
  cin >> n;

  vector<int> a(n);
  cin >> a;

  cout << solve(n, a) << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}