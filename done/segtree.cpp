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
  bool flip = false;
  void reset() { flip = false; }
  void merge(tag const &other) {
    if (other.flip) {
      if (flip)
        flip = false;
      else
        flip = true;
    }
  }
  void init(int tl, int tr) { flip = false; }
};

const ll INF = 1e16;
const ll MOD = 1e9 + 7;

struct node {
  ll min_el, min_idx, max_el, max_idx;

  static node phi() { return {INF, INF, -INF, INF}; }
  static node merge(node const &a, node const &b) {
    node res;
    if (a.min_el <= b.min_el) {
      res.min_el = a.min_el;
      res.min_idx = a.min_idx;
    } else {
      res.min_el = b.min_el;
      res.min_idx = b.min_idx;
    }

    if (a.max_el >= b.max_el) {
      res.max_el = a.max_el;
      res.max_idx = a.max_idx;
    } else {
      res.max_el = b.max_el;
      res.max_idx = b.max_idx;
    }

    return res;
  }

  void apply(ll tl, ll tr, tag const &t) {
    if (t.flip) {
      swap(max_el, min_el);
      swap(min_idx, max_idx);

      min_el = (MOD - min_el) % MOD;
      max_el = (MOD - max_el) % MOD;
    }
  }

  template <typename T>
  void init(ll tl, ll tr, T &ddata) {
    min_el = max_el = ddata;
    min_idx = max_idx = tl;
  }
};

void solve(ll _t) {
  ll n;
  cin >> n;

  vector<ll> a(n);
  cin >> a;

  lazy_segtree<node, tag> st;
  st.init(all(a));

  ll total = 0;

  ll q;
  cin >> q;
  while (q--) {
    ll ql, qr;
    cin >> ql >> qr;
    ql--, qr--;

    st.update(ql, qr, {true});

    ll k = st.query(0, n - 1).max_idx + 1;
    total += k;
  }
  OUT(_t) << total << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
/*

Each element lives in the data structure for some segments of time between
addition and deletions.

Let's build a segment tree over the queries. Each segment when some element is
alive splits into O(log n) nodes of the tree.

Let's put each query when we want to know something about the structure into the
corresponding leaf.

Now to process all queries we will run a DFS on the segemtn tree.

When entering the node we will add all the elements that are inside this node.

Then we will go further to the children of this node or answer the queries (if
the node is a leaf). When leaving the node, we must undo the additions.

Note that if we change the structure in O(T(n)) we can roll back the changes in
O(T(n)) by keeping a stack of changes.

Note that rollbacks break amortized complexity.

----------------------------------------------------


given: undirected graph, currently with n nodes and no edges
queries:
  1. Add an edge between u and v
  2. Remove the edge between u and v;

After each query output the number of connected components;


a single edge can exist in atmost log(T) different nodes, a single edge in a
particular node requires T(n) time when entering that node and T(n) for rollback
from that node;

So the total time complexity: O(m log(T) T(n) + T log(T))

T(n) = log(n)

n log^2(n)
it can run for n upto 1e5;

*/

// data structure that can insert and rollback;
struct rollback_dsu {};