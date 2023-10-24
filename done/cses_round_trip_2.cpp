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
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
  }

  vector<bool> vis(n), ancestor(n);
  vector<int> parent(n);

  // find the back edge
  int back_from = -1, back_to = -1;

  auto dfs = [&](auto &&dfs, int cur, int par) -> void {
    parent[cur] = par;

    vis[cur] = true;
    ancestor[cur] = true;

    for (int it : adj[cur]) {
      if (vis[it]) {
        if (ancestor[it]) {
          // found a back-edge from cur->it
          back_from = cur;
          back_to = it;
        }
        continue;
      }

      dfs(dfs, it, cur);
    }

    ancestor[cur] = false;
  };

  for (int i = 0; i < n; ++i) {
    if (!vis[i]) dfs(dfs, i, -1);
  }

  if (back_from == -1) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  vector<int> cycle;
  cycle.push_back(back_from + 1);

  while (back_from != back_to) {
    back_from = parent[back_from];
    cycle.push_back(back_from + 1);
  }
  cycle.push_back(cycle[0]);
  reverse(all(cycle));
  cout << cycle.size() << endl;
  cout << cycle << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
