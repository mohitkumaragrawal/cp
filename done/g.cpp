#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define OUT(T) cout << "Case #" << T << ": "

#ifdef _DEBUG
#include "debugs.h"
#else
#define dbg(...)
#define endl '\n'
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

ll ExtendedEuclidAlgo(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    ll x1, y1;
    ll gcd = ExtendedEuclidAlgo(b, a % b, x1, y1);
    x = y1;
    y = x1 - floor(a / b) * y1;
    return gcd;
  }
}

pll linearCongruence(ll A, ll B, ll N) {
  A = A % N;
  B = B % N;
  while (A < 0) A += N;
  while (B < 0) B += N;
  A = A % N;
  B = B % N;

  ll u = 0, v = 0;
  ll d = ExtendedEuclidAlgo(A, N, u, v);
  if (B % d != 0) {
    return {-1, -1};
  }

  ll x0 = (u * (B / d)) % N;
  if (x0 < 0) x0 += N;
  return {x0, N / d};
}

void solve(ll _t) {
  ll n, m, H;
  cin >> n >> m >> H;
  vector<ll> l(n), s(n);
  cin >> l >> s;

  vector<vector<ll>> adj(n);
  for (ll i = 0; i < m; ++i) {
    ll u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  const ll INF = 1e17;
  vector<ll> d(n, INF);
  vector<bool> vis(n);
  d[0] = 0;
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [dist, u] = pq.top();
    pq.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;

    for (ll v : adj[u]) {
      auto [x, y] =
          linearCongruence((H + s[u] - s[v]) % H, (H + l[v] - l[u]) % H, H);
      if (x == -1) continue;
      x = x - (x / y) * y;
      ll k = (dist - x + y - 1) / y;

      ll new_dist = x + k * y;
      if (new_dist < d[v]) {
        d[v] = new_dist;
        pq.push({new_dist, v});
      }
    }
  }

  if (d[n - 1] == INF) {
    cout << -1 << endl;
    return;
  }

  cout << 1 + d[n - 1] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}