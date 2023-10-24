#include <bits/stdc++.h>
#include <ctype.h>
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

int findMaxNum(int x, int y, int z) {
  int m = (x + y + z) / 2;
  if (m < x || m < y) return -1;
  return m;
}

int countValidWords(const string &str) {
  int ans = 0;
  stringstream ss(str);

  string word;
  string vowels = "aeiou";
  while (ss >> word) {
    if (word.size() < 3) continue;
    bool vow = false, cons = false, valid = true;
    int cnt = 0;
    for (char ch : word) {
      char x = tolower(ch);

      if (isalnum(x)) {
        cnt++;
      } else {
        valid = false;
      }

      bool vv = false;
      for (char xx : vowels) {
        if (x == xx) vv = true;
      }
      if (isalpha(x)) {
        if (vv) {
          vow = true;
        } else {
          cons = true;
        }
      }
    }
    if (!valid || !vow || !cons) continue;
    if (cnt >= 3) ans++;
  }
  return ans;
}

template <typename node_type, typename tag_type>
struct lazy_segtree {
  vector<node_type> tree;
  vector<tag_type> lazy;
  int n;
  template <typename Iter>
  void init(Iter first, Iter last, int nn = -1) {
    n = nn;
    if (n == -1) n = distance(first, last);
    tree.resize(4 * n);
    lazy.resize(4 * n);
    build_tree(0, 0, n - 1, first);
  }
  node_type query(int ql, int qr) { return query(0, 0, n - 1, ql, qr); }
  void update(int ql, int qr, tag_type const &val) {
    update(0, 0, n - 1, ql, qr, val);
  }

 private:
  template <typename Iter>
  void build_tree(int id, int tl, int tr, Iter first) {
    if (tl == tr) {
      tree[id].init(tl, tr, *(first + tl));
      lazy[id].init(tl, tr);
      return;
    }
    int tm = (tl + tr) / 2;
    build_tree(2 * id + 1, tl, tm, first);
    build_tree(2 * id + 2, tm + 1, tr, first);
    tree[id] = node_type::merge(tree[2 * id + 1], tree[2 * id + 2]);
    lazy[id].init(tl, tr);
  }
  void push(int id, int tl, int tr) {
    if (tl != tr) {
      int tm = (tl + tr) / 2;
      tree[2 * id + 1].apply(tl, tm, lazy[id]);
      lazy[2 * id + 1].merge(lazy[id]);
      tree[2 * id + 2].apply(tm + 1, tr, lazy[id]);
      lazy[2 * id + 2].merge(lazy[id]);
    }
    lazy[id].reset();
  }
  node_type query(int id, int tl, int tr, int ql, int qr) {
    if (tl > qr || ql > tr) return node_type::phi();
    if (ql <= tl && tr <= qr) return tree[id];
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    return node_type::merge(query(2 * id + 1, tl, tm, ql, qr),
                            query(2 * id + 2, tm + 1, tr, ql, qr));
  }
  void update(int id, int tl, int tr, int ql, int qr, tag_type const &val) {
    if (tl > qr || ql > tr) return;
    if (ql <= tl && tr <= qr) {
      tree[id].apply(tl, tr, val);
      lazy[id].merge(val);
      return;
    }
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, ql, qr, val);
    update(2 * id + 2, tm + 1, tr, ql, qr, val);
    tree[id] = node_type::merge(tree[2 * id + 1], tree[2 * id + 2]);
  }
};
struct tag {
  ll inc;
  void reset() { inc = 0; }
  void merge(tag const &other) { inc += other.inc; }
  void init(int tl, int tr) {}
};
struct node {
  static node phi() { return {0LL}; }
  static node merge(node const &a, node const &b) { return {a.data + b.data}; }
  ll data;
  void apply(ll tl, ll tr, tag const &t) { data += (tr - tl + 1) * t.inc; }
  template <typename T>
  void init(ll tl, ll tr, T &ddata) {
    this->data = ddata;
  }
};

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

int getCount(string binary) {
  set<int> st;
  int n = binary.size();

  for (int j = 1; j < (1 << n); ++j) {
    int p = 1;
    int x = 0;

    for (int i = n - 1; i >= 0; --i) {
      if (((j >> i) & 1) == 1) {
        if (binary[i] == '1') x += p;
        p *= 2;
      }
    }

    st.insert(x);
  }

  return st.size();
}

vector<string> recentlyViewed(vector<string> logs) {
  reverse(logs.begin(), logs.end());
  set<string> seen;
  vector<string> res;

  for (string s : logs) {
    if (seen.find(s) != seen.end()) continue;
    res.push_back(s);
    seen.insert(s);
  }
  return res;
}

int findMinimumInefficiency(string serverType) {
  int j = 0;
  int n = serverType.size();
  while (j < n && serverType[j] == '?') j++;
  if (j >= n) return 0;

  for (int i = 0; i < j; ++i) serverType[i] = serverType[j];
  for (int i = j + 1; i < n; ++i) {
    if (serverType[i] == '?') serverType[i] = serverType[i - 1];
  }

  int ans = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (serverType[i] != serverType[i + 1]) ans++;
  }
  return ans;
}

vector<int> predictDays(vector<int> day, int k) {
  int n = day.size();
  vector<int> inc(n), dec(n);

  for (int i = 1; i < n; ++i) {
    if (day[i] <= day[i - 1]) dec[i] = 1 + dec[i - 1];
  }
  for (int i = n - 2; i >= 0; --i) {
    if (day[i] <= day[i + 1]) inc[i] = 1 + inc[i + 1];
  }

  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (inc[i] >= k && dec[i] >= k) ans.push_back(i + 1);
  }
  return ans;
}

void solve(ll _t) {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  cin >> a;

  cout << predictDays(a, k) << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  for (ll t = 1; t <= T; ++t) solve(t);
}
