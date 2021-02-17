#include <bits/stdc++.h>

using namespace std;

struct node {
    int adj;
    int cost;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<node>> edges(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;
        edges[u].push_back(node{.adj = v, .cost = c});
        edges[v].push_back(node{.adj = u, .cost = c});
    }

    priority_queue<pair<int, int64_t>, vector<pair<int, int64_t>>,
                   greater<pair<int, int64_t>>>
        q;

    q.push({0, 0});
    vector<int64_t> best(n, numeric_limits<int64_t>::max());
    best[0] = 0;

    while (!q.empty()) {
        auto [cost_accum, id] = q.top();
        q.pop();
        for (auto const &neigh : edges[id]) {
            auto [adj_id, cost] = neigh;
            int64_t cost_new = static_cast<int64_t>(cost) - cost_accum;
            cost_new = max(cost_new, (int64_t)0);
            if (cost_new + cost_accum < best[adj_id]) {
                best[adj_id] = cost_new + cost_accum;
                q.push({cost_new + cost_accum, adj_id});
            }
        }
    }

    if (best[n - 1] == numeric_limits<int64_t>::max()) {
        cout << "NO PATH EXISTS" << endl;
    } else {
        cout << best[n - 1] << endl;
    }

    return 0;
}
