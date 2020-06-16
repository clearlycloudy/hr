#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <iterator>
#include <map>
using namespace std;

class bitarray{
public:
    list<short> bits;
    string to_string(){
        string s;
        s.resize(bits.size());
        auto it = bits.begin();
        for( int i = 0; i < bits.size(); ++i){
            bool bit = *it;
            s[i] = (bit == 1 ? '1' : '0');
            it++;
        }
        return s;
    }
    void set( int length ){
        bits.clear();
        bits.push_back(1);
        for( int i = 0; i < length-1; ++i ){
            bits.push_back(0);
        }
    }
    void my_xor(){
        auto last = *bits.rbegin();
        
        auto it = bits.rbegin();
        auto it_prev = bits.rbegin();
        ++it_prev;
        for( int i = 1; i < bits.size(); ++i ){
            *it ^= *it_prev;
            //cout << "bit: " << *it <<", ";
            it++;
            it_prev++;
        }
        //cout << endl;
        
        auto it_front = bits.begin();
        *it_front = last ^ *it_front;
    }
};

vector<unsigned int> xor_numbers( string pattern, vector<unsigned int> & nums ){
    vector<unsigned int> ans(pattern.size(),0);
    for( int i = 0; i < pattern.size(); ++i ){
        int offset = i;
        for( int j = 0; j < pattern.size(); ++j ){
            if( pattern[j] == '1' ){
                int index_adjust = (offset + j)%pattern.size();
                ans[i] = ans[i] ^ nums[index_adjust];
            }
        }
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<unsigned int> nums(n);
    for( auto & i : nums ){
        cin >> i;
    }
    
    bitarray ba;
    //set starting pattern
    ba.set(n);
    string bit_pattern = ba.to_string();
    //cout << bit_pattern << endl;
    unsigned long index = 0;
    map<string,unsigned long> memory;
    memory[bit_pattern] = index;
    map<unsigned long,string> memory_inv;
    memory_inv[index] = bit_pattern;
    ++index;
    
    string pat;
    unsigned int period;
    unsigned int pattern_start_index;
    while(true){
        //for( int r = 0; r < 20; ++r ){
        if( index >= m ){
            break;
        }
        ba.my_xor();
        pat = ba.to_string();
        //search for existing pattern
        auto it_find = memory.find(pat);
        if( it_find != memory.end() ){
            period = index - it_find->second;
            pattern_start_index = it_find->second;
            //cout << "found pattern at index: " << pattern_start_index <<", period: " << period << endl;
            break;
        }
        //cout << pat << endl;
        memory[pat] = index;
        memory_inv[index] = pat;
        ++index;    
    }
    
    string final_pattern;
    if( index == m ){
        final_pattern = pat;
    }else{
        //calculate pattern via modulo period
        unsigned long A = m - 1 - pattern_start_index;
        unsigned long B = A % period;
        unsigned long C = B + pattern_start_index;
        final_pattern = memory_inv[C];
    }
    
    //cout << "final pattern: " << final_pattern << endl;
    
    vector<unsigned int> result = xor_numbers( final_pattern, nums );
    for( int v = 0; v < result.size(); ++v ){
        cout << result[v];
        if( v < result.size()-1 ){
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
