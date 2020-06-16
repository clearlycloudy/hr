
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
#include <utility>

using namespace std;

bool is_prime( long a ){
    if( a >= 6 ){
	if( a % 2 == 0 ){
	    // cout << "not prime: " << a << endl;
	    return false;
	}
	if( a % 3 == 0 ){
	    // cout << "not prime: " << a << endl; 
	    return false;
	}
	if( a % 4 == 0 ){
	    // cout << "not prime: " << a << endl; 
	    return false;
	}
	if( a % 5 == 0 ){
	    // cout << "not prime: " << a << endl; 
	    return false;
	}
    }
    long bound = sqrt(a);
    for( long i = 4; i <= bound; ++i ){
	long rem = a % i;
	// cout << "rem: " << a << "%" << i << ": " << rem << endl;
	if( rem == 0 ){
	    return false;
	}
    }
    // cout << "prime: " << a << endl;
    return true;
}

int main(){
   
    long start,end;
    cin >> start >> end;
    list<long> nums {};
    long i = start;
    long ones = start % 10;
    long add_cycle; //starting point of addition cycle
    if( ones <= 2 ){
	i = i - ones + 2;
	add_cycle = 0;
    }else if( ones <= 3 ){
	i = i - ones + 3;
	add_cycle = 1;
    }else if( ones <= 5 ){
	i = i - ones + 5;
	add_cycle = 2;
    }else if( ones <= 7 ){
	i = i - ones + 7;
	add_cycle = 3;
    }else{
	i = i + 10;
	i = i - ones + 2;
	add_cycle = 0;
    }
    long num_prime = 0;
    vector<long> add { 1, 2, 2, 5 }; //do addition with a cycle period of 4
    long digit = 1;
    long count = 0;
    while( i <= end ){
	if( i > 10 ){
	    if( i % 10 == 2 &&
		i % 10 == 5 ){
		i += add[add_cycle];
		add_cycle = (add_cycle + 1)%4;
		continue;
	    }
	}
	bool not_prime = false;
	long j = i;
	while( j > 0 ){
	    if( j%10 != 2 &&
		j%10 != 3 &&
		j%10 != 5 &&
		j%10 != 7 ){
		not_prime = true;
		break;
	    }
	    j = j/10;
	}
	if( !not_prime ){
	    // nums.push_back(i);
	    ++count;
	}
	i += add[add_cycle];
	add_cycle = (add_cycle + 1)%4;
    }

    cout << "count: " << count << endl;
    
    // for( auto it = nums.begin(), it_e = nums.end(); it!= it_e; ++it ){
    // 	if( is_prime( *it ) ){
    // 	    ++num_prime;
    // 	}
    // }    
    // cout << num_prime << endl;
}
