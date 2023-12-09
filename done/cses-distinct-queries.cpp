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
    ind++;
    for (; ind <= size; ind += ind & -ind) {
      bit[ind] += val;
    }
  }
  T pref_sum(int ind) {
    ind++;
    T total = 0;
    for (; ind > 0; ind -= ind & -ind) {
      total += bit[ind];
    }
    return total;
  }
};

void solve(ll _t) {
  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  cin >> a;

  vector<tuple<int, int, int>> queries(q);
  for (int i = 0; i < q; ++i) {
    auto &[l, r, idx] = queries[i];
    cin >> l >> r;
    idx = i;
    l--, r--;
  }
  sort(all(queries));

  BIT<int> bit(n);
  map<int, int> mp;

  vector<int> ans(q);

  int j = q - 1;
  for (int i = n - 1; i >= 0; --i) {
    if (j < 0) break;

    if (mp.count(a[i])) {
      int t = mp[a[i]];
      bit.set(t, 0);
    }
    mp[a[i]] = i;
    bit.set(i, 1);

    while (j >= 0 && get<0>(queries[j]) == i) {
      auto [l, r, idx] = queries[j];
      ans[idx] = bit.pref_sum(r);
      j--;
    }
  }

  for (auto x : ans) cout << x << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}