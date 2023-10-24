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

/*

Things to look out:
1. This questions not only asks to figure out the negative cycle
but also wants to know whether or not that affects the path from 1->n.

2. In some cases, it contains a negative cycle, but does not affect our
main path, like if we go to there, there doesn't exist any path to n;

3. So the main idea was: let's say there are some node (k) get affected by
the negative cycle, then if the  final node is reachable by the affected
node k, and the k is also reachable by the initial node, then there exists
a path which contains a negative cycle between the path from inital node
to the final node

*/

void solve(ll _t) {
  int n, m;
  cin >> n >> m;
  vector<array<ll, 3>> edges(m);
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--, c = -c;
    adj[b].push_back(a);
    edges[i][0] = a, edges[i][1] = b, edges[i][2] = c;
  }
  vector<bool> vis(n);
  auto dfs = [&](auto &&self, int cur) -> void {
    vis[cur] = true;
    for (int it : adj[cur]) {
      if (!vis[it]) self(self, it);
    }
  };
  dfs(dfs, n - 1);

  const ll INF = 1e18;
  vector<ll> dist(n, INF);
  dist[0] = 0;
  auto relax_edges = [&]() -> void {
    for (auto [a, b, c] : edges) {
      if (dist[a] == INF) continue;
      if (dist[b] > dist[a] + c) {
        dist[b] = dist[a] + c;
      }
    };
  };
  for (int i = 0; i < n - 1; ++i) relax_edges();
  bool neg_cycle = false;
  auto prev = dist;
  relax_edges();

  for (int i = 0; i < n; ++i) {
    if (prev[i] != dist[i] && vis[i]) {
      neg_cycle = true;
      break;
    }
  }
  if (neg_cycle) {
    cout << -1 << endl;
    return;
  }
  cout << -dist[n - 1] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
