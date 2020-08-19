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

一看题面显然要二分最小链长，然后可以考虑各种部分分做法，比如链，菊花等等。因为子树中最多只有一条链可以向上产生贡献，所以就要在当前子树的链两两匹配的数量最大的前提下，剩下的向上传的链最长。

交上去有个测试点超时了，为了卡常可以先求树的直径，然后把二分的上边界改成树的直径$+1$，再加上快读足以通过。

上年在$SDSC$听ckw讲这题时感觉特别复杂完全听不懂，今天一看题解感觉没那么难，看来这一年还是有一点进步的，我稍稍感到一点欣慰。

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

### 2020-08-18
金牌爷说，很多选手是在脱离随机变量的情况下学习期望的，这样做是不可取的。那么下面来点公式：

$$P(A|B)=\dfrac{P(AB)}{P(B)}$$

这是条件概率的计算公式。

$$P(A)=\sum_kP(A|B_k)P(B_k)$$

这是全概率公式。

$$P(A|B)=\dfrac{P(B|A)P(A)}{P(B)}$$

这是贝叶斯公式，可以用来计算逆向概率。

$$(X=x)=\{\omega|\omega\in\Omega,X(\omega)=x\}$$

这是对$X=x$这一事件的定义。其中$X$是一个随机变量。

另外，随机变量的定义是一个函数，其自变量为基本事件，函数值为一个实值。所以，其实随机变量既不随机，也不是变量，它是一个确定的函数，因为基本事件的选取是随机的所以函数值才是随机的。事件的定义是一个基本事件的集合。基本事件的定义是一个不能再继续划分的事件。$\Omega$的意思是所有基本事件的集合。

$$E[X]=\sum_\omega X(\omega)P(\omega)=\sum_x xP(X=x)$$

这是期望的定义，其中前面是从每个基本事件考虑计算的，后面是把所有函数值相同的基本事件合并后计算的。

$$P((X|A)=x)=\dfrac{P(X=x,A)}{P(A)}$$

这是已知事件$A$发生的随机变量$X$等于某个值的概率。

$$E[E[X|Y]]=E[X]$$

这是全期望公式。$Y$是一个函数值不确定的随机变量，对于$Y$的每个值$y$都可以计算对应的$E[X|Y=y]$，因此$E[X|Y]$也是一个随机变量，所以这样写是没问题的。

以上内容参考资料：2013年信息学奥林匹克 中国国家队候选队员论文集 《浅析信息学竞赛中概率论的基础和应用》 胡渊鸣

期望$\texttt{DP}$中常设某个随机变量的期望然后进行递推，之所以这样做是对的是因为利用了全期望公式。

#### 收集邮票
https://www.luogu.com.cn/problem/P4550

定义几个离散随机变量，然后推式子即可。

设$X_i$为已经集齐$i$种邮票，全部集齐需要的次数。

$A_i$为已经集齐$i$种邮票，全部集齐需要的价格。

$\Omega=\{0,1\}$。表示这次有没有买到新邮票。

$Y_i$为这次有没有买到新邮票。也就是说$Y_i(\omega)=\omega$，其中$\omega\in\Omega$。

那么下面开始推式子：

$$E[X_i]=E[E[X_i|Y_i]]\\=E[X_i|Y_i=1]P(Y_i=1)+E[X_i|Y_i=0]P(Y_i=0)\\=E[X_{i+1}+1]P(Y_i=1)+E[X_i+1]P(Y_i=0)\\=(E[X_{i+1}]+1)P(Y_i=1)+(E[X_i]+1)P(Y_i=0)\\=E[X_{i+1}]P(Y_i=1)+E[X_i]P(Y_i=0)+1$$

$$E[X_i]P(Y_i=1)=E[X_{i+1}]P(Y_i=1)+1$$

$$P(Y_i=1)=\dfrac{n-i}{n}$$

$$E[X_i]=E[X_{i+1}]+\dfrac{1}{P(Y_i=1)}\\=E[X_{i+1}]+\dfrac{n}{n-i}$$

$$E[A_i]=E[E[A_i|Y_i]]\\=E[A_i|Y_i=1]P(Y_i=1)+E[A_i|Y_i=0]P(Y_i=0)\\=E[A_{i+1}+X_{i+1}+1]P(Y_i=1)+E[A_i+X_i+1]P(Y_i=0)$$

$$E[A_i]P(Y_i=1)=(E[A_{i+1}]+E[X_{i+1}])P(Y_i=1)+E[X_i]P(Y_i=0)+1$$

$$E[A_i]=E[A_{i+1}]+E[X_{i+1}]+\dfrac{P(Y_i=0)}{P(Y_i=1)}E[X_i]+\dfrac{1}{P(Y_i=1)}\\=E[A_{i+1}]+E[X_{i+1}]+\dfrac{i}{n-i}E[X_i]+\dfrac{n}{n-i}$$

推完式子，就可以直接递推了。

```cpp
#include<cstdio>

int n;
double f[10010], g[10010];

int main() {
    scanf("%d", &n);
    f[n] = g[n] = 0;
    for (int i = n - 1; i >= 0; i--) f[i] = f[i + 1] + (double)n / (n - i);
    for (int i = n - 1; i >= 0; i--) g[i] = (double)i / (n - i) * f[i] + g[i + 1] + f[i + 1] + (double)n / (n - i);
    printf("%.2lf\n", g[0]);
    return 0;
}
```

### 2020-08-19
#### [HNOI2015]亚瑟王
https://www.luogu.com.cn/problem/P3239

因为时间比较晚了，这题和下一题等到明天再写。

```cpp
#include<cstdio>
#include<cstring>

int t, n, r, d[250];
double p[250], f[250][150], g[250], pow[250][150], ans;

inline int min(int a, int b) { return a < b ? a : b; }

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &r);
        for (int i = 1; i <= n; i++) scanf("%lf%d", &p[i], &d[i]);
        memset(f, 0, sizeof f); memset(g, 0, sizeof g); memset(pow, 0, sizeof pow); ans = 0;
        for (int i = 1; i <= n; i++) pow[i][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= r; j++) pow[i][j] = pow[i][j - 1] * (1 - p[i]);
        f[1][0] = pow[1][r], f[1][1] = 1 - pow[1][r];
        for (int i = 2; i <= n; i++)
            for (int j = 0; j <= min(i, r); j++) {
                if (j > 0) f[i][j] += (1 - pow[i][r - j + 1]) * f[i - 1][j - 1];
                if (j < i) f[i][j] += pow[i][r - j] * f[i - 1][j];
            }
        g[1] = 1 - pow[1][r];
        for (int i = 2; i <= n; i++)
            for (int j = 0; j <= min(i - 1, r); j++) g[i] += (1 - pow[i][r - j]) * f[i - 1][j];
        for (int i = 1; i <= n; i++) ans += g[i] * d[i];
        printf("%.10lf\n", ans);
    }
    return 0;
}
```

#### [SDOI2006]线性方程组
https://www.luogu.com.cn/problem/P2455

```cpp
#include<cstdio>

const double eps = 1e-6;
int n, ok = 1;
double a[55][55];

inline void swap(double &a, double &b) { double t = a; a = b; b = t; }
inline double abs(double x) { return x > 0 ? x : -x; }
inline bool cmp(int s, int i, int j) {
    if (abs(a[i][s] - a[j][s]) < eps)
        for (int k = s + 1; k <= n; k++) {
            if (abs(a[i][k] - a[j][k]) < eps) continue;
            else return abs(a[i][k]) < abs(a[j][k]);
        }
    else return abs(a[i][s]) > abs(a[j][s]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++) scanf("%lf", &a[i][j]);
    for (int i = 1; i <= n; i++) {
        int maxi = i;
        for (int j = i + 1; j <= n; j++)
            if (cmp(i, j, maxi)) maxi = j;
        if (maxi ^ i) for (int j = i; j <= n + 1; j++) swap(a[maxi][j], a[i][j]);
        if (abs(a[i][i]) < eps) continue;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double d = a[j][i] / a[i][i];
            for (int k = i; k <= n + 1; k++) a[j][k] -= a[i][k] * d;
        }
    }
    for (int i = 1; i <= n; i++)
        if (abs(a[i][i]) < eps && abs(a[i][n + 1]) > eps) ok = -1;
    if (ok == 1) for (int i = 1; i <= n; i++)
        if (abs(a[i][i]) < eps && abs(a[i][n + 1]) < eps) ok = 0;
    if (ok == 1) for (int i = 1; i <= n; i++) printf("x%d=%.2lf\n", i, abs(a[i][n + 1] / a[i][i]) > eps ? a[i][n + 1] / a[i][i] : 0);
    else printf("%d\n", ok);
    return 0;
}
```

#### OSU!
https://www.luogu.com.cn/problem/P1654

推，就硬推。

$X_i$表示第$i$个位置的末尾极大连续全$1$子串长度

$\Omega=\{0,1\}$，表示第$i$位上是几。

$Y_i$表示第$i$位数字是几。

$A_i$就是要求的答案，即极大连续全$1$子串长度立方之和。

下面开始推式子。

$$E[A_i]=E[E[A_i|Y_i]]\\=E[A_i|Y_i=1]P(Y_i=1)+E[A_i|Y_i=0]P(Y_i=0)\\=E[A_{i-1}+(X_{i-1}+1)^3-X_{i-1}^3]P(Y_i=1)+E[A_{i-1}]P(Y_i=0)\\=E[A_{i-1}]P(Y_i=1)+E[3X_{i-1}^2+3X_{i-1}+1]P(Y_i=1)+E[A_{i-1}]P(Y_i=0)\\=E[A_{i-1}]+(3E[X_{i-1}^2]+3E[X_{i-1}]+1)P(Y_i=1)$$

$$E[X_i^2]=E[E[X_i^2|Y_i]]\\=E[X_i^2|Y_i=1]P(Y_i=1)+E[X_i^2|Y_i=0]P(Y_i=0)\\=E[(X_{i-1}+1)^2]P(Y_i=1)+0\\=E[X_{i-1}^2+2X_{i-1}+1]P(Y_i=1)\\=(E[X_{i-1}^2]+2E[X_{i-1}]+1)P(Y_i=1)$$

$$E[X_i]=E[E[X_i|Y_i]]\\=E[X_i|Y_i=1]P(Y_i=1)+E[X_i|Y_i=0]P(Y_i=0)\\=E[X_{i-1}+1]P(Y_i=1)+0\\=(E[X_{i-1}]+1)P(Y_i=1)$$

推完了式子，现在可以直接递推了。

```cpp
#include<cstdio>

int n;
double p[100100], ans[100100], x[100100], x2[100100];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
    for (int i = 1; i <= n; i++) {
        x[i] = (x[i - 1] + 1) * p[i];
        x2[i] = (x2[i - 1] + 2 * x[i - 1] + 1) * p[i];
        ans[i] = ans[i - 1] + (3 * x2[i - 1] + 3 * x[i - 1] + 1) * p[i];
    }
    printf("%.1lf\n", ans[n]);
    return 0;
}
```