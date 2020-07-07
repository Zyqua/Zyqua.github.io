title: 王道征途——NOIP2020冲刺计划·第三周(7.6~7.12)
date: 2020-07-06
weight: 20200706
<!--more-->
按照计划，本周的学习重点是图论(最短路、生成树、二分图)。

其实贪心和二分感觉还有一些题需要做但没来得及做，以后查漏补缺时补上。

### 2020-07-06
#### [USACO2.4]牛的旅行 Cow Tours
https://www.luogu.com.cn/problem/P1522

用$\texttt{Floyd}$求出节点两两之间的距离后，加上一堆预处理。

求完最短路后，首先要对全图做一遍$\texttt{dfs}$染色，以区分不同连通分量的节点。然后可以求出$maxdis_x$表示以节点$x$为端点的最长的路径。在$maxdis$的基础上可以求出$diameter_x$表示第$x$个连通分量的直径。然后枚举点对$(i,j)$，如果不在同一连通分量则可以修路，修路后的连通分量的直径为$\max(maxdis_i+dist(i,j)+maxdis_j, diameter_{belong(i)}, diameter_{belong(j)})$，和$ans$取最小值即可。

第一次写完时把`belong[i] ^ belong[j]`写成了`!g[i][j]`，这样就不是在同一个连通分量，而是有没有直接相连的边了。日常低级错误。

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>

int n, g[155][155], cnt, belong[155];
double dis[155][155], maxdis[155], diameter[155], ans = 1e9;
struct coordinate {
    int x, y;
}coordinates[155];

inline double min(double a, double b) { return a < b ? a : b; }
inline double max(double a, double b) { return a > b ? a : b; }
inline double dist(int i, int j) { return sqrt((double)(coordinates[i].x - coordinates[j].x) * (coordinates[i].x - coordinates[j].x)
                                        + (coordinates[i].y - coordinates[j].y) * (coordinates[i].y - coordinates[j].y)); }
void dfs(int x) {
    if (belong[x]) return;
    belong[x] = cnt;
    for (int j = 1; j <= n; j++)
        if (g[x][j]) dfs(j);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &coordinates[i].x, &coordinates[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) scanf("%1d", &g[i][j]);
    memset(dis, 0x7f, sizeof dis);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (g[i][j]) dis[i][j] = dis[j][i] = dist(i, j);
            else if (i == j) dis[i][j] = dis[j][i] = 0;
        }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for (int i = 1; i <= n; i++)
        if (!belong[i]) cnt++, dfs(i);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (belong[i] == belong[j]) maxdis[i] = max(maxdis[i], dis[i][j]);
    for (int i = 1; i <= n; i++) diameter[belong[i]] = max(diameter[belong[i]], maxdis[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (belong[i] ^ belong[j]) ans = min(ans, max(maxdis[i] + dist(i, j) + maxdis[j], max(diameter[belong[i]], diameter[belong[j]])));
    printf("%.6lf\n", ans);
    return 0;
}
```

#### 速度限制
https://www.luogu.com.cn/problem/P1266

分层图最短路，节点$(x,v)$表示在第$x$个路口，初速度为$v$。然后就做完了。

需要注意的是路径的记录方法。节点是用两项表示的，第一次写的时候写成一维的了。

根据我的理解，分层图最短路和动态规划相似，只不过后者适用于有向无环图，且状态要更为多样，而分层图最短路只能求最短路这一种状态。

```cpp
#include<cstdio>
#include<queue>
#include<cstring>

const int MAXN = 155;
int n, m, d, greatv;
double ans = 1e9, dis[MAXN][510];
bool vis[MAXN][510];
struct edge { int to, next, v, l; };
struct graph {
    int ecnt, head[MAXN];
    edge edges[MAXN * MAXN];

    inline void addedge(int u, int to, int v, int l) {
        edges[++ecnt].to = to;
        edges[ecnt].v = v;
        edges[ecnt].l = l;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x, v;
    double dist;
    node(int xv, int vv, double dv): x(xv), v(vv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;
struct state {
    int x, v;
    state(int xv = 0, int vv = 0): x(xv), v(vv) {}
}from[MAXN][510];

inline void dijkstra() {
    q.push(node(1, 70, 0));
    memset(dis, 0x7f, sizeof dis);
    for (int i = 1; i <= 500; i++) dis[1][i] = 0;
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x][f.v]) continue;
        vis[f.x][f.v] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, v = g.edges[i].v ? g.edges[i].v : f.v, l = g.edges[i].l;
            if (dis[t][v] > dis[f.x][f.v] + (double)l / v) {
                dis[t][v] = dis[f.x][f.v] + (double)l / v;
                from[t][v] = state(f.x, f.v);
                q.push(node(t, v, dis[t][v]));
            }
        }
    }
}
void print(int x, int v) {
    if (!x) return;
    print(from[x][v].x, from[x][v].v);
    printf("%d ", x - 1);
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    d++;
    for (int i = 1; i <= m; i++) {
        int u, to, v, l;
        scanf("%d%d%d%d", &u, &to, &v, &l);
        g.addedge(u + 1, to + 1, v, l);
    }
    dijkstra();
    for (int i = 1; i <= 500; i++) {
        if (ans > dis[d][i]) {
            ans = dis[d][i];
            greatv = i;
        }
    }
    print(d, greatv);
    return 0;
}
```

### 2020-07-07
自从更新了新版$\texttt{Windows10}$系统，每次用$\texttt{vscode}$运行程序时必跳出两个控制台，一个是我的程序，一个是编译器，特烦人。原因是我使用了旧版控制台模式(但我一直以来都在用它，且以前没有这种情况)。改成新版控制台模式后，程序则是完全看不到输出结果，尽管已经输出了。我完全裂开了。

#### [GXOI/GZOI2019]旅行者
https://www.luogu.com.cn/problem/P5304

求指定点之间的最短路。如果把点集分成集合$A$和集合$B$，并从超级源点$s$向$A$中的每个节点连一条边权为$0$的边，从$B$中的每个节点向超级汇点$t$连一条边权为$0$的边，那么从$s$到$t$的最短路，就是$A$和$B$中两两点对的最短路。所以，如果能多次分割点集，并保证任意两个点都能至少在某一次中被分到两个不同集合中，那么就可以求出所有指定点之间的最短路。

可以把指定点按照二进制分组，枚举每一位，把这一位上数字相同的分到一个集合中。如果两个点编号不同，那么必然有至少一位不同，所以满足要求。二进制分组的复杂度是$O(logn)$，算法总复杂度是$O(nlog^2n)$。

因为连完边还要把连的边删掉，所以用$\texttt{vector}$存图要更方便一些。

需要注意的是，因为是有向图，所以源点和汇点分别与指定点连边时要从两个方向各连一遍，跑两遍最短路。

然而这不是这题的最优做法，所以要通过大概得吸氧。但是因为我人傻常数大，所以吸了氧并加了快读也过不去。下面放上的是未优化常数的代码。

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

const int MAXN = 100100;
int t, n, m, k, nodes[MAXN];
long long dis[MAXN], ans;
bool vis[MAXN];
struct edge {
    int to, w;
    edge(int tv, int wv): to(tv), w(wv) {}
};
struct graph {
    std::vector<edge> edges[MAXN];

    inline void addedge(int u, int v, int w) { edges[u].push_back(edge(v, w)); }
    inline void popedge(int x) { edges[x].pop_back(); }
    inline void clear() { for (int i = 1; i <= n; i++) edges[i].clear(); }
}g;
struct node {
    int x;
    long long dist;
    node(int xv, long long dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline long long min(long long a, long long b) { return a < b ? a : b; }
inline void dijkstra(int s) {
    q.push(node(s, 0));
    memset(dis, 0x3f, sizeof(long long) * (n + 3));
    dis[s] = 0;
    memset(vis, 0, sizeof(bool) * (n + 3));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = 0; i < (int)g.edges[f.x].size(); i++) {
            int &t = g.edges[f.x][i].to, w = g.edges[f.x][i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        ans = 0x3fffffffffffffff;
        g.clear();
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g.addedge(u, v, w);
        }
        for (int i = 1; i <= k; i++) scanf("%d", &nodes[i]);
        int a = 1;
        while (a <= n) {
            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.addedge(n + 1, nodes[i], 0);
                else g.addedge(nodes[i], n + 2, 0);
            }
            dijkstra(n + 1);
            ans = min(ans, dis[n + 2]);
            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.popedge(n + 1);
                else g.popedge(nodes[i]);
            }

            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.addedge(nodes[i], n + 1, 0);
                else g.addedge(n + 2, nodes[i], 0);
            }
            dijkstra(n + 2);
            ans = min(ans, dis[n + 1]);
            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.popedge(nodes[i]);
                else g.popedge(n + 2);
            }
            a <<= 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```