#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void solve() {
  ll m, n, x, y, L;
  cin >> n >> m >> x >> y >> L;
  x--, y--;

  ll mx1 = n * m;
  ll mx2 = mx1 + (m + n - 1);

  ll node_count = m * n + 8 * (m + n - 1);

  vector<vector<ll>> adj(node_count);

  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < m; ++j) {
      ll nd = (i * m + j);
      ll sm = (i + j) + (n * m);
      ll df = (i - j) + (m - 1) + (n * m) + (m + n);

      adj[nd].emplace_back(sm);
      adj[nd].emplace_back(df);
      adj[sm].emplace_back(nd);
      adj[df].emplace_back(nd);
    }
  }

  const ll INF = 1e14;
  vector<ll> d(node_count, INF);
  vector<ll> p(node_count);

  d[x * m + y] = 0;
  deque<ll> q;
  q.push_front(x * m + y);
  while (!q.empty()) {
    int v = q.front();

    q.pop_front();
    for (auto edge : adj[v]) {
      int u = edge;
      int w = 1;
      if (d[v] + w < d[u]) {
        d[u] = d[v] + w;
        p[u] = v;

        q.push_back(u);
      }
    }
  }

  ll ans = 0;
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < m; ++j) {
      if (d[i * m + j] <= 2 * L) ans++;
    }
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  solve();
}
