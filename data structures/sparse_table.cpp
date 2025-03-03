/*
  Example: https://codeforces.com/gym/100093/attachments/download/1236/20122013-tryenirovka-spbgu-b-5-zaprosy-na-otryezkye-dyeryevo-otryezkov-ru.pdf
  Problem: E
*/

#include <bits/stdc++.h>

using namespace std;

const int N = (int)1e6 + 11;
const int inf = 1e9 + 7;

typedef long long ll;
typedef long double ld;

typedef pair < int , int > pii;
typedef pair < ll, ll > pll;

ll a[N], mn[30][N], n, m, u[N], v[N], lg[N], ans[N];

ll get (int l, int r){
  int m = r - l + 1;
  m = lg[m];
  return min (mn[m][l], mn[m][r - (1 << m) + 1]);
}

int main (){
  freopen ("sparse.in", "r", stdin);
  freopen ("sparse.out", "w", stdout);
  
  scanf ("%lld %lld %lld %lld %lld", &n, &m, &a[1], &u[1], &v[1]);

  for (int i = 1; i <= n; ++i){
    a[i + 1] = (23 * a[i] + 21563) % 16714589;
    mn[0][i] = a[i];
  }

  for (int i = 2; i <= n; ++i){
    lg[i] = lg[i / 2] + 1;
  }

  for (int i = 1; i <= lg[n]; ++i){
    for (int j = 1; j <= (n - (1 << lg[i]) + 1); ++j){
      mn[i][j] = min (mn[i - 1][j], mn[i - 1][j + (1 << (i - 1))]);
    }
  }

  for (int i = 1; i <= m; ++i){
    int l, r;
    l = min(u[i], v[i]);
    r = max(u[i], v[i]);
    ans[i] = get (l, r);
		v[i + 1] =(((13 * v[i]) +( 593 + ans[i] + (5 * i)) ) % n) + 1;
		u[i + 1] =(((17 * u[i]) +( 751 + ans[i] + (2 * i)) ) % n) + 1;
  }

  printf ("%lld %lld %lld", u[m], v[m], ans[m]);
  return 0;
}
