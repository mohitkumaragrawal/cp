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

const ll N = 2e5 + 1000;
ll tree[4 * N], inc_update[4 * N], set_update[4 * N];
ll n, a[N];

void build_tree(int id, int tl, int tr) {
  if (tl == tr) {
    tree[id] = a[tl];
    return;
  }
  int tm = (tl + tr) / 2;
  build_tree(2 * id + 1, tl, tm);
  build_tree(2 * id + 2, tm + 1, tr);

  tree[id] = tree[2 * id + 1] + tree[2 * id + 2];
}

void range_set(int id, int tl, int tr, ll x) {
  set_update[id] = x;
  inc_update[id] = 0;
  tree[id] = x * (tr - tl + 1);
}

void range_inc(int id, int tl, int tr, ll x) {
  inc_update[id] += x;
  tree[id] += x * (tr - tl + 1);
}

void push(int id, int tl, int tr) {
  if (tl == tr) {
    set_update[id] = 0;
    inc_update[id] = 0;
    return;
  }

  // set >> inc;
  int tm = (tl + tr) / 2;
  if (set_update[id] != 0) {
    range_set(2 * id + 1, tl, tm, set_update[id]);
    range_set(2 * id + 2, tm + 1, tr, set_update[id]);

    set_update[id] = 0;
  }

  if (inc_update[id] != 0) {
    range_inc(2 * id + 1, tl, tm, inc_update[id]);
    range_inc(2 * id + 2, tm + 1, tr, inc_update[id]);

    inc_update[id] = 0;
  }
}

ll query(int id, int tl, int tr, int ql, int qr) {
  if (ql > tr || tl > qr) return 0;
  if (ql <= tl && tr <= qr) return tree[id];

  int tm = (tl + tr) / 2;
  push(id, tl, tr);

  return query(2 * id + 1, tl, tm, ql, qr) +
         query(2 * id + 2, tm + 1, tr, ql, qr);
}

void range_update_add(int id, int tl, int tr, int ql, int qr, ll x) {
  if (ql > tr || tl > qr) return;

  push(id, tl, tr);
  if (ql <= tl && tr <= qr) {
    range_inc(id, tl, tr, x);
    return;
  }

  int tm = (tl + tr) / 2;
  range_update_add(2 * id + 1, tl, tm, ql, qr, x);
  range_update_add(2 * id + 2, tm + 1, tr, ql, qr, x);

  tree[id] = tree[2 * id + 1] + tree[2 * id + 2];
}

void range_update_set(int id, int tl, int tr, int ql, int qr, ll x) {
  if (ql > tr || tl > qr) return;

  push(id, tl, tr);
  if (ql <= tl && tr <= qr) {
    range_set(id, tl, tr, x);
    return;
  }

  int tm = (tl + tr) / 2;
  range_update_set(2 * id + 1, tl, tm, ql, qr, x);
  range_update_set(2 * id + 2, tm + 1, tr, ql, qr, x);

  tree[id] = tree[2 * id + 1] + tree[2 * id + 2];
}

void solve(ll _t) {
  int q;
  cin >> n >> q;
  for (int i = 0; i < n; ++i) cin >> a[i];

  build_tree(0, 0, n - 1);
  while (q--) {
    int t, i, j;
    cin >> t >> i >> j;
    dbg(t, i, j);
    i--, j--;

    ll x;
    if (t == 1) {
      cin >> x;
      range_update_add(0, 0, n - 1, i, j, x);
    } else if (t == 2) {
      cin >> x;
      range_update_set(0, 0, n - 1, i, j, x);
    } else {
      cout << query(0, 0, n - 1, i, j) << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
