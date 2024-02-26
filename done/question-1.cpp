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

struct sieve_t {
  sieve_t(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
      for (int j = i * i; j <= n; j += i) is_prime[j] = false;
    }
    sieve.assign(n + 1, -1);
    for (int i = 2; i <= n; ++i) {
      if (is_prime[i]) {
        sieve[i] = i;
        if ((ll)i * i <= n) {
          for (int j = i * i; j <= n; j += i) {
            if (sieve[j] == -1) sieve[j] = i;
          }
        }
      }
    }
  }
  vector<int> fast_factorize(int k) {
    vector<int> res;
    while (k > 1) {
      ll p = sieve[k];
      res.push_back(p);
      k /= p;
    }
    return res;
  }
  vector<bool> is_prime;
  vector<int> sieve;
};

sieve_t sv(1e5 + 5);

vector<int> solve(vector<int> A, int N, int K) {
  vector<bool> bad(K + 10);
  for (int x : A) {
    auto f = sv.fast_factorize(x);
    for (int y : f) {
      if (y <= K) bad[y] = true;
    }
  }
  for (int j = 2; j <= K; ++j) {
    if (!bad[j]) continue;
    for (int x = j; x <= K; x += j) {
      bad[x] = true;
    }
  }
  vector<int> res;
  for (int i = 1; i <= K; ++i) {
    if (!bad[i]) res.push_back(i);
  }
  return res;
}

void solve(ll _t) {
  int n;
  cin >> n;

  vector<int> a(n);
  cin >> a;

  int k;
  cin >> k;

  cout << solve(a, n, k) << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}