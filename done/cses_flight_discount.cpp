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
  int n, m;
  cin >> n >> m;
  vector<vector<pll>> adj(2 * n);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].push_back({b, c});
    adj[a + n].push_back({b + n, c});
    adj[a].push_back({b + n, (c / 2)});
  }

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  vector<bool> vis(2 * n, false);

  pq.emplace(0, 0);

  vector<ll> d(2 * n, 1e18);
  d[0] = 0;
  while (!pq.empty()) {
    auto [dist, u] = pq.top();
    if (u == 2 * n - 1) break;
    pq.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (auto [v, wt] : adj[u]) {
      if (d[v] > d[u] + wt) {
        d[v] = d[u] + wt;
        pq.emplace(d[v], v);
      }
    }
  }
  cout << d[2 * n - 1] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}
