// m log n in some cases.

vector<int> dijkstra(int s) {
    vector<int> d(n, inf);
    d[root] = 0;
    // объявим очередь с приоритетами для *минимума* (по умолчанию ищется максимум)
    using pair<int, int> Pair;
    priority_queue<Pair, vector<Pair>, greater<Pair>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [cur_d, v] = q.top();
        q.pop();
        if (cur_d > d[v])
            continue;
        for (auto [u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                q.push({d[u], u});
            }
        }
    }
}
