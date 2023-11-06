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
ll q;

void solve_brute() {
  vector<vector<ll>> adj(1);
  vector<ll> ans(1), par(1, -1);

  auto dfs = [&](auto &&dfs, ll cur, ll par, ll x) -> void {
    ans[cur] += x;
    for (ll it : adj[cur]) {
      if (it == par) continue;
      dfs(dfs, it, cur, x);
    }
  };

  for (ll i = 0; i < q; ++i) {
    ll t;
    cin >> t;

    if (t == 1) {
      ll v;
      cin >> v;
      v--;

      ll j = adj.size();
      adj.push_back({});
      adj[v].push_back(j);
      adj[j].push_back(v);
      par.push_back(v);
      ans.push_back(0);
    } else {
      ll v, p;
      cin >> v >> p;
      v--;
      dfs(dfs, v, par[v], p);
    }
  }

  cout << ans << endl;
}

void solve(ll _t) {
  cin >> q;
  solve_brute();
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}