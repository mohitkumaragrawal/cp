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

struct best_path {
  best_path(int capacity) : k(capacity) {}

  bool insert(ll x) {
    if (pq.size() < k) {
      pq.push(x);
      return true;
    }
    ll mx = pq.top();
    if (mx < x) return false;

    pq.pop();
    pq.push(x);
    return true;
  }

  priority_queue<ll> pq;
  int k;
};

void solve(ll _t) {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<pll>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].push_back({b, c});
  }

  vector<best_path> d(n, best_path(k));

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, 0});
  d[0].insert(0);

  vector<int> vis(n);

  while (!pq.empty()) {
    auto [dist, v] = pq.top();
    pq.pop();

    if (vis[v] >= k) continue;
    vis[v]++;

    for (auto [u, w] : adj[v]) {
      if (d[u].insert(dist + w)) {
        pq.push({dist + w, u});
      }
    }
  }

  vector<ll> ans;

  while (!d[n - 1].pq.empty()) {
    ans.push_back(d[n - 1].pq.top());
    d[n - 1].pq.pop();
  }

  reverse(ans.begin(), ans.end());
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
