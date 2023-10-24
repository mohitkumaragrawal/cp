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

const ll N = 1e6 + 10;
ll dp[N][3];
const ll MOD = 1e9 + 7;

void solve(ll _t) {
  ll n;
  cin >> n;

  cout << dp[n][2] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  dp[1][0] = 1;
  dp[1][1] = 3;
  dp[1][2] = 2;

  for (ll i = 1; i < N - 5; ++i) {
    dp[i + 1][0] += dp[i][0];
    dp[i + 1][2] += dp[i][0];

    dp[i + 1][1] += 3 * dp[i][1];
    dp[i + 1][2] += dp[i][1];

    dp[i + 1][0] += dp[i][2];
    dp[i + 1][1] += 3 * dp[i][2];
    dp[i + 1][2] += 2 * dp[i][2];

    for (ll j = 0; j < 3; ++j) dp[i + 1][j] %= MOD;
  }

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
