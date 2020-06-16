#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int main(){
  
  int n,k,x;

  long const M = 1000000000+7;
  
  cin >>n>>k>>x;
  
  // long dp[100001]={0};
  // dp[1] = 1;
  long total = 1;

  long dp[3] = {0};
  dp[1] = 1;

  for(int i=1;i<n-1;++i){//position
    // long total_new = total;
    // for(int j=1;j<=2;++j){//accumulated dp combinations
    //   long possible_candidates = (total-dp[j]+M) % M; //calc possible cnadidates coming into current number j
    //   total_new=(total_new-dp[j]+M)% M;
    //   dp[j]=possible_candidates;
    //   total_new=(total_new+possible_candidates)%M;
    // }
    // total=total_new;//update new total combinations for the current iteration position

    //simplify the above due to symmetry
    
    long total_new = total;
    long candidates1 = (total-dp[1]+M) % M;
    long candidates2 = (total-dp[2]+M) % M;
    total_new = (total_new-((dp[2]*(k-1))%M)+M-dp[1]+M)%M;
    total_new = (total_new+(candidates2*(k-1))%M+candidates1)%M;
    
    dp[2] = candidates2;
    dp[1] = candidates1;
    total = total_new;
  }

  if(x==1){
    cout<<(total-dp[1]+M)%M<<endl;
  }else{
    cout<<(total-dp[2]+M)%M<<endl;
  }
  
  return 0;
}
