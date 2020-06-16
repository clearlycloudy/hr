#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

pair<char, bool> add_str( char a, char b ){
    int temp = (int)(a - '0') + (int)(b - '0');
    bool carry = (temp >= 10);
    char c = (char)(temp % 10) + '0';
    return { c, carry };
}

string add_string( string a, string b ){
    if( a.size() < b.size() ){
	string temp( b.size()-a.size(), '0');
	a.insert( 0, temp );
    } else if( b.size() < a.size() ){
	string temp( a.size()-b.size(), '0');
	b.insert( 0, temp );
    }
    
    string ret;
    bool carry_prev = false;
    for( int i = a.size()-1; i >= 0; --i ){
	auto result = add_str( a[i], b[i] );
	char digit = result.first;
	bool carry_current = result.second;
	if(carry_prev){
	    carry_prev = false;
	    auto result2 = add_str( digit, '1' );
	    digit = result2.first;
	    carry_current |= result2.second;
	}
	carry_prev = carry_current;
	ret += string(1, digit );
    }
    if( carry_prev ){
	ret += "1";
    }
    std::reverse(ret.begin(),ret.end());
    return ret;
}

string compute( string const & s ){
    string ret = string(1, s[0]);
    for( int i = 1; i < s.size(); ++i ){
	ret = add_string( ret, string(1,s[i]) );
    }
    return ret;
}

int main(){

    string n;
    int k;
    cin >> n >> k;

    string sum = compute(n);
    string temp = sum;

    for(int i = 0; i < k-1; ++i ){
	sum = add_string( sum, temp );
    }
    
    while( sum.size() > 1 ){
	sum = compute( sum );
    }
    cout << sum << endl;
    
    return 0;
}
