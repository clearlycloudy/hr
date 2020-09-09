#include <bits/stdc++.h>

using namespace std;

void solve(vector<pair<int,int>> &v){
    set<int> slots;
    int dd = 1;
    for(auto [d,m]: v)
        dd = max(dd, d);
    for(int i=1;i<=dd+1;++i)
	slots.insert(i);
    int ret = 0;
    for(auto i=0;i<v.size();++i){
	auto [d,m] = v[i];
	auto it = slots.upper_bound(d);
        while(m>0 && it!=slots.begin()){
	    --it;
	    --m;
	    it = slots.erase(it);
	}
	ret += m;
	cout << ret << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    vector<pair<int,int>> v;
    for(int i=0; i<t; ++i){
	int d, m;
	cin>>d>>m;
	v.push_back(make_pair(d,m));
    }

    solve(v);
    
    return 0;
}
