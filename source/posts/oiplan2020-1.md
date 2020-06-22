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