#include <bits/stdc++.h>

using namespace std;

vector<int> solve(int cube[50][50][50], int n){
    //solve and store dp values in cube and dp

    //get base base, subcube of size 1x1x1
    int dp[50][50][50] = {0};
    vector<int> ret;
    int count = 0;
    for(int i=0;i<n;++i){
	for(int j=0;j<n;++j){
	    for(int k=0;k<n;++k){
		if(cube[i][j][k]==1) count++;
	    }
	}
    }
    ret.push_back(count);

    //solve problems of larger size up to n
    for(int z=2;z<=n;++z){
	count = 0;
	//get index of current subcube
	for(int i=0;i+z<=n;++i){
	    for(int j=0;j+z<=n;++j){
		for(int k=0;k+z<=n;++k){
		    int z_last = z-1;
		    dp[i][j][k] = max(cube[i][j][k],cube[i+1][j][k]);
		    dp[i][j][k] = max(dp[i][j][k],cube[i][j+1][k]);
		    dp[i][j][k] = max(dp[i][j][k],cube[i][j][k+1]);
		    dp[i][j][k] = max(dp[i][j][k],cube[i+1][j+1][k]);
		    dp[i][j][k] = max(dp[i][j][k],cube[i+1][j][k+1]);
		    dp[i][j][k] = max(dp[i][j][k],cube[i][j+1][k+1]);
		    dp[i][j][k] = max(dp[i][j][k],cube[i+1][j+1][k+1]);
		    if(z==dp[i][j][k]) count++;
		}
	    }
	}
	ret.push_back(count);
	copy(&dp[0][0][0],&dp[0][0][0]+sizeof(dp)/sizeof(int), &cube[0][0][0]);
    }
    return ret;
}

int main(){
    int cube[50][50][50];
    long long q;
    cin >> q;
    for(int _=0; _<q; ++_){
	int n;
	cin>>n;
	for(int i=0;i<n;++i){
	    for(int j=0;j<n;++j){
		for(int k=0;k<n;++k){
		    cin >> cube[i][j][k];
		}
	    }
	}
	for(auto i: solve(cube,n))
	    cout << i << " ";
	cout << endl;
    }
    return 0;
}
