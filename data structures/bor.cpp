/*
    Example problem: https://codeforces.com/contest/706/submission/71739826
*/

# include <bits/stdc++.h>

# define pb push_back
# define sz(x) (int)((x).size())
# define whole(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
const int mod = 1000000007;
const int N = 3000005;

int n, sz = 1; 

struct trie {
 int next[2], cnt;
 trie()
 {
  cnt = 0;
  next[0] = next[1] = 0;
 }
}t[N * 5];

void add (int x, int val)
{
 int v = 1;
 for (int bit = 30; bit >= 0; --bit)
 {
  int nextbit = ((x >> bit) & 1);
  if (!t[v].next[nextbit]) t[v].next[nextbit] = ++sz;
  v = t[v].next[nextbit];
  t[v].cnt += val;
 }
}

int get (int x)
{
 int ans = 0, v = 1;
 for (int bit = 30; bit >= 0; --bit)
 {
  int nextbit = ((x >> bit) & 1);
  int can = (nextbit ^ 1);
  if (t[v].next[can] && t[t[v].next[can]].cnt > 0) ans += (1 << bit), v = t[v].next[can];
  else v = t[v].next[nextbit];
 }
 return ans;
}

int main(){    
 cin >> n;
 add(0, 1);
 for (int i = 1; i <= n; ++i)
 {
  char type;
  int val;
  cin >> type >> val;
  if (type == '+') add(val, 1);
  else if (type == '-') add(val, -1);
  else printf ("%d\n", get(val));
 }
}