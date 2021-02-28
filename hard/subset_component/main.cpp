#include <bits/stdc++.h>

using namespace std;

int solve(int idx, vector<uint64_t> const &components,
          vector<uint64_t> const
              &connections) { // O(2^connections.size() approx. 2^20 = 10^6)
    if (idx >= connections.size()) {
        return components.size();
    } else {
        // not take connections[idx]
        int ret = solve(idx + 1, components, connections);

        // take connections[idx]
        vector<uint64_t> updated_components;
        uint64_t pattern = connections[idx];
        for (auto i : components) { // O(20)
            if ((i & pattern) != 0) {
                // connects to existing component
                pattern |= i; // absorb current component i
            } else {
                // make a independent component
                updated_components.push_back(i);
            }
        }
        if (pattern != 0) { // don't add an empty set
            updated_components.push_back(pattern);
        }
        return ret + solve(idx + 1, updated_components, connections);
    }
}

int main() {
    int n;
    cin >> n;
    vector<uint64_t> arr(n);
    for (auto &i : arr) {
        cin >> i;
    }
    // initial components
    vector<uint64_t> components(64);
    for (int i = 0; i < 64; ++i) {
        components[i] = static_cast<uint64_t>(1) << static_cast<uint64_t>(i);
    }
    cout << solve(0, components, arr) << endl;

    return 0;
}
