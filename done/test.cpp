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

template <typename T, typename CombineT>
struct SegmentTree {
  vector<T> tree;
  CombineT combine;
  T defaultValue;
  ll n;

  void init(ll n, T val) {
    tree.resize(4 * n);
    this->n = n;
    defaultValue = val;
    build_tree(1, 0, n - 1);
  }

  template <typename Itr>
  void init(Itr begin, Itr end) {
    n = distance(begin, end);
    tree.resize(4 * n);

    build_tree(1, 0, n - 1, begin);
  }

  void build_tree(ll id, ll tl, ll tr) {
    if (tl == tr) {
      tree[id] = defaultValue;
      return;
    }
    ll tm = (tl + tr) / 2;
    build_tree(id * 2, tl, tm);
    build_tree(id * 2 + 1, tm + 1, tr);
    tree[id] = combine(tree[id * 2], tree[id * 2 + 1]);
  }

  template <typename Itr>
  void build_tree(ll id, ll tl, ll tr, Itr begin) {
    if (tl == tr) {
      tree[id] = *(begin + tl);
      return;
    }
    ll tm = (tl + tr) / 2;
    build_tree(id * 2, tl, tm, begin);
    build_tree(id * 2 + 1, tm + 1, tr, begin);
    tree[id] = combine(tree[id * 2], tree[id * 2 + 1]);
  }

  T query(ll id, ll tl, ll tr, ll ql, ll qr) {
    if (ql > tr || tl > qr) return defaultValue;
    if (ql <= tl && tr <= qr) return tree[id];
    ll tm = (tl + tr) / 2;
    return combine(query(id * 2, tl, tm, ql, qr),
                   query(id * 2 + 1, tm + 1, tr, ql, qr));
  }

  T query(ll l, ll r) { return query(1, 0, n - 1, l, r); }

  void update(ll id, ll tl, ll tr, ll p, T x) {
    if (tl == tr) {
      tree[id] = x;
      return;
    }
    ll tm = (tl + tr) / 2;
    if (p <= tm)
      update(id * 2, tl, tm, p, x);
    else
      update(id * 2 + 1, tm + 1, tr, p, x);
    tree[id] = combine(tree[id * 2], tree[id * 2 + 1]);
  }

  void update(ll p, T x) { update(1, 0, n - 1, p, x); }
};

void solve(ll _t) { cout << "Hello World" << endl; }

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
