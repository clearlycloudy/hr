#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (auto &i : arr) {
            cin >> i;
        }
        sort(arr.begin(), arr.end());

        // number->length->occurence
        map<int, map<int, int>> existing;

        for (auto j : arr) {
            int v = j - 1;
            if (existing.count(v) == 0) {
                // insert new group of length 1, occurence 1
                existing[j][1]++;
            } else {
                // existing occurence of v of length len
                auto [len, occur] = *existing[v].begin();
                int len_new = len + 1;
                existing[v].begin()->second--;
                if (existing[v].begin()->second == 0) {
                    existing[v].erase(existing[v].begin());
                }
                // insert updated group
                existing[j][len_new]++;
            }
        }
        int ans = numeric_limits<int>::max();
        for (auto &j : existing) {
            for (auto [len, count] : j.second) {
                ans = min(ans, len);
            }
        }
        cout << (ans == numeric_limits<int>::max() ? 0 : ans) << endl;
    }
    return 0;
}
