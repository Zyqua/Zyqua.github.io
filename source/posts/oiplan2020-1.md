title: 王道征途——NOIP2020冲刺计划·第一周(6.22~6.28)
date: 2020-06-22
weight: 20200622
<!--more-->
按照计划，本周的学习重点是基础算法。

### 2020-06-22
晚上做了一道搜索题，连同上周末做的一起写了。

#### [NOI1999]生日蛋糕
https://www.luogu.com.cn/problem/P1731

老题了，年龄比我还大。这题就普通$\texttt{DFS}$加五个剪枝。

1. 可行性剪枝：当前已用体积$v$大于$n$则直接退出。
2. 最优性剪枝：当前表面积$s$大于已知最优答案$ans$则直接退出。
3. 当前表面积$s$加上之后几层的最小表面积大于已知最优答案$ans$则直接退出。

要求之后几层的最小表面积，因为底面积已经固定所以只用求侧面积就好了。侧面积等于$2\pi rh$去掉共同的常数$\pi$也就是$2rh$，要使连续几层最小相当于求平方和$\sum_{i=1}^{m-x+1}2i^2$，其中$x$是目前处于的层数。根据平方和公式得出$\sum_{i=1}^{m-x+1}2i^2=\dfrac{(m-x+1)(m-x+2)(2m-2x+3)}{3}$。

4. 当前体积$v$加上之后几层的最大体积小于等于$n$则直接退出。

很简单不用讲。

5. `s + (n - v) * 2 / lstr > ans`则直接退出。

由侧面积公式$s=2rh$，体积公式$v=r^2h$得出$s=\dfrac{2v}{r}$。$n-v$是剩下可用的体积，$lstr$则是上一层的半径。$v$不变，要使$s$最小，$r$要最大，最大为$lstr-1$，当然我们让此层半径再大一点大到$lstr$也无伤大雅，所以如果当前侧面积$s$加上之后几层的最小侧面积(实际上无法达到)$\dfrac{2(n-v)}{lstr}$比当前最小答案大，则直接退出。

```cpp
#include<cstdio>

int n, m, ans = 0x3fffffff;

inline int min(int a, int b) { return a < b ? a : b; }
void dfs(int x, int lstr, int lsth, int s, int v) {
    if (x == m + 1) {
        if (v ^ n) return;
        ans = min(ans, s);
        return;
    }
    if (s >= ans || v >= n) return;
    if (s + (m - x + 1) * (m - x + 2) * (m * 2 - x * 2 + 3) / 3 >= ans) return;
    if (v + lstr * lstr * lsth * (m - x + 1) <= n) return;
    if (s + (n - v) * 2 / lstr > ans) return;
    for (int r = m - x + 1; r <= lstr - 1; r++)
        for (int h = m - x + 1; h <= lsth - 1; h++) {
            dfs(x + 1, r, h, s + 2 * r * h, v + r * r * h);
        }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int r = m; r * r * r <= n; r++)
        for (int h = m; r * r * h <= n; h++) dfs(2, r, h, r * r + 2 * r * h, r * r * h);
    if (ans ^ 0x3fffffff) printf("%d\n", ans);
    else printf("0\n");
    return 0;
}
```

#### [SCOI2009]生日快乐
https://www.luogu.com.cn/problem/P4160

洛谷的某些题解似乎有部分错误。根据我的理解，矩形的某条边长度为$a$，要把这个矩形平均分成$x$份，则分开的长度必须是$\dfrac{a}{x}$的倍数，并不是因为面积相等，而是因为要使切出的面积为$\dfrac{xy}{n}$，则切出的矩形的两边最小分别为$\dfrac{x}{n}$和$\dfrac{y}{n}$，而要使这块大矩形切出来的小矩形长宽最小能取到$\dfrac{x}{n}$和$\dfrac{y}{n}$，则大矩形的长宽必须为其倍数。

按照我的习惯，$\texttt{dfs}$函数中的$x$应当表示当前在切第几块矩形，但在这题中$x$表示当前矩形需要被分成几块。

然后这题就做完了。

```cpp
#include<cstdio>

int n;
double a, b, ans;

inline void swap(double &a, double &b) { double t = a; a = b; b = t; }
inline double min(double a, double b) { return a < b ? a : b; }
inline double max(double a, double b) { return a > b ? a : b; }
double dfs(int x, double ax, double bx) {
    if (x == 1) {
        if (ax < bx) swap(ax, bx);
        return ax / bx;
    }
    double ans = 0x3fffffff;
    for (double i = ax / x; i < ax; i += ax / x)
        ans = min(ans, max(dfs(i / (ax / x), i, bx), dfs(x - i / (ax / x), ax - i, bx)));
    for (double i = bx / x; i < bx; i += bx / x)
        ans = min(ans, max(dfs(i / (bx / x), ax, i), dfs(x - i / (bx / x), ax, bx - i)));
    return ans;
}

int main() {
    scanf("%lf%lf%d", &a, &b, &n);
    printf("%.6lf\n", dfs(n, a, b));
    return 0;
}
```

### 2020-06-23
#### [NOIP2009]靶形数独
https://www.luogu.com.cn/problem/P1074

这题就是普通的$\texttt{DFS}$加合适的搜索顺序。根据经验，做数独时从空位少的部分开始入手会比较简单。搜索时同样如此，先从空位最少的一行开始搜，会减少搜索的次数，从而提高效率(至于具体证明，不会证)。

然而就算这样写也会$\texttt{TLE}$。于是我自作聪明地把找出空位最少的一行改成了找出相关(即在同一行，或同一列，或同一九宫格)空位最少的一个点，耗时反而更多了。最后直接吸氧过了。

刚写完时没写$\texttt{dfs}$函数中的$\texttt{break}$语句。这样会大大增多无用搜索的次数，导致直接超时。

另外，即使在开始搜索前就判出了相互冲突的情况，但搜索时仍可能存在无解的情况。当`ans == 0`时，即表示无解，直接输出`-1`即可。

```cpp
#include<cstdio>

int a[10][10], cnt, cnt0[10], ans;
bool vis1[10][10], vis2[10][10], vis3[10][10], ok = true;

inline int belong(int x, int y) { return (x / 3 + (x % 3 ? 1 : 0) - 1) * 3 + (y / 3 + (y % 3 ? 1 : 0)); }
inline int score(int x, int y) {
    if (x == 1 || x == 9 || y == 1 || y == 9) return a[x][y] * 6;
    else if (x == 2 || x == 8 || y == 2 || y == 8) return a[x][y] * 7;
    else if (x == 3 || x == 7 || y == 3 || y == 7) return a[x][y] * 8;
    else if (x == 4 || x == 6 || y == 4 || y == 6) return a[x][y] * 9;
    else return a[x][y] * 10;
}
inline int max(int a, int b) { return a > b ? a : b; }
void dfs(int cnt, int scr) {
    if (cnt == 81) {
        ans = max(ans, scr);
        return;
    }
    int x = 0, mincnt0 = 0x3fffffff;
    for (int i = 1; i <= 9; i++)
        if (cnt0[i] < mincnt0 && cnt0[i]) {
            mincnt0 = cnt0[i];
            x = i;
        }
    for (int j = 1; j <= 9; j++)
        if (!a[x][j]) {
            for (int k = 1; k <= 9; k++) {
                if (vis1[x][k] || vis2[j][k] || vis3[belong(x, j)][k]) continue;
                a[x][j] = k, vis1[x][k] = vis2[j][k] = vis3[belong(x, j)][k] = true, cnt0[x]--;
                dfs(cnt + 1, scr + score(x, j));
                a[x][j] = 0, vis1[x][k] = vis2[j][k] = vis3[belong(x, j)][k] = false, cnt0[x]++;
            }
            break;
        }
}

int main() {
    for (int i = 1; i <= 9 && ok; i++)
        for (int j = 1; j <= 9 && ok; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] && (vis1[i][a[i][j]] || vis2[j][a[i][j]] || vis3[belong(i, j)][a[i][j]])) ok = false;
            if (a[i][j]) vis1[i][a[i][j]] = vis2[j][a[i][j]] = vis3[belong(i, j)][a[i][j]] = true;
            if (a[i][j]) cnt++;
            else cnt0[i]++;
        }
    if (!ok) printf("-1\n");
    else {
        int scr = 0;
        for (int i = 1; i <= 9; i++)
            for (int j = 1; j <= 9; j++)
                if (a[i][j]) scr += score(i, j);
        dfs(cnt, scr);
        if (ans) printf("%d\n", ans);
        else printf("-1\n");
    }
    return 0;
}
```

#### 魔板
https://www.luogu.com.cn/problem/P1275

这题好像和搜索没什么关系(我是根据$\texttt{luogu}$的算法标签找题的)，反正我直接套几层$\texttt{for}$循环就完事了。

因为列之间可以互相交换位置，所以只需要保证每一列都能有另外一列与之对应即可。因为反转一整行的状态会影响到每一列，所以每一列被反转所受的影响都是相同的。要使两块魔板上每一列都有另一块魔板上的一列与之对应，必然有某两列在经过某几行的反转后是对应的(好像是废话)，因此枚举魔板$A$的第一列和魔板$B$的第$j$列对应，则每一行是否反转就确定了。然后将魔板$B$的其他列进行同样的反转后，直接$O(nm^2)$枚举每列是否有对应的列即可，总复杂度$O(nm^3)$。

```cpp
#include<cstdio>
#include<cstring>

int k, n, m, a[110][110], b[110][110], delta[110];
bool visa[110], visb[110];

inline bool check(int i, int j) {
    for (int k = 1; k <= n; k++)
        if (a[k][i] ^ (b[k][j] ^ delta[k])) return false;
    return true;
}

int main() {
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) scanf("%d", &b[i][j]);
        bool ok = false;
        for (int j = 1; j <= m; j++) {
            memset(visa, 0, sizeof visa), memset(visb, 0, sizeof visb);
            visa[1] = visb[j] = true;
            for (int i = 1; i <= n; i++) delta[i] = a[i][1] ^ b[i][j];
            bool ok1 = true;
            for (int k = 2; k <= m; k++) {
                if (visa[k]) continue;
                bool ok2 = false;
                for (int l = 1; l <= m; l++) {
                    if (visb[l]) continue;
                    if (check(k, l)) { visa[k] = visb[l] = true; ok2 = true; break; }
                }
                ok1 = ok1 && ok2;
            }
            if (ok1) { ok = true; break; }
        }
        if (ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

### 2020-06-24
今天应该学分治。不过分治好像没有值得专门复习的地方，和递归一样是比较散的知识点，所以就直接去学贪心了。

#### [NOIP2012]国王游戏
https://www.luogu.com.cn/problem/P1080

设目前考虑的两个大臣分别是$i$和$j$且$i+1=j$，$m=\prod_{k=0}^{i-1}a_k$，则两人的奖赏分别为$\dfrac{m}{b_i}$和$\dfrac{ma_i}{b_j}$。交换两人的位置后，两人的奖赏分别为$\dfrac{ma_j}{b_i}$和$\dfrac{m}{b_j}$。邻项交换排序的思路是，若交换前的答案比交换后的答案更优，则不需要交换。

交换前的答案优于交换后的答案，也就是$\max\left(\dfrac{m}{b_i},\dfrac{ma_i}{b_j}\right)<\max\left(\dfrac{ma_j}{b_i},\dfrac{m}{b_j}\right)$。化简后可以得到$\max(b_j,a_ib_i)<\max(a_jb_j,b_i)$。在满足这个条件时不需要交换，即返回$\texttt{true}$(因为快排是按照从小到大的顺序排的，$\texttt{true}$即表示$i<j$，也就是无需交换)。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

int n, l[10010], r[10010], a[10010], mul[10010], ans;

void swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}
int max(int a, int b) { return a > b ? a : b; }
bool cmp(int a, int b) { return l[a] * r[a] < l[b] * r[b]; }

int main() {
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) scanf("%d%d", &l[i], &r[i]), a[i] = i;
	sort(a + 1, a + n + 1, cmp);
	mul[0] = l[0];
	for (int i = 1; i <= n; i++) mul[i] = mul[i - 1] * l[a[i]];
	for (int i = 1; i <= n; i++) ans = max(ans, mul[i - 1] / r[a[i]]);
	printf("%d\n", ans);
	return 0;
}
```

### 2020-06-25
~~太困了直接从晚上7点多睡到第二天4点半，第二天早晨补回来的~~

#### 液体滴落
https://www.luogu.com.cn/problem/P1766

这次是从luogu的题单里找的题，但是这题好像和贪心也没什么关系。

会求一次函数解析式就行了($k=\dfrac{y_1-y_2}{x_1-x_2}$,$b=y_1-kx_1$)。唯一要注意的是精度问题，线段的端点纵坐标要存下来，不要用解析式算。

```cpp
#include<cstdio>

int n, sx, sy, lx[10010], rx[10010], ly[10010], ry[10010];
double k[10010], b[10010];
const double eps = 1e-6;

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    scanf("%d%d", &n, &sx);
    sy = 0x3fffffff;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 < x2) lx[i] = x1, ly[i] = y1, rx[i] = x2, ry[i] = y2;
        else lx[i] = x2, ly[i] = y2, rx[i] = x1, ry[i] = y1;
        k[i] = (double)(y1 - y2) / (x1 - x2), b[i] = y1 - k[i] * x1;
    }
    for (; ; ){
        int maxi = 0;
        double maxy = -0x3fffffff;
        for (int i = 1; i <= n; i++) {
            if (sx <= lx[i] || rx[i] <= sx) continue;
            double y = k[i] * sx + b[i];
            if (maxy < y && y <= sy) {
                maxy = y;
                maxi = i;
            }
        }
        if (!maxi) break;
        if (k[maxi] > 0) sx = lx[maxi], sy = ly[maxi];
        else sx = rx[maxi], sy = ry[maxi];
    }
    printf("%d\n", sx);
    return 0;
}
```

### 2020-06-26
#### 正妹吃月饼
https://www.luogu.com.cn/problem/P2431

贪心，因为吃大的不如把所有比它小的都吃掉更优，所以以$a$对应的方案为初始方案从小到大枚举月饼，如果没吃过且能吃则吃掉。

用二进制写会方便一些。

```cpp
#include<cstdio>

int ans;
long long a, b;

int main() {
    scanf("%lld%lld", &a, &b);
    for (long long c = 1; c <= b; c <<= 1)
        if (!(a & c) && (a | c) <= b) a |= c;
    for (long long c = 1; c <= a; c <<= 1)
        if (a & c) ans++;
    printf("%d\n", ans);
    return 0;
}
```
#### 魔法
https://www.luogu.com.cn/problem/P3619

~~天若有情天亦老，我为长者续一秒~~

贪心，先把$b$大于等于$0$的任务按照$t$从小到大的顺序完成，剩下$b$小于$0$的，再次使用邻项交换法：若在完成任务$i$后还可以完成任务$j$($i+1=j$)，而完成任务$j$后不能完成任务$i$，则当前顺序更优，不需要交换。相当于$\begin{cases}t+b_i>t_j\\\\t+b_j<t_i\end{cases}$，也就是$t_j-b_i<t_i-b_j$。

注意判完成任务后$t$不能小于等于$0$。

```cpp
#include<cstdio>
#include<algorithm>

int z, n, t, ans;
struct task {
    int t, b;
    bool operator < (const task &a) const {
        if (b >= 0 || a.b >= 0) return t < a.t;
        else return a.t - b < t - a.b;
    }
}tasks[100100];

int main() {
    scanf("%d", &z);
    while (z--) {
        scanf("%d%d", &n, &t);
        ans = 0;
        for (int i = 1; i <= n; i++) scanf("%d%d", &tasks[i].t, &tasks[i].b);
        std::sort(tasks + 1, tasks + n + 1);
        for (int i = 1; i <= n; i++)
            if (t > tasks[i].t && t + tasks[i].b > 0) t += tasks[i].b, ans++;
        if (ans == n) printf("+1s\n");
        else printf("-1s\n");
    }
    return 0;
}
```

#### 修改
https://www.luogu.com.cn/problem/P6155

从小到大枚举当前处理到的$a_{cur}$修改若干次后最小是几。处理时间更晚的在乘$b_i$时的权值会更小，所以用栈存放待分配数值的$a_{cur}$，将当前值$i$分配给栈顶的元素。

获取栈顶元素时，一定要确保栈不是空的。

```cpp
#include<cstdio>
#include<algorithm>
#include<stack>

const int MAXN = 1000100;
unsigned long long ans;
int n, a[MAXN], b[MAXN], cnt[MAXN], cur;
std::stack<int> stk;

inline int read() {
    register int ans = 0;
    register char c = getchar();
    while (c == ' ' || c == '\n' || c == '\r') c = getchar();
    while ('0' <= c && c <= '9') {
        ans = (ans << 3) + (ans << 1) + c - '0';
        c = getchar();
    }
    return ans;
}
bool cmp(int a, int b) { return a > b; }

int main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    std::sort(a + 1, a + n + 1);
    cur = 1;
    for (int i = 1; cur <= n || !stk.empty(); i++) {
        if (stk.empty()) i = a[cur];
        while (a[cur] == i) stk.push(cur++);
        cnt[stk.top()] = i - a[stk.top()];
        stk.pop();
    }
    std::sort(b + 1, b + n + 1);
    std::sort(cnt + 1, cnt + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        ans += (unsigned long long)cnt[i] * b[i];
    printf("%llu\n", ans);
    return 0;
}
```

#### 序列排序
https://www.luogu.com.cn/problem/P2127

把序列排序后，从原序列的元素到排序后此元素上的元素连一条有向边，就得到了一张由若干个简单环组成的有向图。对于一个环，环内调整最优的方案是用环内最小的元素来和其他所有元素换一遍，另一种可能的最优方案是把全图的最小元素和环内最小元素交换，然后用换来的最小元素和环内其他元素调整一遍，然后再换回去。前者的代价是$\sum_{1\le x\le n,x\not=minx}(w_x+w_{minx})$即$\sum_{1\le x\le n}w_x+(n-2)w_{minx}$，后者的代价是$\sum_{1\le x\le n,x\not=minx}(w_x+w_{whminx})+2\times(w_{minx}+w_{whminx})$即$\sum_{1\le x\le n}w_x+(n+1)w_{whminx}+w_{minx}$，对于每个环对两者取$\min$，然后相加即为答案。

注意开$\texttt{long long}$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

const int MAXN = 100100;
int n, a[MAXN], b[MAXN], whminw, minw[MAXN], num[MAXN], scccnt;
long long sumw[MAXN], ans;
bool vis[MAXN];
struct edge { int to, next; };
struct graph {
    int ecnt, head[MAXN], w[MAXN];
    edge edges[MAXN];

    inline void addedge(int u, int v) {
        edges[++ecnt].to = v;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;

inline long long min(long long a, long long b) { return a < b ? a : b; }
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    minw[scccnt] = min(minw[scccnt], g.w[x]);
    num[scccnt]++;
    sumw[scccnt] += g.w[x];
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        int &t = g.edges[i].to;
        dfs(t);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
    for (int i = 1; i <= n; i++) g.addedge(a[i], a[a[i]]), g.w[a[i]] = b[a[i]];
    memset(minw, 0x3f, sizeof minw);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) scccnt++, dfs(i);
    whminw = b[1];
    for (int i = 1; i <= scccnt; i++)
        ans += min((long long)sumw[i] + (long long)(num[i] - 2) * minw[i], (long long)sumw[i] + (long long)(num[i] + 1) * whminw + minw[i]);
    printf("%lld\n", ans);
    return 0;
}
```