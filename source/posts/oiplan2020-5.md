title: 王道征途——NOIP2020冲刺计划·第五周(7.20~7.26)
date: 2020-07-20
weight: 20200720
<!--more-->
### 2020-07-20
今天尝试去证明昨天做的树网的核那题的结论，把证明过程都写在上一篇里面了。

#### [SDOI2011]消防
https://www.luogu.com.cn/problem/P2491

这题和树网的核那题有区别吗？

不过重新写一遍熟悉一下双指针也好，因为有些细节需要小心。

```cpp
#include<cstdio>
#include<cstring>
#include<vector>

const int MAXN = 300100;
int n, s, back[MAXN], maxnode, maxdis, diaecc, ans = 0x3fffffff;
bool indiameter[MAXN];
struct edge { int to, next, w; };
struct graph {
    int ecnt = 1, head[MAXN];
    edge edges[MAXN << 1];
    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
std::vector<int> diameter;
struct tools {
    static inline int max(int a, int b) { return a > b ? a : b; }
    static inline int min(int a, int b) { return a < b ? a : b; }
};

void dfs1(int x, int lst, int dis) {
    if (maxdis < dis) {
        maxdis = dis;
        maxnode = x;
    }
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &t = g.edges[i].to;
        back[t] = i ^ 1;
        dfs1(t, i, dis + g.edges[i].w);
    }
}
void dfs2(int x) {
    if (!x) return;
    indiameter[x] = true;
    diameter.push_back(g.edges[back[x]].w);
    dfs2(g.edges[back[x]].to);
}
void dfs3(int x, int lst, int dis) {
    if (indiameter[x]) dis = 0;
    diaecc = tools::max(diaecc, dis);
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &t = g.edges[i].to;
        dfs3(t, i, dis + g.edges[i].w);
    }
}

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w), g.addedge(v, u, w);
    }
    dfs1(1, 0, 0);
    memset(back, 0, sizeof(int) * (n + 1));
    maxdis = 0;
    dfs1(maxnode, 0, 0);
    dfs2(maxnode);
    dfs3(maxnode, 0, 0);
    int l = 0, r = 0, ldis = 0, rdis = maxdis, len = 0;
    while (r + 1 <= (int)diameter.size() - 1 && len + diameter[r] <= s) rdis -= diameter[r], len += diameter[r], r++;
    while (l <= (int)diameter.size() - 1) {
        ans = tools::min(ans, tools::max(diaecc, tools::max(ldis, rdis)));
        ldis += diameter[l], len -= diameter[l], l++;
        while (r + 1 <= (int)diameter.size() - 1 && len + diameter[r] <= s) rdis -= diameter[r], len += diameter[r], r++;
    }
    printf("%d\n", ans);
    return 0;
}
```