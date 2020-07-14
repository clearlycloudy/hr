#include <bits/stdc++.h>

using namespace std;

int solve(vector<pair<int,int>> & arr){
    sort(arr.begin(), arr.end(),[](auto a,auto b){return a.second<b.second;});
    int comp = 0;
    int taken = 0;
    int ret = 1;
    for(int i=1;i<arr.size();++i){
	auto const & [s,e] = arr[i];
	if(s<=arr[taken].second){
	    if(s>comp){
		comp = arr[taken].second;
		taken = i;
		ret++;
	    }
	}else {
	    taken = i;
	    ret++;
	}
    }
    return ret;
}
int main(){
    long long t;
    cin >> t;
    for(int h = 0; h<t; ++h){
	int n;
	cin >> n;
	vector<pair<int,int>> arr;
        for(int _ = 0; _<n; ++_){
	    int a,b;
	    cin>>a>>b;
	    arr.push_back({a,b});
	}
	cout << solve(arr) << endl;
    }
    return 0;
}
