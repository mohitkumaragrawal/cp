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

struct segment_tree {
  template <typename T>
  void init(T begin, T end) {
    n = distance(begin, end);
    tree.resize(4 * n);
    lazy.resize(4 * n);

    auto build_tree = [&](auto &&build_tree, ll id, ll tl, ll tr) -> void {
      if (tl == tr) {
        tree[id] = *(begin + tl);
        return;
      }
      ll tm = (tl + tr) / 2;
      build_tree(build_tree, 2 * id + 1, tl, tm);
      build_tree(build_tree, 2 * id + 2, tm + 1, tr);

      tree[id] = max(tree[2 * id + 1], tree[2 * id + 2]);
    };
    build_tree(build_tree, 0, 0, n - 1);
  }

  void range_add(ll id, ll tl, ll tr, ll x) {
    tree[id] += x;
    lazy[id] += x;
  }

  void push(ll id, ll tl, ll tr) {
    if (lazy[id] == 0) return;

    ll tm = (tl + tr) / 2;
    range_add(2 * id + 1, tl, tm, lazy[id]);
    range_add(2 * id + 2, tm + 1, tr, lazy[id]);

    lazy[id] = 0;
  }

  void update(ll id, ll tl, ll tr, ll ql, ll qr, ll x) {
    if (ql > tr || tl > qr) return;

    if (ql <= tl && tr <= qr) {
      range_add(id, tl, tr, x);
      return;
    }

    push(id, tl, tr);
    ll tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, ql, qr, x);
    update(2 * id + 2, tm + 1, tr, ql, qr, x);

    tree[id] = max(tree[2 * id + 1], tree[2 * id + 2]);
  }

  void update(ll ql, ll qr, ll x) { update(0, 0, n - 1, ql, qr, x); }

  ll query(ll id, ll tl, ll tr, ll ql, ll qr) {
    if (tl > qr || ql > tr) {
      return -1e17;
    }
    if (ql <= tl && tr <= qr) return tree[id];
    push(id, tl, tr);

    ll tm = (tl + tr) / 2;

    ll q1 = query(2 * id + 1, tl, tm, ql, qr);
    ll q2 = query(2 * id + 2, tm + 1, tr, ql, qr);

    return max(q1, q2);
  }

  ll query(ll ql, ll qr) { return query(0, 0, n - 1, ql, qr); }

  ll n;
  vector<ll> tree;
  vector<ll> lazy;
};

void solve(ll _t) {
  segment_tree st;
  ll n, q;
  cin >> n >> q;
  vector<ll> a(n);
  cin >> a;

  vector<ll> pre(n);
  pre[0] = a[0];
  for (ll i = 1; i < n; ++i) pre[i] = pre[i - 1] + a[i];

  st.init(all(pre));

  while (q--) {
    ll t;
    cin >> t;
    if (t == 2) {
      ll x, y;
      cin >> x >> y;
      x--, y--;

      ll x1 = st.query(x, y);
      if (x > 0) {
        x1 -= st.query(x - 1, x - 1);
      }
      cout << max(x1, 0LL) << endl;
    } else {
      ll k, u;
      cin >> k >> u;
      k--;
      ll diff = u - a[k];
      a[k] = u;
      st.update(k, n - 1, diff);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
