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

const ll N = 2e5 + 5;

ll n, m;
vector<tuple<ll, ll, ll>> adj[N];
vector<ll> order;
lld dp[N];
ll inorder[N];

bool check(lld x) {
  fill(dp, dp + n, lld(-1e15));
  dp[0] = 0;
  for (auto i : order) {
    for (auto [j, b, c] : adj[i]) {
      lld w = b - c * x;
      ckmax(dp[j], dp[i] + w);
    }
  }
  return dp[n - 1] >= 0.0;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  cin >> n >> m;
  for (ll i = 0; i < m; ++i) {
    ll u, v, b, c;
    cin >> u >> v >> b >> c;
    u--, v--;
    adj[u].emplace_back(v, b, c);
    inorder[v]++;
  }
  queue<ll> q;
  for (ll i = 0; i < n; ++i) {
    if (inorder[i] == 0) q.push(i);
  }
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    order.push_back(u);
    for (auto [v, b, c] : adj[u]) {
      if (--inorder[v] == 0) q.push(v);
    }
  }
  lld lo = 0, hi = 1e9 + 1;
  lld ep = 1e-10;
  while (hi - lo > ep) {
    lld mid = (lo + hi) / 2;
    if (check(mid))
      lo = mid;
    else
      hi = mid;
  }
  cout << fixed << setprecision(15) << (lo + hi) / 2 << endl;
}