王道征途——NOIP2020冲刺计划·第⑨周(8.17~8.23)
2020-08-17
20200817
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

$$E[X_i]=E[E[X_i|Y_i]]\\\\=E[X_i|Y_i=1]P(Y_i=1)+E[X_i|Y_i=0]P(Y_i=0)\\\\=E[X_{i+1}+1]P(Y_i=1)+E[X_i+1]P(Y_i=0)\\\\=(E[X_{i+1}]+1)P(Y_i=1)+(E[X_i]+1)P(Y_i=0)\\\\=E[X_{i+1}]P(Y_i=1)+E[X_i]P(Y_i=0)+1$$

$$E[X_i]P(Y_i=1)=E[X_{i+1}]P(Y_i=1)+1$$

$$P(Y_i=1)=\dfrac{n-i}{n}$$

$$E[X_i]=E[X_{i+1}]+\dfrac{1}{P(Y_i=1)}\\\\=E[X_{i+1}]+\dfrac{n}{n-i}$$

$$E[A_i]=E[E[A_i|Y_i]]\\\\=E[A_i|Y_i=1]P(Y_i=1)+E[A_i|Y_i=0]P(Y_i=0)\\\\=E[A_{i+1}+X_{i+1}+1]P(Y_i=1)+E[A_i+X_i+1]P(Y_i=0)$$

$$E[A_i]P(Y_i=1)=(E[A_{i+1}]+E[X_{i+1}])P(Y_i=1)+E[X_i]P(Y_i=0)+1$$

$$E[A_i]=E[A_{i+1}]+E[X_{i+1}]+\dfrac{P(Y_i=0)}{P(Y_i=1)}E[X_i]+\dfrac{1}{P(Y_i=1)}\\\\=E[A_{i+1}]+E[X_{i+1}]+\dfrac{i}{n-i}E[X_i]+\dfrac{n}{n-i}$$

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

可以先算每个卡牌在$r$轮中发动过的概率$g[i]$，那么答案就是$\sum_{i=1}^n d[i]g[i]$。$g[i]$取决于每次发动的概率$p[i]$和有机会发动的次数，后者取决于这张卡牌前面有多少张卡牌在$r$轮中发动过。因此设$f[i][j]$表示前$i$张卡牌有恰好$j$张在$r$轮中发动过的概率，那么第$i$张卡牌可能发动也可能不发动，由全概率公式得$f[i][j]=(1-(1-p[i])^{r-j+1})f[i-1][j-1]+(1-p[i])^{r-j}f[i-1][j]$。边界条件是第$1$张卡牌发动和不发动的概率。枚举前$i-1$张有$j$张发动过，可以得出$g[i]=\sum_{j=1}^{\min(i-1,r)}(1-(1-p[i])^{r-j})f[i-1][j]$。

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

高斯消元中每次找到主元系数最大的行，这样是为了使精度损失最小。有可能出现找不到非零主元系数的情况，这样会判成无解，因为只考虑了主元的情况没有考虑其他未知数的情况，事实上有可能无解也有可能多解。解决方法是找行时不仅找主元系数最大的行，而且找主元系数相同时其他未知数系数尽量小的行。

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

$$E[A_i]=E[E[A_i|Y_i]]\\\\=E[A_i|Y_i=1]P(Y_i=1)+E[A_i|Y_i=0]P(Y_i=0)\\\\=E[A_{i-1}+(X_{i-1}+1)^3-X_{i-1}^3]P(Y_i=1)+E[A_{i-1}]P(Y_i=0)\\\\=E[A_{i-1}]P(Y_i=1)+E[3X_{i-1}^2+3X_{i-1}+1]P(Y_i=1)+E[A_{i-1}]P(Y_i=0)\\\\=E[A_{i-1}]+(3E[X_{i-1}^2]+3E[X_{i-1}]+1)P(Y_i=1)$$

$$E[X_i^2]=E[E[X_i^2|Y_i]]\\\\=E[X_i^2|Y_i=1]P(Y_i=1)+E[X_i^2|Y_i=0]P(Y_i=0)\\\\=E[(X_{i-1}+1)^2]P(Y_i=1)+0\\\\=E[X_{i-1}^2+2X_{i-1}+1]P(Y_i=1)\\\\=(E[X_{i-1}^2]+2E[X_{i-1}]+1)P(Y_i=1)$$

$$E[X_i]=E[E[X_i|Y_i]]\\\\=E[X_i|Y_i=1]P(Y_i=1)+E[X_i|Y_i=0]P(Y_i=0)\\\\=E[X_{i-1}+1]P(Y_i=1)+0\\\\=(E[X_{i-1}]+1)P(Y_i=1)$$

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

### 2020-08-22
#### Hankson 的趣味题
https://www.luogu.com.cn/problem/P1072

把这四个数分解质因数，然后枚举每个质因数，找到合法的指数取值区间，然后根据乘法原理把区间长度相乘即可。为了方便可以预处理小于$\sqrt{10^9}$的所有质数。

```cpp
#include<cstdio>
#include<cstring>

int n, a, b, c, d, prime[50010], pcnt, acnt[50010], bcnt[50010], ccnt[50010], dcnt[50010], cnt[50010];
bool isprime[50010];

inline void factorize(int x, int *cnt) {
    for (int i = 1; i <= pcnt && (x ^ 1); i++)
        while (!(x % prime[i])) cnt[i]++, x /= prime[i];
    if (x > 1) { prime[++pcnt] = x; cnt[pcnt] = 1; }
}
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    for (int i = 2; i * i <= 2e9; i++) isprime[i] = true;
    for (int i = 2; i * i <= 2e9; i++) {
        if (isprime[i]) prime[++pcnt] = i;
        for (int j = 1; j <= pcnt && (long long)i * prime[j] * i * prime[j] <= 2e9; j++) {
            isprime[i * prime[j]] = false;
            if (!(i % prime[j])) break;
        }
    }
    scanf("%d", &n);
    while (n--) {
        memset(acnt, 0, sizeof acnt); memset(bcnt, 0, sizeof bcnt); memset(ccnt, 0, sizeof ccnt); memset(dcnt, 0, sizeof dcnt);
        scanf("%d%d%d%d", &a, &b, &c, &d);
        factorize(a, acnt); factorize(b, bcnt); factorize(c, ccnt); factorize(d, dcnt);
        for (int i = 1; i <= pcnt; i++) {
            if (acnt[i] == bcnt[i] && ccnt[i] == dcnt[i]) cnt[i] = max(dcnt[i] - bcnt[i] + 1, 0);
            else if (acnt[i] > bcnt[i] && max(bcnt[i], ccnt[i]) == dcnt[i]) cnt[i] = 1;
            else if (ccnt[i] < dcnt[i] && min(dcnt[i], acnt[i]) == bcnt[i]) cnt[i] = 1;
            else cnt[i] = 0;
        }
        long long ans = 1;
        for (int i = 1; i <= pcnt; i++) ans *= cnt[i];
        printf("%lld\n", ans);
    }
    return 0;
}
```

#### 【模板】扩展欧拉定理
https://www.luogu.com.cn/problem/P5091

$$a^b\equiv\begin{cases}a^{b\bmod\varphi(m)}&a\perp m\\\\a^{b\bmod\varphi(m)+\varphi(m)}&b\ge\varphi(m)\\\\a^b&b<\varphi(m)\end{cases}\pmod m$$

公式的第一条实际上是欧拉定理的推论，即$a^{\varphi(m)}\equiv 1\pmod m(a\perp m)$，因为是$1$所以可以直接除掉，于是指数$b$就可以$\mod\varphi(m)$。

另外，这题$b$的范围很大，但用高精度又比较小题大做，可以边读入边模$\varphi(m)$，这样做的正确性在于$(a+b)\bmod m=a\bmod m+b\bmod m$，这也是$m$比$b$先给出的原因。

```cpp
#include<cstdio>

int a, m, phi;
long long b;
bool flag;

inline long long pow(long long x, long long k) {
    long long ans = 1;
    while (k) {
        if (k & 1) ans = ans * x % m;
        x = x * x % m;
        k >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d%d", &a, &m);
    int temp = m; phi = m;
    for (int i = 2; i * i <= m; i++) {
        if (!(temp % i)) {
            while (!(temp % i)) temp /= i;
            phi = phi / i * (i - 1);
        }
    }
    if (temp > 1) phi = phi / temp * (temp - 1);
    char c;
    while (c = getchar()) {
        if (c == ' ') continue;
        if (!('0' <= c && c <= '9')) break;
        b = b * 10 + c - '0';
        if (b >= phi) b %= phi, flag = true;
    }
    if (flag) printf("%lld\n", pow(a, b + phi));
    else printf("%lld\n", pow(a, b));
    return 0;
}
```

#### 上帝与集合的正确用法
https://www.luogu.com.cn/problem/P4139

求无限层的幂塔，可以用扩展欧拉定理，每递归一层都会把当前模数$m$取为$\varphi(m)$，递归$O(logp)$层后模数会变为$1$，这时直接返回$0$即可。原因是偶数的$\varphi$一定小于等于这个数一半，奇数的$\varphi$一定是偶数。因为是无限层的，所以每次都需要把指数加上当前模数的$\varphi$。

```cpp
#include<cstdio>

int t, prime[1000100], phi[10001000], pcnt;
bool isprime[10001000];

inline int max(int a, int b) { return a > b ? a : b; }
inline int pow(long long x, int k, int mod) {
    long long ans = 1;
    while (k) {
        if (k & 1) ans = ans * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return (int)ans;
}
inline int f(int p) {
    if (p == 1) return 0;
    return pow(2, f(phi[p]) + phi[p], p);
}

int main() {
    phi[1] = 1;
    for (int i = 2; i <= 10000000; i++) isprime[i] = true;
    for (int i = 2; i <= 10000000; i++) {
        if (isprime[i]) prime[++pcnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= pcnt && i * prime[j] <= 10000000; j++) {
            isprime[i * prime[j]] = false;
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
            if (!(i % prime[j])) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
        }
    }
    scanf("%d", &t);
    while (t--) {
        int p;
        scanf("%d", &p);
        printf("%d\n", f(p));
    }
    return 0;
}
```

#### 【模板】乘法逆元
https://www.luogu.com.cn/problem/P3811

设当前枚举到的数为$i$，$p=ki+r$，那么有：

$$ki+r\equiv0\pmod p$$

$$kr^{-1}+i^{-1}\equiv 0\pmod p$$

$$i^{-1}\equiv -kr^{-1}\pmod p$$

$$i^{-1}\equiv -\left\lfloor\dfrac{p}{i}\right\rfloor(p\bmod i)^{-1}$$

最后一行就是逆元的线性递推公式，可以直接背下来。

```cpp
#include<cstdio>

int n, p, inv[3000100];

int main() {
    scanf("%d%d", &n, &p);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = ((-(long long)(p / i) * inv[p % i]) % p + p) % p;
    for (int i = 1; i <= n; i++) printf("%d\n", inv[i]);
    return 0;
}
```

#### 【模板】乘法逆元2
https://www.luogu.com.cn/problem/P5431

因为幂函数是完全积性函数，所以可以求出来前缀积以及所有数的积的逆元，然后倒着推即可。

```cpp
#include<cstdio>

const int MAXN = 5000100;
int n, p, k, a[MAXN], mul[MAXN], mulinv[MAXN], ans, pow[MAXN];

inline void exgcd(register int a, register int b, register int &x, register int &y) {
    if (!b) { x = 1; y = 0; return; }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
inline int inv(register int a) { register int x, y; exgcd(a, p, x, y); return (x % p + p) % p; }
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

int main() {
    n = read(); p = read(); k = read();
    pow[1] = k;
    for (register int i = 2; i <= n; i++) pow[i] = (long long)pow[i - 1] * k % p;
    for (register int i = 1; i <= n; i++) a[i] = read();
    mul[0] = 1;
    for (register int i = 1; i <= n; i++) mul[i] = (long long)mul[i - 1] * a[i] % p;
    mulinv[n] = inv(mul[n]);
    for (register int i = n; i >= 1; i--) {
        if (i ^ n) mulinv[i] = (long long)mulinv[i + 1] * a[i + 1] % p;
        ans = (ans + ((long long)mulinv[i] * mul[i - 1] % p) * pow[i] % p) % p;
    }
    printf("%d\n", ans);
    return 0;
}
```

### 2020-08-23
#### 车的放置
https://www.luogu.com.cn/problem/P1350

这难得是我自己推出来式子的组合题。设$f(i,j,k)$表示长宽为$i,j$的矩形中放$k$个车的方案数，则$f(i,j,k)=\dbinom{i}{k}\dbinom{j}{k}k!$，可以理解为枚举哪些行和列被选择，方案数是$\dbinom{i}{k}\dbinom{j}{k}$，然后枚举哪些行和哪些列匹配，方案数是$k!$。

枚举左上部分的矩形放了几个车，于是答案就是

$$\sum_{i=0}^{\min(a,b,k)}f(a,b,i)f(a+c-i,d,k-i)$$

即

$$\sum_{i=0}^{\min(a,b,k)}\dbinom{a}{i}\dbinom{b}{i}i!\dbinom{a+c-i}{k-i}\dbinom{d}{k-i}(k-i)!$$

然后直接计算即可。注意组合数数组的范围，第一维可以到两千，而不是一千。

说不定我还可以出个增强版的题。

```cpp
#include<cstdio>

const int MOD = 1e5 + 3;
int a, b, c, d, k, cn[2010][1010], ans, fac[1010];

inline int min(int a, int b) { return a < b ? a : b; }

int main() {
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
    fac[0] = 1;
    for (int i = 1; i <= 1000; i++) fac[i] = (long long)fac[i - 1] * i % MOD;
    for (int i = 0; i <= 1000; i++) cn[i][0] = 1;
    for (int i = 1; i <= 2000; i++)
        for (int j = 1; j <= 1000; j++) cn[i][j] = (cn[i - 1][j - 1] + cn[i - 1][j]) % MOD;
    for (int i = 0; i <= min(min(a, b), k); i++)
        ans = (ans + ((long long)cn[a][i] * cn[b][i] * fac[i] % MOD * cn[a + c - i][k - i] * cn[d][k - i] % MOD * fac[k - i] % MOD)) % MOD;
    printf("%d\n", ans);
    return 0;
}
```

#### [六省联考2017]相逢是问候
https://www.luogu.com.cn/problem/P3747

考虑某个位置的值，在计算时最多只会递归$O(\log p)$层，当这$O(\log p)$层都被填充上$c$时，再进行修改操作已无意义，因为值不会再变化。于是可以像区间开方一样，修改时直接暴力修改，当区间内修改次数全都大于递归层数时直接退出。具体来说，每次根据当前位置修改的次数，利用扩展欧拉定理计算数值，但这题和之前的无限层幂塔不一样，这个是有限层的所以要判断指数是否大于模数的$\varphi$。方法是开一个全局变量，每次计算幂时若答案超过模数则置为`true`。复杂度$O(n\log^2 n\log p)$，会超时。

因为幂的底数相同，所以可以分块预处理每个模数下每个整块和块内的幂，因为模数不多只有$O(\log p)$级别所以开得下数组，$O(\sqrt{p}\log p)$预处理后可以$O(1)$求出$p$范围内的所有指数模某个模数的值。这种分块预处理后$O(1)$求出幂的做法称为光速幂。

因为还得再求幂时得出计算过程中是否大于当前模数，所以在预处理时就得求出来。另外还有个细节需要注意：当这次修改后修改次数恰好等于递归层数时，显然仍需要计算修改后的值，但求值时递归层数会比预处理的递归层数多一，因为还有个原来的值。当递归到最后一层时，模数为$0$，这样就会出错。需要特判返回$0$。

```cpp
#include<cstdio>
#include<cmath>

int n, m, p, c, cnt, phi[1010], pwr1[15010][1010], pwr2[15010][1010], block;
bool flag1[15010][1010], flag2[15010][1010];
struct segtreenode { int sum, cnt; };
struct segtree {
    int a[50010];
    bool flag;
    segtreenode nodes[200100];
    inline int lson(int x) { return x << 1; }
    inline int rson(int x) { return x << 1 | 1; }
    inline int min(int a, int b) { return a < b ? a : b; }
    inline void pushup(int x) {
        nodes[x].sum = (nodes[lson(x)].sum + nodes[rson(x)].sum) % p;
        nodes[x].cnt = min(nodes[lson(x)].cnt, nodes[rson(x)].cnt);
    }
    void build(int x, int l, int r) {
        if (l == r) {
            scanf("%d", &a[l]);
            nodes[x].sum = (a[l] %= p);
            return;
        }
        int mid = l + (r - l >> 1);
        build(lson(x), l, mid);
        build(rson(x), mid + 1, r);
        pushup(x);
    }
    inline int pwr(int k, int m) {
        if ((long long)pwr2[k / block][m] * pwr1[k % block][m] >= phi[m]) flag = true;
        if (flag2[k / block][m] || flag1[k % block][m]) flag = true;
        return (long long)pwr2[k / block][m] * pwr1[k % block][m] % phi[m];
    }
    int value(int k, int a, int x) {
        flag = false;
        if (x > cnt) {
            if (a >= 1) flag = true;
            return 0;
        }
        if (x == k) {
            if (a >= phi[x]) { flag = true; return a % phi[x]; }
            return a;
        }
        int b = value(k, a, x + 1);
        if (flag) b += phi[x + 1], flag = false;
        return pwr(b, x);
    }
    void modify(int x, int l, int r, int ql, int qr) {
        if (nodes[x].cnt == cnt + 1) return;
        if (l == r) {
            nodes[x].cnt++;
            nodes[x].sum = value(nodes[x].cnt, a[l], 0);
            return;
        }
        int mid = l + (r - l >> 1);
        if (ql <= mid) modify(lson(x), l, mid, ql, qr);
        if (mid + 1 <= qr) modify(rson(x), mid + 1, r, ql, qr);
        pushup(x);
    }
    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return nodes[x].sum;
        int mid = l + (r - l >> 1), ans = 0;
        if (ql <= mid) ans = query(lson(x), l, mid, ql, qr);
        if (mid + 1 <= qr) ans = ((long long)ans + query(rson(x), mid + 1, r, ql, qr)) % p;
        return ans;
    }
}segtree;

inline int getphi(int x) {
    int ans = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        while (!(x % i)) x /= i;
        ans = ans / i * (i - 1);
    }
    if (x > 1) ans = ans / x * (x - 1);
    return ans;
}
int f(int x, int id) {
    phi[id] = x;
    if (x == 1) return id;
    return f(getphi(x), id + 1);
}
inline void init() {
    block = (int)sqrt(p * 2);
    for (int m = 0; m <= cnt; m++) {
        int mod = phi[m];
        pwr1[0][m] = 1 % mod;
        if (1 >= mod) flag1[0][m] = true;
        for (int i = 1; i <= block; i++) {
            if ((long long)pwr1[i - 1][m] * c >= mod || flag1[i - 1][m]) flag1[i][m] = true;
            pwr1[i][m] = (long long)pwr1[i - 1][m] * c % mod;
        }
        pwr2[0][m] = 1 % mod;
        if (1 >= mod) flag2[0][m] = true;
        for (int i = 1; i <= block; i++) {
            if ((long long)pwr2[i - 1][m] * pwr1[block][m] >= mod || flag2[i - 1][m] || flag1[block][m]) flag2[i][m] = true;
            pwr2[i][m] = (long long)pwr2[i - 1][m] * pwr1[block][m] % mod;
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &p, &c);
    cnt = f(p, 0);
    init();
    segtree.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int opt, l, r;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 0) segtree.modify(1, 1, n, l, r);
        else if (opt == 1) printf("%d\n", segtree.query(1, 1, n, l, r));
    }
    return 0;
}
```

#### [六省联考2017]分手是祝愿
https://www.luogu.com.cn/problem/P3750

这题和上一题的标题是连在一起的，而且都与数学相关，所以我就一起做了。

考虑最优策略怎么做。因为每次修改只会影响到当前位置的左侧，所以可以倒着遍历，如果当前位置为$1$就翻转当前位置，否则无论如何都无法把所有数变为$0$。这和之前在牛客的比赛中做的题的思想类似。

因为期望值只和当前局面上必须操作的位置的数量有关，而与具体局面无关，所以可以以局面中必须操作的位置的数量为状态$\texttt{DP}$。设$dp[i]$表示当前有$i$个位置必须操作，要使所有位置为$0$的期望操作次数，则$dp[i]=\dfrac{i}{n}(dp[i-1]+1)+\dfrac{n-i}{n}(dp[i+1]+1)$，然后这样显然没法递推，需要高斯消元，但这样复杂度明显不对(据说因为这题的矩阵比较特殊所以可以$O(n)$消元，但是我不会)。

可以设$dp[i]$表示当前有$i$个位置必须操作，变为$i-1$个位置必须操作的期望次数，则$dp[i]=\dfrac{i}{n}+\dfrac{n-i}{n}(dp[i+1]+dp[i]+1)$，即$dp[i]=\dfrac{n-i}{i}(dp[i+1]+1)+1$，若$i\le k$则$dp[i]=i$，直接递推即可。

至于为什么要这样做，我也不知道，可能有时候把状态差分一下会比较好处理吧。

```cpp
#include<cstdio>
#include<vector>

const int MOD = 1e5 + 3;
int n, k, a[100100], cnt, dp[100100], fac = 1, ans;
std::vector<int> divisors[100100];

void exgcd(int a, int b, int &x, int &y) {
    if (!b) { x = 1; y = 0; return; }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
inline int inv(int a) { int x, y; exgcd(a, MOD, x, y); return (x % MOD + MOD) % MOD; }

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) fac = (long long)fac * i % MOD;
    for (int i = 1; i <= n; i++)
        for (int j = 1; i * j <= n; j++) divisors[i * j].push_back(i);
    for (int i = n; i >= 1; i--) {
        if (a[i]) {
            cnt++;
            for (int j = 0; j < (int)divisors[i].size(); j++) a[divisors[i][j]] ^= 1;
        }
    }
    dp[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (i <= k) dp[i] = 1;
        else dp[i] = ((long long)(dp[i + 1] + 1) * (n - i) % MOD * inv(i) % MOD + 1) % MOD;
    }
    for (int i = 1; i <= cnt; i++) ans = (ans + dp[i]) % MOD;
    printf("%d\n", (int)((long long)ans * fac % MOD));
    return 0;
}
```