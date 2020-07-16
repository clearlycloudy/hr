#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1000000007;

set<pair<int,int>> neighbour[2][20];
    
bool s(int n, int i, int j, int done, int total, int grid[2][10]){
    if(j==n && i==1){
	return done == total;
    }else if(i==0 && j==n){
	return s(n,1,0,done,total,grid);
    }else{
	if(grid[i][j]==1){
	    return s(n,i,j+1,done,total,grid);
	}else{
	    // cout << "pos: " << i << " " << j << endl;
	    // cout << "done: " << done << ", total: " << total << endl;
	    pair<int,int> choices [] = {{0,-1},{0,1},{-1,0},{1,0},{1,-1},{-1,1}};
	    for(auto [y,x]:choices){
		int yy = i+y;
		int xx = j+x;
		if(yy>=0 && y<2 &&
		   xx>=0 && xx<n){
		    if(grid[yy][xx]==0){
			grid[yy][xx]=1;
			// cout << yy << ", " << xx << endl;
			if(s(n, i, j+1, done+2, total, grid)){
			    return true;
			}
			grid[yy][xx]=0;
		    }
		}
	    }
	}
    }
    return false;
}
    
bool solve(string const & a, string const & b, int const n){
    int count_a_empty = 0;
    int count_b_empty = 0;
    for(auto i: a){
	if(i=='0') count_a_empty++;
    }
    for(auto i: b){
	if(i=='0') count_b_empty++;
    }
    if((count_a_empty + count_b_empty)%2!=0){
	return false;
    }
    int grid[2][10];
    for(int i=0;i<n;++i){
	grid[0][i] = a[i] == '1' ? 1 : 0;
	grid[1][i] = b[i] == '1' ? 1 : 0;
    }
    int total = count_a_empty + count_b_empty;

    return s(n,0,0,0,total,grid);
}

int main() {
    int t;
    cin >> t;
    for(int _=0;_<t;++_){
	// cout <<"---" << endl;
	int n;
	cin >> n;
	string a, b;
	cin >> a;
	cin >> b;
	assert(a.size()==n);
	assert(b.size()==n);
	cout << (solve(a,b,n) ? "YES" : "NO") << endl;
    }
    return 0;
}
