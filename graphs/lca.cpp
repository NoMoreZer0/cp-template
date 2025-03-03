/*
  Example problem: https://codeforces.com/contest/519/submission/40883679
*/
#include <bits/stdc++.h>

using namespace std;

const int N = (int)2e5 + 3;
const int INF = 1e9 + 7;

typedef long long ll;
typedef long double ld;

typedef pair < int, int > pii;
typedef pair < ll, ll > pll;

int n, tin[N], tout[N], timer, up[N][22], sz[N], d[N];
vector < int > g[N];

bool isanc (int x, int y){
  return tin[x] <= tin[y] && tout[x] >= tout[y];
}

void dfs (int v, int p = -1, int depth = 0){
  tin[v] = timer++;
  sz[v] = 1;
  d[v] = depth;
  for (int i = 1; i <= 20; ++i){
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (int i = 0; i < g[v].size(); ++i){
    int to = g[v][i];
    if (to == p) continue;
    up[to][0] = v;
    dfs(to, v, depth + 1);
    sz[v] += sz[to];
  }
  tout[v] = timer++;
}

int lca (int v, int u){
  if (tin[v] < tin[u]) swap (v, u);
  for (int i = 20; i >= 0; --i){
    if (!isanc(up[v][i], u)){
      v = up[v][i];
    }
  }
  v = up[v][0];
  return v;
}

int main(){
  scanf ("%d", &n);
  for (int i = 1; i <= n - 1; ++i){
    int x, y;
    scanf ("%d %d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  up[1][0] = 1;
  dfs(1);
  int q;
  scanf ("%d", &q);
  for (int i = 1; i <= q; ++i){
    int a, b;
    scanf ("%d %d", &a, &b);
    if (a == b){
      printf ("%d\n", n);
      continue;
    }
    int l = lca(a, b), res = 0;
    if (d[a] - d[l] == d[b] - d[l]){
      int aa = a, bb = b;
      for (int j = 20; j >= 0; --j){
        if (!isanc(up[aa][j], l)){
          aa = up[aa][j];
        }
      }
      for (int j = 20; j >= 0; --j){
        if (!isanc(up[bb][j], l)){
          bb = up[bb][j];
        }
      }
      res = n - sz[aa] - sz[bb];
    } else {
      if (d[a] < d[b]) swap (a, b);
      int to = a;
      int dist = d[a] + d[b] - 2 * d[l];
      if (dist & 1){
        res = 0;
      } else {
        dist /= 2;
        int to = a;
        for (int j = 20; j >= 0; --j){
          if (d[a] - d[up[to][j]] < dist){
            to = up[to][j];
          }
        }
        res = sz[up[to][0]] - sz[to];
      }
    }
    printf ("%d\n", res);
  }
  return 0;
}