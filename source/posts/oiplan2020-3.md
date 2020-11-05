������;����NOIP2020��̼ƻ���������(7.6~7.12)
2020-07-06
20200706
<!--more-->
���ռƻ������ܵ�ѧϰ�ص���ͼ��(���·��������������ͼ)��

��ʵ̰�ĺͶ��ָо�����һЩ����Ҫ����û���ü������Ժ��©��ȱʱ���ϡ�

### 2020-07-06
#### [USACO2.4]ţ������ Cow Tours
https://www.luogu.com.cn/problem/P1522

��$\texttt{Floyd}$����ڵ�����֮��ľ���󣬼���һ��Ԥ����

�������·������Ҫ��ȫͼ��һ��$\texttt{dfs}$Ⱦɫ�������ֲ�ͬ��ͨ�����Ľڵ㡣Ȼ��������$maxdis_x$��ʾ�Խڵ�$x$Ϊ�˵�����·������$maxdis$�Ļ����Ͽ������$diameter_x$��ʾ��$x$����ͨ������ֱ����Ȼ��ö�ٵ��$(i,j)$���������ͬһ��ͨ�����������·����·�����ͨ������ֱ��Ϊ$\max(maxdis_i+dist(i,j)+maxdis_j, diameter_{belong(i)}, diameter_{belong(j)})$����$ans$ȡ��Сֵ���ɡ�

��һ��д��ʱ��`belong[i] ^ belong[j]`д����`!g[i][j]`�������Ͳ�����ͬһ����ͨ������������û��ֱ�������ı��ˡ��ճ��ͼ�����

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>

int n, g[155][155], cnt, belong[155];
double dis[155][155], maxdis[155], diameter[155], ans = 1e9;
struct coordinate {
    int x, y;
}coordinates[155];

inline double min(double a, double b) { return a < b ? a : b; }
inline double max(double a, double b) { return a > b ? a : b; }
inline double dist(int i, int j) { return sqrt((double)(coordinates[i].x - coordinates[j].x) * (coordinates[i].x - coordinates[j].x)
                                        + (coordinates[i].y - coordinates[j].y) * (coordinates[i].y - coordinates[j].y)); }
void dfs(int x) {
    if (belong[x]) return;
    belong[x] = cnt;
    for (int j = 1; j <= n; j++)
        if (g[x][j]) dfs(j);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &coordinates[i].x, &coordinates[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) scanf("%1d", &g[i][j]);
    memset(dis, 0x7f, sizeof dis);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (g[i][j]) dis[i][j] = dis[j][i] = dist(i, j);
            else if (i == j) dis[i][j] = dis[j][i] = 0;
        }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for (int i = 1; i <= n; i++)
        if (!belong[i]) cnt++, dfs(i);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (belong[i] == belong[j]) maxdis[i] = max(maxdis[i], dis[i][j]);
    for (int i = 1; i <= n; i++) diameter[belong[i]] = max(diameter[belong[i]], maxdis[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (belong[i] ^ belong[j]) ans = min(ans, max(maxdis[i] + dist(i, j) + maxdis[j], max(diameter[belong[i]], diameter[belong[j]])));
    printf("%.6lf\n", ans);
    return 0;
}
```

#### �ٶ�����
https://www.luogu.com.cn/problem/P1266

�ֲ�ͼ���·���ڵ�$(x,v)$��ʾ�ڵ�$x$��·�ڣ����ٶ�Ϊ$v$��Ȼ��������ˡ�

��Ҫע�����·���ļ�¼�������ڵ����������ʾ�ģ���һ��д��ʱ��д��һά���ˡ�

�����ҵ���⣬�ֲ�ͼ���·�Ͷ�̬�滮���ƣ�ֻ�������������������޻�ͼ����״̬Ҫ��Ϊ���������ֲ�ͼ���·ֻ�������·��һ��״̬��

```cpp
#include<cstdio>
#include<queue>
#include<cstring>

const int MAXN = 155;
int n, m, d, greatv;
double ans = 1e9, dis[MAXN][510];
bool vis[MAXN][510];
struct edge { int to, next, v, l; };
struct graph {
    int ecnt, head[MAXN];
    edge edges[MAXN * MAXN];

    inline void addedge(int u, int to, int v, int l) {
        edges[++ecnt].to = to;
        edges[ecnt].v = v;
        edges[ecnt].l = l;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x, v;
    double dist;
    node(int xv, int vv, double dv): x(xv), v(vv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;
struct state {
    int x, v;
    state(int xv = 0, int vv = 0): x(xv), v(vv) {}
}from[MAXN][510];

inline void dijkstra() {
    q.push(node(1, 70, 0));
    memset(dis, 0x7f, sizeof dis);
    for (int i = 1; i <= 500; i++) dis[1][i] = 0;
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x][f.v]) continue;
        vis[f.x][f.v] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, v = g.edges[i].v ? g.edges[i].v : f.v, l = g.edges[i].l;
            if (dis[t][v] > dis[f.x][f.v] + (double)l / v) {
                dis[t][v] = dis[f.x][f.v] + (double)l / v;
                from[t][v] = state(f.x, f.v);
                q.push(node(t, v, dis[t][v]));
            }
        }
    }
}
void print(int x, int v) {
    if (!x) return;
    print(from[x][v].x, from[x][v].v);
    printf("%d ", x - 1);
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    d++;
    for (int i = 1; i <= m; i++) {
        int u, to, v, l;
        scanf("%d%d%d%d", &u, &to, &v, &l);
        g.addedge(u + 1, to + 1, v, l);
    }
    dijkstra();
    for (int i = 1; i <= 500; i++) {
        if (ans > dis[d][i]) {
            ans = dis[d][i];
            greatv = i;
        }
    }
    print(d, greatv);
    return 0;
}
```

### 2020-07-07
�ԴӸ������°�$\texttt{Windows10}$ϵͳ��ÿ����$\texttt{vscode}$���г���ʱ��������������̨��һ�����ҵĳ���һ���Ǳ��������ط��ˡ�ԭ������ʹ���˾ɰ����̨ģʽ(����һֱ������������������ǰû���������)���ĳ��°����̨ģʽ�󣬳���������ȫ�������������������Ѿ�����ˡ�����ȫ�ѿ��ˡ�

#### [GXOI/GZOI2019]������
https://www.luogu.com.cn/problem/P5304

��ָ����֮������·������ѵ㼯�ֳɼ���$A$�ͼ���$B$�����ӳ���Դ��$s$��$A$�е�ÿ���ڵ���һ����ȨΪ$0$�ıߣ���$B$�е�ÿ���ڵ��򳬼����$t$��һ����ȨΪ$0$�ıߣ���ô��$s$��$t$�����·������$A$��$B$��������Ե����·�����ԣ�����ܶ�ηָ�㼯������֤���������㶼��������ĳһ���б��ֵ�������ͬ�����У���ô�Ϳ����������ָ����֮������·��

���԰�ָ���㰴�ն����Ʒ��飬ö��ÿһλ������һλ��������ͬ�ķֵ�һ�������С�����������Ų�ͬ����ô��Ȼ������һλ��ͬ����������Ҫ�󡣶����Ʒ���ĸ��Ӷ���$O(logn)$���㷨�ܸ��Ӷ���$O(nlog^2n)$��

��Ϊ����߻�Ҫ�����ı�ɾ����������$\texttt{vector}$��ͼҪ������һЩ��

��Ҫע����ǣ���Ϊ������ͼ������Դ��ͻ��ֱ���ָ��������ʱҪ�������������һ�飬���������·��

Ȼ���ⲻ���������������������Ҫͨ����ŵ�������������Ϊ����ɵ���������������������˿��Ҳ����ȥ��������ϵ���δ�Ż������Ĵ��롣

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

const int MAXN = 100100;
int t, n, m, k, nodes[MAXN];
long long dis[MAXN], ans;
bool vis[MAXN];
struct edge {
    int to, w;
    edge(int tv, int wv): to(tv), w(wv) {}
};
struct graph {
    std::vector<edge> edges[MAXN];

    inline void addedge(int u, int v, int w) { edges[u].push_back(edge(v, w)); }
    inline void popedge(int x) { edges[x].pop_back(); }
    inline void clear() { for (int i = 1; i <= n; i++) edges[i].clear(); }
}g;
struct node {
    int x;
    long long dist;
    node(int xv, long long dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline long long min(long long a, long long b) { return a < b ? a : b; }
inline void dijkstra(int s) {
    q.push(node(s, 0));
    memset(dis, 0x3f, sizeof(long long) * (n + 3));
    dis[s] = 0;
    memset(vis, 0, sizeof(bool) * (n + 3));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = 0; i < (int)g.edges[f.x].size(); i++) {
            int &t = g.edges[f.x][i].to, w = g.edges[f.x][i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        ans = 0x3fffffffffffffff;
        g.clear();
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g.addedge(u, v, w);
        }
        for (int i = 1; i <= k; i++) scanf("%d", &nodes[i]);
        int a = 1;
        while (a <= n) {
            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.addedge(n + 1, nodes[i], 0);
                else g.addedge(nodes[i], n + 2, 0);
            }
            dijkstra(n + 1);
            ans = min(ans, dis[n + 2]);
            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.popedge(n + 1);
                else g.popedge(nodes[i]);
            }

            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.addedge(nodes[i], n + 1, 0);
                else g.addedge(n + 2, nodes[i], 0);
            }
            dijkstra(n + 2);
            ans = min(ans, dis[n + 1]);
            for (int i = 1; i <= k; i++) {
                if (nodes[i] & a) g.popedge(nodes[i]);
                else g.popedge(n + 2);
            }
            a <<= 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

### 2020-07-08
ԭ������̨����������������Ϊǰ����ɫ(���ַ���ɫ)�����ó���Ĭ�ϵĺ�ɫ���ͱ�����ȫ��ͬ���Կ���������Ĭ�����þ����ס�

#### Shortest path
http://acm.hdu.edu.cn/showproblem.php?pid=4479

���Ȩ�ϸ���������·���ѱ�Ȩ��С��������Ȼ�����μ��뵽ͼ�ж������˵�����ɳڲ�������Ϊ�ڴ�֮ǰ����ıߵı�Ȩ������С�����Կ��Ա�֤��������·���ı�Ȩ���ϸ�����ġ�

��Ҫע����ǣ����ڱ�Ȩ��ͬ�ıߣ���Ҫͬʱ���뵽ͼ�н����ɳڲ�����Ҳ���Ƕ࿪һ������������µ�$dis$��Ȼ��ѻ��������п��ܸı��ֵ���Ƶ�$dis$�С�

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

int t, n, m;
long long dis[10100], res[10100];
struct edge {
    int u, v, w;
    bool operator < (const edge &a) const { return w < a.w; }
}edges[50100];

inline long long min(long long a, long long b) { return a < b ? a : b; }

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(edges, 0, sizeof(edge) * (m + 2));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        std::sort(edges + 1, edges + m + 1);
        memset(dis, 0x3f, sizeof(long long) * (n + 1));
        dis[1] = 0;
        memset(res, 0x3f, sizeof(long long) * (n + 1));
        res[1] = 0;
        for (int i = 1; i <= m; ) {
            for (int j = i; j <= m; j++) {
                if (edges[j].w ^ edges[j + 1].w) {
                    for (int k = i; k <= j; k++) {
                        int u = edges[k].u, v = edges[k].v, w = edges[k].w;
                        res[u] = min(res[u], min(dis[u], dis[v] + w));
                        res[v] = min(res[v], min(dis[v], dis[u] + w));
                    }
                    for (int k = i; k <= j; k++) {
                        int u = edges[k].u, v = edges[k].v;
                        dis[u] = res[u];
                        dis[v] = res[v];
                    }
                    i = j + 1;
                    break;
                }
            }
        }
        if (dis[n] ^ 0x3f3f3f3f3f3f3f3f) printf("%lld\n", dis[n]);
        else printf("No answer\n");
    }
    return 0;
}
```

#### Buy a Ticket
https://codeforc.es/contest/938/problem/D

��ÿ���㵽�������·�����˶����յ��Ȩ����Сֵ���½�һ��������㣬��ÿ�����볬�����֮����һ����ȨΪ��Ȩ�ıߣ�����ÿ���㵽������Ĵ𰸾͵ȼ�������㵽��������·�����ӳ�����㷴���������·���ɡ�

ԭͼ�еıߵı�ȨҪ�˶���

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m;
long long dis[200100];
bool vis[200100];
struct edge { int to, next; long long w; };
struct graph {
    int ecnt, head[200100];
    edge edges[600100];

    inline void addedge(int u, int v, long long w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    long long dist;
    node(int xv, long long dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline void dijkstra() {
    memset(dis, 0x3f, sizeof(long long) * (n + 2));
    dis[n + 1] = 0;
    q.push(node(n + 1, 0));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to;
            long long w = g.edges[i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        g.addedge(u, v, w << 1), g.addedge(v, u, w << 1);
    }
    for (int i = 1; i <= n; i++) {
        long long w;
        scanf("%lld", &w);
        g.addedge(n + 1, i, w);
    }
    dijkstra();
    for (int i = 1; i <= n; i++) printf("%lld ", dis[i]);
    return 0;
}
```

�б�Ҫ�ܽ�һ�³���Դ��ͳ������ļ��ɣ�

����Դ�����ڶ�������������Ҫ����Ƕ������е�����һ����ָ�����·�������磬������㵽һ���յ�����·�����Խ�����Դ������������㣬Ȼ��𰸾��ǳ���Դ�㵽�յ�����·����һ�ַ����Ƿ��򽨱ߣ����յ㵽�����������·������Դ����Ա��ⷴ�򽨱ߣ���ʱ����������㷨ʱ���ܻ������һЩ(�����һ�����Ҳµ�)��ͬʱ���Բ���ö����㡣

����������ڶ���յ���������Ҫ�����һ����㵽����յ��е�����һ����·�������磬��һ����㵽����յ�����·�����Խ�����������������յ㣬Ȼ��𰸾�����㵽�����������·�����������Բ���ö���յ㡣

����Դ��ͳ��������䣬����������㵽����յ�������һ����Ե�·�������磬������㵽����յ�����·������������ö����������$\texttt{Dijkstra}$����ֻҪ������Դ��ͳ�������е�һ�����Ϳ��Բ����ܶ�����·��������������·��$O(n)$ö�١���ͬʱ������Դ��ͳ�����㣬����ö�٣��𰸾��ǳ���Դ�㵽�����������·��������Ϊ����Դ�����ʹ�㷨����ö����㣬����������ʹ�㷨����ö���յ㡣

�ο����ϣ�https://www.pianshen.com/article/2058609602/ �������ҵ������Ҫ�Ȳο�������д�ø����Щ��

### 2020-07-09
�������˻����û��������Ȼ���ȥ���Ļ����ˡ�

���·������������ѧ�ʱ��������Ҫ��ƻ��ӳ��ⷽ���ѧϰʱ�䡣Ȼ��������Ϊ��Ҫ�п��ˣ��о�Ҳ�ö�Ͷ��㾫�����Ļ����ϣ�����ͷ�۰���

### 2020-07-10
#### Jzzhu and Cities
https://codeforc.es/contest/449/problem/B

����о�Ҫ��ǰ���Ҫ��һЩ�������һ��ǻ��˺ܳ�ʱ��ŵ���������Ҫԭ�������ǰ��տμ��ϵ�����д�ģ�������������������˼�ˣ����տμ�������д����$\texttt{WA}$��

�μ��ϵ���˼��ĳ����·���б�Ҫ���䳤��һ��С��ֻ�õ�·�ߵ����·�������û��д����֮���������ֻ�õ�·��һ�����·����ö��ÿ����·�����ǲ����б�Ҫ���ڡ�Ȼ���һֱ$\texttt{WA}$��������������ж�������ͬһ�Խڵ����·����ö�ٵ���Ҫ����·��Ҫ���ɳڲ��������������ܻ��һЩ����Ҫ����·��Ϊ���б�Ҫ�ġ�һ�õ��ɳڲ�����ֻ�ɳ���һ����Ȼ���У���Χ�Ľڵ�����·����Ҳ����Ӱ�졣�����Ҿ��Լ��ĳɰѵ�·����·����һ�������·��Ȼ���ж�$\texttt1$�������ڵ�����·���м�������·����Ϊ$\texttt{cnt}$��������·��ͬʱ�����ɵ�·(����·һ��)��ɵ�·������ô���԰���$\texttt{cnt}$����·�������������Ҫ��һ����·�������$\texttt{cnt-1}$����·��

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m, k, s[100100], y[100100], ans, cnt[100100];
long long dis[100100];
bool vis[100100], rail[100100];
struct edge { int to, next, w; bool flag; };
struct graph {
    int ecnt, head[100100];
    edge edges[700100];

    inline void addedge(int u, int v, int w, bool flag) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].flag = flag;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    long long dist;
    node(int xv, long long dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline void dijkstra() {
    memset(dis, 0x3f, sizeof(long long) * (n + 1));
    dis[1] = 0;
    q.push(node(1, 0));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, w = g.edges[i].w;
            bool flag = g.edges[i].flag;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
                if (flag) cnt[t] = 1, rail[t] = true;
                else cnt[t] = 0, rail[t] = false;
            }
            else if (dis[t] == dis[f.x] + w) {
                if (flag) cnt[t]++;
                else rail[t] = false;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w, false), g.addedge(v, u, w, false);
    }
    for (int i = 1; i <= k; i++) scanf("%d%d", &s[i], &y[i]), g.addedge(1, s[i], y[i], true);
    dijkstra();
    for (int i = 1; i <= k; i++) {
        if (y[i] > dis[s[i]]) ans++;
        else if (y[i] == dis[s[i]] && cnt[s[i]] > (rail[s[i]] ? 1 : 0)) ans++, cnt[s[i]]--;
    }
    printf("%d\n", ans);
    return 0;
}
```

### 2020-07-11
#### [JSOI2010]���仮��
����$n$���㽨һ����ȫͼ��ͼ����С�������ϵ�$n-k+1$���ߵĳ��Ⱦ��Ǵ𰸡�

����ѡ��������ϲ�Ϊһ�����ϣ������������ľ��벻��ͼ�и�����֮����̵ľ��룬��ô�ϲ���Ĵ���Ȼ���䣬����Ҫʹ�����ÿ�ζ�Ҫ�ϲ�������������ϣ���˿���������ķ�����⡣

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

int n, k, ecnt;
struct tool {
    static inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
};
struct coordinate {
    int x, y;
}coordinates[1010];
struct edge {
    int u, v;
    double w;
    edge(int uv = 0, int vv = 0, double wv = 0): u(uv), v(vv), w(wv) {}
    bool operator < (const edge &a) const { return w < a.w; }
}edges[500100];
struct unionsetnode {
    int fa, size;
    unionsetnode(): size(1) {}
};
struct unionset {
    unionsetnode nodes[1010];
    inline void init() { 
        for (int i = 1; i <= n; i++) 
            nodes[i].fa = i; }
    int find(int x) {
        if (nodes[x].fa == x) return x;
        else return nodes[x].fa = find(nodes[x].fa);
    }
    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (nodes[x].size > nodes[y].size) tool::swap(x, y);
        nodes[x].fa = y;
        nodes[y].size += nodes[x].size;
    }
    inline bool same(int x, int y) { return find(x) == find(y); }
}uset;

inline double dist(int i, int j) { return sqrt((double)(coordinates[i].x - coordinates[j].x) * (coordinates[i].x - coordinates[j].x)
                                            + (coordinates[i].y - coordinates[j].y) * (coordinates[i].y - coordinates[j].y)); }
inline double kruskal() {
    std::sort(edges + 1, edges + ecnt + 1);
    int cnt = 0;
    for (int i = 1; i <= ecnt; i++) {
        int u = edges[i].u, v = edges[i].v;
        double w = edges[i].w;
        if (!uset.same(u, v)) {
            if (cnt == n - k) return w;
            cnt++;
            uset.merge(u, v);
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &k);
    uset.init();
    for (int i = 1; i <= n; i++) scanf("%d%d", &coordinates[i].x, &coordinates[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) edges[++ecnt] = edge(i, j, dist(i, j));
    printf("%.2lf\n", kruskal());
    return 0;
}
```

#### Greg and Graph
https://codeforc.es/contest/295/problem/B

������ֺ��ؽ����ⶼ��ࡣ���ǵ��Ŵ�����ôɾ��ͱ���˼ӵ㣬������$\texttt{Floyd}$�㷨����Ȼ�ش���

��Ҫע��������ۼӴ�ʱ����$\texttt{flag}$�����ʾ���Ƿ񱻼��룬��������㶼����������ô����֮���·���ſ������ȥ��

```cpp
#include<cstdio>

int n, dis[510][510], x[510];
long long ans[510];
bool flag[510];

struct tool {
    static inline int min(int a, int b) { return a < b ? a : b; }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &dis[i][j]);
            if (!dis[i][j] && i ^ j) dis[i][j] = 0x3fffffff;
        }
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    for (int k = n; k >= 1; k--) {
        flag[x[k]] = true;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) dis[i][j] = tool::min(dis[i][j], dis[i][x[k]] + dis[x[k]][j]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (flag[i] && flag[j] && dis[i][j] ^ 0x3fffffff) ans[k] += dis[i][j];
            }
    }
    for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    return 0;
}
```

#### ����λ��
https://www.luogu.com.cn/problem/P1491

�ζ�·ģ���⡣�������·��Ȼ��ö�ٰ����·�ϵ�ÿ��������ȥ����ͼ�����·���õ�����̵����·����ԭͼ�Ĵζ�·��

��Ϊ�ζ�·�����·��Ȼ������һ���߲���ͬ�����Խⷨ����ȷ�ġ�

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>

int n, m, backedge[210];
double dis[210], maxdis = 1e9, secmaxdis = 1e9;
bool vis[210];
struct coordinate {
    int x, y;
}coordinates[210];
struct edge { int to, next; double w; };
struct graph {
    int ecnt = 1, head[210];
    edge edges[40100];

    inline void addedge(int u, int v, double w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    double dist;
    node(int xv, double dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;

inline double dist(int i, int j) { return sqrt((double)(coordinates[i].x - coordinates[j].x) * (coordinates[i].x - coordinates[j].x)
                                                    + (coordinates[i].y - coordinates[j].y) * (coordinates[i].y - coordinates[j].y)); }
inline double dijkstra(int id) {
    q.push(node(1, 0));
    memset(dis, 0x7f, sizeof(double) * (n + 1));
    dis[1] = 0;
    memset(vis, 0, sizeof(bool) * (n + 1));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            if (i == id || i == (id ^ 1)) continue;
            int &t = g.edges[i].to;
            double w = g.edges[i].w;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                q.push(node(t, dis[t]));
                if (!id) backedge[t] = i ^ 1;
            }
        }
    }
    return dis[n];
}
void findway(int x) {
    if (x == 1) return;
    double d = dijkstra(backedge[x]);
    if (d <= maxdis) secmaxdis = maxdis, maxdis = d;
    else if (d < secmaxdis) secmaxdis = d;
    findway(g.edges[backedge[x]].to);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d%d", &coordinates[i].x, &coordinates[i].y);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addedge(u, v, dist(u, v)), g.addedge(v, u, dist(v, u));
    }
    maxdis = dijkstra(0);
    findway(n);
    if (secmaxdis < 1e9) printf("%.2lf\n", secmaxdis);
    else printf("-1\n");
    return 0;
}
```

### 2020-07-12
����$\texttt{Codeforces Round 655}$��
#### A. Omkar and Completion
http://codeforces.com/contest/655/problem/A

Ҫʹ�������������ĺͲ������������У���ô�����е�ÿ��������ȾͿ����ˡ�

```cpp
#include<cstdio>

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) printf("1 ");
        printf("\n");
    }
    return 0;
}
```

#### B. Omkar and Last Class of Math
http://codeforces.com/contest/655/problem/B

������$n$�ֳ���������$a,b$�ĺͣ�ʹ��$lcm(a,b)$��С����$n$Ϊż��ʱ����Ȼ���Խ����Ϊ����$\dfrac{n}{2}$��ʹ��$lcm$��С����$n$Ϊ����ʱ���ܵ�ż��������������������ҵ�$n$��һ������$d$����$n$��Ϊ$\dfrac{n}{d}$��$n-\dfrac{n}{d}$�����ߵ���$\dfrac{n(d-1)}{d}$��������ߵ�$lcm$����$\dfrac{n(d-1)}{d}$��Ҫʹ$\dfrac{n(d-1)}{d}$��С��$d$��Ҫ��С�������ҵ�С��$n$����С�����ӣ�������𰸼��ɡ����û���ҵ���˵��$n$��������������������Ž��ǰ�$n$��Ϊ$1$��$n-1$��

```cpp
#include<cstdio>

int t, n;

inline bool isprime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (!(x % i)) return false;
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (!(n % 2)) printf("%d %d\n", n / 2, n / 2);
        else if (isprime(n)) printf("%d %d\n", 1, n - 1);
        else for (int i = 3; i * i <= n; i++) {
            if (!(n % i)) {
                printf("%d %d\n", n / i, n / i * (i - 1));
                break;
            }
        }
    }
    return 0;
}
```

��ʱ������Ϊ��������ȶ�������һ���ύ�Ĵ������ⲻ��������$\texttt{Unrated}$�ˡ��ټ���$\texttt C$�������̫׼���������Ҿ�ȥ˯���ˡ�

#### [USACO08JAN]Telephone Lines S
https://www.luogu.com.cn/problem/P1948

������ʵ�����ֽⷨ��һ�־���ʮ����Ϥ�ķֲ�ͼ���·����Ȼ����·��Ҳ�ܹ���

��һ���Ƕ��ִ𰸣�����Ȩֵ���ıߵ�Ȩֵ����Ҫ��Ϊ$0$�ı�(��Ȩֵ��������)������ҲԽ��Խ�٣���ô�Ϳ��Զ����ˣ��ж�ʱ��Ȩֵ�������Ƶıߵ�Ȩֵ����$1$��С�ڵ��ڵĿ���$0$��Ȼ����һ�����·��������·С�ڵ���$k$��ô���С�

ֵ��һ����ǣ��������Ǳ�Ȩֻ��$0$��$1$�����·������������$\texttt{Dijkstra}$����Ҳ�����ø��Ӷȸ��ŵ�˫�˶���$\texttt{BFS}$����$\texttt{Dijkstra}$�У��ö����������չ�Ľڵ㣬Ŀ����ʹÿ��ȡ���ĵ���С������$\texttt{BFS}$�У�������ֻ�����ִ�С�����ִ�С�Ĳ�Ϊ$1$���Ҹ�������ͷ�ĸ�С�����ʶ���Ϊ�����㵥���ԡ�ʹ��˫�˶���ά���������չ���Ľڵ��С����Ϊ$0$(�������ı�ȨΪ$0$)����ô���԰��½ڵ���ڶ�ͷ�������С����Ϊ$1$���Ͱ��½ڵ���ڶ�β����Ȼ������Ȼ���㵥���ԣ�����ʡ���˶ѵ�һ��$log$�ͽ��ֲ�ͼ��$k$�����Ӷȸ��š�

�ڱ����У�ʹ��$Dijkstra$�����·���ܸ��Ӷ���$O(k(n+m)log(nk))$��ʹ��˫�˶���$\texttt{BFS}$���ܸ��Ӷ���$O((n+m)log\max l)$��

```cpp
#include<cstdio>
#include<cstring>
#include<queue>

int n, m, k, dis[1010];
bool vis[1010];
struct edge { int to, next, w; };
struct graph {
    int ecnt, head[1010];
    edge edges[20010];

    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x;
    node(int xv): x(xv) {}
};
std::deque<node> q;

int bfs(int mid) {
    q.push_back(node(1));
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    dis[1] = 0;
    memset(vis, 0, sizeof(bool) * (n + 1));
    while (!q.empty()) {
        node f = q.front();
        q.pop_front();
        if (vis[f.x]) continue;
        vis[f.x] = true;
        for (int i = g.head[f.x]; i; i = g.edges[i].next) {
            int &t = g.edges[i].to, w = g.edges[i].w > mid ? 1 : 0;
            if (dis[t] > dis[f.x] + w) {
                dis[t] = dis[f.x] + w;
                if (!w) q.push_front(node(t));
                else q.push_back(node(t));
            }
        }
    }
    return dis[n];
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w), g.addedge(v, u, w);
    }
    int l = 1, r = 1e6 + 1;
    while (l < r) {
        int mid = l + (r - l >> 1);
        if (bfs(mid) <= k) r = mid;
        else l = mid + 1;
    }
    if (bfs(l) <= k) printf("%d\n", l);
    else printf("-1\n");
    return 0;
}
```

#### [USACO11JAN]Roads and Planes G
https://www.luogu.com.cn/problem/P3008

����ߵı�Ȩ�Ǹ�������ߵı�Ȩ����Ϊ���������·��һ���ؼ������Ǳ�֤����ߵ������˵㲻�ܻ��ൽ���˵���ڰ��������ɵ���ͨ��������һ�����ͼ��һ�������޻�ͼ����˿��Զ�ÿ����ͨ������$\texttt{Dijkstra}$�����·������ͨ����֮�����������������·��

��������Ϊ���������Ϊ$0$����ͨ������ӣ�Ȼ��ÿ�ζԶ�ͷ����ͨ������$\texttt{Dijkstra}$�����·���Ȱ���ͨ���������еĵ����ѣ�Ȼ���$\texttt{Dijkstra}$��һ��ÿ��ȡ����С�ĵ㣬Ȼ��һ�����������ǰ����Ե���(��$dis$���ǳ�ʼ����ֵ)��ô�ſ��Զ�����������ɳڲ������������������ȨΪ���ı���ô�ͻ�ѵ���ĵ���£����´���𰸣��������ܵ���ĵ㿴�����Ե�������õ������·��ֵֻ�ȳ�ʼ����ֵСһ�㡣��������˵㲻��ͬһ��ͨ��������ô�Ͱѵ���ĵ����ڵ���ͨ��������ȼ�һ���ڼ���$0$ʱ������ӡ�

��һ��д��ʱ�����������ǰһ����$\texttt{DFS}$���������ᵼ��һ����ͨ�����ڱ�����ʱ���ڲ�������õ����·δ����ȫ���£����´���𰸣���Ϊ���ܴ�����δ������������Ҫ������ͨ����Ҳ���Ե�������㣬��·�����̡�����ԭ����״̬��ƵĲ�ͬ������ǰ��״̬��ÿ���㵽�յ�ľ��룬��������ÿ���㵽���ľ��룬��ʱ����������ǰ�ķ�ʽ����Ȼ�Ǵ���ġ�

�ĳ�$\texttt{BFS}��$�ڸտ�ʼ$\texttt{BFS}$ʱ�Ұ�$s$���ڵ���ͨ������ӣ��������������Ϊ$0$�ĵ���ӣ�����Ϊ��Щ�޷��������ͨ����������ӣ���Ϊ�𰸲����ܱ����£���ʵ�����������ӣ�һЩ�ü������û�м������ܶ���ͨ��������ȶ����ή��$0$�����´�����㶼�޷���������Ҫ���ֻ��$s$���ڵ���ͨ������ӣ���ô������һ�ַ�����������һ��$\texttt{DFS}$��������ܵ������ͨ������Ȼ���ڼ������ʱֻ����Щ����ǵĵ㣬��������Ȼû��һ��$\texttt{for}$ѭ�������������Ϊ$0$����ͨ����ʡ�¡�

���������Ϊ$0$�ĵ���Ӻ󣬴���һ���µ����������һ���޷�����ĵ�ͨ����Ȩ�߸������������ĳ���㣬�ͻᵼ�´���𰸣��������ܵ���ĵ㿴�������Ե����ˡ�����������ڽ����ɳڲ���ʱ�жϵ�ǰ��Ĵ��ǲ��ǳ�ʼ����ֵ���������ô�Ͳ��ý����ɳڲ����ˡ�

Ȼ���һ����ж��Ƿ���ͬһ���ϲ�����ȵĴ���д�����ɳڲ������棬����ֻ�н������ɳڲ����ı߲Ż��ж��Ƿ���ͬһ���ϣ�����һЩ�ü������û�м���һЩ���ܵ���ĵ��޷������ȷд����д�����棬���ɳڲ������С�

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>

const int MAXN = 25010;
int n, m, p, s, belong[MAXN], cnt, dis[MAXN], indeg[MAXN];
bool vis[MAXN];
struct edge { int to, next, w; };
struct graph {
    int ecnt, head[MAXN];
    edge edges[150100];

    inline void addedge(int u, int v, int w) {
        edges[++ecnt].to = v;
        edges[ecnt].w = w;
        edges[ecnt].next = head[u];
        head[u] = ecnt;
    }
}g;
struct node {
    int x, dist;
    node(int xv, int dv): x(xv), dist(dv) {}
    bool operator < (const node &a) const { return dist > a.dist; }
};
std::priority_queue<node> q;
std::vector<int> ccnodes[MAXN];
struct nodecc {
    int x;
    nodecc(int xv): x(xv) {}
};
std::queue<nodecc> qcc;

void dfs1(int x) {
    if (belong[x]) return;
    belong[x] = cnt;
    ccnodes[cnt].push_back(x);
    for (int i = g.head[x]; i; i = g.edges[i].next) {
        int &t = g.edges[i].to;
        dfs1(t);
    }
}
void bfs() {
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    dis[s] = 0;
    for (int i = 1; i <= cnt; i++)
        if (!indeg[i]) qcc.push(nodecc(i));
    while (!qcc.empty()) {
        nodecc fcc = qcc.front();
        qcc.pop();
        register int x = fcc.x;
        for (int i = 0; i < (int)ccnodes[x].size(); i++) q.push(node(ccnodes[x][i], dis[ccnodes[x][i]]));
        while (!q.empty()) {
            node f = q.top();
            q.pop();
            if (vis[f.x]) continue;
            vis[f.x] = true;
            for (int i = g.head[f.x]; i; i = g.edges[i].next) {
                int &t = g.edges[i].to, w = g.edges[i].w;
                if (dis[f.x] ^ 0x3f3f3f3f && dis[t] > dis[f.x] + w) {
                    dis[t] = dis[f.x] + w;
                    if (belong[f.x] == belong[t]) q.push(node(t, dis[t]));
                }
                if (belong[f.x] ^ belong[t]) {
                    indeg[belong[t]]--;
                    if (!indeg[belong[t]]) qcc.push(nodecc(belong[t]));
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &p, &s);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w), g.addedge(v, u, w);
    }
    for (int i = 1; i <= n; i++)
        if (!belong[i]) cnt++, dfs1(i);
    for (int i = 1; i <= p; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v, w);
        indeg[belong[v]]++;
    }
    bfs();
    for (int i = 1; i <= n; i++) {
        if (dis[i] ^ 0x3f3f3f3f) printf("%d\n", dis[i]);
        else printf("NO PATH\n");
    }
    return 0;
}
```

������ܺ���һֱ��ˢ���·��������û��ôˢ������ͼһ��ûѧ���Ժ���Э����ʱ��ɡ�