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
  vector<int> inorder(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    inorder[v]++;
  }

  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (inorder[i] == 0) q.push(i);
  }
  vector<int> order;
  while (!q.empty()) {
    int u = q.front();
    order.push_back(u);
    q.pop();
    for (int it : adj[u]) {
      inorder[it]--;
      if (inorder[it] == 0) q.push(it);
    }
  }
  if (order.size() != n) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  for (int i : order) cout << i + 1 << " ";
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
