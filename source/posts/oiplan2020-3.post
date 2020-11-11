王道征途——NOIP2020冲刺计划·第三周(7.6~7.12)
2020-07-06
20200706
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

### 2020-07-08
原来控制台看不到输出结果是因为前景颜色(即字符颜色)被设置成了默认的黑色，和背景完全相同所以看不到。这默认设置就离谱。

#### Shortest path
http://acm.hdu.edu.cn/showproblem.php?pid=4479

求边权严格递增的最短路。把边权从小到大排序，然后依次加入到图中对两个端点进行松弛操作，因为在此之前加入的边的边权都比它小，所以可以保证产生的新路径的边权是严格递增的。

需要注意的是，对于边权相同的边，需要同时加入到图中进行松弛操作，也就是多开一个缓存数组存新的$dis$，然后把缓存数组中可能改变的值复制到$dis$中。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

int t, n, m;
long long dis[10100], res[10100];
struct edge {
    int u, v, w;
    bool operator < (const edge &a) const { return w < a.w; }
}edges[50100];

inline long long min(long long a, long long b) { return a < b ? a : b; }

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(edges, 0, sizeof(edge) * (m + 2));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        std::sort(edges + 1, edges + m + 1);
        memset(dis, 0x3f, sizeof(long long) * (n + 1));
        dis[1] = 0;
        memset(res, 0x3f, sizeof(long long) * (n + 1));
        res[1] = 0;
        for (int i = 1; i <= m; ) {
            for (int j = i; j <= m; j++) {
                if (edges[j].w ^ edges[j + 1].w) {
                    for (int k = i; k <= j; k++) {
                        int u = edges[k].u, v = edges[k].v, w = edges[k].w;
                        res[u] = min(res[u], min(dis[u], dis[v] + w));
                        res[v] = min(res[v], min(dis[v], dis[u] + w));
                    }
                    for (int k = i; k <= j; k++) {
                        int u = edges[k].u, v = edges[k].v;
                        dis[u] = res[u];
                        dis[v] = res[v];
                    }
                    i = j + 1;
                    break;
                }
            }
        }
        if (dis[n] ^ 0x3f3f3f3f3f3f3f3f) printf("%lld\n", dis[n]);
        else printf("No answer\n");
    }
    return 0;
}
```

#### Buy a Ticket
https://codeforc.es/contest/938/problem/D

求每个点到其他点的路径长乘二加终点点权的最小值。新建一个超级汇点，从每个点与超级汇点之间连一条边权为点权的边，于是每个点到其他点的答案就等价于这个点到超级汇点的路径，从超级汇点反过来求最短路即可。

原图中的边的边权要乘二。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m;
long long dis[200100];
bool vis[200100];
struct edge { int to, next; long long w; };
struct graph {
    int ecnt, head[200100];
    edge edges[600100];

    inline void addedge(int u, int v, long long w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    long long dist;
    node(int xv, long long dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline void dijkstra() {
    memset(dis, 0x3f, sizeof(long long) * (n + 2));
    dis[n + 1] = 0;
    q.push(node(n + 1, 0));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to;
            long long w = g.edges[i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        g.addedge(u, v, w << 1), g.addedge(v, u, w << 1);
    }
    for (int i = 1; i <= n; i++) {
        long long w;
        scanf("%lld", &w);
        g.addedge(n + 1, i, w);
    }
    dijkstra();
    for (int i = 1; i <= n; i++) printf("%lld ", dis[i]);
    return 0;
}
```

有必要总结一下超级源点和超级汇点的技巧：

超级源点用于多个起点的情况，即要求的是多个起点中的任意一个到指定点的路径。例如，求多个起点到一个终点的最短路，可以建超级源点连向所有起点，然后答案就是超级源点到终点的最短路。另一种方法是反向建边，求终点到各个起点的最短路。超级源点可以避免反向建边，有时候搭配其他算法时可能会更方便一些(最后这一句是我猜的)，同时可以不用枚举起点。

超级汇点用于多个终点的情况，即要求的是一个起点到多个终点中的任意一个的路径。例如，求一个起点到多个终点的最短路，可以建超级汇点连向所有终点，然后答案就是起点到超级汇点的最短路。这样做可以不用枚举终点。

超级源点和超级汇点搭配，则是求多个起点到多个终点中任意一个点对的路径。例如，求多个起点到多个终点的最短路，朴素做法是枚举起点做多次$\texttt{Dijkstra}$，但只要建超级源点和超级汇点中的一个，就可以不用跑多次最短路，可以在求出最短路后$O(n)$枚举。而同时建超级源点和超级汇点，则不用枚举，答案就是超级源点到超级汇点的最短路。这是因为超级源点可以使算法不用枚举起点，超级汇点可以使算法不用枚举终点。

参考资料：https://www.pianshen.com/article/2058609602/ 。不过我的理解大概要比参考资料里写得更深刻些。

### 2020-07-09
今天做了会儿题没调出来，然后就去搞文化课了。

最短路、生成树这块的学问比我想象得要深，计划延长这方面的学习时间。然后下周因为就要中考了，感觉也得多投入点精力在文化课上，真是头疼啊。

### 2020-07-10
#### Jzzhu and Cities
https://codeforc.es/contest/449/problem/B

这题感觉要比前面的要简单一些，不过我还是花了很长时间才调出来。主要原因是我是按照课件上的做法写的，不过可能是我理解错意思了，按照课件的做法写总是$\texttt{WA}$。

课件上的意思是某条铁路若有必要，其长度一定小于只用道路走的最短路。后面就没有写，我之后的做法是只用道路跑一遍最短路，再枚举每条铁路看看是不是有必要存在。然后就一直$\texttt{WA}$，后来发现如果有多条连接同一对节点的铁路，在枚举到必要的铁路后要做松弛操作，否则后面可能会把一些不必要的铁路认为是有必要的。一用到松弛操作，只松弛那一个显然不行，周围的节点的最短路可能也会受影响。所以我就自己改成把道路和铁路放在一起跑最短路，然后判断$\texttt1$到其他节点的最短路中有几条是铁路，记为$\texttt{cnt}$，如果最短路中同时存在由道路(和铁路一起)组成的路径，那么可以把这$\texttt{cnt}$条铁路都拆掉，否则需要留一条铁路，即拆掉$\texttt{cnt-1}$条铁路。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m, k, s[100100], y[100100], ans, cnt[100100];
long long dis[100100];
bool vis[100100], rail[100100];
struct edge { int to, next, w; bool flag; };
struct graph {
    int ecnt, head[100100];
    edge edges[700100];

    inline void addedge(int u, int v, int w, bool flag) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].flag = flag;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    long long dist;
    node(int xv, long long dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline void dijkstra() {
    memset(dis, 0x3f, sizeof(long long) * (n + 1));
    dis[1] = 0;
    q.push(node(1, 0));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, w = g.edges[i].w;
            bool flag = g.edges[i].flag;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
                if (flag) cnt[t] = 1, rail[t] = true;
                else cnt[t] = 0, rail[t] = false;
            }
            else if (dis[t] == dis[f.x] + w) {
                if (flag) cnt[t]++;
                else rail[t] = false;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w, false), g.addedge(v, u, w, false);
    }
    for (int i = 1; i <= k; i++) scanf("%d%d", &s[i], &y[i]), g.addedge(1, s[i], y[i], true);
    dijkstra();
    for (int i = 1; i <= k; i++) {
        if (y[i] > dis[s[i]]) ans++;
        else if (y[i] == dis[s[i]] && cnt[s[i]] > (rail[s[i]] ? 1 : 0)) ans++, cnt[s[i]]--;
    }
    printf("%d\n", ans);
    return 0;
}
```

### 2020-07-11
#### [JSOI2010]部落划分
用这$n$个点建一个完全图，图的最小生成树上第$n-k+1$条边的长度就是答案。

考虑选择两个点合并为一个集合，如果这两个点的距离不是图中各集合之间最短的距离，那么合并后的答案依然不变，所以要使答案最大，每次都要合并最近的两个集合，因此可以用上面的方法求解。

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

int n, k, ecnt;
struct tool {
    static inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
};
struct coordinate {
    int x, y;
}coordinates[1010];
struct edge {
    int u, v;
    double w;
    edge(int uv = 0, int vv = 0, double wv = 0): u(uv), v(vv), w(wv) {}
    bool operator < (const edge &a) const { return w < a.w; }
}edges[500100];
struct unionsetnode {
    int fa, size;
    unionsetnode(): size(1) {}
};
struct unionset {
    unionsetnode nodes[1010];
    inline void init() { 
        for (int i = 1; i <= n; i++) 
            nodes[i].fa = i; }
    int find(int x) {
        if (nodes[x].fa == x) return x;
        else return nodes[x].fa = find(nodes[x].fa);
    }
    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (nodes[x].size > nodes[y].size) tool::swap(x, y);
        nodes[x].fa = y;
        nodes[y].size += nodes[x].size;
    }
    inline bool same(int x, int y) { return find(x) == find(y); }
}uset;

inline double dist(int i, int j) { return sqrt((double)(coordinates[i].x - coordinates[j].x) * (coordinates[i].x - coordinates[j].x)
                                            + (coordinates[i].y - coordinates[j].y) * (coordinates[i].y - coordinates[j].y)); }
inline double kruskal() {
    std::sort(edges + 1, edges + ecnt + 1);
    int cnt = 0;
    for (int i = 1; i <= ecnt; i++) {
        int u = edges[i].u, v = edges[i].v;
        double w = edges[i].w;
        if (!uset.same(u, v)) {
            if (cnt == n - k) return w;
            cnt++;
            uset.merge(u, v);
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &k);
    uset.init();
    for (int i = 1; i <= n; i++) scanf("%d%d", &coordinates[i].x, &coordinates[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) edges[++ecnt] = edge(i, j, dist(i, j));
    printf("%.2lf\n", kruskal());
    return 0;
}
```

#### Greg and Graph
https://codeforc.es/contest/295/problem/B

这题和灾后重建那题都差不多。考虑倒着处理，那么删点就变成了加点，可以用$\texttt{Floyd}$算法很自然地处理。

需要注意的是在累加答案时，用$\texttt{flag}$数组表示点是否被加入，如果两个点都被加入了那么他们之间的路径才可以算进去。

```cpp
#include<cstdio>

int n, dis[510][510], x[510];
long long ans[510];
bool flag[510];

struct tool {
    static inline int min(int a, int b) { return a < b ? a : b; }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &dis[i][j]);
            if (!dis[i][j] && i ^ j) dis[i][j] = 0x3fffffff;
        }
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    for (int k = n; k >= 1; k--) {
        flag[x[k]] = true;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) dis[i][j] = tool::min(dis[i][j], dis[i][x[k]] + dis[x[k]][j]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (flag[i] && flag[j] && dis[i][j] ^ 0x3fffffff) ans[k] += dis[i][j];
            }
    }
    for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    return 0;
}
```

#### 集合位置
https://www.luogu.com.cn/problem/P1491

次短路模板题。先求最短路，然后枚举把最短路上的每条边依次去掉后图的最短路，得到的最短的最短路就是原图的次短路。

因为次短路和最短路必然有至少一条边不相同，所以解法是正确的。

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>

int n, m, backedge[210];
double dis[210], maxdis = 1e9, secmaxdis = 1e9;
bool vis[210];
struct coordinate {
    int x, y;
}coordinates[210];
struct edge { int to, next; double w; };
struct graph {
    int ecnt = 1, head[210];
    edge edges[40100];

    inline void addedge(int u, int v, double w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    double dist;
    node(int xv, double dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline double dist(int i, int j) { return sqrt((double)(coordinates[i].x - coordinates[j].x) * (coordinates[i].x - coordinates[j].x)
                                                    + (coordinates[i].y - coordinates[j].y) * (coordinates[i].y - coordinates[j].y)); }
inline double dijkstra(int id) {
    q.push(node(1, 0));
    memset(dis, 0x7f, sizeof(double) * (n + 1));
    dis[1] = 0;
    memset(vis, 0, sizeof(bool) * (n + 1));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            if (i == id || i == (id ^ 1)) continue;
            int &t = g.edges[i].to;
            double w = g.edges[i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
                if (!id) backedge[t] = i ^ 1;
            }
        }
    }
    return dis[n];
}
void findway(int x) {
    if (x == 1) return;
    double d = dijkstra(backedge[x]);
    if (d <= maxdis) secmaxdis = maxdis, maxdis = d;
    else if (d < secmaxdis) secmaxdis = d;
    findway(g.edges[backedge[x]].to);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d%d", &coordinates[i].x, &coordinates[i].y);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addedge(u, v, dist(u, v)), g.addedge(v, u, dist(v, u));
    }
    maxdis = dijkstra(0);
    findway(n);
    if (secmaxdis < 1e9) printf("%.2lf\n", secmaxdis);
    else printf("-1\n");
    return 0;
}
```

### 2020-07-12
打了$\texttt{Codeforces Round 655}$。
#### A. Omkar and Completion
http://codeforces.com/contest/655/problem/A

要使序列任意两数的和不存在在序列中，那么让序列的每个数都相等就可以了。

```cpp
#include<cstdio>

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) printf("1 ");
        printf("\n");
    }
    return 0;
}
```

#### B. Omkar and Last Class of Math
http://codeforces.com/contest/655/problem/B

把整数$n$分成两个整数$a,b$的和，使得$lcm(a,b)$最小。当$n$为偶数时，显然可以将其分为两个$\dfrac{n}{2}$，使得$lcm$最小。当$n$为奇数时，受到偶数情况下做法的启发，找到$n$的一个因子$d$，把$n$分为$\dfrac{n}{d}$和$n-\dfrac{n}{d}$。后者等于$\dfrac{n(d-1)}{d}$，因此两者的$lcm$就是$\dfrac{n(d-1)}{d}$。要使$\dfrac{n(d-1)}{d}$最小，$d$就要最小，所以找到小于$n$的最小质因子，并输出答案即可。如果没有找到，说明$n$是质数，这种情况下最优解是把$n$分为$1$和$n-1$。

```cpp
#include<cstdio>

int t, n;

inline bool isprime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (!(x % i)) return false;
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (!(n % 2)) printf("%d %d\n", n / 2, n / 2);
        else if (isprime(n)) printf("%d %d\n", 1, n - 1);
        else for (int i = 3; i * i <= n; i++) {
            if (!(n % i)) {
                printf("%d %d\n", n / i, n / i * (i - 1));
                break;
            }
        }
    }
    return 0;
}
```

这时比赛因为评测机不稳定，导致一堆提交的代码评测不过来，就$\texttt{Unrated}$了。再加上$\texttt C$题机翻不太准看不懂，我就去睡觉了。

#### [USACO08JAN]Telephone Lines S
https://www.luogu.com.cn/problem/P1948

这题其实有两种解法，一种就是十分熟悉的分层图最短路，虽然很套路但也能过。

另一种是二分答案，随着权值最大的边的权值增大，要置为$0$的边(即权值大于限制)的数量也越来越少，那么就可以二分了，判断时把权值大于限制的边的权值看作$1$，小于等于的看作$0$，然后跑一遍最短路，如果最短路小于等于$k$那么可行。

值得一提的是，这次求的是边权只有$0$或$1$的最短路，常规做法是$\texttt{Dijkstra}$，但也可以用复杂度更优的双端队列$\texttt{BFS}$。在$\texttt{Dijkstra}$中，用堆来保存待扩展的节点，目的是使每次取出的点最小；而在$\texttt{BFS}$中，队列中只有两种大小，两种大小的差为$1$，且更靠近队头的更小。本质都是为了满足单调性。使用双端队列维护，如果扩展到的节点大小增量为$0$(即经过的边权为$0$)，那么可以把新节点放在队头，否则大小增量为$1$，就把新节点放在队尾，显然这样依然满足单调性，而又省掉了堆的一个$log$和建分层图的$k$，复杂度更优。

在本题中，使用$Dijkstra$求最短路的总复杂度是$O(k(n+m)log(nk))$，使用双端队列$\texttt{BFS}$的总复杂度是$O((n+m)log\max l)$。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m, k, dis[1010];
bool vis[1010];
struct edge { int to, next, w; };
struct graph {
    int ecnt, head[1010];
    edge edges[20010];

    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    node(int xv): x(xv) {}
};
std::deque<node> q;

int bfs(int mid) {
    q.push_back(node(1));
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    dis[1] = 0;
    memset(vis, 0, sizeof(bool) * (n + 1));
    while (!q.empty()) {
        node f = q.front();
        q.pop_front();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, w = g.edges[i].w > mid ? 1 : 0;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                if (!w) q.push_front(node(t));
                else q.push_back(node(t));
            }
        }
    }
    return dis[n];
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w), g.addedge(v, u, w);
    }
    int l = 1, r = 1e6 + 1;
    while (l < r) {
        int mid = l + (r - l >> 1);
        if (bfs(mid) <= k) r = mid;
        else l = mid + 1;
    }
    if (bfs(l) <= k) printf("%d\n", l);
    else printf("-1\n");
    return 0;
}
```

#### [USACO11JAN]Roads and Planes G
https://www.luogu.com.cn/problem/P3008

无向边的边权非负，有向边的边权可能为负，求最短路。一个关键条件是保证有向边的两个端点不能互相到达，这说明在把无向边组成的连通分量缩成一个点后，图是一个有向无环图。因此可以对每个连通分量用$\texttt{Dijkstra}$求最短路，在连通分量之间用拓扑排序求最短路。

具体做法为把所有入度为$0$的连通分量入队，然后每次对队头的连通分量用$\texttt{Dijkstra}$求最短路。先把连通分量中所有的点加入堆，然后和$\texttt{Dijkstra}$中一样每次取出最小的点，然后不一样的是如果当前点可以到达(即$dis$不是初始化的值)那么才可以对其他点进行松弛操作，否则如果经过边权为负的边那么就会把到达的点更新，导致错误答案，本来不能到达的点看作可以到达，且最后得到的最短路的值只比初始化的值小一点。如果两个端点不在同一连通分量，那么就把到达的点所在的连通分量的入度减一，在减到$0$时将其入队。

第一次写完时拓扑排序和以前一样是$\texttt{DFS}$，但这样会导致一个连通分量在遍历到时其内部各点求得的最短路未被完全更新，导致错误答案，因为可能从其他未被遍历过但需要遍历连通分量也可以到达这个点，且路径更短。本质原因是状态设计的不同：在以前的状态是每个点到终点的距离，而现在是每个点到起点的距离，这时候再沿用以前的方式，当然是错误的。

改成$\texttt{BFS}后，$在刚开始$\texttt{BFS}$时我把$s$所在的连通分量入队，而不是所有入度为$0$的点入队，我以为那些无法到达的连通分量无需入队，因为答案不可能被更新，但实际上如果不入队，一些该减的入度没有减掉，很多连通分量的入度都不会降到$0$，导致大多数点都无法到达。如果非要坚持只把$s$所在的连通分量入队，那么还有另一种方法，就是做一遍$\texttt{DFS}$标记所有能到达的连通分量，然后在计算入度时只算那些被标记的点，不过这显然没有一行$\texttt{for}$循环加入所有入度为$0$的连通分量省事。

把所有入度为$0$的点入队后，带来一个新的问题是如果一个无法到达的点通过负权边更新了它到达的某个点，就会导致错误答案，本来不能到达的点看起来可以到达了。解决方法是在进行松弛操作时判断当前点的答案是不是初始化的值，如果是那么就不用进行松弛操作了。

然后我还把判断是否在同一集合并减入度的代码写在了松弛操作里面，这样只有进行了松弛操作的边才会判断是否在同一集合，导致一些该减的入度没有减，一些本能到达的点无法到达。正确写法是写在外面，和松弛操作并列。

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>

const int MAXN = 25010;
int n, m, p, s, belong[MAXN], cnt, dis[MAXN], indeg[MAXN];
bool vis[MAXN];
struct edge { int to, next, w; };
struct graph {
    int ecnt, head[MAXN];
    edge edges[150100];

    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x, dist;
    node(int xv, int dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;
std::vector<int> ccnodes[MAXN];
struct nodecc {
    int x;
    nodecc(int xv): x(xv) {}
};
std::queue<nodecc> qcc;

void dfs1(int x) {
    if (belong[x]) return;
    belong[x] = cnt;
    ccnodes[cnt].push_back(x);
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        int &t = g.edges[i].to;
        dfs1(t);
    }
}
void bfs() {
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    dis[s] = 0;
    for (int i = 1; i <= cnt; i++)
        if (!indeg[i]) qcc.push(nodecc(i));
    while (!qcc.empty()) {
        nodecc fcc = qcc.front();
        qcc.pop();
        register int x = fcc.x;
        for (int i = 0; i < (int)ccnodes[x].size(); i++) q.push(node(ccnodes[x][i], dis[ccnodes[x][i]]));
        while (!q.empty()) {
            node f = q.top();
            q.pop();
            if (vis[f.x]) continue;
            vis[f.x] = true;
            for (int i = g.head[f.x]; i; i = g.edges[i].next) {
                int &t = g.edges[i].to, w = g.edges[i].w;
                if (dis[f.x] ^ 0x3f3f3f3f && dis[t] > dis[f.x] + w) {
                    dis[t] = dis[f.x] + w;
                    if (belong[f.x] == belong[t]) q.push(node(t, dis[t]));
                }
                if (belong[f.x] ^ belong[t]) {
                    indeg[belong[t]]--;
                    if (!indeg[belong[t]]) qcc.push(nodecc(belong[t]));
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &p, &s);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w), g.addedge(v, u, w);
    }
    for (int i = 1; i <= n; i++)
        if (!belong[i]) cnt++, dfs1(i);
    for (int i = 1; i <= p; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w);
        indeg[belong[v]]++;
    }
    bfs();
    for (int i = 1; i <= n; i++) {
        if (dis[i] ^ 0x3f3f3f3f) printf("%d\n", dis[i]);
        else printf("NO PATH\n");
    }
    return 0;
}
```

最后，这周好像一直在刷最短路，生成树没怎么刷，二分图一点没学。以后再协调下时间吧。