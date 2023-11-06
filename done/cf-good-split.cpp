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

const int N = 3e5 + 5;

struct min_op {
  ll operator()(ll a, ll b) { return min(a, b); }
};
template <typename OperationT>
struct sparse_table {
  vector<vector<ll>> m;
  OperationT op;
  template <typename Itr>
  void init(Itr begin, Itr end) {
    ll sz = end - begin;
    ll lg = 63 - __builtin_clzll(sz);
    m.assign(sz, vector<ll>(lg + 1));
    for (ll j = 0; j <= lg; ++j) {
      ll len = (1 << j);
      for (ll i = 0; i + len - 1 < sz; ++i) {
        if (len == 1) {
          m[i][j] = *(begin + i);
        } else {
          m[i][j] = op(m[i][j - 1], m[i + (1 << (j - 1))][j - 1]);
        }
      }
    }
  }
  ll query(ll L, ll R) {
    ll j = 63 - __builtin_clzll((R - L + 1));
    return op(m[L][j], m[R + 1 - (1 << j)][j]);
  }
};

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

int n;
int a[N], left_bigger[N], right_bigger[N], y_idx[N];

void solve(ll _t) {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  sparse_table<min_op> rmq;
  rmq.init(a, a + n);

  vector<int> st;
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.back()] < a[i]) {
      right_bigger[st.back()] = i;
      st.pop_back();
    }
    if (st.empty()) {
      left_bigger[i] = -1;
    } else {
      left_bigger[i] = st.back();
    }
    st.push_back(i);
  }
  for (int i : st) right_bigger[i] = -1;
  vector<vector<pii>> push_stack(n + 1), pop_stack(n + 1);
  for (int i = 0; i < n; ++i) {
    int j = right_bigger[i];
    if (j == -1) continue;

    if (rmq.query(j, n - 1) > a[i]) {
      y_idx[i] = n - 1;
      continue;
    }

    int lo = j, hi = n - 1;
    while (hi - lo > 1) {
      int m = (hi + lo) / 2;
      if (rmq.query(j, m) > a[i]) {
        lo = m;
      } else {
        hi = m;
      }
    }
    y_idx[i] = lo;
  }

  for (int i = 0; i < n; ++i) {
    if (right_bigger[i] == -1) continue;

    push_stack[left_bigger[i] + 1].emplace_back(right_bigger[i], y_idx[i]);
    pop_stack[i + 1].emplace_back(right_bigger[i], y_idx[i]);
  }

  vector<int> lst_vec(n);
  lazy_segtree<node, tag> lst;
  lst.init(all(lst_vec));

  int q;
  cin >> q;

  vector<tuple<int, int, int>> queries;
  vector<bool> ans(q);

  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    queries.emplace_back(l, r, i);
  }
  sort(queries.begin(), queries.end());
  int j = 0;

  for (int i = 0; i < n; ++i) {
    for (auto [x, y] : push_stack[i]) lst.update(x, y, {1});
    for (auto [x, y] : pop_stack[i]) lst.update(x, y, {-1});

    while (j < q && get<0>(queries[j]) == i) {
      auto [l, r, qidx] = queries[j];
      int v = lst.query(r, r).data;

      if (v > 0) {
        ans[qidx] = true;
      }
      j++;
    }
  }

  for (int i = 0; i < q; ++i) {
    if (ans[i]) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  solve(0);
}