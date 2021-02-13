#include <bits/stdc++.h>

using namespace std;

string solve(int n, int m, map<int, set<int>> &edges,
             map<pair<int, int>, int> &costs);

int main() {
    int n, m;
    cin >> n >> m;
    // cout << n << " " << m << endl;
    map<int, set<int>> edges;
    map<pair<int, int>, int> costs;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges[a].insert(b);
        edges[b].insert(a);
        if (costs.count({a, b}) == 0) {
            costs[{a, b}] = c;
            costs[{b, a}] = c;
        } else {
            costs[{a, b}] = min(costs[{a, b}], c);
            costs[{b, a}] = min(costs[{a, b}], c);
        }
    }
    auto ans = solve(n, m, edges, costs);
    cout << ans << endl;

    return 0;
}

struct N {
    N *parent = nullptr;
    int count = 1;
    N() : count(1), parent(nullptr) {}
    N *find() {
        if (parent) {
            parent = parent->find();
            return parent;
        } else {
            return this;
        }
    }
    void merge(N *other) {
        if (!other || other == this) {
            return;
        }
        N *p = find();
        N *p2 = other->find();
        if (p->count > p2->count) {
            p->count += p2->count;
            p2->parent = p;
        } else {
            p2->count += p->count;
            p->parent = p2;
        }
    }
};

void count_tree_edges(int n, map<int, set<int>> &tree, int root,
                      map<pair<int, int>, uint64_t> &count);

string solve(int n, int m, map<int, set<int>> &edges,
             map<pair<int, int>, int> &costs) {

    string ret{""};

    // construct mst
    vector<N *> ns;
    for (int i = 0; i < n; ++i) {
        ns.push_back(new N());
    }

    vector<pair<int, pair<int, int>>> ranked_cost;
    for (auto [k, v] : costs) {
        ranked_cost.push_back({v, k});
    }

    sort(ranked_cost.begin(), ranked_cost.end());

    map<int, set<int>> tree;
    for (auto [cost, nodes] : ranked_cost) {
        assert(nodes.first >= 0 && nodes.first < n);
        assert(nodes.second >= 0 && nodes.second < n);
        N *p1 = ns[nodes.first]->find();
        N *p2 = ns[nodes.second]->find();
        if (p1 != p2) {
            ns[nodes.first]->merge(ns[nodes.second]);

            tree[nodes.first].insert(nodes.second);
            tree[nodes.second].insert(nodes.first);

            if (ns[nodes.first]->find()->count == n) {
                break;
            }
        }
    }

    // count number of times each edge in tree is traversed
    int root = 0;
    map<pair<int, int>, uint64_t> count;
    count_tree_edges(n, tree, root, count);

    vector<uint64_t> buckets(
        m * 2,
        0LL); // costs[{n1,n2}] (power of 2) -> accumulation of combinations
    for (auto &[k, v] : count) {
        assert(costs.count(k) == 1);
        buckets[costs[k]] += v;
        // ans += pow(2, costs[k]) * v;
    }

    // add and carry over
    for (int i = 0; i + 1 < buckets.size(); ++i) {
        buckets[i + 1] += buckets[i] / 2LL;
        buckets[i] %= 2LL;
    }

    bool started = false;
    for (int i = buckets.size() - 1; i >= 0; --i) {
        if (buckets[i] == 1LL || started) {
            started = true;
            ret.push_back((buckets[i] == 1 ? '1' : '0'));
        }
    }

    for (auto i : ns)
        delete i;
    return ret;
}

void dfs(int n, map<int, set<int>> &tree, int cur, int parent,
         vector<int> &count_subtree, map<pair<int, int>, uint64_t> &count) {

    // cout << "dfs: " << cur << endl;
    int subtree = 1;
    for (auto c : tree[cur]) {
        if (c != parent) {
            dfs(n, tree, c, cur, count_subtree, count);
            uint64_t combo =
                (uint64_t)count_subtree[c] * (uint64_t)(n - count_subtree[c]);
            count[{cur, c}] = combo;
            subtree += count_subtree[c];
        }
    }
    count_subtree[cur] = subtree;
}

void count_tree_edges(int n, map<int, set<int>> &tree, int root,
                      map<pair<int, int>, uint64_t> &count) {

    vector<int> count_children(n, 0);
    dfs(n, tree, root, -1, count_children, count);
}
