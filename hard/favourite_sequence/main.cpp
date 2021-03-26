#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;
    scanf("%d", &n);

    vector<unordered_set<int>> incoming(1000001);
    vector<unordered_set<int>> outgoing(1000001);

    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        vector<int> arr(k);
        for (auto &j : arr) {
            scanf("%d", &j);
        }

        // no need to construct a dense dependency with n^2 complexity,
        // just linearize it
        for (int j = 1; j < k; ++j) {
            int dest = arr[j];
            int src = arr[j - 1];
            incoming[dest].insert(src);
            outgoing[src].insert(dest);
        }
    }

    priority_queue<int, vector<int>, greater<int>> available;
    for (int i = 1; i <= 1000000; ++i) {
        if (incoming[i].empty() && outgoing[i].size() > 0) {
            available.push(i);
        }
    }

    while (!available.empty()) {
        int v = available.top();
        available.pop();
        printf("%d ", v);
        for (auto &dest : outgoing[v]) {
            incoming[dest].erase(v);
            if (incoming[dest].empty()) { // incoming[dest] is guaranteed to
                                          // become 0 only once
                available.push(dest);
            }
        }
    }

    printf("\n");

    return 0;
}
