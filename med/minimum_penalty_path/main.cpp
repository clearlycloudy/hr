#include <bits/stdc++.h>

using namespace std;

int search(int n, int m, int a, int b, vector<vector<pair<int, int>>> &adj,
           int val) {
    vector<vector<bool>> visited_nodes(n, vector<bool>(1024, false));
    visited_nodes[a][0] = true;
    deque<pair<int, int>> q{{a, 0}}; //(node, cost)
    bool feasible = false;

    while (!q.empty()) {
        auto [node, node_cost] = q.front();
        q.pop_front();
        assert(node_cost <= val);
        for (auto [neigh, edge_cost] : adj[node]) {
            int new_cost = node_cost | edge_cost;
            if (new_cost <= val && !visited_nodes[neigh][new_cost]) {
                if (b == neigh) {
                    feasible = true;
                    break;
                } else {
                    visited_nodes[neigh][new_cost] = true;
                    q.push_back({neigh, new_cost});
                }
            }
        }
    }
    return feasible;
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
        if (u == v) {
            continue;
        }
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
        assert(u != v);
    }
    cin >> a >> b; // start and end nodes
    a--;
    b--;

    // solve

    // bisection outer loop
    int l = 0;
    int r = 1024;
    while (l < r) {
        int mid = (l + r) / 2;
        if (search(n, m, a, b, adj, mid)) { // oracle for feasibility
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if (r == 1024) {
        cout << -1 << endl;
    } else {
        cout << r << endl;
    }
    return 0;
}
