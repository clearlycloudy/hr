#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;
int main(){
    i64 g,n;
    cin>>g;
    for(int i=0;i<g;++i){
	cin>>n;
	i64 parity=0;
	i64 m=0;
	for(int j=0;j<n;++j){
	    i64 v;
	    cin>>v;
	    if(v>m){
		m=v;
		parity=(parity+1)%2;
	    }
	}
	cout << (parity%2==1 ? "BOB" : "ANDY") << endl;
    }
    return 0;
}
