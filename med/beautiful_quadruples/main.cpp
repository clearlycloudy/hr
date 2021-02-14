#include <bits/stdc++.h>

using namespace std;

template <class T> ostream &operator<<(ostream &o, pair<T *, T *> range) {
    auto [start, end] = range;
    while (start != end) {
        o << *start << " ";
        start++;
    }
    return o;
}

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    array<int, 4> arr{a, b, c, d};
    sort(arr.begin(), arr.end());
    auto [aa, bb, cc, dd] = arr;

    // a xor b
    vector<vector<int>> record(3002, vector<int>(4097, 0));
    vector<uint64_t> total(3002, 0);
    for (int i = 1; i <= aa; i++) {
        for (int j = i; j <= bb; j++) {
            int x = i ^ j;
            record[j][x]++;
            total[j]++;
        }
    }

    // partial sum
    for (int j = 1; j <= 3000; j++) {
        total[j + 1] += total[j];
        for (int x = 0; x <= 4096; ++x) {
            record[j + 1][x] += record[j][x];
        }
    }

    // c xor d
    uint64_t ans = 0;
    for (int i = 1; i <= cc; i++) {
        for (int j = i; j <= dd; j++) {
            int x = i ^ j;
            // number of choices that wqould make xor non-zero
            ans += total[i] - record[i][x];
        }
    }

    cout << ans << endl;

    return 0;
}
