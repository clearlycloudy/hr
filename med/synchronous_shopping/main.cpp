#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> stores(n, 0);

    // stores total cost
    vector<array<int, 1024>> dp(n, array<int, 1024>{});

    for (auto &i : dp) {
        i.fill(numeric_limits<int>::max());
    }

    deque<pair<int, int>> q; // starting point: (node, bought fish)

    for (int i = 0; i < n; ++i) { // per node
        int t;
        cin >> t;
        for (int j = 0; j < t; ++j) { // max 10 bits for each fish type
            int type;
            cin >> type;
            type--;
            stores[i] |= 1 << type; // bitmask
        }
        assert(stores[i] >= 0 && stores[i] <= 1023);
        if (i == 0) {
            dp[i][stores[i]] = 0;
            q.push_back({i, stores[i]}); // intialize queue with starting point
        }
    }
    vector<vector<int>> weights(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        weights[u][v] = w;
        weights[v][u] = w;
    }
    while (!q.empty()) {
        auto [node_id, bitpat] = q.front();
        q.pop_front();
        assert((stores[node_id] & bitpat) == stores[node_id]);
        assert(dp[node_id][bitpat] != numeric_limits<int>::max());

        // go to adjacent nodes and incur a cost on the associated edge
        for (auto neighbour_id : adj[node_id]) {
            int cost = dp[node_id][bitpat] + weights[neighbour_id][node_id];
            int pat_new = stores[neighbour_id] | bitpat;
            if (cost < dp[neighbour_id][pat_new]) {
                dp[neighbour_id][pat_new] = cost;
                q.push_back({neighbour_id, pat_new});
            }
        }
    }
    int ans = numeric_limits<int>::max();
    for (int i = 0; i < 1024; ++i) {
        for (int j = 0; j < 1024; ++j) {
            if ((i | j) == (1 << k) - 1) {
                if (dp[n - 1][i] != numeric_limits<int>::max() &&
                    dp[n - 1][j] != numeric_limits<int>::max()) {
                    ans = min(ans, max(dp[n - 1][i], dp[n - 1][j]));
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
