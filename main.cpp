#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define OUT(T) cout << "Case #" << T << ": "

#ifdef _DEBUG
#include "debugs.h"
#else
#define dbg(...)
#define endl '\n'
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

struct min_op {
  ll operator()(ll a, ll b) { return min(a, b); }
};
struct max_op {
  ll operator()(ll a, ll b) { return max(a, b); }
};
struct gcd_op {
  ll operator()(ll a, ll b) { return __gcd(a, b); }
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

void solve(ll _t) {
  ll n;
  cin >> n;

  vector<ll> a(n);
  cin >> a;

  sparse_table<gcd_op> st;
  st.init(all(a));

  map<ll, ll> result;

  for (ll i = 0; i < n; ++i) {
    ll j = i;
    while (j < n) {
      ll v = st.query(i, j);
      ll lo = j, hi = n - 1, ans = j;

      while (hi >= lo) {
        ll m = (hi + lo) / 2;
        if (st.query(i, m) == v) {
          ans = m;
          lo = m + 1;
        } else {
          hi = m - 1;
        }
      }
      result[v] += ans - j + 1;
      j = ans + 1;
    }
  }

  dbg("Here we go");

  ll q;
  cin >> q;

  while (q--) {
    ll x;
    cin >> x;

    cout << result[x] << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}