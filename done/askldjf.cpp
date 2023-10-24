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

const ll N = 6e5;
ll p5[10], D[N];

ll encode(array<ll, 5> a) {
  array<ll, 8> t;
  fill(all(t), 4);
  t[0] = 0;

  for (ll i = 0; i < 30; ++i) {
    ll x = 0;
    for (ll j = 0; j < 3; ++j) {
      x |= ((a[j] >> i) & 1) << j;
    }
    ll y = 0;
    for (ll j = 0; j < 2; ++j) {
      y |= ((a[j + 3] >> i) & 1) << j;
    }
    if (t[x] == 4)
      t[x] = y;
    else if (t[x] != y)
      return -1;
  }
  ll ans = 0;
  for (ll i = 0; i < 8; ++i) {
    ans += p5[i] * t[i];
  }
  return ans;
}

array<ll, 5> decode(ll n) {
  array<ll, 5> res;
  fill(all(res), 0LL);
  for (ll i = 0; i < 8; ++i) {
    ll t = n % 5;
    n /= 5;
    if (t == 4) continue;
    for (ll j = 0; j < 3; ++j) {
      res[j] |= ((i >> j) & 1) << i;
    }
    for (ll j = 0; j < 2; ++j) {
      res[j + 3] |= ((t >> j) & 1) << i;
    }
  }
  return res;
}

bool vis[N];
const ll INF = 1e15;

void solve(ll _t) {
  ll a, b, c, d, m;
  cin >> a >> b >> c >> d >> m;
  array<ll, 5> arr = {a, b, m, c, d};
  ll x = encode(arr);
  if (x == -1 || D[x] == INF) {
    cout << -1 << endl;
    return;
  }
  cout << D[x] << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  p5[0] = 1;
  for (ll i = 1; i < 10; ++i) p5[i] = 5 * p5[i - 1];
  queue<ll> q;
  fill(D, D + N, INF);

  vector<vector<ll>> adj(N);

  for (ll i = 0; i < p5[8]; ++i) {
    auto arr = decode(i);

    ll j = encode(arr);
    if (j == -1) continue;

    if (arr[0] == arr[3] && arr[1] == arr[4]) {
      D[j] = 0;
      vis[j] = true;
      q.push(j);
    }

    {
      auto b = arr;
      b[0] &= b[1];
      ll t = encode(b);
      if (t != -1) {
        adj[t].push_back(j);
      }
    }
    {
      auto b = arr;
      b[0] |= b[1];
      ll t = encode(b);
      if (t != -1) {
        adj[t].push_back(j);
      }
    }
    {
      auto b = arr;
      b[1] ^= b[0];
      ll t = encode(b);
      if (t != -1) {
        adj[t].push_back(j);
      }
    }
    {
      auto b = arr;
      b[1] ^= b[2];
      ll t = encode(b);
      if (t != -1) {
        adj[t].push_back(j);
      }
    }
  }

  while (!q.empty()) {
    ll x = q.front();
    q.pop();
    for (ll y : adj[x]) {
      if (vis[y]) continue;
      vis[y] = true;
      D[y] = D[x] + 1;
      q.push(y);
    }
  }

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
