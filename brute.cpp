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

void solve(ll _t) {
  ll n;
  cin >> n;

  vector<vector<ll>> adj(n);
  for (ll i = 1; i < n; ++i) {
    ll p;
    cin >> p;
    p--;
    adj[p].push_back(i);
  }

  vector<ll> sz(n);
  auto dfs = [&](auto &&dfs, ll u) -> void {
    sz[u] = 1;
    for (auto v : adj[u]) {
      dfs(dfs, v);
      sz[u] += sz[v];
    }
  };
  dfs(dfs, 0);

  auto dfs2 = [&](auto &&dfs, ll u) -> ll {
    ll ans = 0;
    ll total = 0;
    vector<pll> v;
    for (auto x : adj[u]) {
      total += sz[x];
      v.emplace_back(sz[x], x);
    }
    sort(all(v));

    if (v.empty()) {
      return 0;
    }

    ll mx_size = v.back().first;
    ll mx_idx = v.back().second;

    if (2 * mx_size <= total) {
      ans += total / 2;
    } else {
      ll teams = total - mx_size;
      ans += teams;
      mx_size -= teams;

      ans += min(mx_size / 2, dfs(dfs, mx_idx));
    }

    return ans;
  };

  cout << dfs2(dfs2, 0) << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}