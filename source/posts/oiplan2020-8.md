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