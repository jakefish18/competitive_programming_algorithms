//  n * n in all cases.

const int maxn = 1e5, inf = 1e9;
vector< pair<int, int> > g[maxn];
int n;

vector<int> dijkstra(int s) {
    vector<int> d(n, inf), a(n, 0);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        // находим вершину с минимальным d[v] из ещё не помеченных
        int v = -1;
        for (int u = 0; u < n; u++)
            if (!a[u] && (v == -1 || d[u] < d[v]))
                v = u;
        // помечаем её и проводим релаксации вдоль всех исходящих ребер
        a[v] = true;
        for (auto [u, w] : g[v])
            d[u] = min(d[u], d[v] + w);
    }
    return d;
}