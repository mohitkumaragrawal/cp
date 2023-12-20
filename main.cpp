#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (ll i = 0; i < n; i++)
#define rem(i, n) for (ll i = n - 1; i >= 0; i--)
#define ll long long
#define vl vector<ll>
#define pi pair<ll, ll>
#define f first
#define s second
#define pb push_back
#define mod 1000000007
#define mi 1000001
// #define vli(n) vector<ll> v;for (ll i = 0; i < n; i++){ ll a; cin >> a;v.pb(a);}
// #define vl2i(n, m)  vector<vector<ll>> v;  for (ll i = 0; i < n; i++){ vector<ll> temp;for (ll j = 0; j < m; j++){ll a;cin >> a; temp.pb(a);}v.pb(temp);}
void bfs(ll n, vector<ll>adj[],vector<ll>&ans)
{
    ll vis[n] = {0};//(1based-----n+1)   (0 based----n )
    vis[0] = 1;

    queue<pair<ll,ll>> q;
    q.push({0,0});
    while (!q.empty())
    {
        ll node = q.front().first;
        ll par=q.front().second;
        ans[par]++;
        q.pop();
        for (auto it : adj[node])
        {
            if (vis[it]==0)
            {
                vis[it] = 1;
                q.push({it,par+1});
            }
        }
    }
     return ;
}
int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ll q;
  cin >> q;
  while(q--)
  {
    ll n;
    cin>>n;
    vector<ll> v;for (ll i = 0; i < n-1; i++){ ll a; cin >> a;v.pb(a);}
    vector<ll> adj[n];
    vector<ll>ans(n,0);
    for (int i = 0; i < n-1; i++)
    {
        adj[v[i]-1].pb(i+1);
    }
    bfs(n,adj,ans);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << i << "---";
    //     for (int j = 0; j < adj[i].size(); j++)
    //     {
    //         cout << adj[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for(ll i=0;i<n;i++)
    // {
    //     cout<<ans[i]<<" ";
    // }
    // cout<<endl;
    ll count=0;
    ll prev1=0,prev2=0;
    for(ll i=n-1;i>0;i--)
    {
        ll remcur=0;
        if(ans[i]>0)
        {
          if(prev2>0 && ans[i]>1)
          {
              if(ans[i]>=prev2)
              {
               count+=prev2;
               ans[i]-=prev2;
               prev2=0;
              }
              else
              {
                  count+=ans[i];
                  prev2-=ans[i];
                  ans[i]=0;
              }
          }
          if(ans[i]>1 && prev1!=0)
          {
              count++;
              prev1=0;
              ans[i]--;
          }
          count+=(ans[i]/2);
          if(ans[i]%2!=0)
          {
            remcur=1;
          }
        }
        prev2+=prev1;
        prev1=remcur;
        // cout<<count<<" "<<prev1<<" "<<prev2<<endl;
    }
    // cout<<endl;
    cout<<count<<endl;
  }
}