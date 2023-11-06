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

ll MOD = 998244353;
ll binexp(ll a, ll b, ll p = MOD) {
  if (b < 0) return 0;
  ll res = 1;
  while (b > 0) {
    if (b & 1) b--, res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}
inline ll modinv(ll x, ll p = MOD) { return binexp(x, p - 2, p); }
struct mi {
  ll val;
  mi() = default;
  mi(ll x) : val(x) {
    while (val < 0) {
      val += ll(1e8) * MOD;
    }
    val %= MOD;
  }
  mi(mi const& m) : val(m.val) {}
  mi& operator=(mi const& m) {
    val = m.val;
    return *this;
  }
  mi inv() const { return modinv(val); }
  mi pow(mi x) const { return binexp(val, x.val); }
  mi& operator+=(mi const& m) {
    val = (val + m.val) % MOD;
    return *this;
  }
  mi& operator-=(mi const& m) {
    val = (MOD + val - m.val) % MOD;
    return *this;
  }
  mi& operator*=(mi const& m) {
    val = (val * m.val) % MOD;
    return *this;
  }
  mi& operator/=(mi const& m) { return (*this) *= m.inv(); }
  mi& operator++() {
    val = (1 + val) % MOD;
    return *this;
  }
  mi& operator--() {
    val = (MOD + val - 1) % MOD;
    return *this;
  }
  mi operator*(mi const& b) const { return mi{val * b.val}; }
  mi operator-(mi const& b) const { return mi{MOD + val - b.val}; }
  mi operator+(mi const& b) const { return mi{val + b.val}; }
  mi operator/(mi const& b) const { return mi{val * b.inv().val}; }
};
ostream& operator<<(ostream& out, mi const& m) { return (out << m.val); }
istream& operator>>(istream& in, mi& m) {
  ll x;
  in >> x;
  m = x;
  return in;
}

ll next_number(ll m) {
  string s = to_string(m);
  ll ans = 0;
  for (auto ch : s) {
    ans += (ch - '0') * (ch - '0');
  }
  return ans;
}

bool check(ll x) {
  while (x > 1) {
    if (x == 4) return false;
    x = next_number(x);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  ll l, r;
  cin >> l >> r;

  for (ll i = 4;;) {
    cout << i << " ";
    i = next_number(i);
    if (i == 4) break;
  }
  cout << endl;

  for (ll i = l; i <= r; ++i) {
    bool res = check(i);
    if (res) {
      cout << i << " ";
    }
  }
  cout << endl;
}