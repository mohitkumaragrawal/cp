#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define OUT(T) cout << "Case #" << T << ": "
#ifndef _DEBUG
#define endl '\n'
#endif

// clang-format off
template <typename T> ostream &operator<<(ostream &out, const vector<T> &v) { for (const auto &x : v) out << x << ' '; return out; }
template <typename T> istream &operator>>(istream &in, vector<T> &v) { for (auto &x : v) in >> x; return in; }
// clang-format on

using ll = long long;
using lld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll a, ll b) { return a + ((rng()) % (b - a + 1)); }

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll n = 10;

  vector<ll> a(n);
  bool ok = false;

  while (!ok) {
    ll c = 0;
    for (ll i = 0; i < n; ++i) {
      a[i] = rand(0, 1);
      c += a[i];
    }

    if (c <= n / 2)
      ok = true;
  }

  cout << n << endl;
  cout << a << endl;
}
