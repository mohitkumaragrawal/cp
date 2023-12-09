#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 100;

vector<int> sieve(N);

vector<int> get_factors(int x) {
  vector<int> factors;

  while (x > 1) {
    factors.push_back(sieve[x]);
    x /= sieve[x];
  }

  sort(factors.begin(), factors.end());
  factors.erase(unique(factors.begin(), factors.end()), factors.end());
  return factors;
}

bool vis[2 * N];
vector<int> adj[2 * N];

void dfs(int u) {
  vis[u] = true;

  for (int v : adj[u]) {
    if (!vis[v]) {
      dfs(v);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  for (int i = 1; i < N; ++i) {
    sieve[i] = i;
  }

  for (int i = 2; i < N; ++i) {
    if (sieve[i] == i) {
      for (int j = i; j < N; j += i) {
        sieve[j] = i;
      }
    }
  }

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  for (int i = 0; i < n; ++i) {
    auto f = get_factors(a[i]);

    for (int j : f) {
      adj[i].push_back(j + n);
      adj[j + n].push_back(i);
    }
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      ++ans;
      dfs(i);
    }
  }

  cout << ans << endl;
}