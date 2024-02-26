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

int val(string s) {
  int last_one = -10;
  int n = s.size(), ans = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '1') {
      if ((i - last_one) > 1) {
        last_one = i + 1;
        ans++;
      }
    }
  }
  return ans;
}

void solve(ll _t) {
  ll n;
  cin >> n;

  string s;
  cin >> s;

  ll ans = 0;

  vector<int> dp(n, 0);
  int bad = 0;
  auto f = [&](int i) -> int {
    if (i < 0) return 0;
    return dp[i];
  };

  for (int i = 0; i < n; ++i) {
    if (s[i] == '1') {
      dp[i] = (i + 1) - f(i - 1) - f(i - 2);
      ans += dp[i] * 1LL * (n - i);
    }
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}