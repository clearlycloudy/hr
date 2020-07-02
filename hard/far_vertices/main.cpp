#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1000000007;

int main() {

    int n, k;
    cin >> n >> k;

    int def = numeric_limits<int>::max();
    int dist[100][100];
    fill_n(&dist[0][0], 10000, def);
    vector<pair<int,int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        dist[a][b] = 1;
        dist[b][a] = 1;
	edges.push_back({a,b});
    }    
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;

    for (int k = 0; k < n; ++k)
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < n; ++j){
                int x = dist[i][k];
                int y = dist[j][k];
                int z = max(x, y) == numeric_limits<int>::max()
                            ? numeric_limits<int>::max()
                            : y + x;
                dist[i][j] = min(dist[i][j], z);
            }

    if(k==0){
	cout << n << endl;
    }else if(k==1){
	cout << max(n-2,0) << endl;
    }else{ //k>=3
	if(k%2==0){	    
	    int unmarked = 0;
	    for (int i = 0; i < n; ++i) {
		int count = 0;
		for (int j = 0; j < n; ++j) {
		    if (dist[i][j] <= k / 2)
			count++;
		}
		unmarked = max(unmarked, count);
	    }
	    cout << n - unmarked << endl;
	}else{
	    int unmarked = 0;
	    for(auto [a,b]:edges){
		int count = 0;
		for (int j = 0; j < n; ++j) {
		    if (dist[a][j] <= k/2 || dist[b][j]<=k/2)
			count++;
		}
		unmarked = max(unmarked, count);
	    }
	    cout << n - unmarked << endl;
	}
    }
    return 0;
}
