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

const ll N = 2e5 + 100;

int n, m;
ll values[N];

vector<ll> adj[N], adj_rev[N];

vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
  used[v] = true;

  for (auto u : adj[v])
    if (!used[u]) dfs1(u);

  order.push_back(v);
}

void dfs2(int v) {
  used[v] = true;
  component.push_back(v);

  for (auto u : adj_rev[v])
    if (!used[u]) dfs2(u);
}

void solve(ll _t) {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> values[i];
    adj[i].clear();
    adj_rev[i].clear();
  }

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;

    u--, v--;

    adj[u].push_back(v);
    adj_rev[v].push_back(u);
  }

  order.clear();
  used.assign(n, false);

  for (int i = 0; i < n; i++)
    if (!used[i]) dfs1(i);

  reverse(order.begin(), order.end());

  vector<int> roots(n, 0);

  vector<int> root_nodes;
  vector<ll> node_val(n, 0), node_count(n, 0);

  used.assign(n, false);
  for (auto v : order)
    if (!used[v]) {
      dfs2(v);

      int root = component.front();

      ll tot = 0, cnt = 0;
      for (auto u : component) {
        roots[u] = root;

        tot += values[u];
        cnt++;
      }

      root_nodes.push_back(root);

      node_val[root] = tot;
      node_count[root] = cnt;

      // node_val.push_back(tot);
      // node_count.push_back(cnt);

      component.clear();
    }

  vector<vector<int>> adj_scc(n);
  for (int v = 0; v < n; v++)
    for (auto u : adj[v]) {
      int root_v = roots[v], root_u = roots[u];

      if (root_u != root_v) adj_scc[root_v].push_back(root_u);
    }

  for (int i = 0; i < n; ++i) {
    sort(all(adj_scc[i]));
    adj_scc[i].erase(unique(all(adj_scc[i])), adj_scc[i].end());
  }

  vector<int> inorder(n, 0);

  for (int i : root_nodes) {
    for (int j : adj_scc[i]) inorder[j]++;
  }

  queue<int> q;
  for (int i : root_nodes)
    if (inorder[i] == 0) q.push(i);

  vector<int> torder;
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    torder.push_back(v);

    for (int u : adj_scc[v]) {
      inorder[u]--;
      if (inorder[u] == 0) q.push(u);
    }
  }

  auto max_pair = [](pair<ll, ll> &p1, pair<ll, ll> &p2) {
    if (p2.first > p1.first) {
      p1 = p2;
    } else if (p2.first == p1.first) {
      ckmin(p1.second, p2.second);
    }
  };

  vector<pair<ll, ll>> dp(n);
  for (int i : root_nodes) {
    dp[i] = {node_count[i], node_val[i]};
  }

  for (int i : torder) {
    for (int j : adj_scc[i]) {
      pair<ll, ll> new_val = {dp[i].first + node_count[j],
                              dp[i].second + node_val[j]};

      max_pair(dp[j], new_val);
    }
  }

  pair<ll, ll> ans = {0, 0};
  for (int i : root_nodes) {
    max_pair(ans, dp[i]);
  }

  cout << ans.first << " " << ans.second << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}