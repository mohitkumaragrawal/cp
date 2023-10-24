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

const int N = 2e5 + 10;
int cid[N], csz[N], dep[N], nxt[N];
bool vis[N], st[N], cycle[N];

void dfs(int cur) {
  vis[cur] = true;
  st[cur] = true;
  int p = nxt[cur];

  if (vis[p] && st[p]) {
    int sz = 1;
    int it = p;
    while (it != cur) {
      sz++;
      cycle[it] = true;
      it = nxt[it];
    }
    csz[p] = sz;
    cycle[cur] = true;
    cid[cur] = p;
  } else {
    if (!vis[p]) dfs(p);
    cid[cur] = cid[p];
    if (!cycle[cur]) {
      dep[cur] = 1 + dep[p];
    }
  }
  st[cur] = false;
}

void solve(ll _t) {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> nxt[i];
    nxt[i]--;
  }
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) dfs(i);
  }

  for (int i = 0; i < n; ++i) {
    cout << dep[i] + csz[cid[i]] << " ";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  // cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
