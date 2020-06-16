#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>
#include <tuple>

using namespace std;

int main() {
    int t,n;
    cin >> t;
    for(int i = 0;i<t;++i){
	map<int,long> m; //map val-> accumulative weight
	//cout << "testcase: " << i << endl;
	cin >> n;
	vector<int> val(n);
	vector<long> weight(n);
	for(int j=0;j<n;++j){
	    cin >> val[j];
	}
	for(int j=0;j<n;++j){
	    cin >> weight[j];
	}
	for(int j=0;j<n;++j){
	    int v = val[j];
	    long w = weight[j];
	    //cout << "v: " << v << ", w: " << w << endl;
	    auto it = m.lower_bound(v);
	    long accum = 0;
	    int val_prev = -1;
	    bool need_overwrite_weight = false;
	    long existing_prev_accum = 0;
	    if(it!=m.end()){
		while(true){
		    if(it->first >= v){
			if(it->first == v){
			    existing_prev_accum = it->second;
			    need_overwrite_weight = true;
			}
			if(it==m.begin()){ //not found
			    break;
			}
			--it; //keep searching
		    }else{//found
			val_prev = it->first;
			accum = it->second;
			break;
		    }
		}
	    }else{
		auto it_rev = m.rbegin();
		if(it_rev!=m.rend()){
		    if(it_rev->first < v){
			val_prev = it_rev->first;
			accum = it_rev->second;
		    }
		}
	    }
	    accum += w;
	    if(need_overwrite_weight ){
		if(existing_prev_accum < accum){
		    map<int,long>::iterator it_update;
		    bool inserted;
		    std::tie (it_update, inserted) = m.insert({v,accum});
		    if(!inserted){
			it_update->second = accum;
		    }
		    //cout << "overwrite: " << v << ": " << accum << endl;
		    //just erase all higher values with lower accumulated weights than current
		    it_update = std::next(it_update);
		    while(it_update!=m.end()){
			auto it_next = it_update;
			it_next=std::next(it_next);
			if(it_update->second < accum)
			{
			    m.erase(it_update);
			}
			it_update = it_next;
		    }
		}
	    }else{
		map<int,long>::iterator it_update;
		std::tie (it_update, std::ignore) = m.insert({v,accum});
		//just erase all higher values with lower accumulated weights than current
		it_update = std::next(it_update);
		while(it_update!=m.end()){
		    auto it_next = it_update;
		    it_next=std::next(it_next);
		    if(it_update->second < accum)
		    {
			m.erase(it_update);
		    }
		    it_update = it_next;
		}
	    }


	}
	long ans = 0;
	for(auto&h:m){
	    if(ans < h.second){
		ans = h.second;
	    }
	    //cout << "val: " << h.first << ": " << h.second << endl;
	}
	cout << ans << endl;
    }
    return 0;
}
