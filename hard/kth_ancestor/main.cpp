#include <bits/stdc++.h>

using namespace std;

array<array<int, 40>, 100001> parents;
array<int, 100001> node_inputs;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int p;
        cin >> p;
        for (int j = 0; j < parents.size(); ++j) {
            fill(parents[j].begin(), parents[j].end(), 0);
        }
        int l = (int)(log(p) / log(2)) + 1;
        for (int j = 0; j < p; ++j) {
            int x, y;
            cin >> x >> y;
            parents[x][0] = y;  // y is the parent of x, y=-1 for root node x
            node_inputs[j] = x; // compress to input nodes for precompute
        }

        int q;
        cin >> q;

        // precompute dp
        for (int j = 1; j <= l; ++j) {    // skip level
            for (int k = 0; k < p; ++k) { // input node

                // path compression, lockstep for all nodes
                parents[node_inputs[k]][j] =
                    parents[parents[node_inputs[k]][j - 1]][j - 1];
            }
        }

        for (int j = 0; j < q; ++j) {
            int type;
            cin >> type;
            if (type == 0) { // add leaf x
                int y, x;
                cin >> y >> x;
                parents[x][0] = y;
                int k = 1;
                // create skip connections using existing nodes
                while (parents[x][k - 1] != 0) {
                    parents[x][k] = parents[parents[x][k - 1]][k - 1];
                    k++;
                }
                while (k <= l) {
                    parents[x][k] = 0;
                    k++;
                }
            } else if (type == 1) { // remove leaf x
                int x;
                cin >> x;
                for (int a = 0; a <= l; ++a) {
                    parents[x][a] = 0;
                }
            } else { // query kth ancestor of x
                int x, k;
                cin >> x >> k; // k = sum_h{2^h}
                int skip = 0;
                while (k > 0) {
                    if (k & 0b1) {
                        x = parents[x][skip]; // go to next node up
                    }
                    k >>= 1;
                    skip++; // go through exponent of 2^level
                }
                cout << x << endl;
                fflush(stdout);
            }
        }
    }
    return 0;
}
