#include <bits/stdc++.h>

using namespace std;

void find_cycle(vector<vector<int>> &adj, vector<int> &visited, int cur,
                set<int> &out_cycle_nodes) {
    // dfs while marking some node in each cycle

    if (visited[cur] == 1) {
        out_cycle_nodes.insert(cur);
    } else if (visited[cur] == 2) { // already done
        // pass
    } else {
        visited[cur] = 1; // in progress
        for (auto dest : adj[cur]) {
            find_cycle(adj, visited, dest, out_cycle_nodes);
        }
        visited[cur] = 2; // finished visiting children
    }
}

bool check_cycle_present(vector<vector<int>> &adj, vector<int> &visited,
                         set<int> &cycle_nodes, int cur) {

    if (visited[cur] == 0) {

        if (1 == cycle_nodes.count(cur)) {
            return true;
        }

        visited[cur] = 1;
        for (auto dest : adj[cur]) {
            if (check_cycle_present(adj, visited, cycle_nodes, dest)) {
                return true;
            }
        }
        visited[cur] = 2;
    }
    return false;
}

constexpr uint64_t M = 1'000'000'000;

int update_dp(vector<vector<int>> &adj, vector<int> &visited,
              set<int> &cycle_nodes, vector<int> &dp, int cur) {
    // travel from starting source node and explore and update dp
    if (cycle_nodes.count(cur) == 1) {
        return 0; // case of a cycle reachable from starting node 0, just set to
                  // 0
    } else {
        if (visited[cur] != 0) {
            return dp[cur];
        } else {
            int accum = 0;
            for (auto i :
                 adj[cur]) { // gather/reduce results from reachable children
                int ret = update_dp(adj, visited, cycle_nodes, dp, i);
                accum = (static_cast<uint64_t>(ret) +
                         static_cast<uint64_t>(accum)) %
                        M;
            }

            dp[cur] = accum;
            visited[cur] = 1;
            return dp[cur];
        }
    }
}

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> adj_rev(n);
    for (int i = 0; i < m; ++i) {
        int src, dst;
        cin >> src >> dst;
        src--;
        dst--;
        adj[src].push_back(dst);
        adj_rev[dst].push_back(src);
    }

    vector<int> visited(n, 0);
    set<int> out_cycle_nodes;

    find_cycle(adj, visited, 0, out_cycle_nodes);

    fill(visited.begin(), visited.end(), 0);
    bool cycle_present =
        check_cycle_present(adj_rev, visited, out_cycle_nodes, n - 1);

    if (cycle_present) {
        // cycle reacheable from start and to dest
        cout << "INFINITE PATHS" << endl;
    } else {

        // i -> number of paths from node i to node n-1
        vector<int> dp(n, 0);

        fill(visited.begin(), visited.end(), 0);

        dp[n - 1] = 1; // base case
        visited[n - 1] = 1;

        // one last search and update dp
        update_dp(adj, visited, out_cycle_nodes, dp, 0);

        cout << dp[0] << endl;
    }
    return 0;
}
