#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'primeQuery' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER_ARRAY first
 *  3. INTEGER_ARRAY second
 *  4. INTEGER_ARRAY values
 *  5. INTEGER_ARRAY queries
 */

struct node {
    set<int> children;
    int value;
};
unordered_map<int,node> build_tree(int const n, vector<int> const & first, vector<int> const & second, vector<int> const & values){
    map<int, set<int>> links;
    for (int i = 0; i < first.size(); ++i) {
	auto a = first[i];
	auto b = second[i];
	links[a].insert(b);
	links[b].insert(a);
    }
    unordered_map<int, node> t;
    vector<int> q;
    q.push_back(1);
    t[1] = node{ {}, values[0] };

    while (!q.empty()) {
	auto item = q.back();
	q.pop_back();
	if (links.find(item) != links.end()) {
	    for (auto j : links[item]) {
		if (t.find(j) == t.end()) {
		    q.push_back(j);
		    t[item].children.insert(j);
		    t[j] = node { {}, values[j-1] };
		}
	    }
	}
    }
    return t;
}

bool sieve[100001];

void build_sieve(){
    for(int i = 0; i < 100001; ++i){
	sieve[i] = false; //mark as prime
    }
    int i = 2;
    while(i<100001){
	if(sieve[i] == true){
	    ++i;
	    continue;
	}
	bool is_prime = true;
	for(int j = 2; j <= i/2; ++j ){
	    if(i%j == 0){
		is_prime = false;
		break;
	    }
	}
	if(is_prime){
	    for(int j = i + i; j < 100001; j = j + i ){
		sieve[j] = true; //mark as not a prime
	    }
	}
	++i;
    }
    sieve[1] = true; //consider 1 not as a prime
}
vector<int> primeQuery(int n, vector<int> first, vector<int> second, vector<int> values, vector<int> queries) {
    build_sieve();

    auto t = build_tree(n,first,second,values);

    unordered_map<int, int> prime_count;
    for(auto & i: t){
	int node_num = i.first;
	if(sieve[i.second.value] == 0){
	    prime_count[node_num] = 1;
	} else {
	    prime_count[node_num] = 0;
	}
    }

    //aggregate number of primes in build_tree
    vector<int> q;
    q.push_back(1);
    unordered_set<int> processed;
    while(!q.empty()){
	auto item = q.back();
	if(processed.find(item) == processed.end()){
	    processed.insert(item);
	    for (auto &c : t[item].children) {
		q.push_back(c);
	    }
	} else {
	    for (auto &c : t[item].children) {
		auto num_primes = prime_count[c];
		prime_count[item] += num_primes;
	    }
	    q.pop_back();
	}
    }

    vector<int> ret;
    for(auto i : queries){
	ret.push_back(prime_count[i]);
    }
    return ret;
}
