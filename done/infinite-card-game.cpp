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

/*

initialy we will have three types of cards
- immediate winning cards (W)
    These cards have defense value greater than all cards attack value;

- immediate losing cards (L)
    These cards allows opponent to throw their immediate winning cards;

- other gray cards (G)


For a game to reach a conclusion, one must be able to throw their
immediate winning cards, so if there isn't any immediate winning
card we can safely say that all the cards will result in a draw;

Now the most optimal strategy one could follow is to throw the card
with maximum defense value which also has the attack value greater than
the thrown card; because throwing the card with higher defense value is
always better than throwing lesser defense value since the options in
more defense value is a subset of the options in higher defense value;


When the game is undecisive? or its a draw?

When the player 1 can always throw a gray card but never a winning card.
so let's say the higher attack value of winning card = hW
and the highest highest attack value of gray card = hG

then, the card thrown defense value is

defence >= hW
defence < hG

let f[i] = index of card that will be thrown after the index 'i' of B
and g[i] = index of card that will be thrown after the index 'j' of A

*/

void solve(ll _t) {
  int n;
  cin >> n;

  vector<array<int, 2>> a(n);
  // (attack, defense) pair
  for (int j = 0; j < 2; ++j) {
    for (int i = 0; i < n; ++i) {
      cin >> a[i][j];
    }
  }
  sort(all(a));

  int m;
  cin >> m;
  vector<array<int, 2>> b(m);
  for (int j = 0; j < 2; ++j) {
    for (int i = 0; i < m; ++i) {
      cin >> b[i][j];
    }
  }
  sort(all(b));

  // for (int j = 0; j < 2; ++j) {
  //   for (int i = 0; i < n; ++i) {
  //     cout << a[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
  // for (int j = 0; j < 2; ++j) {
  //   for (int i = 0; i < m; ++i) {
  //     cout << b[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  // (attack, defense, index) triplets such that
  // higher attack means lower defense
  auto useful_card = [](vector<array<int, 2>> &cards) -> vector<array<int, 3>> {
    vector<array<int, 3>> result;
    int n = cards.size();
    for (int i = 0; i < n; ++i) {
      while (!result.empty() && result.back()[1] <= cards[i][1]) {
        result.pop_back();
      }
      result.push_back({cards[i][0], cards[i][1], i});
    }
    return result;
  };

  // find the highest defense that could be thrown;
  // if it returns (-1) means it doesn't have any cards left
  // and the opponent wins :)
  auto find_index = [](vector<array<int, 3>> &useful, int defense) -> int {
    auto itr =
        upper_bound(all(useful), array<int, 3>{defense, int(1e8), int(1e8)});
    if (itr != useful.end()) {
      return (*itr)[2];
    } else {
      return -1;
    }
  };
  vector<int> f(n), g(m);
  auto A = useful_card(a), B = useful_card(b);

  vector<int> ea(n), eb(m);
  vector<bool> va(n), vb(m);

  for (int i = 0; i < n; ++i) {
    f[i] = find_index(B, a[i][1]);

    if (f[i] == -1) {
      ea[i] = 1;
      va[i] = true;
    }
  }
  for (int i = 0; i < m; ++i) {
    g[i] = find_index(A, b[i][1]);

    if (g[i] == -1) {
      eb[i] = -1;
      vb[i] = true;
    }
  }
  // cout << endl;

  // cout << f << endl;
  // cout << endl;
  // cout << g << endl;

  for (int i = 0; i < n; ++i) {
    if (va[i]) continue;
    va[i] = true;
    ea[i] = 0;

    stack<pii> st;
    st.emplace(0, i);

    while (!st.empty()) {
      auto [turn, idx] = st.top();

      if (turn == 0) {
        int j = f[idx];
        if (vb[j]) {
          ea[idx] = eb[j];
          st.pop();
        } else {
          vb[j] = true;
          eb[j] = 0;
          st.emplace(1, j);
        }
      } else {
        int j = g[idx];
        if (va[j]) {
          eb[idx] = ea[j];
          st.pop();
        } else {
          va[j] = true;
          ea[j] = 0;
          st.emplace(0, j);
        }
      }
    }
  }

  int win = 0, lose = 0, draw = 0;
  for (int i = 0; i < n; ++i) {
    if (ea[i] == 1) {
      win++;
    } else if (ea[i] == 0) {
      draw++;
    } else {
      lose++;
    }
  }
  cout << win << " " << draw << " " << lose << endl;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);

  ll T = 1;
  cin >> T;
  for (ll t = 1; t <= T; ++t) solve(t);
}