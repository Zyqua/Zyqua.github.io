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