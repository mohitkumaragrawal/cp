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

const ll MOD = 1e9 + 7;

void solve(ll _t) {
  int n, m;
  cin >> n >> m;

  vector<vector<pii>> adj(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].push_back({v, w});
  }

  const ll INF = 1e18;
  vector<ll> d(n, INF);
  d[0] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, 0});

  vector<bool> vis(n);

  while (!pq.empty()) {
    auto [dist, u] = pq.top();
    pq.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (auto [v, w] : adj[u]) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pq.push({d[v], v});
      }
    }
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int x, int y) { return d[x] < d[y]; });

  vector<ll> cnt(n), mx(n), mn(n, INF);
  cnt[0] = 1;
  mx[0] = 1;
  mn[0] = 1;

  for (int i = 0; i < n; ++i) {
    int j = order[i];
    if (cnt[j] == 0) continue;

    for (auto [it, w] : adj[j]) {
      if (d[it] == d[j] + w) {
        cnt[it] = (cnt[it] + cnt[j]) % MOD;
        mx[it] = max(mx[it], mx[j] + 1);
        mn[it] = min(mn[it], mn[j] + 1);
      }
    }
  }

  cout << d[n - 1] << " " << cnt[n - 1] << " " << mn[n - 1] - 1 << " "
       << mx[n - 1] - 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
