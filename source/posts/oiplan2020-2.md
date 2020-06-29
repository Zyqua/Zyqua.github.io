title: 王道征途——NOIP2020冲刺计划·第二周(6.29~7.5)
date: 2020-06-30
weight: 20200630
<!--more-->
按照计划，本周的学习重点依然是基础算法。

### 2020-06-29
#### [NOIP2015]销售员
https://www.luogu.com.cn/problem/P2672

这题很久以前写过，但有必要复习一下思路。

贪心，主要提供了另一种贪心的思路：在当前已有答案的基础上考虑新答案。至于在本题中为什么是正确的，似乎是用反证法但具体不会证，在考场上也没有必要证出来。

#### [NOIP2011]聪明的质监员
https://www.luogu.com.cn/problem/P1314

二分加前缀和。二分很有必要重新复习一遍，之前在$SDOI2020$写$D1T1$时本来要写权值线段树+二分，结果写完线段树发现几个月没学$OI$不会写二分了，最后丢了$60$分，绝了(当然主要还是因为我太菜了)。

以前写二分都是设当前区间为$[l,r]$，经常写错，今天看了某大佬整理的二分写法(https://www.zhihu.com/question/36132386 )，再重新总结一下。

二分的思路：当前区间为$[l,r)$，求出区间终点$\texttt{mid}$然后根据中点判断区间端点怎么移动。主要考虑这几个东西：
1. 搜索范围不为空，即循环条件为`l < r`；
2. 当前区间的左侧都要小于$v$；
3. 当前区间的右侧都要大于$v$。
4. 根据要求的值的位置，确定等于的条件放在$2$里面还是$3$里面。

默认序列是非降序列，若序列为下降序列，把$2$和$3$倒过来即可。

这样，二分的思路就十分清晰明了了。另外，某些题比如这题中要求的是最接近于$v$的数而不是大于等于$v$的最小的数，这种情况可以二分求出大于等于$v$的最小的数后，在$l$与$l-1$之间取舍。

再来看这题，很容易看出来检验值关于$w$是单调的，然后$w=0$时$y$最大，$w > maxw$时$y$最小，二分边界也就确定了。$y$的值可以用前缀和以$O(n+m)$复杂度求出。总复杂度$O((n+m)log\max\{w_i\})$。

还有就是，一定要仔细检查变量类型，第一次写完时很多地方忘了加$\texttt{long long}$。

相同难度下一写二分题就感觉这么得心应手，贪心题一直都对我很难啊。有时间还得继续加强练习。

```cpp
#include<cstdio>

const int MAXN = 200100;
int n, m, w[MAXN], v[MAXN], l[MAXN], r[MAXN], maxw;
long long s, wsum[MAXN], vsum[MAXN];

inline long long min(long long a, long long b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
inline long long abs(long long x) { return x > 0 ? x : -x; }
long long y(long long wx) {
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        wsum[i] = wsum[i - 1] + (w[i] >= wx ? 1 : 0);
        vsum[i] = vsum[i - 1] + (w[i] >= wx ? v[i] : 0);
    }
    for (int i = 1; i <= m; i++)
        ans += (wsum[r[i]] - wsum[l[i] - 1]) * (vsum[r[i]] - vsum[l[i] - 1]);
    return ans;
}

int main() {
    scanf("%d%d%lld", &n, &m, &s);
    for (int i = 1; i <= n; i++) scanf("%d%d", &w[i], &v[i]), maxw = max(maxw, w[i]);
    for (int i = 1; i <= m; i++) scanf("%d%d", &l[i], &r[i]);
    long long lx = 1, rx = maxw + 1;
    while (lx < rx) {
        long long mid = lx + (rx - lx) / 2;
        if (y(mid) <= s) rx = mid;
        else lx = mid + 1;
    }
    printf("%lld\n", min(abs(y(lx) - s), abs(y(lx - 1) - s)));
    return 0;
}
```