#include <bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin >> t;
    int dp[1001][4];
    int temp[1001];
    for(int i=0;i<t;++i){
        int n,a,b,c,d;
        cin>>n>>a>>b>>c>>d;
        for(auto & ii: dp){
            for(auto & jj:ii){
                jj=0;
            }
        }
        for(int j=1;j<=min(a,1000);++j){
            dp[j*1][0]=1;
        }
        for(int j=1;j<=min(b, 1000/2);++j){
            dp[j*2][1]=1;
        }
        for(int j=1;j<=min(c, 1000/5);++j){
            dp[j*5][2]=1;
        }
        for(int j=1;j<=min(d, 1000/10);++j){
            dp[j*10][3]=1;
        }
        for(int k=1;k<4;++k){
            for(int i=1;i<=n;++i){
                temp[i] = dp[i][k-1];
            }
            for(int i=n;i>=1;--i){ //target sum; use reverse order to avoid over compute on current iteration
                for(int j=0;j<=i;++j){ //slide over range [0,sum]
                    int v = i-j;
                    if(v!=0){
                        dp[i][k] += dp[v][k] * dp[j][k-1];
                    }
                }
            }
            for(int i=1;i<=n;++i){
                dp[i][k] += temp[i];
            }
        }
        cout << dp[n][3] << endl;
    }
    return 0;
}
