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
  int n, m, q;
  cin >> n >> m >> q;
  const ll INF = 1e18;
  vector<vector<ll>> mat(n, vector<ll>(n, INF));
  for (int i = 0; i < n; ++i) mat[i][i] = 0;
  for (int i = 0; i < m; ++i) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    ckmin(mat[a][b], c);
    ckmin(mat[b][a], c);
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        ckmin(mat[i][j], mat[i][k] + mat[k][j]);
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    ll ans = mat[a - 1][b - 1];
    if (ans == INF)
      cout << -1 << endl;
    else
      cout << ans << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
