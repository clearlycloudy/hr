#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int h=0; h<t; ++h){
        string x;
	cin >> x;
	list<char> xs;
	for(auto i: x)
	    xs.push_back(i);
	int ret = 0;
	while(true){
	    // for(auto j: xs)
	    // 	cout << j;
	    // cout << endl;
	    auto it = xs.begin();
	    int prev = -1;
	    bool changed = false;
	    list<char>::iterator it_start = xs.end();
	    while(it!=xs.end()){
		int cur = (int)*it;
		if(cur==prev){
		    assert(it_start != xs.end());
		    it++;
		    xs.erase(it_start, it);
		    ret++;
		    changed = true;
		    prev = -1;
		}else{
		    prev = (int)*it;
		    it_start = it;
		    it++;
		}
	    }
	    if(!changed) break;
	}
	cout << ret << endl;
    }
}
