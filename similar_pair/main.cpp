#include <bits/stdc++.h>

using namespace std;

//bit indexed tree via array
struct Bit {
    vector<int64_t> arr;
    int64_t n;
    Bit(int64_t n): arr(n+1,0), n(n) {}
    void update(int64_t index, int64_t delta){
	while(index<=n){
	    arr[index] += delta;
	    index += index & ((~index)+1);
	}
    }
    int64_t query(int64_t index){ //querys accum within [0,index]
	int64_t ret = 0;
	while(index){
	    ret += arr[index];
	    index -= index & ((~index)+1);
	}
	return ret;
    }	
};

void visit(int64_t k, int64_t n, int64_t cur, unordered_map<int64_t,set<int64_t>> & children, Bit & bit, int64_t &ret){
    int64_t l = max((int64_t)0, cur-k-1);
    int64_t r = min(n, cur+k);
    int64_t temp = bit.query(r) - bit.query(l);
    // cout << cur << ": " << temp << endl;
    ret += temp;
    bit.update(cur, 1);
    for(auto const i: children[cur]){
	visit(k,n,i,children,bit,ret);
    }
    bit.update(cur, -1);
}

int64_t solve(int64_t root, unordered_map<int64_t,set<int64_t>> & children, int64_t n, int64_t k){
    Bit bit(n);
    int64_t ret = 0;
    visit(k, n, root, children, bit, ret);
    return ret;
}

int main(){
    int64_t n,k;
    cin >>n>>k;
    vector<int64_t> links(100'001,-1); //links[child id] ->  parent id
    unordered_map<int64_t,set<int64_t>> children;
    for(int64_t i=0;i<n-1;++i){
	int64_t p, c;
	cin >> p;
	cin >> c;
	links[c] = p;
	children[p].insert(c);
    }
    //find root
    int64_t root = -1;
    for(int64_t i=1;i<=n;++i){
	if(links[i]==-1){
	    root = i;
	    break;
	}
    }
    assert(root!=-1);
    // cout << "root : " << root << endl;
    cout << solve(root, children, n, k) << endl;
    
    return 0;
}
