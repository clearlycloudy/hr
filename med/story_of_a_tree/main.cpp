#include <bits/stdc++.h>

using namespace std;

void traverse_reference(int current, int parent, vector<vector<int>> &edges,
                        map<pair<int, int>, int> &guesses, int &score,
                        map<pair<int, int>, int> &guesses_correct,
                        map<pair<int, int>, int> &guesses_incorrect) {
    if (auto it = guesses.find({parent, current}); it != guesses.end()) {
        score += it->second; // tally scores for correct guess
        guesses_correct[{parent, current}] += it->second;
    }
    if (auto it = guesses.find({current, parent}); it != guesses.end()) {
        guesses_incorrect[{current, parent}] += it->second;
    }

    for (auto i : edges[current]) {
        if (i != parent) {
            traverse_reference(i, current, edges, guesses, score,
                               guesses_correct, guesses_incorrect);
        }
    }
}

void traverse_and_root_node(int k, int current, int parent,
                            vector<vector<int>> &edges,
                            map<pair<int, int>, int> &guesses_correct,
                            map<pair<int, int>, int> &guesses_incorrect,
                            int score, int &feasible) {

    if (score >= k) {
        feasible++; // current node is root and score is above threshold
    }

    for (auto child : edges[current]) {
        if (child != parent) {
            // reverse arrow as we traverse down to child and prepare to root
            // child
            int score_augment = score;
            if (auto it = guesses_correct.find({current, child});
                it != guesses_correct.end()) {
                score_augment -=
                    it->second; // reference topology has positive
                                // correlation to guess, so subtract it
                                // as edge change makes it incorrect
            }

            if (auto it = guesses_incorrect.find({child, current});
                it != guesses_incorrect.end()) {
                score_augment += it->second; // reference topology has opposite
                                             // correlation to guess, so add it
                                             // as edge change makes it correct
            }

            traverse_and_root_node(k, child, current, edges, guesses_correct,
                                   guesses_incorrect, score_augment, feasible);
        }
    }
}
int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int n;
        cin >> n;
        vector<vector<int>> edges(n);
        for (int j = 0; j < n - 1; ++j) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        int g, k;
        cin >> g >> k;
        map<pair<int, int>, int> guesses;
        map<pair<int, int>, int> guesses_correct;
        map<pair<int, int>, int> guesses_incorrect;
        for (int i = 0; i < g; ++i) {
            int parent, v;
            cin >> parent >> v;
            parent--;
            v--;
            guesses[{parent, v}]++;
        }
        int score{0};
        // get score for refrence tree topology rooted at node 0
        traverse_reference(0, -1, edges, guesses, score, guesses_correct,
                           guesses_incorrect);

        // now we traverse once more and root current node during traversal:
        int feasible{0}; // number of feasible tree topologies with scores
                         // passing the threshold k
        traverse_and_root_node(k, 0, -1, edges, guesses_correct,
                               guesses_incorrect, score, feasible);

        auto gcd = [](int a, int b, auto f) {
            if (a > b) {
                swap(a, b);
            }
            if (a == 0) {
                return b;
            }
            return f(b % a, a, f);
        };
        int common = gcd(feasible, n, gcd);
        cout << feasible / common << "/" << n / common << endl;
    }
    return 0;
}
