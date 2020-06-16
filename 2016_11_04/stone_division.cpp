#include <cmath>
#include <cstdio>
#include <list>
#include <iostream>
#include <list>
#include <utility>
#include <algorithm>
using namespace std;

list< pair<long long, long long> > game_rule( long long pile, list<long long> factors ){
    list< pair<long long, long long > > arr {};
    for( auto i : factors ){
	long long num = i;
	if( (pile % num) == 0 ){
	    long long new_num = pile/num;
	    arr.push_back( pair<long long, long long>( num, new_num ) );
	}
    }
    return arr;
}

bool nextmove( bool turn, list<long long> factors, long long pile ){
    list< pair<long long, long long> > validpartitions = game_rule( pile, factors );
    if( validpartitions.size() == 0 ){
	//base case
	return !turn; //win for the other player
    }else{
	list<bool> bool_arr{};
	for( auto i : validpartitions ){
	    long long num = i.first;
	    long long new_num = i.second;
	    cout << "num: " << num <<", new_num: " << new_num << endl;
	    bool result = nextmove( !turn, factors, new_num );
	    if( result == !turn ){
		//odd number of moves for !turn to win
		if( num % 2 == 1 ){
		    //odd number of sets
		    result = result;
		}else{
		    //even number of sets
		    result = !result;
		}
	    }else {
		//even number of moves for !turn to win
		result = result;
	    }
	    bool_arr.push_back( result );
	}
	bool ret;
	if( turn ){
	    //first player's turn
	    ret = true;
	    for( auto i : bool_arr ){
		ret &= i; //AND
	    }
	}else{
	    //second player's turn
	    ret = false;
	    for( auto i : bool_arr ){
		ret |= i; //OR
	    }
	}
	return ret;
    }
}

int main() {
    long long pile;
    int m;
    cin >> pile;
    cin >> m;
    list<long long> factors;
    for( int i = 0; i < m; ++i ){
	long long num;
	cin >> num;
	factors.push_back(num);
    }
    bool turn = true; //first player turn
    bool first_wins = nextmove( turn, factors, pile );
    cout << ( first_wins ? "First" : "Second" ) << endl;

    return 0;
}
