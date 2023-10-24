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

int n;
int mat[1005][1005];

struct segtree {
  int tree[4 * 1005];
  template <typename T>
  void build_tree(int id, int tl, int tr, T &&f) {
    if (tl == tr) {
      tree[id] = f(tl);
      return;
    }
    int tm = (tl + tr) / 2;
    build_tree(2 * id + 1, tl, tm, f);
    build_tree(2 * id + 2, tm + 1, tr, f);
    tree[id] = tree[2 * id + 1] + tree[2 * id + 2];
  }
  void update(int id, int tl, int tr, int p, int x) {
    if (p > tr || p < tl) return;
    if (tl == tr) {
      tree[id] += x;
      return;
    }
    int tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, p, x);
    update(2 * id + 2, tm + 1, tr, p, x);
    tree[id] = tree[2 * id + 1] + tree[2 * id + 2];
  }
  void update(int p, int x) { update(0, 0, n - 1, p, x); }
  int query(int id, int tl, int tr, int ql, int qr) {
    if (tl > qr || ql > tr) return 0;
    if (ql <= tl && tr <= qr) return tree[id];
    int tm = (tl + tr) / 2;
    return query(2 * id + 1, tl, tm, ql, qr) +
           query(2 * id + 2, tm + 1, tr, ql, qr);
  }
  int query(int ql, int qr) { return query(0, 0, n - 1, ql, qr); }
};

struct seg2d {
  vector<segtree> tree;
  void build_tree(int id, int tl, int tr) {
    if (tl == tr) {
      tree[id].build_tree(0, 0, n - 1, [&](int x) { return mat[tl][x]; });
      return;
    }
    int tm = (tl + tr) / 2;
    build_tree(2 * id + 1, tl, tm);
    build_tree(2 * id + 2, tm + 1, tr);
    tree[id].build_tree(0, 0, n - 1, [&](int x) {
      return tree[2 * id + 1].query(x, x) + tree[2 * id + 2].query(x, x);
    });
  }
  void init() {
    tree.resize(4 * n);
    build_tree(0, 0, n - 1);
  }
  int query(int id, int tl, int tr, int ql, int qr, int qql, int qqr) {
    if (tl > qr || ql > tr) return 0;
    if (ql <= tl && tr <= qr) {
      return tree[id].query(qql, qqr);
    }
    int tm = (tl + tr) / 2;
    int x1 = query(2 * id + 1, tl, tm, ql, qr, qql, qqr);
    int x2 = query(2 * id + 2, tm + 1, tr, ql, qr, qql, qqr);
    return x1 + x2;
  }
  void update(int id, int tl, int tr, int p, int pp, int x) {
    if (p > tr || p < tl) return;
    if (tl == tr) {
      tree[id].update(pp, x);
      return;
    }
    int tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, p, pp, x);
    update(2 * id + 2, tm + 1, tr, p, pp, x);
    tree[id].update(pp, x);
  }
};

void solve(ll _t) {
  int q;
  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j) {
      if (s[j] == '*') {
        mat[i][j] = 1;
      } else {
        mat[i][j] = 0;
      }
    }
  }
  seg2d st;
  st.init();
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int p, pp;
      cin >> p >> pp;
      p--, pp--;
      int x = (mat[p][pp] ^ 1) - mat[p][pp];
      mat[p][pp] ^= 1;
      st.update(0, 0, n - 1, p, pp, x);
    } else {
      int ql, qql, qr, qqr;
      cin >> ql >> qql >> qr >> qqr;
      ql--, qql--, qr--, qqr--;
      int ans = st.query(0, 0, n - 1, ql, qr, qql, qqr);
      cout << ans << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}