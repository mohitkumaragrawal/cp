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

map<string, string> jsonParser(string &json) {
  int n = json.size();

  map<string, string> res;
  if (n == 0 || json[1] == '}') return res;

  int cur = 0;
  auto read_word = [&]() -> string {
    if (json[cur] == '"') cur++;
    string ans;
    while (json[cur] != '"') {
      ans.push_back(json[cur]);
      cur++;
    }
    cur++;
    return ans;
  };

  cur = 1;
  while (json[cur] != '}') {
    string key = read_word();
    cur++;
    string val = read_word();
    if (json[cur] == ',') cur++;
    res[key] = val;
  }

  return res;
}

vector<string> getJSONDiff(string json1, string json2) {
  auto obj1 = jsonParser(json1);
  auto obj2 = jsonParser(json2);

  vector<string> ans;
  for (auto it : obj1) {
    string k = it.first;
    string v = it.second;
    if (obj2.find(k) != obj2.end() && obj2[k] != v) {
      ans.push_back(k);
    }
  }
  return ans;
}

#define long long long

long pthFactor(long n, long p) {
  vector<long> smaller, larger;
  long total = 0;

  for (long i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      ll j = n / i;

      smaller.push_back(i);
      if (i != j) {
        larger.push_back(j);
      }
    }
  }

  if (smaller.size() + larger.size() < p) {
    return 0;
  }
  if (p <= smaller.size()) {
    return smaller[p - 1];
  }
  p -= smaller.size();
  return larger[larger.size() - p];
}

void solve(ll _t) {
  ll n, p;
  cin >> n >> p;

  cout << pthFactor(n, p);
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  /* cin >> T; */
  for (ll t = 1; t <= T; ++t) solve(t);
}
