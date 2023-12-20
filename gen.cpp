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

int random_func(int j) {
  return rng() % j;
}

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

ll n = rand(2, 30);
  cout << 1 << endl;
  cout << n << endl;

  for (ll i = 2; i <= n; ++i) {
    ll p = rand(1, i-1);
    cout << p << " " ;
  }
  cout << endl;
}
