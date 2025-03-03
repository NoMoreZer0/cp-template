/*
  Example problem: https://codeforces.com/contest/271/submission/75746188
*/

# include <bits/stdc++.h>

# define pb emplace_back
# define sz(x) (int)((x).size())
# define whole(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;

const int mod1 = 1000000007;
const int mod2 = 1000000009;
const int P1 = max(259, rand());
const int P2 = max(261, rand());
const int N = 2000;
  
string s, alpha;
int k, pref[N];
pair < ll, ll > h[N], deg[N];

pair < ll, ll > get (int l, int r)
{
  --l, --r;
  ll ans1 = (h[r + 1].first - (h[l].first * 1ll * deg[r - l + 1].first)) % mod1;
  ll ans2 = (h[r + 1].second - (h[l].second * 1ll * deg[r - l + 1].second)) % mod2;
  if (ans1 < 0) ans1 += mod1;
  if (ans2 < 0) ans2 += mod2;
  return {ans1, ans2};
}

int main(){ 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> s >> alpha >> k;
  for (int i = 0; i < 26; ++i)
  {
    if (alpha[i] == '0') alpha[i] = '1';
    else alpha[i] = '0';
  }
  int n = sz(s);
  for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + (alpha[s[i - 1] - 'a'] - '0');
  deg[0].first = 1;
  deg[0].second = 1;   
  deg[1].first = mod1;
  deg[1].second = mod2;
  for (int i = 0; i < n; ++i)
  {
    h[i + 1].first = ((h[i].first * 1ll * P1) % mod1 + s[i]) % mod1;
    h[i + 1].second = ((h[i].second * 1ll * P2) % mod2 + s[i]) % mod2;
    deg[i + 1].first = (deg[i].first * 1ll * P1) % mod1;
    deg[i + 1].second = (deg[i].second * 1ll * P2) % mod2;
  }
  set < pair < ll, ll > > st;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = i; j <= n; ++j)
    {
      if (pref[j] - pref[i - 1] <= k) st.insert(get(i, j));
    }
  }
  cout << sz(st) << "\n";
  return 0;
}