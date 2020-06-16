#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

const int cluster_size = 2;

struct node {
    int val;
    int num;
    vector<int> nb;
    int prev;
};

class mycomp {
    public:
    bool operator()(std::pair<int,int> const & a, std::pair<int,int> const & b ){
        if(a.second > b.second ){
            return true;
        }else if( a.second < b.second ){
            return false;
        }else{
            if(a.first > b.first){
                return true;
            }else{
                return false;
            }
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int q,n;
    cin>>n>>q;
    vector<node> ns(n+1);
    for(int i = 1; i <= n; ++i ){
        cin >> ns[i].val;
        ns[i].num = i;
    }
    for( int i = 1; i <= n-1; ++i ){
        int x,y;
        cin>>x>>y;
        ns[x].nb.push_back(y);
        ns[y].nb.push_back(x);
    }
    vector<int> group(n+1,-1);
    map< pair<int,int>, pair<int,int> > group_connect; //map groupA,groupB -> nodeA, nodeB which connects the two groups
    
    //depth first search and divide graph into smaller clusters of 5x10E2 nodes
    {
        int group_num = 0;
        int num_nodes = 0;
        vector<bool> visited(n+1,false);
        vector<int> prev(n+1,-1);
        list<int> s;
        s.push_back(1);
        visited[1] = true;
        vector<int> last;
        while(!s.empty()){
            auto c = s.back();
            s.pop_back();
            ++num_nodes;
            if(num_nodes > cluster_size ){ //cutoff for each cluster based on cluster size
                num_nodes = 1;
                ++group_num;
                last.clear();
            }
            group[c] = group_num; //map current node index to a group cluster
            if( group[c] != group[prev[c]] && prev[c] != -1 ){
                group_connect[ {group[c],group[prev[c]]} ] = {c, prev[c]};
                group_connect[ {group[prev[c]],group[c]} ] = {prev[c],c};
            }
            last.push_back(c);
            for( auto neigh : ns[c].nb ){
                if(visited[neigh] == false){
                    visited[neigh] = true;
                    prev[neigh] = c;
                    s.push_back(neigh);
                }
            }            
            if( ns[c].nb.size() == 1 && group[c] != 0 ){ //reached leaf
                //cout << "leaf: " << c << ", group_num: " << group_num << endl;
                //cout << "last: " << last.size() << endl;
                //add the nodes to the last group
                for(auto h : last){
                    group_connect.erase({group[c],group[prev[c]]});
                    group_connect.erase({group[prev[c]],group[c]});
                    group[c] = group_num - 1;
                    if( group[c] != group[prev[c]] && prev[c] != -1 ){
                        group_connect[ {group[c],group[prev[c]]} ] = {c, prev[c]};
                        group_connect[ {group[prev[c]],group[c]} ] = {prev[c],c};
                    }
                    ++group_num;
                    //reset num_nodes for current group_num
                    num_nodes = 0;
                }
                last.clear();
            }
        }
    }
    map<int,vector<int>> group_nodes;
    for( int i = 1; i < group.size(); ++i ){
        if(group_nodes.find(group[i]) == group_nodes.end()){
            group_nodes[group[i]] = vector<int>();
        }
        group_nodes[group[i]].push_back(i);
    }
    map<pair<int,int>,int> group_path;
    map<pair<int,int>,int> group_best_path;
    vector<int> group_index;
    
    map<int,map<pair<int,int>,int>> intergroup_path;
    map<int,map<pair<int,int>,int>> intergroup_best_path;
    
    for(auto & i : group_nodes){
        group_index.push_back(i.first);
        //set default path values between nodes in each cluster
        for(auto j: i.second ){
            for(auto k: i.second ){
                if(k==j){
                    intergroup_path[i.first][{j,k}] = 0;
                    intergroup_best_path[i.first][{j,k}] = k;
                }else{
                    intergroup_path[i.first][{j,k}] = 9999999;
                }
            }
        }
        //set viable paths
        for(auto j: i.second ){
            for( auto k : ns[j].nb){
                intergroup_path[i.first][{j,k}] = 1;
                intergroup_best_path[i.first][{j,k}] = k;
            }
        }
        /*
        cout << "intergroup_path: " << i.first << ": " << endl;
        for( auto & m : intergroup_path[i.first] ){
            cout << m.first.first << ", " << m.first.second << ": " << m.second << endl;
        }
        cout << endl;
        */
        //calculate all pairwise paths between clusters
        for(auto b: i.second ){
            for(auto a: i.second ){
                for(auto c: i.second ){
                    if( intergroup_path[i.first][{a,c}] > (intergroup_path[i.first][{a,b}] + intergroup_path[i.first][{b,c}]) ){
                        intergroup_path[i.first][{a,c}] = intergroup_path[i.first][{a,b}] + intergroup_path[i.first][{b,c}];
                        intergroup_best_path[i.first][{a,c}] = intergroup_best_path[i.first][{a,b}];
                    }
                }
            }
        }
        /*
        cout << "intergroup best path: " << i.first << ": " << endl;
        for( auto & m : intergroup_best_path[i.first] ){
            cout << m.first.first << ", " << m.first.second << ": " << m.second << endl;
        }
        cout << endl;
        */
    }
    
    //set default path values between group clusters
    for(auto i : group_index ){
        for(auto j : group_index ){
            if(i==j){
                group_path[{i,j}] = 0;
                group_best_path[{i,j}] = i;
            }else{
                group_path[{i,j}] = 99999999;
            }
        }
    }
    
    //set viable inter group paths
    for(auto & i : group_connect){
        //cout << "group connection: " << i.first.first<< ", " << i.first.second;
        //cout << ", nodes: " << i.second.first << ", " << i.second.second << endl;
        group_path[{i.first.first,i.first.second}] = 1;
        group_best_path[{i.first.first,i.first.second}] = i.first.second;
    }
    /*
    cout << "group path:" << endl;
    for(auto & i : group_path ){
        cout << i.first.first << ", " << i.first.second << ": " << i.second << endl;
    }
    */
    //calculate all pairwise paths between clusters
    for(auto j : group_index ){
        for(auto i : group_index ){
            for(auto k : group_index ){
                if( group_path[{i,k}] > (group_path[{i,j}] + group_path[{j,k}]) ){
                    group_path[{i,k}] = group_path[{i,j}] + group_path[{j,k}];
                    group_best_path[{i,k}] = group_best_path[{i,j}];
                }
            }
        }
    }
    

    
    /*
    cout << "group path after calc.:" << endl;
    for(auto & i : group_path ){
        cout << i.first.first << ", " << i.first.second << ": " << i.second << endl;
    }
    
    cout << "group best path after calc.:" << endl;
    for(auto & i : group_best_path ){
        cout << i.first.first << ", " << i.first.second << ": " << i.second << endl;
    }
    */
    for(int i = 0; i < q; ++i ){
        //cout << "query: " << i << endl;
        vector<bool> visited(n+1,false);
        vector<int> prev(n+1,-1);
        int u,v,k;
        cin>>u>>v>>k;
        int node_current = u;
        int group_u = group[u];
        int group_v = group[v];
        //cout << "group_u: " << group_u << endl;
        //cout << "group_v: " << group_v << endl;
        
        int group_current = group_u;
        while(group_current!=group_v){
            int group_next = group_best_path[{group_current,group_v}];
            //cout << "next group: " << group_next << endl;
            
            //get connecting nodes between group clusters
            auto cluster_nodes = group_connect[{group_current,group_next}];
            //cout << "connecting node: " << cluster_nodes.first;
            //cout << ", " << cluster_nodes.second << endl;
            int node_u_dest = cluster_nodes.first;
            int node_v_start = cluster_nodes.second;
            //traverse local group cluster from node u to node u_dest:
            vector<int> bt_trail;
            while(node_current!=node_u_dest){
                int node_next = intergroup_best_path[group_current][{node_current,node_u_dest}];
                prev[node_next] = node_current;
                node_current = node_next;
            }
            //interconnection between group cluster
            visited[node_v_start] = true;
            prev[node_v_start] = node_u_dest;
            node_current = node_v_start;
            group_current = group_next;
        }
        //cout << "group destination reached" << endl;
        //perform one last group cluster search
        while(node_current!=v){
            int node_next = intergroup_best_path[group_current][{node_current,v}];
            prev[node_next] = node_current;
            node_current = node_next;
        }

        //backtrack found trail
        map<int,int> trail;
        trail[ns[v].val] = 1;
        int bt = v;
        while(prev[bt]!=-1){
            //cout << "backtrack node: " << bt << " " << endl;
            bt = prev[bt];
            auto it = trail.find(ns[bt].val);
            if(it==trail.end()){
                trail[ns[bt].val] = 1;
            }else{
                it->second += 1;
            }
        }
        //cout << "backtrack node: " << bt << " " << endl;
        //cout << "backtrack end-----" << endl;
        vector<pair<int,int>> arr;
        for(auto&j: trail){
            arr.push_back(j);
        }
        std::sort(arr.begin(),arr.end(),mycomp());
        auto & ans = arr[k-1];
        cout << ans.first << endl;
    }
    return 0;
}
