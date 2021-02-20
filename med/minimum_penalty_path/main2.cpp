#include <bits/stdc++.h>

using namespace std;

bool search(int n, int m, int a, int b, vector<vector<pair<int, int>>> &adj,
            int val) {

    vector<int> visited_node_cost(
        n, numeric_limits<int>::max()); // best cost for that node
    visited_node_cost[a] = 0;

    auto cmp = [](pair<int, int> const &aa, pair<int, int> const &bb) {
        return aa.second > bb.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(
        cmp);
    q.push({a, 0});

    while (!q.empty()) {
        auto [node, node_cost] = q.top();
        q.pop();
        assert(node_cost < val);
        for (auto [neigh, c] : adj[node]) {
            if (c < val) {
                int new_cost = node_cost | c;
                if (new_cost < visited_node_cost[neigh]) {
                    visited_node_cost[neigh] = new_cost;
                    q.push({neigh, new_cost});
                }
            }
        }
    }

    return visited_node_cost[b] != numeric_limits<int>::max();
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    cin >> a >> b; // start and end nodes
    a--;
    b--;

    // solve
    int ans = 0;
    for (int bit = 9; bit >= 0; --bit) {
        int val = 1 << bit;
        if (search(n, m, a, b, adj, val)) {
        } else {
            ans |= val;
        }
    }
    cout << "ans: " << ans << endl;
    if (ans == 0) {
        if (search(n, m, a, b, adj, 1 << 10)) {
            ans = 1023;
        } else {
            ans = -1;
        }
    }

    cout << ans << endl;

    return 0;
}
