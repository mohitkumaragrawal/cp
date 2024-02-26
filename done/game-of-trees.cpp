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

struct DSU {
  vector<int> parent, siz;
  void init(int n) {
    parent.resize(n);
    siz.resize(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      siz[i] = 1;
    }
  }
  int find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find(parent[x]);
  }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (siz[x] < siz[y]) swap(x, y);
    parent[y] = x;
    siz[x] += siz[y];
  }
  int size(int x) { return siz[find(x)]; }
  bool same(int x, int y) { return find(x) == find(y); }
};

template <int SZ, bool VALS_IN_EDGES>
struct HLD {
  int N;
  vector<int> adj[SZ];
  int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
  int pos[SZ];
  vector<int> rpos;
  void ae(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  void dfsSz(int x) {
    sz[x] = 1;
    for (auto &y : adj[x]) {
      par[y] = x;
      depth[y] = depth[x] + 1;
      adj[y].erase(find(adj[y].begin(), adj[y].end(), x));
      dfsSz(y);
      sz[x] += sz[y];
      if (sz[y] > sz[adj[x][0]]) swap(y, adj[x][0]);
    }
  }
  void dfsHld(int x) {
    pos[x] = ti++;
    rpos.push_back(x);
    for (auto &y : adj[x]) {
      root[y] = (y == adj[x][0] ? root[x] : y);
      dfsHld(y);
    }
  }
  void init(int _N, int R = 0) {
    N = _N;
    par[R] = depth[R] = ti = 0;
    dfsSz(R);
    root[R] = R;
    dfsHld(R);
  }
  int lca(int x, int y) {
    for (; root[x] != root[y]; y = par[root[y]]) {
      if (depth[root[x]] > depth[root[y]]) swap(x, y);
    }
    return depth[x] < depth[y] ? x : y;
  }
  int dist(int x, int y) { return depth[x] + depth[y] - 2 * depth[lca(x, y)]; }
  template <class BinaryOp>
  void processPath(int x, int y, BinaryOp op) {
    for (; root[x] != root[y]; y = par[root[y]]) {
      if (depth[root[x]] > depth[root[y]]) swap(x, y);
      op(pos[root[y]], pos[y]);
    }
    if (depth[x] > depth[y]) swap(x, y);
    op(pos[x] + VALS_IN_EDGES, pos[y]);
  }
};

const ll MOD = 1e9 + 7;
template <class T>
class BIT {
 private:
  int size;
  vector<T> bit;
  vector<T> arr;

 public:
  BIT(int size) : size(size), bit(size + 1), arr(size) {}
  void set(int ind, int val) { add(ind, val - arr[ind]); }
  void add(int ind, int val) {
    arr[ind] += val;
    arr[ind] %= MOD;
    ind++;
    for (; ind <= size; ind += ind & -ind) {
      bit[ind] += val;
      bit[ind] %= MOD;
    }
  }
  T pref_sum(int ind) {
    ind++;
    T total = 0;
    for (; ind > 0; ind -= ind & -ind) {
      total += bit[ind];
      total %= MOD;
    }
    return total;
  }

  T range_sum(int l, int r) {
    return (MOD + pref_sum(r) - pref_sum(l - 1)) % MOD;
  }
};

const int MAXN = 1e5 + 100;
HLD<MAXN, true> hld;

int solve(int N, int Q, int M, vector<vector<int>> A) {
  vector<ll> ans(Q, -1);

  DSU dsu;
  dsu.init(N + 1);

  for (int i = 0; i < Q; ++i) {
    auto q = A[i];
    if (q[0] == 1) {
      dsu.merge(q[1], q[2]);
      hld.ae(q[1], q[2]);
    } else if (q[0] == 2) {
      if (!dsu.same(q[1], q[2])) {
        ans[i] = 0;
      }
    }
  }

  hld.init(N + 1, 1);

  vector<int> order(Q);
  for (int i = 0; i < Q; ++i) order[i] = i;

  sort(order.begin(), order.end(), [&](int i, int j) {
    int li = (A[i][0] == 1) ? A[i][4] : A[i][3];
    int lj = (A[j][0] == 1) ? A[j][4] : A[j][3];

    if (li == lj) {
      return i < j;
    }
    return li < lj;
  });

  BIT<ll> bit(N + 1);
  for (int i : order) {
    auto q = A[i];

    if (q[0] == 1) {
      hld.processPath(q[1], q[2], [&](int l, int r) { bit.add(l, q[3]); });
      ans[i] = 0;
    } else if (ans[i] != -1) {
      ll res = 0;

      hld.processPath(q[1], q[2], [&](int l, int r) {
        res += bit.range_sum(l, r);
        res %= MOD;
      });

      ans[i] = res;
    }
  }

  int res = 0;
  for (int i = 0; i < Q; ++i) {
    if (ans[i] != -1) {
      res ^= ans[i];
    }
  }

  return res;
}

void solve(ll _t) {
  int N, Q, M;
  cin >> N >> Q >> M;
  vector<vector<int>> A(Q, vector<int>(5));
  for (int i = 0; i < Q; ++i) {
    for (int j = 0; j < 5; ++j) {
      cin >> A[i][j];
    }
  }

  cout << solve(N, Q, M, A) << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}
