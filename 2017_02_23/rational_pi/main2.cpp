#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <utility>

using namespace std;

double pi = 3.1415926535897932384626433832795028841971693993751;

double get_error( long top, long bot ){
    return abs((double)top/bot - pi);
}

void get_rational( vector<long> & cf, long & top, long & bot ){
    long numer = 1;
    long denom = cf.back();
    for( int i = cf.size() - 2; i >= 0; --i ){
	// cout << "numer: " << numer << ", denom: " << denom << endl;
	numer = numer + denom * cf[i];
	//swap numerator and denominator
	if( i == 0 )
	    break;
	long swap = numer;
	numer = denom;
	denom = swap;
    }
    bot = denom;
    top = numer;
}

int main() {
    //continued fraction approximation
    for( int j = 2; j < 28; ++j ){
	double r = pi;
	vector<long> cf {};
	for( int i = 0; i < j; ++i ){
	    long n = (long)r; //truncate
	    r = r - n; //remainder
	    r = 1/r;
	    cf.push_back(n);
	}
	long top, bot;
	get_rational( cf, top, bot );
	cout << top << "/" << bot << endl;

	if( bot > 1e15 ){
	    cout << "limit reached." << endl;
	}
    }
    
    return 0;
}
