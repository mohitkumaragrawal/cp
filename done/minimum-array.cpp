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

  vector<ll> a(n + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = n - 1; i >= 1; --i) {
    a[i] -= a[i - 1];
  }

  int q;
  cin >> q;

  set<pll> changes;

  const ll INF = 1e16;

  auto add_change = [&](ll p, ll x) {
    auto itr = changes.lower_bound({p, -INF});
    if (itr != changes.end() && itr->first == p) {
      x += itr->second;
      changes.erase(itr);
    }
    if (x == 0) return;
    changes.insert({p, x});
  };

  for (int i = 0; i < q; ++i) {
    ll l, r, x;
    cin >> l >> r >> x;
    l--, r--;

    add_change(l, x);
    add_change(r + 1, -x);

    if (changes.empty()) continue;

    if (changes.begin()->second < 0) {
      for (auto [p, d] : changes) {
        a[p] += d;
      }
      changes.clear();
    }
  }

  for (int i = 1; i < n; ++i) a[i] += a[i - 1];

  for (int i = 0; i < n; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}