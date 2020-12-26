#include<bits/stdc++.h>

using namespace std;

void dfs(map<int,set<int>> & con,
	 map<pair<int,int>,int> & weight,
	 map<int,bool> & machine,
	 int parent,
	 int cur,
	 map<int,int> & costs,
	 int & ret){

    for(auto i: con[cur]){
	if(i!=parent){
	    dfs(con,weight,machine,cur,i,costs,ret);
	}
    }
    
    //process this node
    
    if(machine[cur]){
	for(auto i: con[cur]){
	    if(i!=parent && machine[i]){
		ret += costs[i];
	    }
	}
	costs[cur] = weight[{parent,cur}];
    }else{
	vector<int> temp;
	for(auto i: con[cur]){
	    if(i!=parent && machine[i]){
		temp.push_back(costs[i]);
	    }
	}
        sort(temp.begin(),temp.end());
	if(temp.size()>0){
	    for(int j=0;j<temp.size()-1;++j){
		ret += temp[j];
	    }
	    costs[cur] = min(weight[{parent,cur}],temp.back());
	    machine[cur] = true;
	}else{
	    costs[cur] = 0;
	}
    }
}

int solve(map<int,set<int>> & con,
	  map<pair<int,int>,int> & weight,
	  map<int,bool> & machine){
    map<int,int> costs;
    int ret = 0;
    dfs(con,weight,machine,-1,0, costs, ret);
    return ret;
}

int main(){
    int n, k;
    cin>> n >> k;
    map<int,set<int>> con;
    map<pair<int,int>,int> weight;
    map<int,bool> machine;
    for(int i=0;i<n;++i){
	machine[i]=false;
    }
    for(int i=0;i<n-1;++i){
	int a, b, t;
	cin >> a >> b >> t;
	assert(a!=b);
	con[a].insert(b);
	con[b].insert(a);
	weight[{a,b}] = t;
	weight[{b,a}] = t;
    }
    for(int i=0; i<k; ++i){
	int m;
	cin >> m;
	machine[m]=true;
    }
    cout << solve(con,weight,machine) << endl;
    return 0;
}
