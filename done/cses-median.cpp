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
  ll n, k;
  cin >> n >> k;

  vector<ll> a(n);
  cin >> a;

  multiset<ll> left, right;
  ll left_sum = 0, right_sum = 0;

  auto balance = [&]() {
    while (right.size() < left.size()) {
      auto itr = prev(left.end());
      right.insert(*itr);
      right_sum += *itr;
      left_sum -= *itr;
      left.erase(itr);
    }

    while (left.size() < right.size()) {
      auto itr = right.begin();
      left.insert(*itr);
      left_sum += *itr;
      right_sum -= *itr;
      right.erase(itr);
    }

    while (!left.empty() && !right.empty() && *left.rbegin() > *right.begin()) {
      auto x1 = *left.rbegin(), x2 = *right.begin();
      left.erase(prev(left.end()));
      right.erase(right.begin());
      left.insert(x2);
      right.insert(x1);

      left_sum += (x2 - x1);
      right_sum += (x1 - x2);
    }
  };

  auto calc_answer = [&]() {
    ll m = *left.rbegin();
    return m;
  };

  auto remove = [&](ll v) {
    if (left.find(v) != left.end()) {
      left.erase(left.find(v));
      left_sum -= v;
    } else {
      right.erase((right.find(v)));
      right_sum -= v;
    }
    balance();
  };

  for (ll i = 0; i < k; ++i) {
    right.insert(a[i]);
    right_sum += a[i];
  }
  balance();

  cout << calc_answer() << " ";
  for (ll i = k; i < n; ++i) {
    right.insert(a[i]);
    right_sum += a[i];
    remove(a[i - k]);
    cout << calc_answer() << " ";
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
