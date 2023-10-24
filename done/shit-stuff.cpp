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

class Animal {
 public:
  int x = 10;

  void speak() { cout << "Animal speaks" << endl; }
};

class Dog : virtual public Animal {
 public:
  void speak() { cout << "Dog barks" << endl; }
};

class Cat : virtual public Animal {
 public:
  void speak() { cout << "Cat meows" << endl; }
};

class Pet : public Dog, public Cat {};

int main() {
  Pet myPet;
  myPet.Dog::speak();  // Ambiguity: Which speak() method to call?
                       //
  cout << myPet.x << endl;
  return 0;
}
