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

  vector<array<ll, 3>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    edges[i] = {a, b, c};
  }

  vector<ll> p(n, -1), d(n);
  int x = -1;
  for (int i = 0; i < n; ++i) {
    x = -1;
    bool any = false;
    for (auto [u, v, w] : edges) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
        x = v;
        any = true;
      }
    }

    if (!any) break;
  }

  if (x == -1) {
    cout << "NO" << endl;
  } else {
    int y = x;
    for (int j = 0; j < n; ++j) {
      y = p[y];
    }
    x = y;
    vector<int> path;
    do {
      path.push_back(y + 1);
      y = p[y];
    } while (y != x);
    path.push_back(y + 1);
    cout << "YES" << endl;
    reverse(all(path));
    cout << path << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
