title: 王道征途——NOIP2020冲刺计划·第七周(8.3~8.9)
date: 2020-08-08
weight: 20200808
<!--more-->
前段时间上正睿的课，因为父母不让晚上熬夜所以一直没有时间总结，今天(8.7)来$\texttt{SDSC}$报到，晚上熬夜没人管，爽了。
### 2020-08-07
今天搞了搞博弈论。

博弈论主要就是个$sg$函数，不过先在这里写下先手必胜与必败状态(因为总会按照最优策略选择，所以是胜负是必然确定的)：

必胜就是$\texttt{N-position}$，这里的"$N$"指$Next$，为啥这么叫我也不知道。必败是$\texttt{P-position}$，"$P$"指$Previous$。

必胜局面一定存在一个后继节点是必败局面，必败局面一定不存在一个后继节点是必败局面(即所有后继节点都是必胜局面)，这个很好理解。没有后继节点的是必败局面。

定义一个节点的$sg$函数值为它的后继节点的$\texttt{mex}$，那么没有后继节点的$sg$相当于空集的$\texttt{mex}$，即$0$；一个节点的$sg$大于$0$，说明一定有一个后继节点的$sg$为$0$；一个节点的$sg$为$0$，说明不存在一个后继节点的$sg$为$0$，这恰好对应了上面这一段的逻辑。也就是说，$sg$为$0$的节点为必败局面，$sg$大于$0$的节点为必胜局面。

这只是单独一个游戏的$sg$。若有多个子游戏，则整个游戏的$sg$为所有子游戏的$sg$的异或和，这就是$\texttt{SG}$定理。

很不严谨的证明：设所有子游戏的$sg$的异或和为$k$。若$k>0$，那么必然有某个子$sg$对应$k$的最高位上为$1$，那么把这个$sg$变为$sg\^k$后，一定会变小，因为$k$的最高位对应的$1$没了，其他更小的位再怎么变也没有影响。所以总能找到一个子$sg$将其变为$sg\^k$，然后异或和就变为$0$，对应着必败局面，而异或和大于$0$，则对应着必胜局面。

#### 【模板】nim游戏
https://www.luogu.com.cn/problem/P2197

这个就是名副其实的模板，每堆都是一个子游戏，每个子游戏的$sg$为$sg(x)=x$，可以用归纳法证明。

另外似乎大家讲博弈论都喜欢用这个问题导入，而不是像上面那样直接讲，我更喜欢直接讲，因为之前这个$sg(x)=x$搞得我很迷惑。

```cpp
#include<cstdio>

int t, n, a[10010];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int sg = 0;
        for (int i = 1; i <= n; i++) sg ^= a[i];
        if (sg) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```

#### [USACO09OPEN]Cow Digit Game S
https://www.luogu.com.cn/problem/P2953

每个节点有两个后继节点，然后直接递推预处理$sg$即可。

一个技巧是把$sg$开为$\texttt{bool}$型数组，因为我们只关心$sg$是否大于$0$，这样就避免了麻烦的$\texttt{mex}$。

```cpp
#include<cstdio>

int t, n;
bool sg[1000100];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
inline int minnum(int x) {
    register int ans = 10;
    while (x) {
        if (x % 10) ans = min(ans, x % 10);
        x /= 10;
    }
    return ans;
}
inline int maxnum(int x) {
    register int ans = 0;
    while (x) {
        ans = max(ans, x % 10);
        x /= 10;
    }
    return ans;
}

int main() {
    for (int i = 1; i <= 1000000; i++)
        sg[i] = !sg[i - minnum(i)] || !sg[i - maxnum(i)];
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (sg[n]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

#### 取火柴游戏
https://www.luogu.com.cn/problem/P1247

首先判断一下是否必胜，然后求第一步的方案。本质上是把异或和变为$0$，于是通过上面的文字，可以知道只要从左到右枚举找到最小的$b$使得$a[b]\^ sg< a[b]$即可，至于$a$的字典序，因为$a$是唯一的所以不用管它。

```cpp
#include<cstdio>

int n, a[500100], sg, b;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) sg ^= a[i];
    if (!sg) printf("lose\n");
    else {
        for (int i = 1; i <= n; i++)
            if ((a[i] ^ sg) < a[i]) { b = i; break; }
        printf("%d %d\n", a[b] - (a[b] ^ sg), b);
        a[b] = a[b] ^ sg;
        for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    }
    return 0;
}
```

### 2020-08-08
今天是$\texttt{wqy}$讲的图论。
#### 运输计划
https://www.luogu.com.cn/problem/P2680

这题在一年多前曾写过，当时在学树剖，写法是树剖加暴力枚举，但没有过。现在再做，正解做法是二分最长链长度，每次判断能否通过把某条边变为$0$，使得最长链长度小于等于二分的值。具体就是对于每个长度大于二分值的链，把链上每条边标记一下也就是加一，这个可以用树上差分处理。然后枚举每条边，找到一条被所有大于二分值的路径标记且边权最大的边，并把它的边权变为$0$，如果最长链减去置$0$的边后长度小于二分值，说明方案可行，因为其他链都小于最长链，所以减去这条边后还是小于最长链。至于要找被所有大于二分值的路径经过的边，是因为如果不找被所有大于二分值的路径经过的边，那么把它置$0$后总有一条链大于二分值，那么一定不能找到可行方案。

另外，$\texttt{wqy}$还讲了一些卡常的技巧。二分左边界可以写成最长链减最大边，右边界可以写成最长链，这样就把二分范围从$3e8$降到了$1e3$。然后在树上差分计算子树和时，可以用$\texttt{bfs}$代替$\texttt{dfs}$，这样更快，还可以预先把树$\texttt{bfs}$一遍按照顺序存下节点，然后到时候直接遍历数组就可以，不用开队列，更快。

实测普通正解做法总运行时间为$\texttt{3.16s}$，加入卡常技巧后为$\texttt{1.81s}$，快了接近一倍。

总复杂度$O(n+m)logw$。

另外记得$\texttt{cnt}$要及时清空。
```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m, depth[300100], dis[300100], f[300100][20], cnt[300100], w[300100], maxdist, maxw, bfnnode[300100], bfncnt;
struct chain { int u, v, lca; }plans[300100];
struct edge { int to, next, w; };
struct graph {
	int ecnt = 1, head[300100];
	edge edges[600100];
	inline void addedge(int u, int v, int w) {
		edges[++ecnt].to = v;
		edges[ecnt].w = w;
		edges[ecnt].next = head[u];
		head[u] = ecnt;
	}
}g;
std::queue<int> q;

inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
inline int max(int a, int b) { return a > b ? a : b; }
void dfs(int x, int fa) {
	depth[x] = depth[fa] + 1;
	f[x][0] = fa;
	for (int i = 1; i < 20; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for (int i = g.head[x]; i; i = g.edges[i].next) {
		int &t = g.edges[i].to;
		if (t == fa) continue;
		dis[t] = dis[x] + g.edges[i].w;
		w[t] = g.edges[i].w;
		dfs(t, x);
	}
}
int lca(int x, int y) {
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (depth[f[x][i]] >= depth[y]) x = f[x][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; i--)
		if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
inline void bfs1() {
	q.push(1);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		bfnnode[++bfncnt] = x;
		for (int i = g.head[x]; i; i = g.edges[i].next) {
			int &t = g.edges[i].to;
			if (depth[t] < depth[x]) continue;
			q.push(t);
		}
	}
}
inline void bfs2() {
	for (int i = n; i >= 1; i--) {
		int x = bfnnode[i];
		for (int j = g.head[x]; j; j = g.edges[j].next) {
			int &t = g.edges[j].to;
			if (depth[t] < depth[x]) continue;
			cnt[x] += cnt[t];
		}
	}
}
inline int dist(int i) { return dis[plans[i].u] + dis[plans[i].v] - (dis[plans[i].lca] << 1); }
bool check(int maxdis) {
	memset(cnt, 0, sizeof(int) * (n + 1));
	int plancnt = 0, maxdist = 0;
	for (int i = 1; i <= m; i++) {
		if (dist(i) <= maxdis) continue;
		cnt[plans[i].u]++, cnt[plans[i].v]++, cnt[plans[i].lca] -= 2;
		plancnt++;
		maxdist = max(maxdist, dist(i));
	}
	bfs2();
	int maxw = 0;
	for (int x = 1; x <= n; x++)
		if (cnt[x] == plancnt) maxw = max(maxw, w[x]);
	return maxdist - maxw <= maxdis;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g.addedge(u, v, w), g.addedge(v, u, w);
		maxw = max(maxw, w);
	}
	dfs(1, 0);
	bfs1();
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &plans[i].u, &plans[i].v);
		plans[i].lca = lca(plans[i].u, plans[i].v);
		maxdist = max(maxdist, dist(i));
	}
	int l = max(maxdist - maxw, 0), r = maxdist + 1;
	while (l < r) {
		int mid = l + (r - l >> 1);
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
```

#### Royal Questions
https://www.luogu.com.cn/problem/CF875F

把王子看作点，公主看作边，那么问题求的就是图的最大生成基环森林。做法和$\texttt{Kruskal}$十分类似，只要多记录一个连通块是否存在环就可以了。

```cpp
#include<cstdio>
#include<algorithm>

int n, m, ans;
struct unionsetnode { int fa, size; bool iscircle; };
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
struct unionset {
	unionsetnode nodes[200100];
	inline void init() { for (int i = 1; i <= n; i++) nodes[i].fa = i, nodes[i].size = 1; }
	int find(int x) {
		if (nodes[x].fa == x) return x;
		return nodes[x].fa = find(nodes[x].fa);
	}
	inline void merge(int x, int y) {
		x = find(x), y = find(y);
		if (nodes[x].size < nodes[y].size) swap(x, y);
		nodes[y].fa = x;
		nodes[x].size += nodes[y].size;
		nodes[x].iscircle = nodes[x].iscircle || nodes[y].iscircle;
	}
	inline bool same(int x, int y) { return find(x) == find(y); }
	inline bool iscircle(int x) { return nodes[find(x)].iscircle; }
	inline void setcircle(int x) { nodes[find(x)].iscircle = true; }
}uset;
struct edge {
	int u, v, w;
	bool operator < (const edge &a) const { return w > a.w; }
}edges[200100];

int main() {
	scanf("%d%d", &n, &m);
	uset.init();
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
	std::sort(edges + 1, edges + m + 1);
	for (int i = 1; i <= m; i++) {
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		if (!uset.same(u, v) && !(uset.iscircle(u) && uset.iscircle(v))) uset.merge(u, v), ans += w;
		else if (uset.same(u, v) && !uset.iscircle(u)) uset.setcircle(u), ans += w;
	}
	printf("%d\n", ans);
	return 0;
}
```

### 2020-08-09
今天是$\texttt{ckw}$讲的线段树，虽然按照计划应该学数学但实在是没时间了，晚上还得打$\texttt{CF}$。
#### 园丁的烦恼
https://www.luogu.com.cn/problem/P2163

先把坐标离散化，然后把一个点看作一次加点操作，一次查询通过二维前缀和分成共四次正查询操作和负查询操作，然后把所有操作按照纵坐标和操作种类排序，并用扫描线从小到大枚举纵坐标，用树状数组求得每次查询操作的答案。总复杂度$O((n+m)logn)$，但是常数很大需要吸氧才能过。因为坐标在$1e7$范围内所以可以开个桶代替$\texttt{std::lower_bound}$，降低常数，但不吸氧还是过不去。

注意$\texttt{sx,sy}$要开到$1.5e6$，而不是$5e5$，然后还有离散化后两个坐标的最大值分别是$\texttt{lenx}$和$\texttt{leny}$而不是$\texttt{sx[lenx]}$和$\texttt{sy[leny]}$。

另外发现$\texttt{C++}$的$\texttt{template}$真好用，可以大大减轻写代码的负担。

```cpp
#include<cstdio>
#include<algorithm>

int n, m, cur = 1, ans[500100];
struct treearray {
	int a[500100], len;
	inline int lowbit(int x) { return x & (-x); }
	inline void add(int x, int v) { for (; x <= len; x += lowbit(x)) a[x] += v; }
	inline int sum(int x) {
		register int ans = 0;
		for (; x >= 1; x -= lowbit(x)) ans += a[x];
		return ans;
	}
}ft;
struct query {
	int x, y, type, id;
	query(int xv = 0, int yv = 0, int tv = 0, int iv = 0): x(xv), y(yv), type(tv), id(iv) {}
};
template<typename data, int len>
struct array {
	data a[len];
	int cnt;
	inline void push_back(data x) { a[++cnt] = x; }
	data& operator [] (const int &idx) { return a[idx]; }
};
array<int, 1500100> sx, sy;
array<query, 2500100> queries;

bool cmp(const query &a, const query &b) {
	if (a.y ^ b.y) return a.y < b.y;
	return a.type < b.type;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x++, y++;
		sx.push_back(x), sy.push_back(y);
		queries.push_back(query(x, y, 1, 0));
	}
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a++, b++, c++, d++;
		queries.push_back(query(c, d, 2, i));
		queries.push_back(query(a - 1, d, 3, i));
		queries.push_back(query(c, b - 1, 3, i));
		queries.push_back(query(a - 1, b - 1, 2, i));
		sx.push_back(c), sx.push_back(a - 1);
		sy.push_back(d), sy.push_back(b - 1);
	}
	std::sort(sx.a + 1, sx.a + sx.cnt + 1); std::sort(sy.a + 1, sy.a + sy.cnt + 1);
	int lenx = std::unique(sx.a + 1, sx.a + sx.cnt + 1) - sx.a - 1, leny = std::unique(sy.a + 1, sy.a + sy.cnt + 1) - sy.a - 1;
	for (int i = 1; i <= queries.cnt; i++) {
		queries[i].x = std::lower_bound(sx.a + 1, sx.a + lenx + 1, queries[i].x) - sx.a;
		queries[i].y = std::lower_bound(sy.a + 1, sy.a + leny + 1, queries[i].y) - sy.a;
	}
	std::sort(queries.a + 1, queries.a + queries.cnt + 1, cmp);
	ft.len = lenx;
	for (int y = 1; y <= leny; y++) {
		for (; queries[cur].y <= y && cur <= queries.cnt; cur++) {
			int x = queries[cur].x, opt = queries[cur].type;
			if (opt == 1) ft.add(x, 1);
			else if (opt == 2) ans[queries[cur].id] += ft.sum(x);
			else if (opt == 3) ans[queries[cur].id] -= ft.sum(x);
		}
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
```

#### A. Suborrays
http://codeforces.com/contest/1391/problem/A

每次直接从小到大输出一个从$1$到$n$的序列即可。因为这样对于每个长度为$k$的区间，区间最大值至少为$k$，而区间按位或和大于等于区间最大值，所以满足条件。

```cpp
#include<cstdio>

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) printf("%d ", i);
        printf("\n");
    }
    return 0;
}
```

#### B. Fix You
http://codeforces.com/contest/1391/problem/B

还以为是$\texttt{DP}$，调了一个小时没调出来，最后发现只要考虑把边界上会让包裹丢失的点改一下就行了。

```cpp
#include<cstdio>
#include<cstring>

int t, n, m;
char dir[110][110];

inline char read() {
    register char c = getchar();
    while (!('A' <= c && c <= 'Z')) c = getchar();
    return c;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        int ans = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) dir[i][j] = read();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (i == n && dir[i][j] == 'D') ans++;
                if (j == m && dir[i][j] == 'R') ans++;
            }
        printf("%d\n", ans);
    }
    return 0;
}
```