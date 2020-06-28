#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    list<char> arr;
    bool num_lock = true;
    list<char>::iterator it = arr.end();
    for (auto const i : s) {
        switch (i) {
        case '#':
            num_lock = !num_lock;
            break;
        case '*':
            if (arr.size() > 0) {
                if (it != arr.begin()) {
                    it--;
                    it = arr.erase(it);
                }
            }
            break;
        case '<':
            it = arr.begin();
            break;
        case '>':
            it = arr.end();
            break;
        default:
            if ((i >= '0' && i <= '9' && num_lock) || (i < '0' || i > '9'))
                arr.insert(it, i);
        }
    }
    for (auto const i : arr)
        cout << i;
    cout << endl;
    return 0;
}
