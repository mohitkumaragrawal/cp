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

void solve(ll _t) {
  ll n;
  cin >> n;

  vector<ll> a(n);
  cin >> a;

  string s;
  cin >> s;

  vector<ll> pre(n);
  pre[0] = a[0];
  for (ll i = 1; i < n; ++i) pre[i] = pre[i - 1] ^ a[i];

  auto get_xor = [&](ll l, ll r) {
    ll ans = pre[r];
    if (l > 0) ans ^= pre[l - 1];
    return ans;
  };

  // for g = 1;
  vector<ll> tree(4 * n);

  vector<bool> flipped(4 * n);

  auto build = [&](auto &&build, ll id, ll tl, ll tr) -> void {
    if (tl == tr) {
      if (s[tl] == '1') tree[id] = a[tl];
      return;
    }
    ll tm = (tl + tr) / 2;
    build(build, 2 * id + 1, tl, tm);
    build(build, 2 * id + 2, tm + 1, tr);
    tree[id] = tree[2 * id + 1] ^ tree[2 * id + 2];
  };
  build(build, 0, 0, n - 1);

  auto range_flip = [&](ll id, ll tl, ll tr) {
    flipped[id] = !flipped[id];
    ll total = pre[tr];
    if (tl > 0) total ^= pre[tl - 1];
    tree[id] ^= total;
  };

  auto push = [&](ll id, ll tl, ll tr) {
    if (flipped[id]) {
      flipped[id] = false;

      if (tl != tr) {
        ll tm = (tl + tr) / 2;
        range_flip(2 * id + 1, tl, tm);
        range_flip(2 * id + 2, tm + 1, tr);
      }
    }
  };

  auto update = [&](auto &&update, ll id, ll tl, ll tr, ll ql, ll qr) -> void {
    if (tl > qr || ql > tr) return;
    push(id, tl, tr);

    if (ql <= tl && tr <= qr) {
      range_flip(id, tl, tr);
      return;
    }

    ll tm = (tl + tr) / 2;
    update(update, 2 * id + 1, tl, tm, ql, qr);
    update(update, 2 * id + 2, tm + 1, tr, ql, qr);

    tree[id] = tree[2 * id + 1] ^ tree[2 * id + 2];
  };

  auto query = [&](auto &&query, ll id, ll tl, ll tr, ll ql, ll qr) -> ll {
    if (tl > qr || ql > tr) return 0LL;
    push(id, tl, tr);

    if (ql <= tl && tr <= qr) {
      return tree[id];
    }

    ll tm = (tl + tr) / 2;
    ll x1 = query(query, 2 * id + 1, tl, tm, ql, qr);
    ll x2 = query(query, 2 * id + 2, tm + 1, tr, ql, qr);

    return x1 ^ x2;
  };

  ll q;
  cin >> q;
  while (q--) {
    ll t;
    cin >> t;

    if (t == 1) {
      ll l, r;
      cin >> l >> r;
      l--, r--;

      update(update, 0, 0, n - 1, l, r);
    } else {
      ll g;
      cin >> g;

      ll val = tree[0];
      ll tot = pre[n - 1];
      if (g == 0) {
        cout << (tot ^ val) << " ";
      } else {
        cout << val << " ";
      }
    }
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
