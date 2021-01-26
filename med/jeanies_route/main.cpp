#include <bits/stdc++.h>
using namespace std;

// int dfs(int par, int cur, map<int, set<int>> &edge, map<int, int> &letters,
//         map<pair<int, int>, int> &cost, map<int, int> &dist) {
//     int accum_letters = 0;
//     int accum_dist = 0;
//     for (auto i : edge[cur]) {
//         if (i != par) {
//             int count_marked = dfs(cur, i, edge, letters, cost, dist);
//             int d = cost[{cur, i}] * count_marked + dist[i];
//             accum_letters += count_marked;
//             accum_dist += d;
//         }
//     }
//     dist[cur] = accum_dist;
//     letters[cur] += accum_letters;
//     return letters[cur];
// }

// void dfs_2(int par, int cur, map<int, set<int>> &edge, map<int, int>
// &letters,
//            map<int, int> &letters_orig, map<pair<int, int>, int> &cost,
//            int &best, int accum_dist_par) {
//     int n_current = letters[cur];
//     int n_other = letters[par] - n_current;
//     int edge_cost = cost[{par, cur}];

//     int accum_dist_current = letters[cur];

//     int delta_dist = edge_cost * (n_other - (n_current - letters_orig[cur]));

//     int dist = accum_dist_par + delta_dist;
//     cout << cur << " : " << dist << endl;
//     best = min(best, dist);

//     for (auto i : edge[cur]) {
//         if (i != par) {
//             dfs_2(cur, i, edge, letters, letters_orig, cost, best, dist);
//         }
//     }
// }

template <class T> class Optional {
  public:
    bool valid = false;
    T v;
    Optional(T n) : v(n), valid(true) {}
    Optional() { valid = false; }
    static Optional nullopt() { return Optional(); }
    operator bool() { return valid; }
    T &operator*() { return v; }
};

Optional<int> tree_diameter(int par, int cur, map<int, set<int>> &edge,
                            map<int, int> &letters,
                            map<pair<int, int>, int> &cost, int &ret) {

    vector<pair<int, int>> dist_children;
    vector<pair<int, int>> dist_children_to_current;
    for (auto i : edge[cur]) {
        if (i != par) {
            auto d = tree_diameter(cur, i, edge, letters, cost, ret);
            if (d) {
                int dist = *d;
                dist_children.push_back({dist, i});
                dist_children_to_current.push_back({dist + cost[{i, cur}], i});
            }
        }
    }

    sort(dist_children.begin(), dist_children.end());
    sort(dist_children_to_current.begin(), dist_children_to_current.end());

    if (dist_children.size() == 0) {
        if (letters[cur] > 0) { // case: leaf node is marked to be considered
            return Optional<int>(0);
        } else {
            return Optional<int>::nullopt();
        }
    } else if (dist_children.size() == 1) {
        if (letters[cur] > 0) {
            auto [d, idx] = dist_children.back();
            ret = max(ret, d + cost[{idx, cur}]);
        }
        auto [d, _] = dist_children_to_current.back();
        return Optional<int>(d);
    } else {
        int l = dist_children_to_current.size();
        auto [d1, idx1] = dist_children_to_current[l - 1];
        auto [d2, idx2] = dist_children_to_current[l - 2];
        ret = max(ret, d1 + d2);
        auto [d, _] = dist_children_to_current.back();
        return Optional<int>(d);
    }
}

// bool explore(int par, int cur, map<pair<int, int>, int> &cost,
//              map<int, set<int>> &edge, map<int, int> &letters, int diameter,
//              int d, set<int> &nodes) {
//     if (d > diameter) {
//         return false;
//     } else if (d == diameter) {
//         return letters[cur] > 0;
//     } else {
//         for (auto i : edge[cur]) {
//             if (i != par) {
//                 nodes.insert(i);
//                 int dd = cost[{cur, i}] + d;
//                 if (explore(cur, i, cost, edge, letters, diameter, dd,
//                 nodes)) {
//                     return true;
//                 } else {
//                     nodes.erase(i);
//                 }
//             }
//         }
//         return false;
//     }
// }

// set<int> find_diameter_nodes(int n, map<pair<int, int>, int> &cost,
//                              map<int, set<int>> &edge, map<int, int>
//                              &letters, int diameter) {
//     set<int> nodes;
//     int root = -1;
//     for (auto [idx, count] : letters) {
//         if (count > 0) {
//             root = idx;
//         }
//     }
//     assert(root != -1);
//     nodes.insert(root);
//     // cout << "root: " << root << endl;
//     explore(-1, root, cost, edge, letters, diameter, 0, nodes);
//     return nodes;
// }

Optional<int> connect_full_explore(int par, int cur,
                                   map<pair<int, int>, int> &cost,
                                   map<int, set<int>> &edge,
                                   map<int, int> &letters) {

    vector<int> ds;
    for (auto i : edge[cur]) {
        if (par != i) {
            auto d = connect_full_explore(cur, i, cost, edge, letters);
            if (d) {
                ds.push_back(*d + cost[{i, cur}]);
            }
        }
    }
    if (ds.size() == 0) { // only propagate marked leaf nodes upward
        if (letters[cur] > 0) {
            return Optional<int>(0);
        } else {
            return Optional<int>::nullopt();
        }
    } else {
        // continue propagating up
        int sum = 0;
        for (auto j : ds) {
            sum += j;
        }
        return Optional<int>(sum);
    }
}

int connect_full(int n, map<pair<int, int>, int> &cost,
                 map<int, set<int>> &edge, map<int, int> &letters) {
    int root = -1;
    for (auto [k, v] : letters) {
        if (v > 0) {
            root = k;
            break;
        }
    }
    assert(root >= 0);
    auto dd = connect_full_explore(-1, root, cost, edge, letters);
    assert(dd);
    int ret = *dd;
    return ret;
}

int solve(int n, map<pair<int, int>, int> &cost, map<int, set<int>> &edge,
          map<int, int> &letters) {
    int diameter = 0;
    tree_diameter(-1, 0, edge, letters, cost, diameter);
    // cout << "diameter: " << diameter << endl;

    // set<int> nodes = find_diameter_nodes(n, cost, edge, letters, diameter);
    // cout << "diameter nodes: " << endl;
    // for (auto i : nodes) {
    //     cout << i << " ";
    // }
    // cout << endl;

    // set<int> remain;
    // for (auto [k, v] : letters) {
    //     if (v > 0 && nodes.count(k) == 0) {
    //         remain.insert(k);
    //     }
    // }
    int d = connect_full(n, cost, edge, letters);
    // cout << "remaining path dist: " << d << endl;
    int ans = d * 2 - diameter;
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    map<int, int> letters;
    map<pair<int, int>, int> cost;
    map<int, set<int>> edge;
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        a--;
        letters[a]++;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;
        cost[{u, v}] = c;
        cost[{v, u}] = c;
        edge[u].insert(v);
        edge[v].insert(u);
    }

    cout << solve(n, cost, edge, letters) << endl;
    return 0;
}
