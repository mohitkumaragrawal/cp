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
using MODINT = MODINT_<MOD>;
vector<MODINT> factorial;
void init_factorial() {
  factorial.resize(50);
  factorial[0] = factorial[1] = 1;
  for (ll i = 2; i < 50; ++i) {
    factorial[i] = (factorial[i - 1] * i);
  }
}
inline MODINT choose(const MODINT& a, const MODINT& b) {
  if (a.value < b.value) return 0;
  return factorial[a.value] /
         (factorial[b.value] * factorial[(a.value - b.value)]);
}

class Solution {
 public:
  int countKSubsequencesWithMaxBeauty(string s, int k) {
    init_factorial();

    map<char, int> freq;
    for (auto ch : s) freq[ch]++;

    vector<int> ff;
    for (auto [c, v] : freq) ff.push_back(v);

    int total = ff.size();
    if (k > total) return 0;

    map<int, int> ffc;
    for (auto x : ff) ffc[x]++;
    sort(ff.begin(), ff.end());
    ff.erase(unique(ff.begin(), ff.end()), ff.end());
    reverse(ff.begin(), ff.end());

    MODINT ans = 1;
    for (int i = 0; i < ff.size(); ++i) {
      int c = ffc[ff[i]];

      int take = min(c, k);
      ans *= choose(c, take) * binexp(ff[i], take);
      if (c >= k) {
        break;
      }
      k -= take;
    }

    return ans.value;
  }
};

void solve(ll _t) {
  ll n;
  cin >> n;

  ll ans = 0;
  ll z = 0;
  for (ll i = n; i >= 1;) {
    ll t = (n / i);
    ll x_min = 1 + (n / (t + 1));
    ll x_max = n / t;
    ll cnt = (x_max - x_min + 1);

    ans += t * cnt;
    z++;
    i -= cnt;
  }

  ll rt = sqrt(n);

  dbg(ans, ((1.0 * z) / (1.0 * rt)));
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  string s;
  int k;
  cin >> s >> k;

  Solution sln;

  cout << sln.countKSubsequencesWithMaxBeauty(s, k) << endl;
}
