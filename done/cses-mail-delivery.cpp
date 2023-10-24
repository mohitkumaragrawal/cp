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
  ll n, m;
  cin >> n >> m;

  vector<set<ll>> adj(n);
  vector<ll> deg(n);

  for (ll i = 0; i < m; ++i) {
    ll u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].insert(v);
    adj[v].insert(u);

    deg[u]++, deg[v]++;
  }

  // check for even degrees;
  for (ll i = 0; i < n; ++i) {
    if (deg[i] & 1) {
      cout << "IMPOSSIBLE" << endl;
      return;
    }
  }

  stack<ll> st;
  st.push(0);

  vector<ll> res;

  while (!st.empty()) {
    ll v = st.top();

    if (adj[v].empty()) {
      st.pop();
      res.push_back(v + 1);
    } else {
      ll u = *adj[v].begin();

      adj[v].erase(u);
      adj[u].erase(v);

      st.push(u);
    }
  }
  if (res.size() != m + 1) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
