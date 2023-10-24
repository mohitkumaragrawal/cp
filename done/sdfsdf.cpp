#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define OUT(T) cout << "Case #" << T << ": "
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
  ll n;
  cin >> n;

  vector<vector<ll>> adj(n + 1);
  vector<ll> parent(n + 1);
  parent[1] = -1;
  for (ll i = 2; i <= n; ++i) {
    ll p;
    cin >> p;
    parent[i] = p;

    adj[p].push_back(i);
  }

  vector<ll> depth(n + 1);
  ll k = 0;
  auto dfs = [&](auto &&dfs, ll cur, ll dep) -> void {
    depth[cur] = dep;
    ckmax(k, dep);
    for (ll x : adj[cur]) {
      dfs(dfs, x, dep + 1);
    }
  };
  dfs(dfs, 1, 0);

  cout << k << endl;
  for (ll i = 2; i <= n; ++i) {
    cout << depth[i] << " ";
  }
  cout << endl;

  while (true) {
    ll t;
    cin >> t;

    if (t != 0) return;

    vector<ll> clr(k);
    cin >> clr;

    for (ll i = 0; i < k; ++i) {
      if (clr[i] != 0) {
        cout << i + 1 << endl;
        break;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
