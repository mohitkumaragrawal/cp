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
struct subarray_sum_node {
  subarray_sum_node() : ans(-INF), pre(-INF), suf(-INF), sum(-INF) {}
  ll ans, pre, suf, sum;
  void set_to(ll x) { ans = pre = suf = sum = x; }

  static subarray_sum_node merge(subarray_sum_node a, subarray_sum_node b) {
    subarray_sum_node res;
    res.sum = a.sum + b.sum;
    res.pre = max(a.pre, a.sum + b.pre);
    res.suf = max(b.suf, b.sum + a.suf);
    res.ans = max({a.ans, b.ans, a.suf + b.pre});
    return res;
  }
};

const int N = 1e5 + 10;
struct subarray_sum_segtree {
  ll n;
  subarray_sum_node t[4 * N];

  void init(ll n) {
    this->n = n;
    for (int i = 0; i < 4 * n; ++i) t[i].set_to(0);
  }

  void update(ll id, ll tl, ll tr, ll p, ll x) {
    if (p > tr || p < tl) return;
    if (tl == tr) {
      t[id].set_to(x);
      return;
    }
    ll tm = (tl + tr) / 2;
    update(id * 2, tl, tm, p, x);
    update(id * 2 + 1, tm + 1, tr, p, x);
    t[id] = subarray_sum_node::merge(t[id * 2], t[id * 2 + 1]);
  }
  subarray_sum_node query(ll id, ll tl, ll tr, ll l, ll r) {
    if (l > tr || r < tl) {
      subarray_sum_node res;
      res.set_to(-INF);
      return res;
    }
    if (l <= tl && tr <= r) return t[id];
    ll tm = (tl + tr) / 2;
    return subarray_sum_node::merge(query(id * 2, tl, tm, l, r),
                                    query(id * 2 + 1, tm + 1, tr, l, r));
  }

  void update(ll p, ll x) { update(1, 0, n - 1, p, x); }
  ll query(ll l, ll r) { return query(1, 0, n - 1, l, r).ans; }
};

struct query_tree {
  vector<int> tree[4 * N];
  int n;

  void init(int n) { this->n = n; }

  void add_operation(int id, int tl, int tr, int ql, int qr, int j) {
    if (ql > tr || qr < tl) return;
    if (ql <= tl && tr <= qr) {
      tree[id].push_back(j);
      return;
    }
    int tm = (tl + tr) / 2;
    add_operation(id * 2, tl, tm, ql, qr, j);
    add_operation(id * 2 + 1, tm + 1, tr, ql, qr, j);
  }

  void add_operation(int ql, int qr, int j) {
    add_operation(1, 0, n - 1, ql, qr, j);
  }
};

ll n, m;
vector<ll> operations;

vector<ll> ans;
map<int, vector<tuple<int, int, int>>> mp;

void solve(ll _t) {
  dbg("solve started");
  cin >> n >> m;

  query_tree qt;
  qt.init(n);

  operations.resize(m);

  for (int i = 0; i < m; ++i) {
    ll l, r, x;
    cin >> l >> r >> x;
    l--, r--;
    operations[i] = x;
    qt.add_operation(l, r, i);
  }

  ll q;
  cin >> q;

  ans.resize(q);
  for (int i = 0; i < q; ++i) {
    int k, l, r;
    cin >> k >> l >> r;
    k--, l--, r--;
    mp[k].push_back({i, l, r});
  }

  dbg("query tree done");

  subarray_sum_segtree st;
  st.init(m);

  auto dfs = [&](auto &&dfs, int id, int tl, int tr) -> void {
    for (auto j : qt.tree[id]) {
      st.update(j, operations[j]);
    }

    if (tl == tr) {
      for (auto [i, l, r] : mp[tl]) {
        ans[i] = st.query(l, r);
      }
    } else {
      int tm = (tl + tr) / 2;
      dfs(dfs, id * 2, tl, tm);
      dfs(dfs, id * 2 + 1, tm + 1, tr);
    }

    for (auto j : qt.tree[id]) {
      st.update(j, 0);
    }
  };

  dfs(dfs, 1, 0, n - 1);
  for (auto x : ans) cout << x << endl;
}

int main() {
  dbg("program started");

  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);

  dbg("END ZZZZ");
}