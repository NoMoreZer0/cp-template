/*
    Example: https://codeforces.com/gym/100094/attachments/download/1239/20122013-tryenirovka-spbgu-b-6-zaprosy-na-otryezkye-dyeryevo-otryezkov-2-ru.pdf
    Problem: C
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = (int)1e6 + 7;
const int INF = (int)1e9 + 7;
const ll linf = (ll)1e18 + 1;

struct node {
    int cnt, pref, suff, add, sum;
} t[N * 4]; 

node combine(node a, node b) { 
    node cur;
    cur.pref = a.pref, cur.suff = b.suff;
    cur.cnt = b.cnt + a.cnt;
    cur.sum = a.sum + b.sum;
    cur.add = -1;
    if (a.suff && b.pref) cur.cnt--;
    return cur;
}

void build(int v, int tl, int tr) { 
    if (tl == tr) { 
        t[v].cnt = t[v].pref = t[v].suff = t[v].sum = 0;
        t[v].add = -1;
    } else { 
        int tm = tl + tr >> 1;
        build((v << 1), tl, tm);
        build((v << 1) + 1, tm + 1, tr);
        t[v] = combine(t[(v << 1)], t[(v << 1) + 1]);
    }
}

void push(int v, int tl, int tr) { 
    if (t[v].add != -1) {
        t[v].sum = (tr - tl + 1) * t[v].add;
        t[v].pref = t[v].suff = t[v].sum;
        t[v].cnt = t[v].add;
        if (tl != tr) t[(v << 1) + 1].add = t[(v << 1)].add = t[v].add;
        t[v].add = -1;
    }
}

void update(int v, int tl, int tr, int l, int r, int val) { 
    push(v, tl, tr);
    if (tl > r || tr < l || l > r) return;
    if (l <= tl && tr <= r) {
        t[v].add = val;
        push(v, tl, tr);
        return;
    } 
    int tm = tl + tr >> 1;
    update((v << 1), tl, tm, l, r, val);
    update((v << 1) + 1, tm + 1, tr, l, r, val);
    t[v] = combine(t[(v << 1)], t[(v << 1) + 1]);
}

int main() { 
    freopen("painter.in", "r", stdin);
    freopen("painter.out", "w", stdout);
    int n; cin >> n;
    build(1, 0, N);
    for (int i = 1; i <= n; ++i) { 
        char type; cin >> type;
        int l, x; cin >> l >> x;
        l += (int)5e5;
        if (type == 'W') update(1, 0, N, l, l + x - 1, 0);
        else update(1, 0, N, l, l + x - 1, 1);
        cout << t[1].cnt << " " << t[1].sum << "\n";
    }
    return 0;
}