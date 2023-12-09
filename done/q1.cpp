#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<char> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  string ans;

  int i = 0;
  while (i < n && v[i] != 'S') i++;
  assert(i < n);

  int j = i;
  while (j < n && v[j] != 'D') j++;

  while (i < j) {
    if (v[i + 1] != '*') {
      ans.push_back('W');
      i++;
    } else {
      ans.push_back('J');
      i++;
      while (i < n && v[i] == '*') i++;
    }
  }

  cout << ans << endl;
}