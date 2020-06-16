#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

class column {
    public:
    std::vector< std::set<int> > sides;
    int current_side;
    column(){
       sides = std::vector< std::set<int> >( 2, std::set<int>() );
	   current_side = 0;
	   sides.clear();
    }
    void flip(){
	if( current_side == 0 )
	    current_side = 1;
	else
	    current_side = 0;
    }
    std::set<int> & get_side(){
	return sides[current_side];
    }
    void calc_otherside( int m ){
	int other_side;
	if( current_side == 0 ){
	    other_side = 1;
	}else{
	    other_side = 0;
	}
	for( int i = 1; i <= m; ++i ){
	    if( sides[current_side].find(i) == sides[current_side].end() ){
		sides[other_side].insert(i);
	    }
	}
    }
    bool is_num_in_front_side( int num ){
	if( sides[current_side].find( num ) == sides[current_side].end() ){
	    return false;
	}else{
	    return true;
	}
    }
};

vector< column > cols;

int a;
int range = 0;
class column_comparator {
public:
    bool operator()( int & indexa, int & indexb ){
	column & ca = cols[indexa];
	column & cb = cols[indexb];
	int count_range_a = 0;
	int count_range_b = 0;
	for( auto i = a; i >= 1; --i ){
	    if( !ca.is_num_in_front_side(i) ){
		break;
	    }
	    ++count_range_a;
	}
	for( auto i = a; i >= 1; --i ){
	    if( !cb.is_num_in_front_side(i) ){
		break;
	    }
	    ++count_range_b;
	}
	// cout << "count_range_a: " << count_range_a << ", count_range_b: " << count_range_b << endl;
	range = std::max( range, std::max(count_range_a, count_range_b) );
	if( count_range_a > count_range_b ){
	    return true;
	}else{
	    return false;
	}
    }
};
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long n,m,q;
    cin >>n>>m>>q;
    vector<long> lookupsquare(m+1);
    for(int i=0;i<m+1;++i){
	lookupsquare[i] = i*i;
    }
    cols = vector< column > ( n + 1 );
    for(int i=1;i<=n;++i){
	int x;
	cin >>x;
	for(int j=0;j<x;++j){
	    int num;
	    cin >> num;
	    cols[i].get_side().insert(num);
	}
    }
    for(int i=1;i<=n;++i){
	cols[i].calc_otherside( m );
    }   
    // for(int i=1;i<=n;++i){
    // 	cout << i << ": ";
    // 	for( auto & j : cols[i].get_side() ){
    // 	    cout << j << " ";
    // 	}
    // 	cout << endl;
    // 	cout << "back side: ";
    // 	cols[i].flip();
    // 	for( auto & j : cols[i].get_side() ){
    // 	    cout << j << " ";
    // 	}
    // 	cout << endl;
    // 	cols[i].flip();
    // }

    //query starts
    for(int i=0;i<q;++i){
	// cout << "query " << i << endl;;
    	int l,r;
    	cin>>l>>r;
        set<int> col_index{};
	set<int> final_nums{};
	for( int j = l; j<=r; ++j ){
	    col_index.insert(j);
	}
	a = m;
	while( a >= 1 && !col_index.empty() && final_nums.size() < m ){
	    range = 1;
	    //flip cards to get the highest number on the front visible side
	    for( auto j : col_index ){
		auto & c = cols[j];
		if( !c.is_num_in_front_side( a ) ){
		    c.flip();
		}
	    }
	    //sort the card with the biggest contiguous range starting from a
	    vector<int> col_index_vec( col_index.begin(), col_index.end() );
	    // cout << "col_index_vec: ";
	    // for( auto h : col_index_vec ){
	    // 	cout << h << " ";
	    // }
	    // cout << endl;
	    std::sort( col_index_vec.begin(), col_index_vec.end(), column_comparator() );
	    // cout << "sorted: " << endl;
	    // for( auto j : col_index_vec ){
	    // 	cout << j << " ";
	    // }
	    // cout << endl;
	    //collect numbers from the highest sorted column
	    final_nums.insert( cols[ col_index_vec[0] ].get_side().begin(), cols[ col_index_vec[0] ].get_side().end() );
	    //remove first column in the sorted vector
	    col_index.erase( col_index_vec[0] );

	    // cout << "collected numbers: ";
	    // for( auto h : final_nums ){
	    // 	cout << h << " ";
	    // }
	    // cout << endl;
	    // cout << "range: " << range << endl;
	    // a = a - range;
        int temp = a;
        while( final_nums.find(temp) != final_nums.end() ){
            --temp;
        }
        a = temp;
	    // cout << "a updated: " << a << endl;
	}
	// cout << "final numbs: ";
	long ans = 0;
	for( auto h : final_nums ){
	    // cout << h << " ";
	    ans += h*h;
	}
	// cout << endl;
	cout << ans << endl;
    }
    return 0;
}
