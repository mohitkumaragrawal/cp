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

int dp[100][100];

int solve(string &s, int l, int r) {
  if (l == r) return 1;
  if (dp[l][r] != -1) return dp[l][r];
  int n = r - l + 1;
  vector<int> pi(n);

  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i + l] != s[j + l]) {
      j = pi[j - 1];
    }
    if (s[i + l] == s[j + l]) j++;
    pi[i] = j;
  }

  int k = n - pi[n - 1];
  if (k != n && n % k == 0) {
    return dp[l][r] = solve(s, l, l + k - 1);
  } else {
    int ans = 1e8;
    for (int k = l; k < r; ++k) {
      int new_ans = solve(s, l, k) + solve(s, k + 1, r);
      ckmin(ans, new_ans);
    }

    return dp[l][r] = ans;
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  while (true) {
    string s;
    cin >> s;

    if (s == "*") break;

    memset(dp, -1, sizeof dp);
    int ans = solve(s, 0, s.size() - 1);
    cout << ans << endl;
  }
}
