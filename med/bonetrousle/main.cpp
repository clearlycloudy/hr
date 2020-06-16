#include <iostream>
#include <vector>
#include <cassert>
#include <ios>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t,n,k,b;
  cin >> t;
  for(int h = 0;h<t;++h){
    cin >>n>>k>>b;
    long long sum = 0;
    long long bound_l = 0;
    long long bound_h = 0;      
    for(long long j = 1; j<=b; j++){
      bound_l +=j;
    }
    for(long long j = k-b+1; j<=k; j++){
      bound_h +=j;
      if(bound_h >= n) {
	break;
      }
    }
    long long bound_max = k;
    long long count = 0;
    if( bound_l <= n && bound_h >= n ){
      sum = b*(long long)(b+1)/2;
      for(int i=b; i>=1;--i){
	if( sum - i + bound_max < n ){ //set to max possible value 
	  sum -= i;
	  sum += bound_max;
	  bound_max--; //decrease max
	  ++count;
	}else{
	  //make numbers add up to desired value n
	  for(long long j=bound_max+1;j<=k;++j){
	    cout << j << " ";
	  }
	  cout << n-(sum-i);
	  for(long long j=1;j<=b-count-1;++j){
	    cout << " " << j;
	  }
	  cout << "\n";
	  break;
	}
      }
    }else{
      cout << "-1" << "\n";
    }
  }
  return 0;
}
