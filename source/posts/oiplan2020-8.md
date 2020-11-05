������;����NOIP2020��̼ƻ����ڰ���(8.10~8.16)
2020-08-10
20200810
<!--more-->
### 2020-08-10
�������署�������������������ģ��һ��A�����⣬ˬ��
#### ��ģ�塿���������
https://www.luogu.com.cn/problem/P3376

�����ģ�塣�����з��˲�֪�����ٴε�`ecnt`û�г�ʼ��Ϊ$1$��Ȼ���������ݷ�Χ�д�������Ҳ�ÿ�`long long`������$\texttt{dfs}$��©���˵�ǰ���Ż����ж�`flow`�Ƿ�Ϊ�ա�����һ��������ǹ��ڵ�ǰ���Ż�����һ��ʼд���ǣ�
```cpp
for (; g.now[x] && flow; g.now[x] = g.edges[g.now[x]].next) {
	int &i = g.now[x];
```
Ȼ����ȷ��д���ǣ�
```cpp
for (int i = g.now[x]; i && flow; i = g.edges[i].next) {
	g.now[x] = i;
```
������д�����������𲻴󣬵���ϸ˼���ᷢ�ֵ�һ��д��ֻ����ÿ���߱�����һ�Σ���ĩβ�ı߿�����Ȼ�в������������㣬�������ͻ�����������������ߣ�������һ����ȥ��Ȼ���������в����ı߾͵õȵ��´�$\texttt{dfs}$�������ˡ����ڶ���д����ĩβ�ı����в���ʱ����������һ���ߣ����ǻ��������������ֱ�������߲��������㡣��Ȼ��һ��д��Ч��Ҫ�͡�ʵ������$\texttt{luogu}$�Ĳ��Ե���$\texttt{TLE}$�ˡ�

���о���$\texttt{bfs}$���ҵ�����·��Ҫ�������أ�����Ҳ���ܱ���Ȼ��$\texttt{TLE}$��

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

#### ����Ա��Է�������
https://www.luogu.com.cn/problem/P2756

��Ȼ����Ǹ�����ͼ���ƥ�䡣��Դ�����⼮����Ա���ߣ����⼮����Ա����ƥ���Ӣ������Ա���ߣ���Ӣ������Ա�������ߣ�����ȫ��Ϊ$1$��Ȼ�����������

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

������Ƕ���ͼ���ƥ��ı��֣���Դ����ʳ�����ߣ���ʳ������ƥ���ţ���ߣ���ţ����ƥ����������ߣ��������������ߣ�����ȫ��$1$��Ȼ����Ϊÿ��ţֻ��ƥ��һ������ÿ��ţ������Ҳ��$1$�����ǵ�û�����������Կ��԰ѵ��Ϊһ������һ�����㣬����������������Ϊ$1$�ıߣ��Ӷ���Ϊ����Ϊ$1$�ĵ㡣����ͼ����������ɡ�

ע����õ�ĸ�������һ�ν�����˵���$\texttt{WA}$�ˡ�

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

#### ���ڵ�����
https://www.luogu.com.cn/problem/P2055

�����˺ʹ��Ķ���ͼ���ƥ�䡣Ȼ������ָ��Ҫ�����ˣ����Է�Ϊ�д�(����Уѧ��)�Ҳ���У���˺�û�����ˣ�����У���˲���Ҫ�������ùܡ�

��һ�ν���`g.head[v]`д����`g.head[x]`������ϸ�����濴������(�Ͼ�����Ϲ)��

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

#### [SDOI2015]�Ǽ�ս��
https://www.luogu.com.cn/problem/P3324

��Ϊ��Ŀ��Ҫʹ���ֵ��С�����Կ��Կ��Ƕ���ʱ��$ti$��Ȼ���Դ��������������Ϊ$b[i]\times ti$�ıߣ�����������������������޵ıߣ��ӻ���������������Ϊ$a[i]$�ıߣ���������Ƿ�Ϊװ��ֵ֮�͡�

ע��$\texttt{double}$��д����$\texttt{int}$��Ȼ����ñߵ���������һ�ν�ʱ����û���$\texttt{RE}$�ˡ�

�����ܶ��������������һ���һǧ�����ڳ���һ���һǧ�Ӷ����⸡�����ģ����Ǻܶ����ⲻ�������鷳��

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
#### ��ģ�塿��С���������
https://www.luogu.com.cn/problem/P3381

��ʵ��������$\texttt{Dinic}$������������ע�ⷴ��ߵı�Ȩ��������ߵı�Ȩ���෴�����Լ�$\texttt{ecnt}$һ��Ҫ��ʼ��Ϊ$1$��

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

#### [Vani��Լ��]�����β��
https://www.luogu.com.cn/problem/P4556

��ʵ�߶����ϲ����Ǹ�������ֱ�Ӱ�ÿ��λ���ϵĽڵ����ݼ��������У���Ȼ����ͨ�߶���������ÿ�κϲ����Ӷ���$O(nlogn)$�ģ������ڽڵ���ٵĶ�̬�����߶������������ӶȽ�С����Ϊÿ�κϲ��ĸ��Ӷ�ȡ�������������ص�Ҷ�Ӹ��������ص�Ҷ������Ϊ$n$���ܸ��Ӷ�Ϊ$O(nlogn)$��

������Զ�ÿ���ڵ㿪��ͰȻ�����ϲ�֣��������鿪���£���ʱ������Ȩֵ�߶�����������䵱Ͱ����Ϊ�в������ÿ���ڵ���߶�����Ҫ����Ľڵ���٣��ܹ���Ҫ����Ľڵ������$O(m)$�ģ������ܸ��Ӷ���$O(mlogw)$������$w$Ϊֵ�ķ�Χ��

ע����ʱ�Ƕ�$lca$�����ĸ��׷ֱ�$-1$���ϲ���һ��Ҫ���¸��ڵ��š�

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

#### ������
https://www.luogu.com.cn/problem/P3224

�ò��鼯ά����ͨ�ԣ���ÿ����ͨ��ά��һ��Ȩֵ�߶�����������ͨ�������Ҫ�ȣ���ѯʱֱ�Ӳ�������ˣ��ϲ�ʱ�ͺϲ��߶�����

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
#### [SDOI2015]Ѱ����Ϸ
https://www.luogu.com.cn/problem/P3320

$\texttt{luogu}$������ƻ��ﹾ����̫���ˣ�����һ��һ������Ȼ��֮ǰ�����ǵ�����ʯ��ȫһ������Ȼ��ǰд��������û��һ�����������$dis$���ڱ�������֮������ˣ�����ÿ���ڵ��$dis$���ǵ����ڵ�ľ��룬�����ǵ����ڵ�ľ��롣

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

#### �ܳ�����
https://www.luogu.com.cn/problem/P1495

$\texttt{CRT}$��ģ���⡣����ͬ�෽����$\begin{cases}x\equiv a_1\pmod {m_1}\\\\x\equiv a_2\pmod {m_2}\\\\...\\\\x\equiv a_n\pmod {m_n}\end{cases}$������ģ�����ʣ�����$M=\prod_{i=1}^n m_i$��$M_i=\dfrac{M}{m_i}$��$k_i=M_i^{-1}\pmod {m_i}$������һ����Ϊ$x=\sum_{i=1}^n a_iM_ik_i$��������Ϊ��������һ��������$x\equiv a_j\pmod {m_j}$����$x\equiv a_jM_jk_j\pmod {m_j}$���������$m_j$�ı������Ծ�û�ˡ���$M_j$��$k_j$��$\mod m_j$�����»�Ϊ��Ԫ�����$x\equiv a_j\pmod {m_j}$������Ȼ�����������ģ$M$��

��Ҫע������������$\texttt{exgcd}$����Ԫ�����������������С�������⣬��������$0$��Ҫģһ��$M$������ȡ����ģ$M$����$M$����

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

#### �����ɼ�
https://www.luogu.com.cn/problem/P1447

�򵥵�Ī����Ī�������Ҫ�����õ���������$\mu\ast1=\varepsilon$��$\varphi\ast1=id$��$f\ast\varepsilon=f$��$\mu\ast id=\varphi$��Ȼ����ǽ�����ͺš�

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
#### [HEOI2016/TJOI2016]����
https://www.luogu.com.cn/problem/P2824

����Ķ��֡����������������±�$q$��Ӧ��ֵ$v$����������С��$v$��������$0$�����ڵ���$v$��������$1$��˼·�Ĺؼ������ӽ�������Ĺ��̣�ֱ�ӿ������������������������У���������ϵ����ֻ�����$v$�ı仯���仯�������$q$λΪ$1$˵����$q$λ�ϵ����ִ��ڵ���$v$������С��$v$���������߶���ά������$01$�����ܸ��Ӷ�$O(mlog^2n)$��

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

#### [���Ҽ�ѵ��]�Ȳ�������
https://www.luogu.com.cn/problem/P2757

�߶���ά��$hash$��������ǿ�һ��Ȩֵ�߶�����ÿλ����$0$��$1$��ʾ��û���������Ȼ��ͨ������Ԥ������ݺ�Ĥ$19260817$����$hash$�������Ϳ��Ե����޸ĺ������ѯ$hash$ֵ��Ȼ���ɨ�߼����������ֵ�������ֵ�����Ե�ǰ����������Ϊ���ĵ����಻�Գƣ�˵�������Ե�ǰ����������Ϊ���ĵĵȲ����У����ǿ���ά����������$hash$ֵ������Ե�ǰ����������Ϊ���ĵļ�����������$hash$ֵ��ͬ��Գƣ�Ҳ���ǲ������Ե�ǰ����������Ϊ���ĵĵȲ����С�

�����Ҷ϶����������߸�Сʱ��̬�������ˣ���Ϊ�ǵ�һ��д$hash$���Ի���Ϊ��$hash$д���˻��߱�$\texttt{int}$��֮��ģ���������ǲ�ѯʱĳһ���ӽڵ�$hash$ֵ����Ԥ�������ʱ���˵��ݵ�ָ�����ӽڵ�����䳤�ȣ������ڲ�ѯ�����䲻��ȫ���ǵ�ǰ�ڵ�ʱ�ᵼ��$hash$ֵ������ȷ�����ǳ˵��ݵ�ָ��Ϊ��ѯ������߽絽�е�����䳤�ȡ�

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

#### [HAOI2009]ëë��
https://www.luogu.com.cn/problem/P3174

������֮ǰ���ź��ѣ������ҹ�����������������������⣬���־��Ǹ��ܼ򵥵�ħ������$\texttt{DP}$��ֱ��������$dp[x]$��ʾ��$x$Ϊ���������ڽڵ�����ëë�棬Ȼ����ԭ�����Ļ����ϼӼӼ����ͺ��ˡ�

ע��$n=1$�������

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
#### Emiya �ҽ���ķ�
https://www.luogu.com.cn/problem/P5664

ÿһ�еĲ˲�����һ��ķ���������û�����Ƶķ�������ȥĳһ���ϵĲ˳���һ��ķ�������ѡ��Ĳ˳���һ��������ֻ��һ������˿���ö����һ�У�Ȼ����$dp[i][j][k]$��ʾǰ$i$���е�ǰѡ��ĵ�$l$��ѡ��$j$�������������ܹ�ѡ��$k$������Ȼ��$dp[i][j][k]=dp[i-1][j][k]+dp[i-1][j-1][k]\times a[i][l]+dp[i-1][j][k-1]\times (sum[i]-a[i][l])$����Ϊֻ���ĵ�ǰ�к������еĴ�С��ϵ��˿�����$dp[i][j]$��ʾǰ$i$���е�ǰѡ�ĵ�$k$��ѡ�������������ܹ�ѡ�����Ĳ�Ϊ$j$����ô$dp[i][j]=dp[i-1][j]+dp[i-1][j-1]\times a[i][k]+dp[i-1][j+1]\times (sum[i]-a[i][k])$���߽�������$dp[0][0]=1$������$\sum_{i=1}^n dp[n][i]$��ע��ڶ�ά�����Ǹ��������������ö��ʱ����������һ���̶�������ʹ�ü��Ϻ�һ�����ڵ���$0$��û�����Ƶķ��������򵥣���$dp[i][j]$Ϊǰ$i$���ܹ�ѡ��$j$�����ķ�������Ȼ��$dp[i][j]=dp[i-1][j]+dp[i-1][j-1]\times sum[i]$���߽�������$dp[0][0]=1$������$\sum_{i=1}^n dp[n][i]$��

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
#### ����
https://www.luogu.com.cn/problem/P4981

�б���и�����������Ҫ�õ�һ����$\texttt{prufer}$���еĶ���������ʹһ���޸�����һ�������໥ת�����޸����϶���Ϊ$1$�ĵ��ΪҶ�ӽڵ㡣����һ������ÿ���ҳ������С��Ҷ�ӽڵ㣬Ȼ��Ѻ���Ψһ���ӵĵ�ı��д������ĩβ��ֱ��ֻʣ�������㣬�õ������о����������$\texttt{prufer}$���С�����һ��$\texttt{prufer}$���У������ұ�����ÿ���ڵ㼯���ҵ����������еı����С�ĵ㣬�������͵�ǰ�������������ϵĵ���һ���ߣ����ѵ㼯��ʣ����������һ���ߣ�Ȼ��͵õ���������ж�Ӧ������

$\texttt{prufer}$���к�����һһ��Ӧ�ġ�һ��$n$���������Ӧ��$\texttt{prufer}$���еĳ���Ϊ$n-2$���������������һ������ֵ����Ϊ$[1,n]$������һ���������$n$������б���޸���������Ϊ$n^{n-2}$��

�����и���������ö����ÿ���㶼������������б���и���������Ϊ$n^{n-1}$��

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

#### [HNOI2004]���ļ���
https://www.luogu.com.cn/problem/P2290

һ����Ķ���Ϊ$d_i$����ô����$\texttt{prufer}$�����г��ֵĴ�������$d_i-1$��������Ǻ���Ȼ�ġ����������ת��Ϊÿ��Ԫ�س��ֹ�ָ�������������������Ȱ���ͬԪ�ؿ�����ͬԪ�����Ǵ���$(n-2)!$��Ȼ����ͬԪ��֮�佻��λ�ò���������ף���������в�Ӱ��𰸣����԰Ѵ𰸳���ÿ�����Ķ�����һ�Ľ׳ˡ����Դ���$\dfrac{(n-2)!}{\prod_{i=1}^n (d_i-1)!}$��

���ⲻ��ȡģ����$\texttt{long long}$�ڷ�Χ�ڣ����м�����лᱬ$\texttt{long long}$��д�߾��ȱȽ�С���������Ϊֻ�г˳����������Կ���ÿ�ΰ�Ҫ�˳������������ֽ⣬Ȼ��ת��Ϊ�Ӽ�����

ע�����С�

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

#### A. ţţ���ַ���
https://ac.nowcoder.com/acm/contest/6885/A

���ϱȽ��У���ȥ����ţ�͵ı�������һ�δ�ֱ��Ĥ�㼴�ɣ������ҽ���$6$�βŹ���

˳�㵱��ѧϰ��$\texttt{getline}$���÷���

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

#### B. ţţ��λ����
https://ac.nowcoder.com/acm/contest/6885/B

$a\And b\le a,b$����˴𰸾�����������

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

#### C. ţţ������
https://ac.nowcoder.com/acm/contest/6885/C

������˰��첻���������д�˸�$O(t+nlogn)$�ı�������ҹ��ɣ�����$3$�ı����Ǳذܾ��棬�����Ǳ�ʤ���档

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
#### D. ţ�ð�����
https://ac.nowcoder.com/acm/contest/6885/D

����̰�ģ�����������У������ǰ������������ǰһ��������$1$��ǰ׺��ת��ǰλ�ã����򵥵㷭ת��ǰλ�á�

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

�������ⶼ���ᡣ

### 2020-08-15
#### [SDOI2016]���м���
https://www.luogu.com.cn/problem/P4071

ö����Щλ������������������$\dbinom{n}{m}$��Ȼ�����ÿ�������ʣ�µ�λ�þ���һ���������⣬��$f[n]$��ʾû�����ֺ��±���ͬ������������𰸾���$\dbinom{n}{m}f[n-m]$��

���������Ԥ����׳ˣ�Ȼ����׳˵���Ԫ��$O(logp)$���㡣���������ַ�����һ�ֿ���$O(n)$Ԥ����$f[n]=(n-1)\times(f[n-1]+f[n-2])$��������Ϊ��$n$�������ܷŵ���$n$��λ�ã�����ö�ٷŵ�ǰ$n-1$��λ�ã���ŵ��˵�$k$��λ�ã���ô��$k$��λ���ϵ������Էŵ���$n$��λ�ã���������������$f[n-2]$��Ҳ���Բ����ڵ�$n$��λ�ã���ʱ����$p_k$����$p_n$����$p_n$���ڵ�$n$��λ�ã���ô����������$f[n-1]$�������ܷ���������$(n-1)\times(f[n-1]+f[n-2])$��

��һ�ַ������ݳ�ԭ�������$\texttt{SDSC}$�ؼҵ�·��������һ����������ͨΪʲô���ŵĵ��ƹ�ʽ���ݳ�ԭ��Ĺ�ʽ�ǶԵ���(���������Լ�����̫�ó�)�����Ͽ�����2013��ļ�ѵ�����ļ������潲�ݳ�ԭ���ú���ϸ���ҿ��˾��ú��������ϸ��һ��Ȼ��������д�ݳ�ķ�������Ϊ�ص������ֲ��ܰ�ҹ�ˣ��ҵ��ഺ�����ˡ�

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

### 2020-08-16
����Ѳ��͵�$\LaTeX$�޺��ˣ�Ҫ��������û�����ˡ�(������������û��������ʾ)

�����ݳ�ԭ����Ҫ��������ʽ��
$$\left|\bigcup_{i=1}^nS_i\right|=\sum_{m=1}^n(-1)^{m+1}\sum_{a_i<a_{i+1}}\left|\bigcap_{i=1}^mS_{a_i}\right|$$
$$\left|\bigcap_{i=1}^nS_i\right|=|U|-\left|\bigcup_{i=1}^n\overline{S_i}\right|$$

��һ�������ݳ�ԭ��Ĺ�ʽ���ݳ�ԭ����ʵ��һ��ת���Ƕȵ�˼ά��ʽ����һ���ǰ��󲢼�ת��Ϊ�󽻼����ڶ����ǰ��󽻼�ת��Ϊ�󲹼��Ĳ�����һ���ҳ���Ŀ��Ҫ��������һЩ����������Ϊ$P_i$��������$P_i$�Ĵ𰸵ļ�����Ϊ$S_i$��Ȼ�����������$\left|\bigcap_{i=1}^nS_i\right|$��

�������⣺��$i$��λ���ϵ�����$P_i$����$p_i\not=i$��$S_i=\{p|p_i\not=i\}$����$\left|\bigcap_{i=1}^nS_i\right|$��

$\overline{S_i}=\{p|p_i=i\}$������$|\overline{S_i}|=(n-1)!$��$|\bigcap_{i=1}^m\overline{S_i}|=(n-m)!$����ˣ�

$$\left|\bigcup_{i=1}^n\overline{S_i}\right|=\sum_{m=1}^n(-1)^{m+1}\sum_{a_i<a_{i+1}}\left|\bigcap_{i=1}^m\overline{S_{a_i}}\right|\\\\=\sum_{m=1}^n(-1)^{m+1}\dbinom{n}{m}(n-m)!\\\\=\sum_{m=1}^n(-1)^{m+1}\dfrac{n!}{m!}.$$

$|U|=n!$�����Դ�Ϊ��

$$\left|\bigcap_{i=1}^nS_i\right|=|U|-\left|\bigcup_{i=1}^n\overline{S_i}\right|\\\\=n!-\sum_{m=1}^n(-1)^{m+1}\dfrac{n!}{m!}\\\\=n!\left(1+\sum_{m=1}^n\dfrac{(-1)^m}{m!}\right)\\\\=n!\sum_{m=0}^n\dfrac{(-1)^m}{m!}$$

�������ǾͿ���$O(n)$�����������Ĵ𰸡���Ȼ�ݳ�ԭ��Ĺ�ʽ��ö���Ӽ��ĸ��Ӷ���ָ�����ģ���ͨ����ʽ�Ӻϲ��𰸿��Եó�����Ч�ļ��㷽����

�������̽�ĸ���������$\sum_{i=1}^nx_i=m$�ķǸ�������ĸ���Ϊ$\dbinom{m+n-1}{n-1}$�����ǲ�巨���൱����$m$�����м���$n-1$����Ȼ��ѡ��$n-1$�����û��ѡ���$m$����ֳ�$n$�顣

��ÿ����������$x_i\le b_i$�����ƺ󣬿���ͨ���ݳ�����ĸ�����$\overline{S_i}$�൱��$x_i\ge b_i+1$����������û�����ƵĽ�ĸ�������ô�ѵ�ʽ���߼�ȥ$b_i+1$���Ͱ�����ת��Ϊ����Ǹ�������ĸ��������������Ǹ�����������$\overline{S_i}$�Ľ����ļ��㷽��Ҳ����ˡ�ʣ�µĶ���ֱ�����ݳ�Ĺ�ʽ�������ͽ�������⡣

�������ݲο����ϣ�

- 2013����Ϣѧ����ƥ�� �й����ҶӺ�ѡ��Ա���ļ� ��ǳ̸�ݳ�ԭ��(����)��

- https://sshwy.github.io/2019/04/41980/ �ݳ�ԭ������ (sshwy)

��ô˳��дһ������$\texttt{D2T1}$�Ĺ�ʽ���ⷨ($\texttt{CSP2019}$����Զ��ʹ)��

ö��ÿ��ѡ���ĵ��ˣ���$i$�п�ѡ$sx_i$���ˣ���$i$��ѡ��$sy_i$���ˡ���������$P_i$��$sy_i\le\left\lfloor\dfrac{n}{2}\right\rfloor$����ô

$$\left|\bigcap_{i=1}^mS_i\right|=|U|-\left|\bigcup_{i=1}^m\overline{S_i}\right|\\\\=\prod_{i=1}^nsx_i-\sum_{i=1}^m|\overline{S_i}|\\\\=\prod_{i=1}^nsx_i-\sum_{i=1}^m\sum_{j=1}^ndp[n][j]$$

�ڶ�������Ϊ���ֻ��һ�в�������������˲���֮��û�н�����ֱ�Ӽ��������ɡ�

#### [HAOI2008]Ӳ�ҹ���
https://www.luogu.com.cn/problem/P1450

��$\sum_{i=1}^4c_ix_i=s$�ķǸ�������ĸ�����Ҫ��$x_i\le d_i$�����û��������ô��������ȫ����Ԥ�������𰸡��������ƺ�������ú�����һ���ķ����ݳ�ϲ��𰸡�

```cpp
#include<cstdio>

int c[5], n, d[5], s;
long long dp[100100];

int main() {
    scanf("%d%d%d%d%d", &c[1], &c[2], &c[3], &c[4], &n);
    dp[0] = 1;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 100000; j++)
            if (j - c[i] >= 0) dp[j] += dp[j - c[i]];
    while (n--) {
        scanf("%d%d%d%d%d", &d[1], &d[2], &d[3], &d[4], &s);
        long long ans = 0;
        for (int stt = 1; stt <= 15; stt++) {
            int cnt = 0, t = s;
            for (int i = 1; i <= 4; i++) if (stt & (1 << (i - 1))) t -= c[i] * (d[i] + 1), cnt++;
            if (t < 0) continue;
            if (cnt % 2) ans += dp[t];
            else ans -= dp[t];
        }
        printf("%lld\n", dp[s] - ans);
    }
    return 0;
}
```

#### [HAOI2016]������
https://www.luogu.com.cn/problem/P3182

��Ϊ�ϰ�����ͬһ��ͬһ�����Կ�����������к��е�˳����������һ����λ��������ӣ�Ȼ��ö��ÿ�зŵ��������ڵ��е�λ�ã���������һ���������⣬����ֱ�ӵ�����⣬��Ϊû��ģ������Ҫд�߾��ȡ�

Ȼ�����ѹ$8$λ�ĸ߾�������$1e8$��д��$1e9$����һ��Сʱ��

```cpp
#include<cstdio>
#include<cstring>

int n;
struct number {
    int a[5010], n;
    int& operator [] (const int &idx) { return a[idx]; }
    inline int max(int a, int b) { return a > b ? a : b; }
    inline void add(number &x, number &y) {
        for (int i = 1; i <= max(x.n, y.n); i++) {
            a[i + 1] += ((long long)x[i] + y[i]) / (int)1e8;
            a[i] += ((long long)x[i] + y[i]) % (int)1e8;
        }
        n = max(x.n, y.n);
        if (a[n + 1]) n++;
    }
    inline void mul(int x, number y) {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= y.n; i++) {
            a[i + 1] += ((long long)x * y[i]) / (int)1e8;
            a[i] += ((long long)x * y[i]) % (int)1e8;
        }
        n = y.n;
        if (a[n + 1]) n++;
    }
    inline void print() {
        printf("%d", a[n]);
        for (int i = n - 1; i >= 1; i--) printf("%08d", a[i]);
        printf("\n");
    }
}dp[210];

int main() {
    scanf("%d", &n);
    dp[2].a[1] = 1, dp[2].n = 1;
    for (int i = 3; i <= n; i++) {
        dp[i].add(dp[i - 1], dp[i - 2]);
        dp[i].mul(i - 1, dp[i]);
    }
    dp[n].print();
    return 0;
}
```