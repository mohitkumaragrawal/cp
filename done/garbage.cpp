#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
int fx, fy, ix, iy, jx, jy;

vector<vector<bool>> vis;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool done = false;

void dfs(int x, int y) {
  if (vis[x][y]) return;
  vis[x][y] = true;

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

    // check if fire reaches here;

    ll d1 = abs(nx - ix) + abs(ny - iy);
    d1 *= d1;

    ll d2 = (nx - fx) * 1LL * (nx - fx) + (ny - fy) * 1LL * (ny - fy);

    if (nx == jx && ny == jy) {
      done = true;
    }

    if (d1 >= d2) continue;
    dfs(nx, ny);
  }
}

int main() {
  int T;
  cin >> n >> m >> T;

  while (T--) {
    cin >> fx >> fy >> ix >> iy >> jx >> jy;
    done = false;
    vis.assign(n, vector<bool>(m, false));

    if (ix == fx && iy == fy) {
      cout << "NO" << endl;
      continue;
    }

    dfs(ix, iy);

    bool ans = vis[jx][jy] || done;

    if (ans) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}