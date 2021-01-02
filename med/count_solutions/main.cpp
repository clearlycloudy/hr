#include<bits/stdc++.h>

using namespace std;

int64_t solve(int64_t a,int64_t b, int64_t c, int64_t d){
    //x^2-ax+y^2-by=0
    //for y \in [1,d]:
    // check if x = (a +/- sqrt(a^2-4(y^2-by)))/2 \in [1,c]
    int64_t ret = 0;
    for(int64_t y=1;y<=d;++y){
        auto f = [=](int64_t sign) -> int64_t {
                     return (a + sign * sqrt(a*a - 4*(y*y-b*y)))/2;
                 };
        int64_t choices [] = {f(1), f(-1)};
        ret = accumulate(choices,
                         unique(choices,choices+2),
                         ret,
                         [=](int acc, int64_t x) -> int {
                             bool ret = x>=1 && x<=c && x*x-a*x+y*y-b*y==0;
                             return acc + static_cast<int>(ret);
                         });
    }
    return ret;
}

int main(){
    int q; cin >> q;
    for(int _=0; _<q; ++_){
        int64_t a,b,c,d;
        cin>>a>>b>>c>>d;
        cout << solve(a,b,c,d) << endl;
    }
    return 0;
}
