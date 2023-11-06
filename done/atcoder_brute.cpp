#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll dp[101][101][1001][3];

/*

dp[i][j][k][l]:
i -> # numbers placed
j -> # of connected components
k -> Total sum |a_{i} - a_{i-1}| assuming '?' are a_{i+1}
l -> # of endpoints that are filled;

*/

ll a[105];
const ll MOD = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll n, l;
  cin >> n >> l;

  for (ll i = 0; i < n; ++i) cin >> a[i];

  sort(a, a + n);
  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }

  a[n] = 10000;

  if (a[1] - a[0] <= l) {
    dp[1][1][a[1] - a[0]][1] = 2;
  }

  if (2 * (a[1] - a[0]) <= l) {
    dp[1][1][2 * (a[1] - a[0])][0] = 1;
  }

  for (ll i = 1; i < n; ++i) {
    ll diff = a[i + 1] - a[i];

    for (ll j = 1; j <= i; ++j) {
      for (ll k = 0; k <= l; ++k) {
        for (ll z = 0; z < 3; ++z) {
          if (!dp[i][j][k][z]) continue;

          // First, try to fill one of the ends;
          {
            ll kk = k + diff * (2 * j - z - 1);
            if (z < 2 && kk <= l) {
              if (i == n - 1) {
                dp[i + 1][j][kk][z + 1] += dp[i][j][k][z] * (2 - z) * j;
              } else if (z == 0 || j > 1) {
              }
            }
          }
        }
      }
    }
  }
}