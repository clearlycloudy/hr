#include <bits/stdc++.h>

using namespace std;

// edge
struct E {
    int from;
    int to;
    int cap;
    int rev;
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin >> n >> t;

    int source = n + t;
    int sink = n + t + 1;
    int nodes_total = n + t + 2;

    vector<int> skills(n, 0);
    for (auto &i : skills) {
        cin >> i;
    }
    vector<vector<int>> adj(nodes_total); // node -> edge id in es
    int e_id = 0;
    vector<E> es; // edges

    // connect source and sink to skill nodes
    for (int i = 0; i < skills.size(); ++i) {

        adj[source].push_back(e_id);
        adj[i].push_back(e_id + 1);
        es.push_back(
            E{.from = source, .to = i, .cap = skills[i], .rev = e_id + 1});
        es.push_back(E{.from = i, .to = source, .cap = 0, .rev = e_id});
        e_id += 2;

        adj[i].push_back(e_id);
        adj[sink].push_back(e_id + 1);
        es.push_back(E{.from = i, .to = sink, .cap = 1, .rev = e_id + 1});
        es.push_back(E{.from = sink, .to = i, .cap = 0, .rev = e_id});
        e_id += 2;
    }

    // process trainer nodes
    for (int i = 0; i < t; ++i) {
        int l;
        cin >> l;
        vector<int> from(l, 0);
        for (auto &j : from) {
            cin >> j;
            j--;
        }
        cin >> l;
        vector<int> to(l, 0);
        for (auto &j : to) {
            cin >> j;
            j--;
        }
        // connect trainer nodes to other skill nodes
        for (auto j : from) {

            adj[j].push_back(e_id);
            adj[n + i].push_back(e_id + 1);
            es.push_back(E{.from = j, .to = n + i, .cap = 1, .rev = e_id + 1});
            es.push_back(E{.from = n + i, .to = j, .cap = 0, .rev = e_id});
            e_id += 2;
        }
        for (auto j : to) {

            adj[n + i].push_back(e_id);
            adj[j].push_back(e_id + 1);
            es.push_back(E{.from = n + i, .to = j, .cap = 1, .rev = e_id + 1});
            es.push_back(E{.from = j, .to = n + i, .cap = 0, .rev = e_id});
            e_id += 2;
        }
    }

    assert(e_id == es.size());

    vector<int> node_levels(nodes_total);

    int ans = 0;

    while (true) {

        // construct level graph from residual graph
        fill(node_levels.begin(), node_levels.end(), -1);

        node_levels[source] = 0;

        deque<int> q{source};
        while (q.size() > 0) {
            auto idx = q.front();
            q.pop_front();
            for (auto edge_id : adj[idx]) {
                auto edge = es[edge_id];
                assert(edge.from == idx);
                int neighbour = edge.to;
                int residual = edge.cap;

                if ((residual > 0) && (node_levels[neighbour] == -1)) {
                    node_levels[neighbour] = node_levels[idx] + 1;
                    q.push_back(neighbour);
                }
            }
        }

        if (node_levels[sink] == -1) {
            break;
        }

        // avoid searching repeatedly for adjacent edges to a node
        vector<int> idx_edge_start(nodes_total, 0);

        // find an augmenting path
        auto dfs_search = [&](int cur, int par, int fwd_flow, auto f) -> int {
            if (cur == sink || fwd_flow == 0) {
                return fwd_flow;
            }
            for (int &index = idx_edge_start[cur]; index < adj[cur].size();
                 ++index) {

                int edge_id = adj[cur][index];
                auto &edge = es[edge_id];

                int neighbour = edge.to;
                assert(edge.from == cur);
                int residual = edge.cap;

                if (node_levels[cur] + 1 == node_levels[neighbour] &&
                    residual > 0) {

                    int fwd_flow_constrained = min(fwd_flow, residual);

                    int fwd_augment =
                        f(neighbour, cur, fwd_flow_constrained, f);

                    if (fwd_augment > 0) {

                        edge.cap -= fwd_augment;
                        es[edge.rev].cap += fwd_augment;

                        assert(edge.cap >= 0);
                        assert(es[edge.rev].cap >= 0);

                        return fwd_augment;
                    }
                }
            }
            return 0;
        };

        int flow;
        do {
            flow =
                dfs_search(source, -1, numeric_limits<int>::max(), dfs_search);
            ans += flow;
        } while (flow > 0);
    }

    cout << ans << endl;
    fflush(stdout);

    return 0;
}
