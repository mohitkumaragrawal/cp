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

  string s;
  cin >> s;

  vector<int> op(n);
  vector<int> pressed(n);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int v = s[i] - '0';
    if (op[i] & 1) {
      v ^= 1;
    }
    if (v == 1) {
      ans++;
      pressed[i] = 1;
      for (int j = i; j < n; j += (i + 1)) {
        op[j]++;
      }
    }
  }

  int q;
  cin >> q;

  ll total = 0;

  for (int i = 0; i < q; ++i) {
    int x;
    cin >> x;
    x--;

    if (pressed[x] == 1) {
      pressed[x] = 0;
      ans--;
      total += ans;
    } else {
      pressed[x] = 1;
      ans++;
      total += ans;
    }
  }

  OUT(_t) << total << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
