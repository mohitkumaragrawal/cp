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

template <typename node_type, typename tag_type>
struct lazy_segtree {
  vector<node_type> tree;
  vector<tag_type> lazy;
  int n;
  template <typename Iter>
  void init(Iter first, Iter last, int nn = -1) {
    n = nn;
    if (n == -1) n = distance(first, last);
    tree.resize(4 * n);
    lazy.resize(4 * n);
    build_tree(0, 0, n - 1, first);
  }
  node_type query(int ql, int qr) { return query(0, 0, n - 1, ql, qr); }
  void update(int ql, int qr, tag_type const &val) {
    update(0, 0, n - 1, ql, qr, val);
  }

 private:
  template <typename Iter>
  void build_tree(int id, int tl, int tr, Iter first) {
    if (tl == tr) {
      tree[id].init(tl, tr, *(first + tl));
      lazy[id].init(tl, tr);
      return;
    }
    int tm = (tl + tr) / 2;
    build_tree(2 * id + 1, tl, tm, first);
    build_tree(2 * id + 2, tm + 1, tr, first);
    tree[id] = node_type::merge(tree[2 * id + 1], tree[2 * id + 2]);
    lazy[id].init(tl, tr);
  }
  void push(int id, int tl, int tr) {
    if (tl != tr) {
      int tm = (tl + tr) / 2;
      tree[2 * id + 1].apply(tl, tm, lazy[id]);
      lazy[2 * id + 1].merge(lazy[id]);
      tree[2 * id + 2].apply(tm + 1, tr, lazy[id]);
      lazy[2 * id + 2].merge(lazy[id]);
    }
    lazy[id].reset();
  }
  node_type query(int id, int tl, int tr, int ql, int qr) {
    if (tl > qr || ql > tr) return node_type::phi();
    if (ql <= tl && tr <= qr) return tree[id];
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    return node_type::merge(query(2 * id + 1, tl, tm, ql, qr),
                            query(2 * id + 2, tm + 1, tr, ql, qr));
  }
  void update(int id, int tl, int tr, int ql, int qr, tag_type const &val) {
    if (tl > qr || ql > tr) return;
    if (ql <= tl && tr <= qr) {
      tree[id].apply(tl, tr, val);
      lazy[id].merge(val);
      return;
    }
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, ql, qr, val);
    update(2 * id + 2, tm + 1, tr, ql, qr, val);
    tree[id] = node_type::merge(tree[2 * id + 1], tree[2 * id + 2]);
  }
};
struct tag {
  ll inc;
  void reset() { inc = 0; }
  void merge(tag const &other) { inc += other.inc; }
  void init(int tl, int tr) {}
};
struct node {
  static node phi() { return {0LL}; }
  static node merge(node const &a, node const &b) { return {a.data + b.data}; }
  ll data;
  void apply(ll tl, ll tr, tag const &t) { data += (tr - tl + 1) * t.inc; }
  template <typename T>
  void init(ll tl, ll tr, T &ddata) {
    this->data = ddata;
  }
};

ll q;
void solve(ll _t) {
  cin >> q;
  vector<vector<ll>> adj(1);
  vector<tuple<ll, ll, ll>> queries;
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

      queries.push_back({t, j, 0LL});
    } else {
      ll p, x;
      cin >> p >> x;
      p--;
      queries.push_back({t, p, x});
    }
  }

  ll n = adj.size();
  vector<ll> in_time(n), out_time(n);

  ll time = 0;
  auto dfs = [&](auto &&dfs, ll cur, ll par) -> void {
    in_time[cur] = time++;
    for (auto it : adj[cur]) {
      if (it == par) continue;
      dfs(dfs, it, cur);
    }
    out_time[cur] = time - 1;
  };
  dfs(dfs, 0, -1);

  lazy_segtree<node, tag> lst;
  vector<ll> data(n);
  lst.init(all(data));

  vector<ll> ans(n);

  for (ll i = q - 1; i >= 0; --i) {
    auto [t, x, y] = queries[i];
    if (t == 1) {
      ans[x] = lst.query(in_time[x], in_time[x]).data;
    } else {
      lst.update(in_time[x], out_time[x], {y});
    }
  }

  ans[0] = lst.query(0, 0).data;
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}