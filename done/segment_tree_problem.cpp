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

struct node {
  ll pre_max, suf_max;
  ll sum;
  ll ans;

  node(ll x) {
    sum = x;
    pre_max = suf_max = ans = max(0LL, x);
  }
  node() = default;
};

node combine(node a, node b) {
  node res(0);
  res.sum = a.sum + b.sum;
  res.ans = max({a.ans, b.ans, a.suf_max + b.pre_max});

  res.pre_max = max({a.pre_max, a.sum + b.pre_max});

  res.suf_max = max({b.suf_max, b.sum + a.suf_max});

  return res;
};

vector<node> tree(800004);

void build_tree(ll id, ll tl, ll tr, vector<ll> &a) {
  if (tl == tr) {
    tree[id] = node(a[tl]);
    return;
  }

  ll tm = (tl + tr) / 2;
  build_tree(2 * id + 1, tl, tm, a);
  build_tree(2 * id + 2, tm + 1, tr, a);

  tree[id] = combine(tree[2 * id + 1], tree[2 * id + 2]);
}

void update(ll id, ll tl, ll tr, ll p, ll x) {
  if (p < tl || p > tr) return;
  if (tl == tr) {
    tree[id] = node(x);
    return;
  }

  ll tm = (tl + tr) / 2;
  update(2 * id + 1, tl, tm, p, x);
  update(2 * id + 2, tm + 1, tr, p, x);

  tree[id] = combine(tree[2 * id + 1], tree[2 * id + 2]);
}

node query(ll id, ll tl, ll tr, ll ql, ll qr) {
  if (ql > tr || tl > qr) return node(0);
  if (ql <= tl && tr <= qr) return tree[id];

  ll tm = (tl + tr) / 2;
  auto x1 = query(2 * id + 1, tl, tm, ql, qr);
  auto x2 = query(2 * id + 2, tm + 1, tr, ql, qr);

  return combine(x1, x2);
}

void solve(ll _t) {
  ll n, m;
  cin >> n >> m;

  vector<ll> a(n);
  cin >> a;

  build_tree(0, 0, n - 1, a);

  while (m--) {
    ll t;
    cin >> t;

    if (t == 1) {
      ll k, u;
      cin >> k >> u;
      k--;

      update(0, 0, n - 1, k, u);
    } else {
      ll x, y;
      cin >> x >> y;
      x--, y--;

      cout << query(0, 0, n - 1, x, y).pre_max << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}
