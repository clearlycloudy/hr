#include <bits/stdc++.h>

using namespace std;

int main(){
    long long n,m,k;
    cin >> n >> m >> k;
    vector<vector<char>> arr(n,vector<char>(m));
    pair<int,int> dest;
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<m; ++j){
	    cin >> arr[i][j];
	    if(arr[i][j]=='*'){
		dest = {i,j};
	    }
	}
    }
    int dp [51][51];
    fill(&dp[0][0], &dp[0][0] + sizeof(dp)/sizeof(int), numeric_limits<int>::max());
    
    dp[0][0] = 0;

    int dp_move [51][51];
    fill(&dp_move[0][0], &dp_move[0][0] + sizeof(dp_move)/sizeof(int), 0);

    deque<pair<int,int>> q{{0,0}};
    while(!q.empty()){
	auto [y,x] = q.front();
	q.pop_front();
	pair<int,int> offsets[] = {{-1,0},{1,0},{0,-1},{0,1}};
	for(auto [off_y, off_x]: offsets){
	    int xx = x+off_x;
	    int yy = y+off_y;
	    if(xx>=0 && xx<m &&
	       yy>=0 && yy<n &&
	       arr[y][x] != '*'){
		if(off_y==-1){
		    int actions = dp[y][x] + (arr[y][x]=='U' ? 0 : 1);
		    if(dp[yy][xx] > actions && dp_move[y][x] + 1 <= k){
			dp[yy][xx] = dp[y][x] + (arr[y][x]=='U' ? 0 : 1);
			dp_move[yy][xx] = dp_move[y][x] + 1;
			q.push_back({yy,xx});
		    }
		}else if(off_y==1){
		    int actions = dp[y][x] + (arr[y][x]=='D' ? 0 : 1);
		    if(dp[yy][xx] > actions && dp_move[y][x] + 1 <= k){
			dp[yy][xx] = dp[y][x] + (arr[y][x]=='D' ? 0 : 1);
			dp_move[yy][xx] = dp_move[y][x] + 1;
			q.push_back({yy,xx});
		    }
		}else if(off_x==-1){
		    int actions = dp[y][x] + (arr[y][x]=='L' ? 0 : 1);
		    if(dp[yy][xx] > actions && dp_move[y][x] + 1 <= k){
			dp[yy][xx] = dp[y][x] + (arr[y][x]=='L' ? 0 : 1);
			dp_move[yy][xx] = dp_move[y][x] + 1;
			q.push_back({yy,xx});
		    }
		}else if(off_x==1){
		    int actions = dp[y][x] + (arr[y][x]=='R' ? 0 : 1);
		    if(dp[yy][xx] > actions && dp_move[y][x] + 1 <= k){
			dp[yy][xx] = dp[y][x] + (arr[y][x]=='R' ? 0 : 1);
			dp_move[yy][xx] = dp_move[y][x] + 1;
			q.push_back({yy,xx});
		    }
		}
	    }
	}
    }
    // for(int r = 0; r < n; ++r){
    // 	for(int c = 0; c < m; ++c)
    // 	    cout << dp[r][c] << " ";
    // 	cout << endl;
    // }
    // cout << "--" << endl;
    auto [i,j] = dest;
    if(dp[i][j] <= k){
	cout << dp[i][j] << endl;
    } else {
	cout << -1 << endl;
    }
    return 0;
}
