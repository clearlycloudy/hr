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

using Queue = priority_queue<pair<int, int>, vector<pair<int, int>>,
                             greater<pair<int, int>>>;

int find_transition(unordered_map<int, int> const &teleport, int start) {
    int pos = start;
    while (teleport.count(pos) == 1) {
        pos = teleport.find(pos)->second;
    }
    return pos;
}

int solve(unordered_map<int, int> const &teleport) {

    vector<int> dp(
        101, numeric_limits<int>::max()); // cell -> min steps to get there

    Queue q;        // expansion queue
    q.push({0, 1}); // initial cell

    while (!q.empty()) {
        auto [cost, cell] = q.top();
        q.pop();
        assert(cell >= 1 && cell <= 100);
        if (cost < dp[cell]) {
            dp[cell] = cost;
            // do an expansion
            for (int roll = 1; roll <= 6; roll++) { // values of a dice
                int cell_next = cell + roll;
                int cost_next = cost + 1;
                if (cell_next <= 100) { // constraint
                    int cell_dest = find_transition(teleport, cell_next);
                    if (cost_next < dp[cell_dest]) {
                        q.push({cost_next, cell_dest});
                    }
                }
            }
        }
    }

    return dp[100] == numeric_limits<int>::max() ? -1 : dp[100];
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) { // test case
        int n;
        scanf("%d", &n);
        unordered_map<int, int> teleport;
        for (int j = 0; j < n; ++j) { // ladders
            int start, end;
            scanf("%d %d", &start, &end);
            teleport[start] = end;
        }
        int m;
        scanf("%d", &m);
        for (int j = 0; j < m; ++j) { // snakes
            int start, end;
            scanf("%d %d", &start, &end);
            teleport[start] = end;
        }
        printf("%d\n", solve(teleport));
    }
    return 0;
}
