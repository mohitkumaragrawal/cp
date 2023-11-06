/*

Things learnt ->

Try to compress the values of the input into some reasonable value
Examples:

i) If we want to know about coprimes:
    instead of having state for every single number we
    can just store the primes which have been used;

ii) In this problem instead of the storing the last number
  in the sequence we can just store the value of floor(p/ (last number)),
  which basically gives the upper bound on the next number

  i.e,

  let the sequence we have is something like this

  x x x x x L

  it has length i and ends with L;
  dp[i][p/L] = # of sequences of length 'i' and (p / (last element)) is given

  There are O(sqrt(p)) distinct values of floor(p / x) for x belongs to +integer

  so instead of storing the value of L in our dp, we store the floor(p/L)
  in our dp and thereby optimizing our dp state;

  How it works?

  x x x x x L x

  here, L * x <= p => x_max = floor(p / L)

  let C(x) = floor(P/x),

  Statement:

  if x * y <= p => C(x) * C(y) >= p

  this can proved as:
  1/p <= 1/(x * y)

  p <= (p/x) * (p/y)



*/

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

const ll MOD = 1e9 + 7;
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
template <ll mod>
struct MODINT_ {
  ll value;
  MODINT_() = default;
  MODINT_(ll x) : value(x % mod) {}
  MODINT_(const MODINT_& m) : value(m.value % mod) {}
  MODINT_& operator=(const MODINT_& m) {
    value = m.value;
    return *this;
  }
  ll inverse_value() const { return modinv(value, mod); }
  MODINT_& operator+=(const MODINT_& m) {
    value = (value + m.value) % mod;
    return *this;
  }
  MODINT_& operator-=(const MODINT_& m) {
    value = (mod + value - m.value) % mod;
    return *this;
  }
  MODINT_& operator*=(const MODINT_& m) {
    value = (value * m.value) % mod;
    return *this;
  }
  MODINT_& operator/=(const MODINT_& m) {
    value = (value * m.inverse_value()) % mod;
    return *this;
  }
  MODINT_& operator++() {
    value++;
    value %= mod;
    return *this;
  }
  MODINT_& operator--() {
    value--;
    value %= mod;
    return *this;
  }
  MODINT_ operator*(const MODINT_& b) { return MODINT_(value * b.value); }
  MODINT_ operator*(ll b) { return MODINT_(value * b); }
  MODINT_ operator-(const MODINT_& b) { return MODINT_(mod + value - b.value); }
  MODINT_ operator-(ll b) { return MODINT_(mod + value - b); }
  MODINT_ operator+(const MODINT_& b) { return MODINT_(value + b.value); }
  MODINT_ operator+(ll b) { return MODINT_(value + b); }
  MODINT_ operator/(const MODINT_& b) {
    return MODINT_(value * modinv(b.value, mod));
  }
  MODINT_ operator/(ll b) { return MODINT_(value * modinv(b, mod)); }
};
template <ll mod>
ostream& operator<<(ostream& out, const MODINT_<mod>& m) {
  out << m.value % mod;
  return out;
}
template <ll mod>
istream& operator>>(istream& in, MODINT_<mod>& m) {
  ll x;
  in >> x;
  m.value = (x % mod);
  return in;
}
using mi = MODINT_<MOD>;

void solve(ll _t) {
  ll n, p;
  cin >> n >> p;

  map<ll, ll, greater<ll>> cnt;
  for (ll i = 1; i * i <= p; ++i) {
    cnt[p / i]++;
  }
  for (ll t = 1; t * t <= p; ++t) {
    cnt[t] = (p / t) - (p / (t + 1));
  }
  vector<ll> cls, cc;

  vector<mi> dp;
  for (auto [k, v] : cnt) {
    if (v == 0) continue;
    cls.push_back(k);
    dp.push_back(v);
    cc.push_back(v);
  }

  ll m = cls.size();

  for (ll i = 2; i <= n; ++i) {
    vector<mi> ndp(m), pre(m);

    pre[0] = dp[0];
    for (ll i = 1; i < m; ++i) pre[i] = pre[i - 1] + dp[i];

    for (ll j = 0; j < m; ++j) {
      ll t = m - 1 - j;
      ndp[j] = pre[t] * cc[j];
    }
    dp = ndp;
  }

  mi ans = 0;
  for (ll i = 0; i < m; ++i) ans += dp[i];

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}