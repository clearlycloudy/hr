#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> arr;
    for (int i = 0; i < n; ++i) {
        int t, f;
        cin >> t >> f;
        int a = t - f;
        int b = t + f;
        arr.push_back({a, b});
    }
    sort(arr.begin(), arr.end());

    // find longest decreasing subsequence
    set<int> s;
    for (auto [_, b] : arr) {
        int val = -b;
        auto it = s.lower_bound(val);
        if (it != s.end()) {
            s.erase(it);
        }
        s.insert(val);
    }

    cout << s.size() << endl;
    return 0;
}
