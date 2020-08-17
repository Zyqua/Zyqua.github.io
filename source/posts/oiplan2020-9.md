title: 王道征途——NOIP2020冲刺计划·第九周(8.17~8.23)
date: 2020-08-17
weight: 20200817
<!--more-->
### 2020-08-17
昨天半夜里突然发现博客的$\LaTeX$在本地正常，交到服务器上就挂了，不过不管了，反正基本上都是给自己看的，中国有句古话叫做闷声发大财，这是坠吼的，至于我为什么总是这么自闭，无可奉告。

~~我不会说今天颓了一下午的冒险王精灵物语~~
#### 寻找段落
二分一个$x$，表示判断是否存在一个平均值大于等于$x$的区间。即$\dfrac{\sum_{i=l}^r a_i}{r-l+1}\ge x$。简单推式子得到$\sum_{i=l}^r(a_i-x)\ge 0$，那么可以把序列中每个数减去$x$，再顺序遍历一遍数组，把区间和转换为前缀和的差，用单调队列维护合法的位置(即满足到当前位置的距离$\in[s,t]$)的前一个位置的前缀和的最小值(因为要使当前区间最大，所以要使减去的数最小)，如果区间和大于$0$则可行。

```cpp
#include<cstdio>
#include<queue>

const double eps = 1e-6;
int n, s, t, a[100100];
double sum[100100];

bool check(double mid) {
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i] - mid;
    std::deque<int> q;
    for (int i = s; i <= n; i++) {
        while (!q.empty() && sum[q.back()] >= sum[i - s]) q.pop_back();
        q.push_back(i - s);
        while (!q.empty() && q.front() < i - t) q.pop_front();
        if (sum[i] - sum[q.front()] >= 0) return true;
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &s, &t);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    double l = -10000, r = 10001;
    while (r - l > eps) {
        double mid = l + (r - l) / 2;
        if (check(mid)) l = mid + eps;
        else r = mid;
    }
    printf("%.3lf\n", l - eps);
    return 0;
}
```

#### [USACO14MAR]Sabotage G
https://www.luogu.com.cn/problem/P2115

和上一题差不多，由$\dfrac{\sum_{i=1}^n a_i-\sum_{i=l}^r a_i}{n-(r-l+1)}\le x$得$\sum_{i=1}^n(a_i-x)-\sum_{i=l}^r(a_i-x)\le 0$，然后为了使上面那个式子尽量小$\sum_{i=l}^r(a_i-x)$要尽量大，所以还是单调队列维护最小值。然后遍历时不需要考虑第$1$个位置和第$n$个位置，只有计算总和时要算上。

```cpp
#include<cstdio>

const double eps = 1e-6;
int n, a[100100];
double sum[100100];

inline double min(double a, double b) { return a < b ? a : b; }

bool check(double mid) {
    for (int i = 2; i < n; i++) sum[i] = sum[i - 1] + a[i] - mid;
    double minsum = 1e9, sumn = sum[n - 1] + a[1] - mid + a[n] - mid;
    for (int i = 2; i < n; i++) {
        minsum = min(minsum, sum[i - 1]);
        if (sum[i] - minsum >= sumn) return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    double l = 1, r = 10001;
    while (r - l > eps) {
        double mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + eps;
    }
    printf("%.3lf\n", l);
    return 0;
}
```

#### 赛道修建
https://www.luogu.com.cn/problem/P5021

一看题面显然要二分最小链长，然后因为子树中最多只有一条链可以向上产生贡献，所以就要在当前子树的链两两匹配的数量最大的前提下，剩下的向上传的链最长。

```cpp
#include<cstdio>
#include<set>

int n, m, cnt, lim, minw = 0x3fffffff, sumw, dp[50010], diameter;
struct edge { int to, next, w; };
struct graph {
    int ecnt = 1, head[50010];
    edge edges[100100];
    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
int dfs(int x, int lst) {
    register int ans = 0;
    std::multiset<int> s;
    for (register int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &v = g.edges[i].to, w = g.edges[i].w;
        int f = dfs(v, i);
        if (f + w >= lim) cnt++;
        else s.insert(f + w);
    }
    while (!s.empty()) {
        std::multiset<int>::iterator i = s.begin(), p = s.lower_bound(lim - *i);
        if (p == i) p++;
        if (p != s.end()) s.erase(p), cnt++;
        else ans = max(ans, *i);
        s.erase(i);
    }
    return ans;
}
inline int read() {
    register int ans = 0;
    register char c = getchar();
    while (c == ' ' || c == '\n' || c == '\r') c = getchar();
    while ('0' <= c && c <= '9') {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}
void dfs2(int x, int lst) {
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        if (i == (lst ^ 1)) continue;
        int &v = g.edges[i].to, w = g.edges[i].w;
        dfs2(v, i);
        diameter = max(diameter, dp[x] + dp[v] + w);
        dp[x] = max(dp[x], dp[v] + w);
    }
}

int main() {
    n = read(); m = read();
    for (register int i = 1; i < n; i++) {
        register int u, v, w;
        u = read(); v = read(); w = read();
        g.addedge(u, v, w); g.addedge(v, u, w);
        minw = min(minw, w), sumw += w;
    }
    dfs2(1, 0);
    register int l = minw, r = diameter + 1;
    while (l < r) {
        int mid = l + (r - l >> 1); lim = mid;
        cnt = 0; dfs(1, 0);
        if (cnt >= m) l = mid + 1;
        else r = mid;
    }
    printf("%d\n", l - 1);
    return 0;
}
```