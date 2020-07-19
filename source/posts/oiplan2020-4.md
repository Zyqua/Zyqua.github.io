title: 王道征途——NOIP2020冲刺计划·第四周(7.13~7.19)
date: 2020-07-13
weight: 20200713
<!--more-->
### 2020-07-13 ~ 2020-07-16
因为要中考所以没刷题。
### 2020-07-17
关于最小生成树：
- 切割性质：将点集分为任意两个不相交的非空子集，则连接两个不同点集的点的最小的边一定在图的最小生成树中。
- 回路性质：原图的环上最大的边一定不在图的最小生成树中。
- 一个没有名字但常见的思路：把一条边加入到当前的生成树中形成一个环，若这条边小于环上最大的边则把最大的边去掉，加入当前边，形成的新生成树比原生成树小。
- 由上面得出的一个推论：原图的环上最小的边一定在图的最小生成树中。
#### 走廊泼水节
https://www.acwing.com/problem/content/description/348/

对于树上的一条边，边的两侧是两个连通块，需要在两个连通块之间加边，使得每两个节点之间都有边。为了不破坏原有的最小生成树，所加的边的边权必须大于当前最小生成树的最大边，因此至少为当前边的边权加一。一条边对答案的贡献为$(w+1)\times(size_x\times size_y - 1)$。

对于为什么要从小到大扫描，网上的题解大多知其然不知其所以然。这个问题我想了半天，最后得出的结论是为了使答案最小。最小生成树不变已经在上面的操作中得到了保证，而从小到大扫描可以使答案最小。考虑不按照从小到大扫描，每次合并时加的边权是两个生成树中最大的边的边权加一，那么大的边更早地加入到最小生成树中，显然会使每次合并时的答案更大。为了使答案最小，大的边需要尽量晚地加入到最小生成树中。
```cpp
#include<cstdio>
#include<algorithm>

int t, n, ans;
struct tools { static inline void swap(int &a, int &b) { int t = a; a = b; b = t; } };
struct edge {
    int u, v, w;
    bool operator < (const edge &a) const { return w < a.w; }
}edges[6010];
struct unionsetnode { int fa, size; };
struct unionset {
    unionsetnode nodes[6010];
    inline void init() { for (int i = 1; i <= n; i++) nodes[i].fa = i, nodes[i].size = 1; }
    int find(int x) {
        if (nodes[x].fa == x) return x;
        return nodes[x].fa = find(nodes[x].fa);
    }
    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (nodes[x].size < nodes[y].size) tools::swap(x, y);
        nodes[y].fa = x;
        nodes[x].size += nodes[y].size;
    }
    inline bool same(int x, int y) { return find(x) == find(y); }
    inline int count(int x) { return nodes[find(x)].size; }
}uset;

int main() {
    scanf("%d", &t);
    while (t--) {
        ans = 0;
        scanf("%d", &n);
        uset.init();
        for (int i = 1; i < n; i++)
            scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        std::sort(edges + 1, edges + n);
        for (int i = 1; i < n; i++) {
            int &u = edges[i].u, &v = edges[i].v, &w = edges[i].w;
            ans += (w + 1) * (uset.count(u) * uset.count(v) - 1);
            uset.merge(u, v);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

#### MST Company
https://www.luogu.com.cn/problem/CF125E

假设给出的是连通图。把与$1$相连的边去掉后求一遍最小生成森林，并在$1$与每个连通块之间加入一条最小的边。如果$1$的度数大于$k$，则无解。否则需要做若干次操作，每次加入一条端点是$1$的边，并删掉形成的环上最大的边(为了使生成树最小)，为了使生成树最小，每次操作的权值和增量需要最小。

主要思路就是这么简单，然而代码有些复杂。主要就是别把边在数组的下标和在原图的序号写混了，然后记得判无解，还有我把`diredge edges[MAXM << 1]`写成了`diredge edges[MAXN << 1]`导致$\texttt{RE}$，二十分钟才调出来。

还有，这题第一行输出边的数量，第二行输出的边在原图的序号，顺序任意。翻译里没写，我就自己猜的。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN = 5010, MAXM = 100100;
int n, m, k, maxid[MAXN], maxw[MAXN], deg1, ccminid[MAXN], ccminw[MAXN], cnt;
bool inmst[MAXM];
struct undiredge {
    int u, v, w, id;
    bool operator < (const undiredge &a) const { return w < a.w; }
}edges[MAXM];
struct diredge { int to, next, w, id; };
struct graph {
    int ecnt = 1, head[MAXN];
    diredge edges[MAXM << 1];
    inline void addedge(int u, int v, int w, int id) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].id = id;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct tools {
    static inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
    static inline int max(int a, int b) { return a > b ? a : b; }
    static inline int maxedge(int i, int j) { return g.edges[i].w > g.edges[j].w ? i : j; }
};
struct unionsetnode { int fa, size; };
struct unionset {
    unionsetnode nodes[MAXN];
    inline void init() {
        for (int i = 1; i <= n; i++) nodes[i].fa = i, nodes[i].size = 1;
    }
    int find(int x) {
        if (nodes[x].fa == x) return x;
        return nodes[x].fa = find(nodes[x].fa);
    }
    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (nodes[x].size < nodes[y].size) tools::swap(x, y);
        nodes[y].fa = x;
        nodes[x].size += nodes[y].size;
    }
    inline bool same(int x, int y) { return find(x) == find(y); }
}uset;

inline void kruskal() {
    for (int i = 1; i <= m; i++) {
        int &u = edges[i].u, &v = edges[i].v;
        if (u == 1 || v == 1) continue;
        if (!uset.same(u, v)) {
            uset.merge(u, v);
            inmst[edges[i].id] = true;
            cnt++;
        }
    }
}
void dfs(int x, int maxidnow, int maxwnow, int lst) {
    maxid[x] = g.edges[maxidnow].id;
    maxw[x] = maxwnow;
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1) || !inmst[g.edges[i].id]) continue;
        int &t = g.edges[i].to, &w = g.edges[i].w;
        if (x ^ 1) dfs(t, tools::maxedge(maxidnow, i), tools::max(maxwnow, w), i);
        else dfs(t, maxidnow, maxwnow, i);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges[i].u = u, edges[i].v = v, edges[i].w = w, edges[i].id = i;
        g.addedge(u, v, w, i), g.addedge(v, u, w, i);
    }
    std::sort(edges + 1, edges + m + 1);
    uset.init();
    kruskal();
    memset(ccminw, 0x3f, sizeof(int) * (n + 1));
    for (int i = g.head[1]; i; i = g.edges[i].next) {
        int t = uset.find(g.edges[i].to), &w = g.edges[i].w;
        if (ccminw[t] > w) {
            ccminw[t] = w;
            ccminid[t] = g.edges[i].id;
        }
    }
    for (int i = 1; i <= n; i++)
        if (ccminid[i]) inmst[ccminid[i]] = true, deg1++, cnt++;
    while (deg1 < k) {
        dfs(1, 0, 0, 0);
        int addid = 0, mindelta = 0x3fffffff, delid = 0;
        for (int i = g.head[1]; i; i = g.edges[i].next) {
            if (inmst[g.edges[i].id]) continue;
            int &t = g.edges[i].to, &w = g.edges[i].w;
            if (mindelta > w - maxw[t]) {
                mindelta = w - maxw[t];
                addid = g.edges[i].id;
                delid = maxid[t];
            }
        }
        if (!addid || !delid) break;
        inmst[delid] = false;
        inmst[addid] = true;
        deg1++;
    }
    if (deg1 ^ k || cnt ^ (n - 1)) printf("-1\n");
    else {
        printf("%d\n", n - 1);
        for (int i = 1; i <= m; i++)
            if (inmst[i]) printf("%d ", i);
    }
    return 0;
}
```

### 2020-07-18
#### 黑暗城堡
https://loj.ac/problem/10064

先做一遍$\texttt{Dijkstra}$求最短路，然后对于边$(u,v)$，若$dis[u]+w=dis[v]$则说明这条边可行。做一个类似于$\texttt{Prim}$算法的过程，把节点按照$dis$从小到大排序，以保证$dis[x]>dis[t]$，$x$是当前要加入的节点，$t$是已加入且与$x$有边的节点。找到满足$dis[x]+w=dis[t]$的边的数量，然后根据乘法原理乘到答案里。

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

const int MOD = (1 << 31) - 1;
int n, m, dis[1010], nodes[1010], rank[1010];
bool vis[1010];
long long ans = 1;
struct edge {
    int to, next, w;
};
struct graph {
    int ecnt, head[1010];
    edge edges[1000100];
    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x, dist;
    node(int xv = 0, int dv = 0) : x(xv), dist(dv) {}
    bool operator<(const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline void dijkstra() {
    q.push(node(1, 0));
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    dis[1] = 0;
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x])
            continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, w = g.edges[i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
            }
        }
    }
}
inline bool cmp(int &i, int &j) { return dis[i] < dis[j]; }

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w), g.addedge(v, u, w);
    }
    dijkstra();
    for (int i = 1; i <= n; i++) nodes[i] = i;
    std::sort(nodes + 1, nodes + n + 1, cmp);
    for (int i = 1; i <= n; i++) rank[nodes[i]] = i;
    for (int i = 2; i <= n; i++) {
        int x = nodes[i], cnt = 0;
        for (int j = g.head[x]; j; j = g.edges[j].next) {
            int &t = g.edges[j].to, &w = g.edges[j].w;
            if (dis[x] == dis[t] + w && rank[t] < rank[x])
                cnt++;
        }
        ans = (ans * cnt) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
```

#### 二分图最大匹配
https://www.luogu.com.cn/problem/P3386

对于每个节点从它出发找增广路，找到了就把增广路上的边取反，使得这个节点找到匹配点。因为前面的节点只会改变匹配点，不会失去匹配，所以从每个节点出发遍历一次就可以。

需要注意的是图的存储比较特别，只需要存从左部到右部的边，不需要存反向边。开的数组也是只需要开左部的大小。因为$\texttt{DFS}$时当前节点总是在左部，虽然边指向右部节点但直接就通过$\texttt{match}$数组跳到左部了。

```cpp
#include<cstdio>
#include<cstring>

int n, m, e, ans, match[510];
bool vis[510];
struct edge { int to, next; };
struct graph {
    int ecnt, head[510];
    edge edges[50100];
    inline void addedge(int u, int v) {
        edges[++ecnt].to = v;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;

bool dfs(int x) {
    vis[x] = true;
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        int &t = g.edges[i].to;
        if (vis[match[t]]) continue;
        if (!match[t] || dfs(match[t])) {
            match[t] = x;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1; i <= e; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addedge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(bool) * (n + 1));
        if (dfs(i)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
```

#### 棋盘覆盖
https://www.acwing.com/problem/content/description/374/

二分图匹配的两个要素：相同集合内没有边，每个节点只能匹配一个不同集合的点。把棋盘按照坐标和奇偶性分成两个集合，那么相邻的格子在不同的集合，可以在它们之间连边，在同一集合的点一定不相邻，也就没有边。连完边做一遍二分图最大匹配就可以了。

```cpp
#include<cstdio>
#include<cstring>

const int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
int n, p, ans;
bool able[110][110], vis[110][110];
struct state {
    int x, y;
    state(int xv = 0, int yv = 0): x(xv), y(yv) {}
    bool operator ! () const { return x == 0 && y == 0; }
}match[110][110];
struct edge { state to; int next; };
struct graph {
    int ecnt, head[110][110];
    edge edges[40100];
    inline void addedge(state u, state v) {
        edges[++ecnt].to = v;
        edges[ecnt].next = head[u.x][u.y];
        head[u.x][u.y] = ecnt;
    }
}g;

bool dfs(state x) {
    vis[x.x][x.y] = true;
    for (int i = g.head[x.x][x.y]; i; i = g.edges[i].next) {
        state &t = g.edges[i].to;
        if (vis[match[t.x][t.y].x][match[t.x][t.y].y]) continue;
        if (!match[t.x][t.y] || dfs(match[t.x][t.y])) {
            match[t.x][t.y] = state(x.x, x.y);
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) able[i][j] = true;
    for (int i = 1; i <= p; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        able[x][y] = false;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if ((i + j) % 2 || !able[i][j]) continue;
            for (int k = 0; k < 4; k++) {
                int xg = i + dir[k][0], yg = j + dir[k][1];
                if (xg < 1 || xg > n || yg < 1 || yg > n || !able[xg][yg]) continue;
                g.addedge(state(i, j), state(xg, yg));
            }
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if ((i + j) % 2 || !able[i][j]) continue;
            memset(vis, 0, sizeof vis);
            if (dfs(state(i, j))) ans++;
        }
    printf("%d\n", ans);
    return 0;
}
```

#### [APIO2010]巡逻
https://www.luogu.com.cn/problem/P3629

求树的直径有两种方法。两次$\texttt{DFS}$，第一次随便选一个点找到最远的点，然后从找到的点在$\texttt{DFS}$一次找到最远的点，第一次找到的一定是直径的端点，而第二次找到的是直径。可以用反证法证明是正确的，但这种方法不适用于有负边权的情况。树形$\texttt{DP}$，状态是当前节点到子树的节点中最远的距离，然后当前子树的直径就是$dp_i+w_i+dp_j+w_j$，其中$i,j$是当前节点的两个子节点。不需要枚举$i,j$，在遍历子节点时用当前子节点加上之前遍历到的最远子节点就可以了，即$dp[x]+dp[t]+w$。然后答案在每个节点的子树的最长链中取$\max$，这样能够找到直径的原因是直径总会有一个最靠近根节点的顶点，所以直径总会在顶点处被枚举到，从而更新答案。可以用于有负边权的情况，但只能求数值不能求路径。

$k=1$时很简单，修出来的路可以让形成的环上本来要经过两次的边变成一次，于是直接找到直径然后在两个端点上修路就可以了。$k=2$时两个环的交集需要遍历两次，所以交集需要去掉。第一次需要在直径上修路，原因我也不知道，不会证明，我去问了$\texttt{wyh}$学长说应该是选非直径的情况可以转为选直径的情况且答案不会更劣(大概意思是这样)，具体我还是不会证。找到直径后把直径上的边权变为$-1$，然后再求一遍直径，变为$-1$的作用是使找到的链与先前找到的直径有交集时答案更劣，也就是把交集去掉。

另外这题还有树形$\texttt{DP}$的做法，就是求两条最长不相交链。

```cpp
#include<cstdio>

const int MAXN = 100100;
int n, k, maxdist, maxnode, from[MAXN], maxdist2, dp[MAXN];
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
struct tools { static int max(int a, int b) { return a > b ? a : b; } };

void dfs1(int x, int lst, int dist) {
    if (dist >= maxdist) {
        maxdist = dist;
        maxnode = x;
    }
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &t = g.edges[i].to;
        dfs1(t, i, dist + g.edges[i].w);
        from[t] = x;
    }
}
void dfs2(int x) {
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        int &t = g.edges[i].to;
        if (t == from[x]) {
            g.edges[i].w = g.edges[i ^ 1].w = -1;
            dfs2(t);
        }
    }
}
void dfs3(int x, int lst) {
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &t = g.edges[i].to, w = g.edges[i].w;
        dfs3(t, i);
        maxdist2 = tools::max(maxdist2, dp[x] + w + dp[t]);
        dp[x] = tools::max(dp[x], dp[t] + w);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addedge(u, v, 1), g.addedge(v, u, 1);
    }
    dfs1(1, 0, 0);
    from[maxnode] = 0;
    dfs1(maxnode, 0, 0);
    dfs2(maxnode);
    dfs3(1, 0);
    if (k == 1) printf("%d\n", 2 * (n - 1) - maxdist + 1);
    else printf("%d\n", 2 * n - maxdist - maxdist2);
    return 0;
}
```