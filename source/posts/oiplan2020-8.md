title: 王道征途——NOIP2020冲刺计划·第八周(8.10~8.16)
date: 2020-08-10
weight: 20200810
<!--more-->
### 2020-08-10
今天上午讲了网络流。加上最大流模板一天A了五题，爽。
#### 【模板】网络最大流
https://www.luogu.com.cn/problem/P3376

最大流模板。错误有犯了不知道多少次的`ecnt`没有初始化为$1$，然后题面数据范围有错误，容量也得开`long long`，还有$\texttt{dfs}$中漏掉了当前弧优化的判断`flow`是否为空。还有一个错误就是关于当前弧优化，我一开始写的是：
```cpp
for (; g.now[x] && flow; g.now[x] = g.edges[g.now[x]].next) {
	int &i = g.now[x];
```
然而正确的写法是：
```cpp
for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
	g.now[x] = i;
```
这两种写法看起来区别不大，但仔细思考会发现第一种写法只会让每条边遍历到一次，而末尾的边可能仍然有残量还可以增广，但这样就会在增广后跳过这条边，跳到下一条边去，然后这条仍有残量的边就得等到下次$\texttt{dfs}$再增广了。而第二种写法在末尾的边仍有残量时不会跳到下一条边，而是会继续留在这条边直到这条边不能再增广。显然第一种写法效率要低。实际上在$\texttt{luogu}$的测试点中$\texttt{TLE}$了。

还有就是$\texttt{bfs}$中找到增广路后要立即返回，否则也可能被卡然后$\texttt{TLE}$。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

const long long INF = 0x7fffffffffffffff;
int n, m, s, t;
long long maxflow;
struct edge { int to, next; long long cap, flow; };
struct graph {
	int ecnt = 1, head[210], dep[210], now[210];
	edge edges[10010];
	inline void addedge(int u, int v, long long cap) {
		edges[++ecnt].to = v;
		edges[ecnt].cap = cap;
		edges[ecnt].next = head[u];
		head[u] = ecnt;
	}
}g;
std::queue<int> q;

inline long long min(long long a, long long b) { return a < b ? a : b; }
inline bool bfs() {
	while (!q.empty()) q.pop();
	memset(g.dep, 0, sizeof g.dep);
	g.dep[s] = 1;
	g.now[s] = g.head[s];
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = g.head[x]; i; i = g.edges[i].next) {
			if (g.edges[i].flow >= g.edges[i].cap || g.dep[g.edges[i].to]) continue;
			int &v = g.edges[i].to;
			g.dep[v] = g.dep[x] + 1;
			g.now[v] = g.head[v];
			if (v == t) return true;
			q.push(v);
		}
	}
	return false;
}
long long dfs(int x, long long flow) {
	if (x == t) return flow;
	long long ans = 0, f = 0;
	for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
		g.now[x] = i;
		if (g.edges[i].flow >= g.edges[i].cap || (g.dep[x] + 1 ^ g.dep[g.edges[i].to])) continue;
		int &v = g.edges[i].to;
		f = dfs(v, min(flow, g.edges[i].cap - g.edges[i].flow));
		if (!f) g.dep[v] = 0;
		g.edges[i].flow += f; g.edges[i ^ 1].flow -= f;
		ans += f; flow -= f;
	}
	return ans;
}
inline void dinic() { while (bfs()) maxflow += dfs(s, INF); }

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1; i <= m; i++) {
		int u, v; long long w;
		scanf("%d%d%lld", &u, &v, &w);
		g.addedge(u, v, w); g.addedge(v, u, 0);
	}
	dinic();
	printf("%lld\n", maxflow);
	return 0;
}
```

#### 飞行员配对方案问题
https://www.luogu.com.cn/problem/P2756

显然这就是个二分图最大匹配。从源点向外籍飞行员连边，从外籍飞行员向能匹配的英国飞行员连边，从英国飞行员向汇点连边，容量全部为$1$，然后求最大流。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

const int INF = 0x7fffffff;
int n, m, s, t, maxflow;
struct edge { int to, next, cap, flow; };
struct graph {
	int ecnt = 1, head[110], dep[110], now[110];
	edge edges[20010];
	inline void addedge(int u, int v, int cap) {
		edges[++ecnt].to = v;
		edges[ecnt].cap = cap;
		edges[ecnt].next = head[u];
		head[u] = ecnt;
	}
}g;
std::queue<int> q;

inline int min(int a, int b) { return a < b ? a : b; }
inline bool bfs() {
	while (!q.empty()) q.pop();
	memset(g.dep, 0, sizeof g.dep);
	g.dep[s] = 1;
	g.now[s] = g.head[s];
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = g.head[x]; i; i = g.edges[i].next) {
			if (g.edges[i].flow >= g.edges[i].cap || g.dep[g.edges[i].to]) continue;
			int &v = g.edges[i].to;
			g.dep[v] = g.dep[x] + 1;
			g.now[v] = g.head[v];
			if (v == t) return true;
			q.push(v);
		}
	}
	return false;
}
int dfs(int x, int flow) {
	if (x == t) return flow;
	int ans = 0, f = 0;
	for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
		g.now[x] = i;
		if (g.edges[i].flow >= g.edges[i].cap || (g.dep[x] + 1 ^ g.dep[g.edges[i].to])) continue;
		int &v = g.edges[i].to;
		f = dfs(v, min(flow, g.edges[i].cap - g.edges[i].flow));
		if (!f) g.dep[v] = 0;
		g.edges[i].flow += f; g.edges[i ^ 1].flow -= f;
		ans += f; flow -= f;
	}
	return ans;
}
inline void dinic() { while (bfs()) maxflow += dfs(s, INF); }

int main() {
	scanf("%d%d", &m, &n);
	s = n + 1, t = n + 2;
	for (; ; ) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u == -1 && v == -1) break;
		g.addedge(u, v, 1); g.addedge(v, u, 0);
	}
	for (int x = 1; x <= m; x++) { g.addedge(s, x, 1); g.addedge(x, s, 0); }
	for (int x = m + 1; x <= n; x++) { g.addedge(x, t, 1); g.addedge(t, x, 0); }
	dinic();
	printf("%d\n", maxflow);
	for (int x = 1; x <= m; x++)
		for (int i = g.head[x]; i; i = g.edges[i].next) {
			int &v = g.edges[i].to;
			if (1 <= v && v <= n && g.edges[i].flow) printf("%d %d\n", x, v);
		}
	return 0;
}
```

#### [USACO07OPEN]Dining G
https://www.luogu.com.cn/problem/P2891

这个算是二分图最大匹配的变种，从源点向食物连边，从食物向能匹配的牛连边，从牛向能匹配的饮料连边，从饮料向汇点连边，容量全是$1$，然后因为每个牛只能匹配一次所以每个牛的容量也是$1$，但是点没有容量，所以可以把点拆为一个入点和一个出点，从入点向出点连容量为$1$的边，从而作为容量为$1$的点。建完图求最大流即可。

注意算好点的个数，第一次交算错了点数$\texttt{WA}$了。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

const int INF = 0x7fffffff;
int n, a, b, s, t, maxflow;
struct edge { int to, next, cap, flow; };
struct graph {
	int ecnt = 1, head[410], dep[410], now[410];
	edge edges[200100];
	inline void addedge(int u, int v, int cap) {
		edges[++ecnt].to = v;
		edges[ecnt].cap = cap;
		edges[ecnt].next = head[u];
		head[u] = ecnt;
	}
}g;
std::queue<int> q;

inline int min(int a, int b) { return a < b ? a : b; }
inline bool bfs() {
	while (!q.empty()) q.pop();
	memset(g.dep, 0, sizeof g.dep);
	g.dep[s] = 1;
	g.now[s] = g.head[s];
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = g.head[x]; i; i = g.edges[i].next) {
			if (g.edges[i].flow >= g.edges[i].cap || g.dep[g.edges[i].to]) continue;
			int &v = g.edges[i].to;
			g.dep[v] = g.dep[x] + 1;
			g.now[v] = g.head[v];
			if (v == t) return true;
			q.push(v);
		}
	}
	return false;
}
int dfs(int x, int flow) {
	if (x == t) return flow;
	int ans = 0, f = 0;
	for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
		g.now[x] = i;
		if (g.edges[i].flow >= g.edges[i].cap || (g.dep[x] + 1 ^ g.dep[g.edges[i].to])) continue;
		int &v = g.edges[i].to;
		f = dfs(v, min(flow, g.edges[i].cap - g.edges[i].flow));
		if (!f) g.dep[v] = 0;
		g.edges[i].flow += f; g.edges[i ^ 1].flow -= f;
		ans += f; flow -= f;
	}
	return ans;
}
inline void dinic() { while (bfs()) maxflow += dfs(s, INF); }
inline int cow1id(int x) { return x; }
inline int cow2id(int x) { return n + a + b + x; }
inline int foodid(int x) { return n + x; }
inline int drinkid(int x) { return n + a + x; }

int main() {
	scanf("%d%d%d", &n, &a, &b);
	s = n + a + b + n + 1, t = n + a + b + n + 2;
	for (int i = 1; i <= n; i++) {
		g.addedge(cow1id(i), cow2id(i), 1); g.addedge(cow2id(i), cow1id(i), 0);
		int f, d;
		scanf("%d%d", &f, &d);
		for (int j = 1; j <= f; j++) {
			int x;
			scanf("%d", &x);
			g.addedge(foodid(x), cow1id(i), 1); g.addedge(cow1id(i), foodid(x), 0);
		}
		for (int j = 1; j <= d; j++) {
			int x;
			scanf("%d", &x);
			g.addedge(cow2id(i), drinkid(x), 1); g.addedge(drinkid(x), cow2id(i), 0);
		}
	}
	for (int i = 1; i <= a; i++) { g.addedge(s, foodid(i), 1); g.addedge(foodid(i), s, 0); }
	for (int i = 1; i <= b; i++) { g.addedge(drinkid(i), t, 1); g.addedge(t, drinkid(i), 0); }
	dinic();
	printf("%d\n", maxflow);
	return 0;
}
```

#### 假期的宿舍
https://www.luogu.com.cn/problem/P2055

就是人和床的二分图最大匹配。然后人是指需要床的人，可以分为有床(即在校学生)且不离校的人和没床的人，而离校的人不需要床，不用管。

第一次交把`g.head[v]`写成了`g.head[x]`，不仔细看还真看不出来(毕竟我眼瞎)。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

const int INF = 0x7fffffff;
int T, n, s, t, maxflow, cnt;
bool havebed[55], gohome[55];
struct edge { int to, next, cap, flow; };
struct graph {
    int ecnt = 1, head[110], dep[110], now[110];
    edge edges[20010];
    inline void addedge(int u, int v, int cap) {
        edges[++ecnt].to = v;
        edges[ecnt].cap = cap;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
    inline void clear() {
        ecnt = 1; memset(edges, 0, sizeof edges);
        memset(head, 0, sizeof head); memset(dep, 0, sizeof dep); memset(now, 0, sizeof now);
    }
}g;
std::queue<int> q;

inline int min(int a, int b) { return a < b ? a : b; }
inline bool bfs() {
    while (!q.empty()) q.pop();
    memset(g.dep, 0, sizeof g.dep);
    g.dep[s] = 1;
    g.now[s] = g.head[s];
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = g.head[x]; i; i = g.edges[i].next) {
            if (g.edges[i].flow >= g.edges[i].cap || g.dep[g.edges[i].to]) continue;
            int &v = g.edges[i].to;
            g.dep[v] = g.dep[x] + 1;
            g.now[v] = g.head[v];
            if (v == t) return true;
            q.push(v);
        }
    }
    return false;
}
int dfs(int x, int flow) {
    if (x == t) return flow;
    int ans = 0, f = 0;
    for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
        g.now[x] = i;
        if (g.edges[i].flow >= g.edges[i].cap || (g.dep[x] + 1 ^ g.dep[g.edges[i].to])) continue;
        int &v = g.edges[i].to;
        f = dfs(v, min(flow, g.edges[i].cap - g.edges[i].flow));
        if (!f) g.dep[v] = 0;
        g.edges[i].flow += f; g.edges[i ^ 1].flow -= f;
        ans += f; flow -= f;
    }
    return ans;
}
inline void dinic() {
    while (bfs())
        maxflow += dfs(s, INF);
}
inline int personid(int x) { return x; }
inline int bedid(int x) { return n + x; }

int main() {
    scanf("%d", &T);
    while (T--) {
        g.clear();
        memset(havebed, 0, sizeof havebed); memset(gohome, 0, sizeof gohome); maxflow = 0; cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            if (x) havebed[i] = true;
        }
        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            if (x) gohome[i] = true;
        }
        s = n + n + 1; t = n + n + 2;
        for (int i = 1; i <= n; i++) {
            if ((havebed[i] && !gohome[i]) || !havebed[i]) { g.addedge(s, personid(i), 1); g.addedge(personid(i), s, 0); cnt++; }
            if (havebed[i]) { g.addedge(bedid(i), t, 1); g.addedge(t, bedid(i), 0); }
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                int x;
                scanf("%d", &x);
                if (x || (i == j))
                    if (((havebed[i] && !gohome[i]) || !havebed[i]) && havebed[j]) { g.addedge(personid(i), bedid(j), 1); g.addedge(bedid(j), personid(i), 0); }
            }
        dinic();
        if (maxflow == cnt) printf("^_^\n");
        else printf("T_T\n");
    }
    return 0;
}
```

#### [SDOI2015]星际战争
https://www.luogu.com.cn/problem/P3324

因为题目是要使最大值最小，所以可以考虑二分时间$ti$，然后从源点向武器连容量为$b[i]\times ti$的边，从武器向机器人连容量无限的边，从机器人向汇点连容量为$a[i]$的边，求最大流是否为装甲值之和。

注意$\texttt{double}$别写成了$\texttt{int}$。然后算好边的数量，第一次交时边数没算对$\texttt{RE}$了。

题解里很多把所有容量乘上一万或一千最后答案在除以一万或一千从而避免浮点数的，不是很懂，这不是自找麻烦吗。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

const int INF = 0x7fffffff;
const double eps = 1e-3;
int n, m, s, t, a[55], b[55], suma, sumb;
bool able[55][55];
double ti, maxflow;
struct edge { int to, next; double cap, flow; };
struct graph {
    int ecnt = 1, head[110], dep[110], now[110];
    edge edges[10010];
    inline void addedge(int u, int v, double cap) {
        edges[++ecnt].to = v;
        edges[ecnt].cap = cap;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
    inline int weapon(int x) { return x; }
    inline int bot(int x) { return m + x; }
    inline void init() {
        ecnt = 1; memset(edges, 0, sizeof edges); maxflow = 0;
        memset(head, 0, sizeof head); memset(dep, 0, sizeof dep); memset(now, 0, sizeof now);
        for (int i = 1; i <= m; i++) { addedge(s, weapon(i), b[i] * ti); addedge(weapon(i), s, 0); }
        for (int i = 1; i <= n; i++) { addedge(bot(i), t, a[i]); addedge(t, bot(i), 0); }
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (able[i][j]) { addedge(weapon(i), bot(j), INF); addedge(bot(j), weapon(i), 0); }
    }
}g;
std::queue<int> q;

inline double min(double a, double b) { return a < b ? a : b; }
inline bool bfs() {
    while (!q.empty()) q.pop();
    memset(g.dep, 0, sizeof g.dep);
    g.dep[s] = 1;
    g.now[s] = g.head[s];
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = g.head[x]; i; i = g.edges[i].next) {
            if (g.edges[i].flow >= g.edges[i].cap || g.dep[g.edges[i].to]) continue;
            int &v = g.edges[i].to;
            g.dep[v] = g.dep[x] + 1;
            g.now[v] = g.head[v];
            if (v == t) return true;
            q.push(v);
        }
    }
    return false;
}
double dfs(int x, double flow) {
    if (x == t) return flow;
    double ans = 0, f = 0;
    for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
        g.now[x] = i;
        if (g.edges[i].flow >= g.edges[i].cap || (g.dep[x] + 1 ^ g.dep[g.edges[i].to])) continue;
        int &v = g.edges[i].to;
        f = dfs(v, min(flow, g.edges[i].cap - g.edges[i].flow));
        if (!f) g.dep[v] = 0;
        g.edges[i].flow += f; g.edges[i ^ 1].flow -= f;
        ans += f; flow -= f;
    }
    return ans;
}
inline void dinic() { while (bfs()) maxflow += dfs(s, INF); }
inline double abs(double x) { return x > 0 ? x : -x; }

int main() {
    scanf("%d%d", &n, &m);
    s = n + m + 1; t = n + m + 2;
    for (int i = 1; i <= n; i++) { scanf("%d", &a[i]); suma += a[i]; }
    for (int i = 1; i <= m; i++) { scanf("%d", &b[i]); sumb += b[i]; }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            int x; scanf("%d", &x);
            if (x) able[i][j] = true;
        }
    double l = (double)suma / sumb, r = suma;
    while (r - l > eps) {
        double mid = l + (r - l) / 2;
        ti = mid;
        g.init();
        dinic();
        if (abs(maxflow - suma) <= eps) r = mid;
        else l = mid + eps;
    }
    printf("%lf\n", l);
    return 0;
}
```

### 2020-08-11
#### 【模板】最小费用最大流
https://www.luogu.com.cn/problem/P3381

其实费用流用$\texttt{Dinic}$照样可以做。注意反向边的边权等于正向边的边权的相反数。以及$\texttt{ecnt}$一定要初始化为$1$。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

const int INF = 0x7fffffff;
int n, m, s, t, maxflow, minw;
struct edge { int to, next, cap, flow, w; };
struct graph {
    int ecnt = 1, head[5010], dis[5010], now[5010];
    bool vis[5010];
    edge edges[100100];
    inline void addedge(int u, int v, int cap, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].cap = cap;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
std::queue<int> q;

inline int min(int a, int b) { return a < b ? a : b; }
inline bool spfa() {
    while (!q.empty()) q.pop();
    memset(g.dis, 0x3f, sizeof g.dis);
    memset(g.vis, 0, sizeof g.vis);
    g.dis[s] = 0;
    g.now[s] = g.head[s];
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        g.vis[x] = false;
        for (int i = g.head[x]; i; i = g.edges[i].next) {
            if (g.edges[i].flow >= g.edges[i].cap) continue;
            int &v = g.edges[i].to, w = g.edges[i].w;
            g.now[v] = g.head[v];
            if (g.dis[v] > g.dis[x] + w) {
                g.dis[v] = g.dis[x] + w;
                if (!g.vis[v]) { q.push(v); g.vis[v] = true; }
            }
        }
    }
    return g.dis[t] ^ 0x3f3f3f3f;
}
int dfs(int x, int flow) {
    if (x == t) return flow;
    g.vis[x] = true;
    int ans = 0, f = 0;
    for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
        g.now[x] = i;
        int &v = g.edges[i].to, w = g.edges[i].w;
        if (g.edges[i].flow >= g.edges[i].cap || (g.dis[x] + w != g.dis[v]) || g.vis[v]) continue;
        f = dfs(v, min(flow, g.edges[i].cap - g.edges[i].flow));
        if (!f) g.dis[v] = INF;
        g.edges[i].flow += f; g.edges[i ^ 1].flow -= f;
        ans += f; flow -= f; minw += f * w;
    }
    g.vis[x] = false;
    return ans;
}
inline void dinic() {
    while (spfa())
		maxflow += dfs(s, INF);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        int u, v, w, f;
        scanf("%d%d%d%d", &u, &v, &w, &f);
        g.addedge(u, v, w, f); g.addedge(v, u, 0, -f);
    }
    dinic();
    printf("%d %d\n", maxflow, minw);
    return 0;
}
```

#### [Vani有约会]雨天的尾巴
https://www.luogu.com.cn/problem/P4556

其实线段树合并就是个暴力，直接把每个位置上的节点数据加起来就行，显然对普通线段树这样做每次合并复杂度是$O(nlogn)$的，但对于节点较少的动态开点线段树这样做复杂度较小，因为每次合并的复杂度取决于两棵树的重叠叶子个数，若重叠叶子总数为$n$则总复杂度为$O(nlogn)$。

这题可以对每个节点开个桶然后树上差分，但是数组开不下，这时可以用权值线段树代替数组充当桶，因为有差分所以每个节点的线段树需要插入的节点很少，总共需要插入的节点个数是$O(m)$的，所以总复杂度是$O(mlogw)$，其中$w$为值的范围。

注意差分时是对$lca$和它的父亲分别$-1$。合并后一定要更新根节点编号。

```cpp
#include<cstdio>

int n, m, f[100100][20], depth[100100], root[100100], ans[100100];
struct edge { int to, next; };
struct graph {
	int ecnt = 1, head[100100];
	edge edges[200100];
	inline void addedge(int u, int v) {
		edges[++ecnt].to = v;
		edges[ecnt].next = head[u];
		head[u] = ecnt;
	}
}g;
inline int max(int a, int b) { return a > b ? a : b; }
struct segtreenode { int ans, cnt, lson, rson; };
struct segtree {
	int cnt;
	segtreenode nodes[8000100];
	inline void pushup(int x) {
		nodes[x].cnt = max(nodes[nodes[x].lson].cnt, nodes[nodes[x].rson].cnt);
		if (!nodes[nodes[x].lson].ans || !nodes[nodes[x].rson].ans)
			nodes[x].ans = nodes[nodes[x].lson].ans ^ nodes[nodes[x].rson].ans;
		else if (nodes[nodes[x].lson].cnt >= nodes[nodes[x].rson].cnt) nodes[x].ans = nodes[nodes[x].lson].ans;
		else nodes[x].ans = nodes[nodes[x].rson].ans;
	}
	int insert(int x, int l, int r, int q, int v) {
		if (!x) x = ++cnt;
		if (l == r) {
			nodes[x].cnt += v;
			if (nodes[x].cnt > 0) nodes[x].ans = q;
			else nodes[x].ans = 0;
			return x;
		}
		int mid = l + (r - l >> 1);
		if (q <= mid) nodes[x].lson = insert(nodes[x].lson, l, mid, q, v);
		else if (mid + 1 <= q) nodes[x].rson = insert(nodes[x].rson, mid + 1, r, q, v);
		pushup(x);
		return x;
	}
	int merge(int x, int y, int l, int r) {
		if (!x || !y) return x ^ y;
		if (l == r) {
			nodes[x].cnt += nodes[y].cnt;
			if (nodes[x].cnt > 0) nodes[x].ans = l;
			else nodes[x].ans = 0;
			return x;
		}
		int mid = l + (r - l >> 1);
		nodes[x].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
		nodes[x].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
		pushup(x);
		return x;
	}
}segtree;

void dfs1(int x, int fa) {
	depth[x] = depth[fa] + 1;
	f[x][0] = fa;
	for (int i = 1; i < 20; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for (int i = g.head[x]; i; i = g.edges[i].next) {
		int &v = g.edges[i].to;
		if (v == fa) continue;
		dfs1(v, x);
	}
}
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
inline int lca(int x, int y) {
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (depth[f[x][i]] >= depth[y]) x = f[x][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; i--)
		if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
void dfs2(int x, int lst) {
	for (int i = g.head[x]; i; i = g.edges[i].next) {
		if (i == (lst ^ 1)) continue;
		int &v = g.edges[i].to;
		dfs2(v, i);
		root[x] = segtree.merge(root[x], root[v], 1, 100000);
	}
	ans[x] = segtree.nodes[root[x]].ans;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.addedge(u, v); g.addedge(v, u);
	}
	dfs1(1, 0);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		int a = lca(x, y);
		root[x] = segtree.insert(root[x], 1, 100000, z, 1);
		root[y] = segtree.insert(root[y], 1, 100000, z, 1);
		root[a] = segtree.insert(root[a], 1, 100000, z, -1);
		if (f[a][0]) root[f[a][0]] = segtree.insert(root[f[a][0]], 1, 100000, z, -1);
	}
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
```

#### 永无乡
https://www.luogu.com.cn/problem/P3224

用并查集维护连通性，对每个连通块维护一棵权值线段树，保存连通块里的重要度，查询时直接查就完事了，合并时就合并线段树。

```cpp
#include<cstdio>

const int MAXN = 100100;
int n, m, q, p[MAXN], root[MAXN], pnode[MAXN];
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
struct usetnode { int fa, size; };
struct uset {
    usetnode nodes[MAXN];
    inline void init() { for (int i = 1; i <= n; i++) nodes[i].fa = i, nodes[i].size = 1; }
    int find(int x) {
        if (nodes[x].fa == x) return x;
        return nodes[x].fa = find(nodes[x].fa);
    }
    inline void merge(int x, int y) {
        nodes[y].fa = x;
        nodes[x].size += nodes[y].size;
    }
    inline bool same(int x, int y) { return find(x) == find(y); }
}uset;
struct segtreenode { int cnt, lson, rson; };
struct segtree {
    int cnt;
    segtreenode nodes[MAXN * 80];
    inline void pushup(int x) { nodes[x].cnt = nodes[nodes[x].lson].cnt + nodes[nodes[x].rson].cnt; }
    int insert(int x, int l, int r, int q, int v) {
        if (!x) x = ++cnt;
        if (l == r) { nodes[x].cnt += v; return x; }
        int mid = l + (r - l >> 1);
        if (q <= mid) nodes[x].lson = insert(nodes[x].lson, l, mid, q, v);
        else if (mid + 1 <= q) nodes[x].rson = insert(nodes[x].rson, mid + 1, r, q, v);
        pushup(x);
        return x;
    }
    int merge(int x, int y, int l, int r) {
        if (!x || !y) return x ^ y;
        if (l == r) { nodes[x].cnt += nodes[y].cnt; return x; }
        int mid = l + (r - l >> 1);
        nodes[x].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
        nodes[x].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
        pushup(x);
        return x;
    }
    int kth(int x, int l, int r, int k) {
        if (l == r) return l;
        int mid = l + (r - l >> 1);
        if (k <= nodes[nodes[x].lson].cnt) return kth(nodes[x].lson, l, mid, k);
        else if (k <= nodes[x].cnt) return kth(nodes[x].rson, mid + 1, r, k - nodes[nodes[x].lson].cnt);
        else return -1;
    }
}segtree;

inline char read() {
    register char c = getchar();
    while (c == ' ' || c == '\n' || c == '\r') c = getchar();
    return c;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        pnode[p[i]] = i;
        root[i] = segtree.insert(root[i], 1, 100000, p[i], 1);
    }
    uset.init();
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (!uset.same(u, v)) {
            u = uset.find(u); v = uset.find(v);
            if (uset.nodes[u].size < uset.nodes[v].size) swap(u, v);
            uset.merge(u, v);
            root[u] = segtree.merge(root[u], root[v], 1, 100000);
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        char opt = read();
        if (opt == 'B') {
            int x, y;
            scanf("%d%d", &x, &y);
            if (!uset.same(x, y)) {
                x = uset.find(x); y = uset.find(y);
                if (uset.nodes[x].size < uset.nodes[y].size) swap(x, y);
                uset.merge(x, y);
                root[x] = segtree.merge(root[x], root[y], 1, 100000);
            }
        }
        else if (opt == 'Q') {
            int x, k;
            scanf("%d%d", &x, &k);
            x = uset.find(x);
            int ans = segtree.kth(root[x], 1, 100000, k);
            if (ans ^ -1) printf("%d\n", pnode[ans]);
            else printf("-1\n");
        }
    }
    return 0;
}
```

### 2020-08-12
#### [SDOI2015]寻宝游戏
https://www.luogu.com.cn/problem/P3320

$\texttt{luogu}$的任务计划里咕的题太多了，随便打开一个一看，竟然和之前做的那道异象石完全一样。虽然以前写过但还是没有一遍过样例，把$dis$放在遍历子树之后更新了，这样每个节点的$dis$就是到父节点的距离，而不是到根节点的距离。

```cpp
#include<cstdio>
#include<set>

const int MAXN = 100100;
int n, m, depth[MAXN], f[MAXN][20], dfn[MAXN], cnt;
long long dis[MAXN], ans;
bool exist[MAXN];
struct edge { int to, next, w; };
struct graph {
    int ecnt, head[MAXN];
    edge edges[MAXN << 1];
    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    node(int xv = 0): x(xv) {}
    bool operator < (const node &a) const { return dfn[x] < dfn[a.x]; }
};
std::set<node> nodes;

void dfs(int x, int fa) {
    dfn[x] = ++cnt;
    depth[x] = depth[fa] + 1;
    f[x][0] = fa;
    for (int i = 1; i < 20; i++) f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        int &v = g.edges[i].to;
        if (v == fa) continue;
        dis[v] = dis[x] + g.edges[i].w;
        dfs(v, x);
    }
}
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
inline int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (depth[f[x][i]] >= depth[y]) x = f[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--)
        if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}
inline long long dist(int x, int y) { return dis[x] + dis[y] - (dis[lca(x, y)] << 1); }
inline void insert(int x) {
    std::set<node>::iterator p = nodes.insert(node(x)).first;
    std::set<node>::iterator l = (p == nodes.begin()) ? --nodes.end() : --nodes.find(node(x));
    std::set<node>::iterator r = (p == --nodes.end()) ? nodes.begin() : ++nodes.find(node(x));
    ans -= dist(l -> x, r -> x);
    ans += dist(l -> x, p -> x) + dist(p -> x, r -> x);
}
inline void remove(int x) {
    std::set<node>::iterator p = nodes.find(node(x));
    std::set<node>::iterator l = (p == nodes.begin()) ? --nodes.end() : --nodes.find(node(x));
    std::set<node>::iterator r = (p == --nodes.end()) ? nodes.begin() : ++nodes.find(node(x));
    ans -= dist(l -> x, p -> x) + dist(p -> x, r -> x);
    ans += dist(l -> x, r -> x);
    nodes.erase(p);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w); g.addedge(v, u, w);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        exist[x] = !exist[x];
        if (exist[x]) insert(x);
        else remove(x);
        printf("%lld\n", ans);
    }
    return 0;
}
```

#### 曹冲养猪
https://www.luogu.com.cn/problem/P1495

$\texttt{CRT}$的模板题。对于同余方程组$\begin{cases}x\equiv a_1\pmod {m_1}\\x\equiv a_2\pmod {m_2}\\...\\x\equiv a_n\pmod {m_n}\end{cases}$，其中模数互质，定义$M=\prod_{i=1}^n m_i$，$M_i=\dfrac{M}{m_i}$，$k_i=M_i^{-1}\pmod {m_i}$。存在一个解为$x=\sum_{i=1}^n a_iM_ik_i$。这是因为对于任意一个方程组$x\equiv a_j\pmod {m_j}$，有$x\equiv a_jM_jk_j\pmod {m_j}$，其他项都是$m_j$的倍数所以就没了。而$M_j$和$k_j$在$\mod m_j$意义下互为逆元，因此$x\equiv a_j\pmod {m_j}$成立。然后算出来还得模$M$。

需要注意的是这题得用$\texttt{exgcd}$求逆元，但求出来并不是最小正整数解，如果解大于$0$需要模一遍$M$，否则取反后模$M$再用$M$减。

```cpp
#include<cstdio>

int n, a[11], m[11];
long long ans;

void exgcd(long long a, long long b, long long &x, long long &y) {
	if (!b) { x = 1; y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
inline long long inv(long long x, long long m) { long long a, b; exgcd(x, m, a, b); return a > 0 ? a : m - (-a % m); }
inline void crt() {
	long long M = 1;
	for (int i = 1; i <= n; i++) M *= m[i];
	for (int i = 1; i <= n; i++)
		ans = (ans + (a[i] * (M / m[i])) % M * inv(M / m[i], m[i]) % M) % M;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &m[i], &a[i]);
	crt();
	printf("%lld\n", ans);
	return 0;
}
```

#### 能量采集
https://www.luogu.com.cn/problem/P1447

简单的莫反。莫反大概主要就是用到几个结论$\mu\ast1=\varepsilon$，$\varphi\ast1=id$，$f\ast\varepsilon=f$，$\mu\ast id=\varphi$，然后就是交换求和号。

```cpp
#include<cstdio>

int n, m, p[100100], pcnt;
long long ans, phi[100100];
bool isprime[100100];

inline int min(int a, int b) { return a < b ? a : b; }

int main() {
    scanf("%d%d", &n, &m);
    int k = min(n, m);
    for (int i = 2; i <= k; i++) isprime[i] = true;
    phi[1] = 1;
    for (int i = 2; i <= k; i++) {
        if (isprime[i]) {
            p[++pcnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= pcnt && i * p[j] <= k; j++) {
            isprime[i * p[j]] = false;
            if (i % p[j]) phi[i * p[j]] = phi[i] * phi[p[j]];
            else {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
        }
    }
    for (int i = 1; i <= k; i++) phi[i] += phi[i - 1];
    for (int i = 1, j; i <= k; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (long long)(n / i) * (m / i) * (phi[j] - phi[i - 1]);
    }
    printf("%lld\n", ans * 2 - (long long)n * m);
    return 0;
}
```

### 2020-08-13
#### [HEOI2016/TJOI2016]排序
https://www.luogu.com.cn/problem/P2824

巧妙的二分。二分最后的序列上下标$q$对应的值$v$，将序列中小于$v$的数看作$0$，大于等于$v$的数看作$1$。思路的关键是无视进行排序的过程，直接看进行完所有排序操作后的序列，这个序列上的数字会随着$v$的变化而变化。如果第$q$位为$1$说明第$q$位上的数字大于等于$v$，否则小于$v$。可以用线段树维护区间$01$排序，总复杂度$O(mlog^2n)$。

```cpp
#include<cstdio>

int n, m, q, a[100100], v;
struct operation { int op, l, r; }opts[100100];
struct segtreenode { int cnt0, asntag; };
struct segtree {
	segtreenode nodes[400100];
	inline int lson(int x) { return x << 1; }
	inline int rson(int x) { return x << 1 | 1; }
	inline void pushup(int x) { nodes[x].cnt0 = nodes[lson(x)].cnt0 + nodes[rson(x)].cnt0; }
	inline void pushdown(int x, int l, int r) {
		if (nodes[x].asntag == -1) return;
		int mid = l + (r - l >> 1);
		if (nodes[x].asntag == 0) nodes[lson(x)].cnt0 = mid - l + 1, nodes[rson(x)].cnt0 = r - mid;
		else nodes[lson(x)].cnt0 = nodes[rson(x)].cnt0 = 0;
		nodes[lson(x)].asntag = nodes[rson(x)].asntag = nodes[x].asntag;
		nodes[x].asntag = -1;
	}
	void build(int x, int l, int r) {
		nodes[x].asntag = -1;
		if (l == r) {
			if (a[l] < v) nodes[x].cnt0 = 1;
			else nodes[x].cnt0 = 0;
			return;
		}
		int mid = l + (r - l >> 1);
		build(lson(x), l, mid);
		build(rson(x), mid + 1, r);
		pushup(x);
	}
	void assign(int x, int l, int r, int ql, int qr, int v) {
		if (ql > qr) return;
		if (ql <= l && r <= qr) {
			if (!v) nodes[x].cnt0 = r - l + 1;
			else nodes[x].cnt0 = 0;
			nodes[x].asntag = v;
			return;
		}
		pushdown(x, l, r);
		int mid = l + (r - l >> 1);
		if (ql <= mid) assign(lson(x), l, mid, ql, qr, v);
		if (mid + 1 <= qr) assign(rson(x), mid + 1, r, ql, qr, v);
		pushup(x);
	}
	int query(int x, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) {
			if (!v) return nodes[x].cnt0;
			else return r - l + 1 - nodes[x].cnt0;
		}
		pushdown(x, l, r);
		int mid = l + (r - l >> 1), ans = 0;
		if (ql <= mid) ans += query(lson(x), l, mid, ql, qr, v);
		if (mid + 1 <= qr) ans += query(rson(x), mid + 1, r, ql, qr, v);
		return ans;
	}
}segtree;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &opts[i].op, &opts[i].l, &opts[i].r);
	scanf("%d", &q);
	int l = 1, r = n + 1;
	while (l < r) {
		v = l + (r - l >> 1);
		segtree.build(1, 1, n);
		for (int i = 1; i <= m; i++) {
			int opt = opts[i].op, l = opts[i].l, r = opts[i].r;
			int cnt0 = segtree.query(1, 1, n, l, r, 0), cnt1 = r - l + 1 - cnt0;
			if (opt == 0) segtree.assign(1, 1, n, l, l + cnt0 - 1, 0), segtree.assign(1, 1, n, l + cnt0, r, 1);
			else segtree.assign(1, 1, n, l, l + cnt1 - 1, 1), segtree.assign(1, 1, n, l + cnt1, r, 0);
		}
		int t = segtree.query(1, 1, n, q, q, 1);
		if (t) l = v + 1;
		else r = v;
	}
	printf("%d\n", l - 1);
	return 0;
}
```

#### [国家集训队]等差子序列
https://www.luogu.com.cn/problem/P2757

线段树维护$hash$。具体就是开一个权值线段树，每位上是$0$或$1$表示有没有这个数，然后通过乘上预处理的幂和膜$19260817$进行$hash$，这样就可以单点修改和区间查询$hash$值，然后边扫边加入遍历到的值，如果在值域上以当前遍历到的数为中心的两侧不对称，说明存在以当前遍历到的数为中心的等差序列，于是可以维护正反两个$hash$值，如果以当前遍历到的数为中心的极大区间正反$hash$值相同则对称，也就是不存在以当前遍历到的数为中心的等差序列。

这题我断断续续调了七个小时心态都调崩了，因为是第一次写$hash$所以还以为是$hash$写挂了或者爆$\texttt{int}$了之类的，最后查出来是查询时某一侧子节点$hash$值乘上预处理的幂时，乘的幂的指数是子节点的区间长度，这样在查询的区间不完全覆盖当前节点时会导致$hash$值错误，正确做法是乘的幂的指数为查询的区间边界到中点的区间长度。

```cpp
#include<cstdio>

const int BASE = 2, MOD = 19260817;
int t, n, pwr[100100], p[100100];
struct segtreenode { long long hash1, hash2; };
struct segtree {
	segtreenode nodes[400100];
	inline int lson(int x) { return x << 1; }
	inline int rson(int x) { return x << 1 | 1; }
	inline void pushup(int x, int l, int r) {
		int mid = l + (r - l >> 1);
		nodes[x].hash1 = (nodes[lson(x)].hash1 * pwr[r - mid] % MOD + nodes[rson(x)].hash1) % MOD;
		nodes[x].hash2 = (nodes[lson(x)].hash2 + (nodes[rson(x)].hash2 * pwr[mid - l + 1] % MOD)) % MOD;
	}
	void insert(int x, int l, int r, int v) {
		if (l == r) {
			nodes[x].hash1 = nodes[x].hash2 = 1;
			return;
		}
		int mid = l + (r - l >> 1);
		if (v <= mid) insert(lson(x), l, mid, v);
		else if (mid + 1 <= v) insert(rson(x), mid + 1, r, v);
		pushup(x, l, r);
	}
	long long query(int x, int l, int r, int ql, int qr, int type) {
		if (ql <= l && r <= qr) {
			if (type == 1) return nodes[x].hash1;
			else return nodes[x].hash2;
		}
		int mid = l + (r - l >> 1);
		if (ql <= mid && mid + 1 <= qr) {
			if (type == 1) return (query(lson(x), l, mid, ql, mid, type) * pwr[qr - mid] % MOD + query(rson(x), mid + 1, r, mid + 1, qr, type)) % MOD;
			else return (query(lson(x), l, mid, ql, mid, type) + (query(rson(x), mid + 1, r, mid + 1, qr, type) * pwr[mid - ql + 1] % MOD)) % MOD;
		}
		else if (ql <= mid) return query(lson(x), l, mid, ql, qr, type);
		else if (mid + 1 <= qr) return query(rson(x), mid + 1, r, ql, qr, type);
	}
	void clear(int x, int l, int r) {
		nodes[x].hash1 = nodes[x].hash2 = 0;
		if (l == r) return;
		int mid = l + (r - l >> 1);
		clear(lson(x), l, mid);
		clear(rson(x), mid + 1, r);
	}
}segtree;

inline int min(int a, int b) { return a < b ? a : b; }

int main() {
	pwr[0] = 1;
	for (int i = 1; i <= 100000; i++) pwr[i] = pwr[i - 1] * BASE % MOD;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		segtree.clear(1, 1, n);
		for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
		bool ans = false;
		for (int i = 1; i <= n && !ans; i++) {
			segtree.insert(1, 1, n, p[i]);
			int r = min(p[i], n - p[i] + 1);
			if (segtree.query(1, 1, n, p[i] - r + 1, p[i] + r - 1, 1) != segtree.query(1, 1, n, p[i] - r + 1, p[i] + r - 1, 2)) ans = true;
		}
		if (ans) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
```

#### [HAOI2009]毛毛虫
https://www.luogu.com.cn/problem/P3174

这题我之前看着很难，今晚半夜里做完上面那题就随便点进这题，发现就是个很简单的魔改树形$\texttt{DP}$求直径，定义$dp[x]$表示以$x$为根到子树内节点的最大毛毛虫，然后在原做法的基础上加加减减就好了。

注意$n=1$的情况。

```cpp
#include<cstdio>

const int MAXN = 300100;
int n, m, deg[MAXN], dp[MAXN], ans;
struct edge { int to, next; };
struct graph {
    int ecnt = 1, head[MAXN];
    edge edges[MAXN << 1];
    inline void addedge(int u, int v) {
        edges[++ecnt].to = v;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;

inline int max(int a, int b) { return a > b ? a : b; }
void dfs(int x, int lst) {
    dp[x] = deg[x] + 1;
    ans = max(ans, dp[x]);
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &v = g.edges[i].to;
        dfs(v, i);
        ans = max(ans, dp[x] + dp[v] - 2);
        dp[x] = max(dp[x], dp[v] + deg[x] - 1);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addedge(u, v); g.addedge(v, u);
        deg[u]++, deg[v]++;
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}
```

### 2020-08-14
#### Emiya 家今天的饭
https://www.luogu.com.cn/problem/P5664

每一列的菜不超过一半的方案数等于没有限制的方案数减去某一列上的菜超过一半的方案数。选择的菜超过一半的列最多只有一个，因此可以枚举这一列，然后设$dp[i][j][k]$表示前$i$行中当前选择的第$l$列选了$j$个数，其他列总共选了$k$个数，然后$dp[i][j][k]=dp[i-1][j][k]+dp[i-1][j-1][k]\times a[i][l]+dp[i-1][j][k-1]\times (sum[i]-a[i][l])$。因为只关心当前列和其他列的大小关系因此可以设$dp[i][j]$表示前$i$行中当前选的第$k$列选的数与其他列总共选的数的差为$j$，那么$dp[i][j]=dp[i-1][j]+dp[i-1][j-1]\times a[i][k]+dp[i-1][j+1]\times (sum[i]-a[i][k])$。边界条件是$dp[0][0]=1$。答案是$\sum_{i=1}^n dp[n][i]$。注意第二维可能是负数，解决方法是枚举时给变量加上一个固定的数，使得加上后一定大于等于$0$。没有限制的方案数更简单，设$dp[i][j]$为前$i$行总共选了$j$个数的方案数，然后$dp[i][j]=dp[i-1][j]+dp[i-1][j-1]\times sum[i]$。边界条件是$dp[0][0]=1$。答案是$\sum_{i=1}^n dp[n][i]$。

```cpp
#include<cstdio>
#include<cstring>

const int MOD = 998244353;
int n, m, a[110][2010];
long long f[110][210], g[110][110], sum[110], tot, cnt;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]), sum[i] = (sum[i] + a[i][j]) % MOD;
	for (int k = 1; k <= m; k++) {
		memset(f, 0, sizeof f);
		f[0][n + 1] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = -i + n + 1; j <= i + n + 1; j++) {
				f[i][j] = ((f[i - 1][j] + f[i - 1][j - 1] * a[i][k] % MOD) % MOD + f[i - 1][j + 1] * (sum[i] - a[i][k]) % MOD) % MOD;
			}
		for (int j = 1 + n + 1; j <= n + n + 1; j++) cnt = (cnt + f[n][j]) % MOD;
	}
	g[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n; j++) {
			g[i][j] = g[i - 1][j];
			if (j > 0) g[i][j] = (g[i][j] + g[i - 1][j - 1] * sum[i] % MOD) % MOD;
		}
	for (int i = 1; i <= n; i++) tot = (tot + g[n][i]) % MOD;
	printf("%lld\n", (tot - cnt + MOD) % MOD);
	return 0;
}
```
#### 父子
https://www.luogu.com.cn/problem/P4981

有标号有根树计数。需要用到一个叫$\texttt{prufer}$序列的东西，可以使一棵无根树和一个序列相互转化。无根树上度数为$1$的点称为叶子节点。对于一棵树，每次找出编号最小的叶子节点，然后把和它唯一连接的点的编号写到序列末尾，直到只剩下两个点，得到的序列就是这棵树的$\texttt{prufer}$序列。对于一个$\texttt{prufer}$序列，从左到右遍历，每次在点集中找到不在序列中的编号最小的点，把这个点和当前遍历到的序列上的点连一条边，最后把点集中剩下两个点连一条边，然后就得到了这个序列对应的树。

$\texttt{prufer}$序列和树的一一对应的。一个$n$个点的树对应的$\texttt{prufer}$序列的长度为$n-2$。这个序列上任意一个数的值可以为$[1,n]$中任意一个数，因此$n$个点的有标号无根树的数量为$n^{n-2}$。

对于有根树，可以枚举让每个点都当作根，因此有标号有根树的数量为$n^{n-1}$。

```cpp
#include<cstdio>

const int MOD = 1e9 + 9;
int t;

long long pow(long long x, int k) {
	long long ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % MOD;
		x = x * x % MOD;
		k >>= 1;
	}
	return ans;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%lld\n", pow(n, n - 1));
	}
	return 0;
}
```

#### [HNOI2004]树的计数
https://www.luogu.com.cn/problem/P2290

一个点的度数为$d_i$，那么它在$\texttt{prufer}$序列中出现的次数就是$d_i-1$。这个还是很显然的。于是问题就转化为每种元素出现过指定次数的排列数量，先把相同元素看作不同元素于是答案是$(n-2)!$，然后相同元素之间交换位置不会产生贡献，即随便排列不影响答案，所以把答案除以每个数的度数减一的阶乘。所以答案是$\dfrac{(n-2)!}{\prod_{i=1}^n (d_i-1)!}$。

这题不用取模，答案$\texttt{long long}$在范围内，但中间过程中会爆$\texttt{long long}$，写高精度比较小题大做，因为只有乘除法操作所以可以每次把要乘除的数质因数分解，然后转化为加减法。

注意特判。

```cpp
#include<cstdio>

int n, deg[160], p[160], d[160], id[160], pcnt;
bool isprime[160], ok = true;
struct number {
    int cnt[160];
    inline void mul(int x) {
        int flag = x > 0 ? 1 : -1;
        x = x > 0 ? x : -x;
        while (x ^ 1) cnt[id[d[x]]] += flag, x /= d[x];
    }
    inline long long value() {
        long long ans = 1;
        for (int i = 1; i <= pcnt; i++)
            for (int j = 1; j <= cnt[id[p[i]]]; j++) ans *= p[i];
        return ans;
    }
}ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &deg[i]);
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += deg[i];
    if (sum != n * 2 - 2) ok = false;
    if (n != 1) for (int i = 1; i <= n; i++)
        if (!deg[i]) ok = false;
    if (ok) {
        for (int i = 2; i <= n; i++) isprime[i] = true;
        for (int i = 2; i <= n; i++) {
            if (isprime[i]) p[++pcnt] = i, d[i] = i, id[i] = pcnt;
            for (int j = 1; j <= pcnt && i * p[j] <= n; j++) {
                isprime[i * p[j]] = false;
                d[i * p[j]] = p[j];
                if (!(i % p[j])) break;
            }
        }
        for (int i = 2; i <= n - 2; i++) ans.mul(i);
        for (int i = 1; i <= n; i++)
            for (int j = 2; j <= deg[i] - 1; j++) ans.mul(-j);
        printf("%lld\n", ans.value());
    }
    else printf("0\n");
    return 0;
}
```

#### A. 牛牛爱字符串
https://ac.nowcoder.com/acm/contest/6885/A

晚上比较闲，就去打了牛客的比赛，第一次打。直接膜你即可，不过我交了$6$次才过。

顺便当场学习了$\texttt{getline}$的用法。

```cpp
#include<cstdio>
#include<iostream>
#include<string>

std::string s;

int main() {
    while (getline(std::cin, s)) {
        bool innum = false;
        for (int i = 0; i < s.size(); i++) {
            if ('1' <= s[i] && s[i] <= '9') {
                printf("%c", s[i]);
                innum = true;
            }
            else if (s[i] == '0' && innum) printf("0");
            else if (s[i] == '0' && !('0' <= s[i + 1] && s[i + 1] <= '9')) printf("0 ");
            else if (!('0' <= s[i] && s[i] <= '9')) {
                if (innum) printf(" ");
                innum = false;
            }
            else if (s[i] == ' ' && ('0' <= s[i - 1] && s[i - 1] <= '9')) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
```

#### B. 牛牛爱位运算
https://ac.nowcoder.com/acm/contest/6885/B

$a&b\le a,b$，因此答案就是最大的数。

```cpp
#include<cstdio>

int t;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    scanf("%d", &t);
    while (t--) {
        int n, ans = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            ans = max(ans, x);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

#### C. 牛牛爱博弈
https://ac.nowcoder.com/acm/contest/6885/C

这个想了半天不会做，最后写了个$O(t+nlogn)$的暴力打表找规律，发现$3$的倍数是必败局面，否则是必胜局面。

```cpp
#include<cstdio>

int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        if (n % 3) printf("Alan\n");
        else printf("Frame\n");
    }
    return 0;
}
```
#### D. 牛妹爱序列
https://ac.nowcoder.com/acm/contest/6885/D

胡乱贪心，倒序遍历序列，如果当前遍历到的数和前一个数都是$1$就前缀翻转当前位置，否则单点翻转当前位置。

```cpp
#include<cstdio>

int n, ans, flag, a[100100];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = n; i >= 1; i--) {
        if (a[i] ^ flag == 1 && a[i - 1] ^ flag == 1) ans++, flag ^= 1;
        else if (a[i] ^ flag) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
```

后面两题都不会。

### 2020-08-15
#### [SDOI2016]排列计数
https://www.luogu.com.cn/problem/P4071

枚举哪些位置满足条件，数量是$\dbinom{n}{m}$。然后对于每种情况，剩下的位置就是一个错排问题，设$f[n]$表示没有数字和下标相同的排列数，则答案就是$\dbinom{n}{m}f[n-m]$。

组合数可以预处理阶乘，然后算阶乘的逆元，$O(logp)$计算。错排有两种方法求，一种可以$O(n)$预处理，$f[n]=(n-1)\times(f[n-1]+f[n-2])$。这是因为第$n$个数不能放到第$n$个位置，所以枚举放到前$n-1$个位置，设放到了第$k$个位置，那么第$k$个位置上的数可以放到第$n$个位置，这样方案数就是$f[n-2]$，也可以不放在第$n$个位置，这时假设$p_k$就是$p_n$，让$p_n$不在第$n$个位置，那么方案数就是$f[n-1]$，所以总方案数就是$(n-1)\times(f[n-1]+f[n-2])$。

另一种方法是容斥原理。今天从$\texttt{SDSC}$回家的路上我想了一下午终于想通为什么错排的递推公式和容斥原理的公式是对的了(可能天生对计数不太擅长)，晚上看了下2013年的集训队论文集，里面讲容斥原理讲得很详细，我看了觉得很妙，打算仔细读一下然后明天再写容斥的方法，因为回到家里又不能熬夜了，我的青春结束了。

```cpp
#include<cstdio>

const int MOD = 1e9 + 7;
int t;
long long fac[1000100], f[1000100];

void exgcd(int a, int b, int &x, int &y) {
    if (!b) { x = 1; y = 0; return; }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
inline int inv(int a) { int x, y; exgcd(a, MOD, x, y); return (x % MOD + MOD) % MOD; }
inline long long c(int n, int m) { return fac[n] * inv(fac[m]) % MOD * inv(fac[n - m]) % MOD; }

int main() {
    fac[0] = 1;
    for (int i = 1; i <= 1000000; i++) fac[i] = fac[i - 1] * i % MOD;
    f[0] = 1; f[2] = 1;
    for (int i = 3; i <= 1000000; i++) f[i] = (i - 1) * ((f[i - 1] + f[i - 2]) % MOD) % MOD;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("%lld\n", c(n, m) * f[n - m] % MOD);
    }
    return 0;
}
```