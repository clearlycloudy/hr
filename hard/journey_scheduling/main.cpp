#include <bits/stdc++.h>

using namespace std;

// int tree_width(int n, int m, vector<vector<int>> &edges) {
//     auto inner = [&edges](int current, int parent, int &best, auto f) -> int
//     {
//         int longest_subbranch = 0;
//         priority_queue<int, vector<int>, greater<int>> q;
//         for (auto child : edges[current]) {
//             if (child != parent) {
//                 int l = f(child, current, best, f);
//                 longest_subbranch = max(longest_subbranch, l + 1);
//                 q.push(l);
//                 if (q.size() > 2) {
//                     q.pop();
//                 }
//             }
//         }
//         if (q.size() == 2) {
//             int a = q.top();
//             q.pop();
//             best = max(best, a + q.top() + 2);
//         } else if (q.size() == 1) {
//             best = max(best, q.top() + 1);
//         }
//         return longest_subbranch;
//     };
//     int best = 0;
//     inner(0, -1, best, inner);
//     return best;
// }

int prop_up(int current, int parent, vector<vector<int>> &edges,
            vector<int> &subbranch_max, int &width) {
    int best = 0;
    priority_queue<int, vector<int>, greater<int>> q;

    for (auto child : edges[current]) {
        if (child != parent) {
            int d_child = prop_up(child, current, edges, subbranch_max, width);
            best = max(best, d_child + 1);

            q.push(d_child);
            if (q.size() > 2) {
                q.pop();
            }
        }
    }

    // save top 2 max distances, to be used in prop_down
    if (q.size() == 2) {
        int a = q.top();
        q.pop();
        width = max(width, a + q.top() + 2);
    } else if (q.size() == 1) {
        width = max(width, q.top() + 1);
    }

    // dist from subtree path
    subbranch_max[current] = best;
    return best;
};

void prop_down(int current, int parent, int parent_parent,
               vector<vector<int>> &edges, vector<int> &cache,
               vector<int> &dist_parent, vector<int> &subbranch_max,
               vector<vector<pair<int, int>>> &dist_sibling) {

    int d_parent = parent != -1 ? dist_parent[parent] + 1 : 0;

    for (auto c : edges[current]) {
        if (c != parent) { // any sibling node
            // thus it is 2 hops from current node
            int d_sib = subbranch_max[c] + 2;
            if (dist_sibling[current].size() < 2) {
                dist_sibling[current].push_back({d_sib, c});
            } else {
                int d_min = numeric_limits<int>::max();
                int idx_min = -1;
                int idx = 0;
                for (auto [d, _] : dist_sibling[current]) {
                    if (d < d_min) {
                        idx_min = idx;
                        d_min = d;
                    }
                    idx++;
                }
                if (d_sib > d_min && idx_min != -1) {
                    dist_sibling[current][idx_min] = {d_sib, c};
                }
            }
        }
    }
    int d_max_sibling = 0;
    if (parent != -1) {
        for (auto [d, idx] : dist_sibling[parent]) {
            if (idx != current) {
                d_max_sibling = max(d_max_sibling, d);
            }
        }
    }
    // update parent path dist
    dist_parent[current] = max(dist_parent[current], d_parent);
    dist_parent[current] = max(dist_parent[current], d_max_sibling);

    // take max from leaf path and parent path
    cache[current] = max(subbranch_max[current], dist_parent[current]);

    for (auto c : edges[current]) {
        if (c != parent) {
            prop_down(c, current, parent, edges, cache, dist_parent,
                      subbranch_max, dist_sibling);
        }
    }
};

pair<vector<int>, int> dp_farthest(int n, int m, vector<vector<int>> &edges) {

    vector<int> cache(n, 0);

    // save max length from a leaf in subranch to current node
    vector<int> subbranch_max(n, 0);
    int width = 0;
    prop_up(0, -1, edges, subbranch_max, width);

    // max dist from parent path
    vector<int> dist_parent(n, 0);
    vector<vector<pair<int, int>>> dist_sibling(n, vector<pair<int, int>>());
    prop_down(0, -1, -1, edges, cache, dist_parent, subbranch_max,
              dist_sibling);

    return {cache, width};
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(100000);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    // int width = tree_width(n, m, edges);

    auto [cache, width] = dp_farthest(n, m, edges);

    for (int i = 0; i < m; ++i) {
        int v, k;
        scanf("%d %d", &v, &k);
        v--;
        uint64_t ans =
            static_cast<uint64_t>(k - 1) * static_cast<uint64_t>(width) +
            static_cast<uint64_t>(cache[v]);
        printf("%lu\n", ans);
    }
    fflush(stdout);
    return 0;
}
