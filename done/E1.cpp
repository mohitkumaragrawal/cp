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

using ll = int;

const ll LOG = 20;

const int N = 1e6 + 5;
int up[N][LOG], ans[N], val[N];

void solve(ll _t) {
  ll n;
  cin >> n;

  vector<vector<ll>> adj(n + 10);

  ll cur = 0;
  ll nxt_node = 1;

  stack<ll> prev;
  vector<ll> queries;

  for (ll i = 0; i < n; ++i) {
    char type;
    cin >> type;

    if (type == '+') {
      ll x;

      cin >> x;
      adj[cur].push_back(nxt_node);

      up[nxt_node][0] = cur;
      for (int j = 1; j < LOG; ++j)
        up[nxt_node][j] = up[up[nxt_node][j - 1]][j - 1];

      prev.push(cur);
      cur = nxt_node;
      val[nxt_node] = x;

      nxt_node++;
    } else if (type == '-') {
      ll k;
      cin >> k;

      prev.push(cur);

      for (ll j = 0; j < LOG; ++j) {
        if ((k >> j) & 1) {
          cur = up[cur][j];
        }
      }
    } else if (type == '!') {
      cur = prev.top();
      prev.pop();
    } else {
      queries.push_back(cur);
    }
  }

  vector<bool> seen(N);
  int count = 0;

  auto dfs = [&](auto &&self, ll cur, ll par) -> void {
    ans[cur] = count;

    for (auto it : adj[cur]) {
      if (it == par) continue;

      bool pushed = false;
      int v = val[it];

      if (!seen[v]) {
        seen[v] = true;
        count++;
        pushed = true;
      }

      self(self, it, cur);

      if (pushed) {
        seen[v] = false;
        count--;
      }
    }
  };

  dfs(dfs, 0, -1);

  for (ll x : queries) {
    cout << ans[x] << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
