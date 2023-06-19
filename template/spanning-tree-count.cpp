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

ostream &operator<<(ostream &out, vector<vector<ll>> &M) {
  for (auto v : M) out << v << endl;
  return out;
}

// calculates the absolute value of the determinant;
ll det(vector<vector<ll>> M, ll n) {
  // find guassian elimination
  ll row_anchor = 0, col_anchor = 0;

  vector<ll> N, D;
  while (col_anchor < n) {
    // find a row;
    for (int i = row_anchor; i < n; ++i) {
      if (M[i][col_anchor] != 0) {
        swap(M[i], M[row_anchor]);
        break;
      }
    }

    if (M[row_anchor][col_anchor] == 0) {
      ++col_anchor;
      continue;
    }

    // make all other rows 0
    for (int i = row_anchor + 1; i < n; ++i) {
      ll x = M[i][col_anchor], y = M[row_anchor][col_anchor];

      if (x == 0) continue;

      ll lcm = (x * y) / __gcd(x, y);

      ll f1 = lcm / x;
      ll f2 = lcm / y;

      D.push_back(f1);

      for (ll j = 0; j < n; ++j) {
        M[i][j] = M[i][j] * f1 - M[row_anchor][j] * f2;
      }
    }
    row_anchor++;
    col_anchor++;
  }

  for (ll i = 0; i < n; ++i) N.push_back(M[i][i]);

  // now cancel the stuff from the numerator and denominator;
  for (auto &x : D) {
    for (auto &y : N) {
      ll g = __gcd(x, y);
      if (g != 1) {
        x /= g;
        y /= g;
      }
    }
  }

  ll det = 1;
  for (ll x : N) det *= x;
  for (ll y : D) det /= y;

  return det;
}

int spanningTrees(vector<vector<int>> &M, int n, int m) {
  // Write your code here

  vector<int> degree(n);
  for (int i = 0; i < n; ++i) {
    int deg = 0;
    for (int j = 0; j < n; ++j) {
      if (M[i][j] == 1) {
        deg++;
      }
    }
    degree[i] = deg;
  }

  // laplacian matrix;

  vector<vector<ll>> L(n, vector<ll>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j)
        L[i][j] = degree[i];
      else
        L[i][j] = -M[i][j];
    }
  }

  // now find absolute value of the cofactor of this
  // laplacian matrix; to do that we will
  // remove the last row and last column;
  // and find it's determinant;

  int ans = det(L, n - 1);
  return ans;
}

int main() {
  int T;
  cin >> T;

  while (T--) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;

      mat[u][v] = 1;
      mat[v][u] = 1;
    }

    cout << spanningTrees(mat, n, m) << endl;
  }
}
