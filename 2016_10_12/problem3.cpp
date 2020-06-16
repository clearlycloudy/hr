#include "chess_engine.hpp"
#include "chess_move.hpp"

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>
#include <list>
#include <stack>
#include <set>
using namespace std;


void parse_piece( colour piece_colour, list<piece> & p ){
    char t, c, r;
    cin >> t >> c >> r;
    piece a;
    switch( t ){
    case 'Q':
        a._type = queen;
        break;
    case 'N':
        a._type = knight;
        break;
    case 'B':
        a._type = bishop;
        break;
    case 'R':
        a._type = rook;
        break;
    default:
	assert( 0 && "invalid piece type" );
    }
    int y = r-'1';
    int x = c-'A';
    // cout << "piece: " << t << ", pos: " << y << ", " << x << endl;
    a._y = y;
    a._x = x;
    a._colour = piece_colour;
    p.push_back(a);
}
void init_game( chess_engine & b, list<piece> & p ){
    for( list<piece>::iterator it = p.begin(), it_end = p.end(); it != it_end; ++it ){
	b.add_piece_to_board( &(*it) );
    }
}
bool simulate_game( int moves, chess_engine & b ){
    //todo: return true if black loses in 6 turns no matter what move, otherwise return false
    b._count_max_move = moves;
    b.init_play();
    bool black_loses = b.play();
    return black_loses;
}
int main() {
    int g;
    cin >> g;
    for( int i = 0; i < g; ++i ){
        chess_engine b;
	b._dim_x = 4;
	b._dim_y = 4;
        list<piece> pieces;
	int num_white, num_black, m;
	cin >> num_white >> num_black >> m;
	b._count_max_move = m;
	for( int j = 0; j < num_white; ++j ){
	    parse_piece( white, pieces ); //get white pieces
	}
	for( int j = 0; j < num_black; ++j ){
	    parse_piece( black, pieces ); //get black pieces
	}
	init_game( b, pieces ); //setup pieces on board
	// b.print_pieces_in_grave();
	// b.print_pieces_on_board();
	// b.print_pos_to_piece_map();
	bool result = simulate_game( m, b );
	if(result)
	    cout << "YES" << endl;
	else
	    cout << "NO" << endl;
    }
    return 0;
}
