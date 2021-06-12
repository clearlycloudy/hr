#include <bits/stdc++.h>

using namespace std;

namespace std {
template <> struct hash<pair<int, int>> {
    std::size_t operator()(const pair<int, int> &k) const {
        using std::hash;
        using std::size_t;

        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        return ((hash<int>()(k.first) ^ (hash<int>()(k.second) << 1)) >> 1);
    }
};
} // namespace std

// min priority queue
using Queue = priority_queue<pair<int, int>, vector<pair<int, int>>,
                             greater<pair<int, int>>>;

void search(unordered_map<int, unordered_set<int>> &adj,
            unordered_map<pair<int, int>, int> &cost,
            unordered_map<int, int> &ret, Queue &q) {
    if (q.empty()) {
        return;
    }
    auto [top_cost, top] = q.top();
    assert(ret.count(top) == 1);
    q.pop();
    if (ret[top] < top_cost) {            // discard top
        return search(adj, cost, ret, q); // tail call
    } else {
        for (auto neigh : adj[top]) {
            pair<int, int> key = {top, neigh};
            assert(cost.count(key) == 1);
            int c = cost[key];
            if (ret.count(neigh) == 0) { // non-exiting neighbour
                ret[neigh] = c + ret[top];
                q.push({c, neigh}); // make neigh eligeable for search
            } else {
                if (c + ret[top] < ret[neigh]) { // top->neigh
                    ret[neigh] = c + ret[top];
                    q.push({c, neigh}); // make neigh eligeable for search
                }
            }
        }
        return search(adj, cost, ret, q); // tail call
    }
}

void solve(unordered_map<int, unordered_set<int>> &adj,
           unordered_map<pair<int, int>, int> &cost, int start, int n) {
    unordered_map<int, int> ret; // best cost from single source start
    ret[start] = 0;
    Queue q; // queue to search
    q.push({0, start});
    search(adj, cost, ret, q);
    for (int i = 1; i <= n; ++i) {
        if (i != start) {
            if (ret.count(i) == 0) {
                // cout << -1 << " ";
                printf("-1 ");
            } else {
                // cout << ret[i] << " ";
                printf("%d ", ret[i]);
            }
        }
    }
    // cout << endl;
    printf("\n");
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int t;
    scanf("%d", &t);
    // cin >> t;
    for (int i = 0; i < t; ++i) { // test case
        int n, m, s;
        // cin >> n >> m;
        scanf("%d %d", &n, &m);
        unordered_map<int, unordered_set<int>> adj;
        unordered_map<pair<int, int>, int> cost;
        for (int j = 0; j < m; ++j) { // edges
            int x, y;
            static int const r = 6; // constant edge weight
            // cin >> x >> y >> r;
            scanf("%d %d", &x, &y);
            // take min of cost
            if (cost.count({x, y}) == 0) {
                cost[{x, y}] = r;
                cost[{y, x}] = r;
            } else {
                cost[{x, y}] = min(cost[{x, y}], r);
                cost[{y, x}] = min(cost[{y, x}], r);
            }
            adj[x].insert(y);
            adj[y].insert(x);
        }
        // cin >> s;
        scanf("%d", &s);
        solve(adj, cost, s, n);
    }
    return 0;
}
