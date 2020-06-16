#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <bitset>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int q;
    cin >> q;
    for( int i = 0; i < q; ++i ){
        long long x;
        cin >> x;
        //find number of a 
        
        uint64_t mask = 1;
        long long y = x;
        long long count = 1;
        //cout << "input: " << y << endl;
        y = y >> 1;
        while( y > 0 ){
            y = y >> 1;
            count++;
            mask = mask << 1;
        }
        mask = (mask << 1)-1;
        //cout << "mask: " << std::bitset<64>(mask) << endl;
        
        long long complement_x = (~x & mask );
        if( complement_x == 0 ){
            cout << 0 << endl;
        }else{
            //cout << "count"<<count <<endl;
            //cout << "complement: " << complement_x << endl;
            //cout << "complement: " << std::bitset<64>(complement_x) << endl;
            uint64_t ans = 0;
            //cout << "ans init: " << ans << endl;
            for( int i = count - 1; i >= 0; --i ){
                uint64_t compare = complement_x & ((uint64_t)1 << i);
                if( compare > 0 ){
                    //cout << "i:"<<i<<": " << std::bitset<64>(compare) << endl;
                    ans += (uint64_t)1 << i;
                }
            }
            cout << ans << endl;
        }
        
    }
    return 0;
}
