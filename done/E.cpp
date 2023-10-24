#include <bits/stdc++.h>

#include <algorithm>
#include <queue>
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
  ll n, t;
  cin >> n >> t;

  vector<vector<pll>> adj(n);
  const ll INF = 1e16;
  vector<ll> d(n, INF);
  d[0] = -1;

  for (ll i = 0; i < t; ++i) {
    ll m;
    cin >> m;

    for (ll j = 0; j < m; ++j) {
      ll u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
    }
  }

  ll k;
  cin >> k;
  vector<vector<ll>> v(t);
  for (ll i = 0; i < k; ++i) {
    ll x;
    cin >> x;
    x--;
    v[x].push_back(i);
  }

  vector<bool> vis(n);
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({-1, 0});

  while (!pq.empty()) {
    auto [j, u] = pq.top();
    pq.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (auto [it, mom] : adj[u]) {
      auto itr = upper_bound(all(v[mom]), d[u]);
      if (itr == v[mom].end()) continue;
      ll jj = *itr;

      if (d[it] > jj) {
        d[it] = jj;
        pq.push({d[it], it});
      }
    }
  }

  if (d[n - 1] >= k) {
    cout << -1 << endl;
    return;
  }

  cout << d[n - 1] + 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  solve(0);
}
