#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int h=0; h<t; ++h){
	string x;
	cin >> x;
	vector<int> xs;
	for(auto const i: x)
	    xs.push_back((i=='1'?1:0));
	int k;
	cin >> k;
	for(int ii=0; ii<xs.size(); ++ii){
	    if(k>=1 && xs[ii]==0){
		k--;
		cout << 1;
	    }else{
		cout << 0;
	    }
	}
	cout << endl;
    }
}
