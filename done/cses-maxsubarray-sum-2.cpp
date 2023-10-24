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

void solve(ll _t) {
  ll n, a, b;
  cin >> n >> a >> b;
  vector<ll> arr(n);
  cin >> arr;

  vector<ll> pre(n + 1);
  for (ll i = 1; i <= n; ++i) pre[i] = arr[i - 1] + pre[i - 1];
  ll ans = -1e18;

  deque<ll> q;
  for (ll i = a; i <= n; ++i) {
    while (!q.empty() && pre[q.back()] > pre[i - a]) q.pop_back();
    while (!q.empty() && q.front() < i - b) q.pop_front();
    q.push_back(i - a);

    ckmax(ans, pre[i] - pre[q.front()]);
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
