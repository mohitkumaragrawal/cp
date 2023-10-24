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

const ll INF = 1e17;
struct SegTree {
  vector<ll> tree;
  ll n;

  void init(ll nn, auto &f) {
    n = nn;
    tree.resize(4 * n);
    build_tree(0, 0, n - 1, f);
  }

  void build_tree(ll id, ll tl, ll tr, auto &f) {
    if (tl == tr) {
      tree[id] = f[tl];
      return;
    }
    ll tm = (tl + tr) / 2;
    build_tree(2 * id + 1, tl, tm, f);
    build_tree(2 * id + 2, tm + 1, tr, f);
    tree[id] = max(tree[2 * id + 1], tree[2 * id + 2]);
  }

  ll query(ll id, ll tl, ll tr, ll ql, ll qr) {
    if (tl > qr || ql > tr) return -INF;
    if (ql <= tl && tr <= qr) return tree[id];
    ll tm = (tl + tr) / 2;

    return max(query(2 * id + 1, tl, tm, ql, qr),
               query(2 * id + 2, tm + 1, tr, ql, qr));
  }

  ll query(ll ql, ll qr) { return query(0, 0, n - 1, ql, qr); }

  void update(ll id, ll tl, ll tr, ll p, ll x) {
    if (p < tl || p > tr) return;
    if (tl == tr) {
      tree[id] = x;
      return;
    }
    ll tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, p, x);
    update(2 * id + 2, tm + 1, tr, p, x);
    tree[id] = max(tree[2 * id + 1], tree[2 * id + 2]);
  }
  void update(ll p, ll x) { update(0, 0, n - 1, p, x); }
};

struct binary_lift {
  vector<vector<ll>> up;
  vector<ll> depth;
  const ll LOG = 18;
  void init(vector<vector<ll>> const &adj) {
    ll n = adj.size();
    depth.resize(n);
    up.assign(n, vector<ll>(LOG + 1));
    function<void(ll, ll, ll)> dfs = [&](ll u, ll p, ll d) {
      depth[u] = d;
      up[u][0] = p;
      for (ll i = 1; i <= LOG; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
      }
      for (ll v : adj[u]) {
        if (v != p) dfs(v, u, d + 1);
      }
    };
    dfs(0, 0, 0);
  }
  ll lift_node(ll n, ll d) {
    for (ll i = LOG; i >= 0; --i) {
      if (d & (1 << i)) n = up[n][i];
    }
    return n;
  }
  ll lca(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = lift_node(u, depth[u] - depth[v]);
    if (u == v) return u;
    for (ll i = LOG; i >= 0; --i) {
      if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
      }
    }
    return up[u][0];
  }
  ll dist(ll u, ll v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};

struct HLD {
  vector<ll> chain, sz, heavy, dt;
  ll n;
  vector<SegTree> seg;
  binary_lift bl;

  void init_hld(vector<vector<ll>> const &adj, vector<ll> const &data) {
    dt = data;
    n = adj.size();
    chain.resize(n), sz.assign(n, 1LL), heavy.assign(n, -1), seg.resize(n);
    iota(all(chain), 0LL);
    auto dfs = [&](auto &&dfs, ll cur, ll par) -> void {
      ll hsz = 0;
      for (ll x : adj[cur]) {
        if (x == par) continue;

        dfs(dfs, x, cur);
        sz[cur] += sz[x];

        if (sz[x] > hsz) {
          heavy[cur] = x;
          hsz = sz[x];
        }
      }
    };
    dfs(dfs, 0, -1);

    auto dfs2 = [&](auto &&dfs, ll cur, ll par) -> void {
      ll hv = heavy[cur];
      if (hv != -1) chain[hv] = chain[cur];
      for (ll x : adj[cur]) {
        if (x == par) continue;
        dfs(dfs, x, cur);
      }
    };
    dfs2(dfs2, 0, -1);

    bl.init(adj);

    for (ll i = 0; i < n; ++i) {
      if (chain[i] != i) continue;
      vector<ll> val;
      ll it = i;
      while (it != -1) {
        val.push_back(data[it]);
        it = heavy[it];
      }
      seg[i].init(val.size(), val);
    }
  }

  void update(ll nd, ll x) {
    auto &st = seg[chain[nd]];
    ll idx = bl.depth[nd] - bl.depth[chain[nd]];
    st.update(idx, x);
  }

  ll query_verticle(ll u, ll v) {
    if (bl.depth[u] < bl.depth[v]) swap(u, v);
    ll ans = -INF;

    while (bl.depth[u] >= bl.depth[v]) {
      ll c = chain[u];

      ll u_idx = bl.depth[u] - bl.depth[c];
      ll v_idx = max(0LL, bl.depth[v] - bl.depth[c]);
      ckmax(ans, seg[c].query(v_idx, u_idx));
      if (v == c) break;
      u = bl.up[c][0];
    }
    return ans;
  }

  ll query_path(ll u, ll v) {
    ll l = bl.lca(u, v);

    ll q1 = query_verticle(u, l);
    ll q2 = query_verticle(v, l);
    return max(q1, q2);
  }
};

void solve(ll _t) {
  ll n, q;
  cin >> n >> q;

  vector<ll> data(n);
  cin >> data;

  vector<vector<ll>> adj(n);
  for (ll i = 0; i < n - 1; ++i) {
    ll u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  HLD hld;
  hld.init_hld(adj, data);

  while (q--) {
    ll t;
    cin >> t;
    if (t == 1) {
      ll s, x;
      cin >> s >> x;
      s--;
      hld.update(s, x);
    } else {
      ll a, b;
      cin >> a >> b;
      a--, b--;
      ll ans = hld.query_path(a, b);
      cout << ans << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
