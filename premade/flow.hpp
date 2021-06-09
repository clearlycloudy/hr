#pragma once

#include <bits/stdc++.h>

using namespace std;

// edge
struct E {
    int from;
    int to;
    int cap;
    int rev;
};

struct MaxFlow {
    vector<vector<int>> adj; // node id -> adjacent edge id
    int e_id = 0;            // edge id
    vector<E> es;            // edges
    int source;              // source node id
    int sink;                // sink node id
    MaxFlow(int nodes, int source, int sink)
        : adj(nodes), source(source), sink(sink) {}
    void add_edge(int from, int to, int capacity = 1) {

        adj[from].push_back(e_id);
        es.push_back(
            E{.from = from, .to = to, .cap = capacity, .rev = e_id + 1});
        e_id++;

        adj[to].push_back(e_id);
        es.push_back(E{.from = to, .to = from, .cap = 0, .rev = e_id - 1});
        e_id++;
    }
    int solve() {
        int nodes_total = adj.size();
        int ret = 0;
        vector<int> node_levels(nodes_total);

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
                break; // no further progress is possible
            }

            // avoid searching repeatedly for adjacent edges to a node
            vector<int> idx_edge_start(nodes_total, 0);

            // find an augmenting path
            auto dfs_search = [&](int cur, int fwd_flow, auto f) -> int {
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
                        residual > 0) { // only explore nodes using level graph

                        int fwd_flow_constrained = min(fwd_flow, residual);

                        int fwd_augment = f(neighbour, fwd_flow_constrained, f);

                        if (fwd_augment > 0) { // update flow in graph

                            edge.cap -= fwd_augment;
                            es[edge.rev].cap += fwd_augment;

                            assert(edge.cap >= 0);
                            assert(es[edge.rev].cap >= 0);

                            return fwd_augment; // found a flow
                        }
                    }
                }
                return 0;
            };

            int flow;
            do { // find flow while possible
                flow =
                    dfs_search(source, numeric_limits<int>::max(), dfs_search);
                ret += flow;
            } while (flow > 0);
        }
        return ret;
    }
};

// int main() {
//     int t;
//     cin >> t;
//     for (int i = 0; i < t; ++i) {
//         int n, k;
//         cin >> n >> k;
//         vector<int> vs(n);
//         for (auto &j : vs) {
//             cin >> j;
//         }

//         // use max flow algorithm to solve for min path cover problem

//         // decompose each original node into 2 nodes: 1 for outoging flow, 1 for
//         // incoming flow

//         // run max flow and number of paths = number of unmatched incoming nodes

//         int source = n * 2;
//         int sink = n * 2 + 1;
//         int nodes_total = 2 * n + 2;

//         MaxFlow mf(nodes_total, source, sink);

//         // connect source and outgoing nodes
//         for (int j = 0; j < n; ++j) {
//             mf.add_edge(source, j);
//         }

//         // connect sink and incoming nodes
//         for (int j = 0; j < n; ++j) {
//             mf.add_edge(n + j, sink);
//         }

//         // connect original node edges
//         for (int j = 0; j < n; ++j) {
//             for (int m = j + 1; m < n; ++m) {
//                 if (abs(vs[j] - vs[m]) >= k) { // feasibility guard
//                     int from = j;
//                     int to = n + m;
//                     mf.add_edge(from, to);
//                 }
//             }
//         }

//         int matches_incoming = mf.solve();
//         cout << n - matches_incoming << endl; // number of paths
//     }
// }
