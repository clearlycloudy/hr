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

list<pair<int,int> > chess_engine::generator_valid_positions_for_piece( piece* p ){
    list<pair<int,int> > ret;
    colour piece_colour;
    switch( p->_type ){
    case queen:
    case rook:
    {
	int y = p->_y;
	//fix y
	for( int x = p->_x-1; x >= 0; --x ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }
	}
	for( int x = p->_x+1; x < _dim_x; ++x ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }
	}
	//fix x
	int x = p->_x;
	for( int y = p->_y-1; y >= 0; --y ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }
	}
	for( int y = p->_y+1; y < _dim_y; ++y ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }
	}
	if( p->_type == rook ){
	    break;
	}
    }
    case bishop:
    {
	int y = p->_y-1;
	int x = p->_x-1;
	while( y >= 0 && x >= 0 ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }       
	    --y;
	    --x;
	}
	y = p->_y+1;
	x = p->_x+1;
	while( y < _dim_y && x < _dim_x ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }       
	    ++y;
	    ++x;
	}
	//----
	y = p->_y-1;
	x = p->_x+1;
	while( y >= 0 && x < _dim_x ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }       
	    --y;
	    ++x;
	}
	y = p->_y+1;
	x = p->_x-1;
	while( y < _dim_y && x >= 0 ){
	    if( is_position_occupied( y, x, piece_colour ) ){
		if( piece_colour != p->_colour ){
		    ret.push_back( pair<int,int>(y,x) );
		    break;
		}else{
		    break;
		}
	    }else{
		ret.push_back( pair<int,int>(y,x) );
	    }       
	    ++y;
	    --x;
	}
	break;
    }
    case knight:
    {
	vector<int> delta_y;
	delta_y.push_back( p->_y + 2 );
	delta_y.push_back( p->_y - 2 );
	vector<int> delta_x;
	delta_x.push_back( p->_x + 1 );
	delta_x.push_back( p->_x - 1 );
	for( auto it_y = delta_y.begin(), it_y_end = delta_y.end(); it_y!=it_y_end; ++it_y ){
	    for( auto it_x = delta_x.begin(), it_x_end = delta_x.end(); it_x!=it_x_end; ++it_x ){
		int y = *it_y;
		int x = *it_x;
		if( x >= 0 && y >= 0 && x < _dim_x && y < _dim_y ){
		    if( is_position_occupied( y, x, piece_colour ) ){
			if( piece_colour != p->_colour ){
			    ret.push_back( pair<int,int>(y,x) );
			}
		    }else{
			ret.push_back( pair<int,int>(y,x) );
		    }       
		}
	    }
	}
	//---
	delta_y.clear();
	delta_y.push_back( p->_y + 1 );
	delta_y.push_back( p->_y - 1 );
	delta_x.clear();
	delta_x.push_back( p->_x + 2 );
	delta_x.push_back( p->_x - 2 );
	for( auto it_y = delta_y.begin(), it_y_end = delta_y.end(); it_y!=it_y_end; ++it_y ){
	    for( auto it_x = delta_x.begin(), it_x_end = delta_x.end(); it_x!=it_x_end; ++it_x ){
		int y = *it_y;
		int x = *it_x;
		if( x >= 0 && y >= 0 && x < _dim_x && y < _dim_y ){
		    if( is_position_occupied( y, x, piece_colour ) ){
			if( piece_colour != p->_colour ){
			    ret.push_back( pair<int,int>(y,x) );
			}
		    }else{
			ret.push_back( pair<int,int>(y,x) );
		    }       
		}
	    }
	}
    }
    break;
    default:
	assert( 0 && "unexpected piece." );
    }
    return ret;
}
list<pair<int,int> > chess_engine::generator_valid_moves_for_piece( piece* p ){
    //todo
    list<pair<int,int> > moves = generator_valid_positions_for_piece( p );
    // auto it = moves.begin(), it_e = moves.end();
    // cout << "valid moves for piece: " << p->_type << endl;
    // while( it != it_e ){
    // 	cout << "y: " << it->first << ", x: " << it->second << endl;
    // 	++it;
    // }
    return moves;
}
bool chess_engine::move_piece( piece* p, int dest_y, int dest_x, chess_move & m ){
    if( _count_move >= _count_max_move ){
	return false;
    }
    m._piece = p;
    m._y_pre = p->_y;
    m._x_pre = p->_x;
    m._y_post = dest_y;
    m._x_post = dest_x;
    colour piece_colour;
    if( is_position_occupied( dest_y, dest_x, piece_colour ) ){
	if( piece_colour != p->_colour ){
	    m._kill_another = true;
	    piece * kill = _pos_to_piece[ std::pair<int,int>( dest_y, dest_x ) ];
	    m._killed = kill;
	}else{
	    return false;
	}
    }
    return true;
}
void chess_engine::add_piece_to_board( piece * p ){
    _pos_to_piece[ std::pair<int,int>(p->_y,p->_x) ] = p;
    _set_grave.erase(p);
    _set_alive.insert(p);
    if( p->_colour == white ){
	_set_white.insert(p);
    }else{
	_set_black.insert(p);
    }
}
void chess_engine::add_piece_to_grave( piece * p ){
    _set_grave.insert(p);
    _set_alive.erase(p);
    _pos_to_piece.erase( std::pair<int,int>(p->_y,p->_x) );
    
}
void chess_engine::print_pieces_on_board(){
    cout << "on board: " << endl;
    set<piece*>::iterator it = _set_alive.begin();
    set<piece*>::iterator it_end = _set_alive.end();
    while( it != it_end ){
	cout << "colour: " << (*it)->_colour << ", type: " << (*it)->_type << ", y: " << (*it)->_y << ", x: " << (*it)->_x << endl;
	++it;
    }
}
void chess_engine::print_pieces_in_grave(){
    cout << "in grave:: " << endl;
    set<piece*>::iterator it = _set_grave.begin();
    set<piece*>::iterator it_end = _set_grave.end();
    while( it != it_end ){
	cout << "colour: " << (*it)->_colour << ", type: " << (*it)->_type << ", y: " << (*it)->_y << ", x: " << (*it)->_x << endl;
	++it;
    }
}
void chess_engine::print_pos_to_piece_map(){
    cout << "position to piece map: " << endl;
    map<pair<int/*y*/,int/*x*/>, piece*>::iterator it = _pos_to_piece.begin();
    map<pair<int/*y*/,int/*x*/>, piece*>::iterator it_end = _pos_to_piece.end();
    while( it != it_end ){
	cout << "colour: " << it->second->_colour << ", type: " << it->second->_type << ", y: " << it->second->_y << ", x: " << it->second->_x << endl;
	++it;
    }
}
bool chess_engine::is_position_occupied( int y, int x, colour & piece_colour ){
    map<pair<int/*y*/,int/*x*/>, piece*>::iterator it_find = _pos_to_piece.find(pair<int,int>(y,x));
    if( it_find != _pos_to_piece.end() ){
	piece_colour = it_find->second->_colour;
	return true;
    }else{
	return false;
    }
}

void chess_engine::init_play(){
    // draw();
    _is_turn_white = true;

    //sentinel root move and piece to record result
    _root_piece._colour = black;
    _root_move._piece = &_root_piece;
    _root_move.init_children_black_queen_killed( &_root_piece );
    
    //push all initial possible moves by white onto the stack
    for( auto it = _set_white.begin(), it_e = _set_white.end(); it != it_e; ++it ){
	piece * p = *it;
	if( _set_alive.end() != _set_alive.find( p ) ){
	    list<pair<int,int> > valid_moves = generator_valid_moves_for_piece( p );
	    for( auto it_list = valid_moves.begin(), it_list_end = valid_moves.end(); it_list != it_list_end; ++it_list ){
		chess_move m;
		m.init_children_black_queen_killed(p);
		m._parent_move = &_root_move;
		int move_y = it_list->first;
		int move_x = it_list->second;
	        bool movable = move_piece( p, move_y, move_x, m );
		//add to stack of moves
		if( movable ){
		    _moves.push( m );
		}
	    }

	}
    }
}
bool chess_engine::play(){
    while( !_moves.empty() ){
	// cout <<"num moves on stack: " << _moves.size() << endl;
	// cout <<"count moves: " << _count_move << endl;
	chess_move & current_move = _moves.top();
	if( !current_move._done ){
	    bool white_queen = false, black_queen = false;
	    bool killed_queen = current_move.execute( this, white_queen, black_queen );
	    // cout << "====exe" << endl;
	    // draw();
	    _count_total++;
	    /*
	    cout << "count total moves: " << _count_total << endl;
	    cout << "count total queen kills white: " << _count_total_queen_kills_white << endl;
	    cout << "count total queen kills black: " << _count_total_queen_kills_black << endl;
	    */
	    // getchar();
	    if ( killed_queen ){
		if( white_queen ){
		    _count_total_queen_kills_white++;
		}else{
		    _count_total_queen_kills_black++;
		}
		continue; //stop and rewind stack
	    }
	}else{
	    //already executed, so invert move and pop it
	    current_move.execute_inverse( this );
	    //report result to its parent move
	    current_move._parent_move->record_child_result( current_move._children_black_queen_killed );
	    _moves.pop();
	    
	    //cout << "====popped" << endl;
	    //draw();
	    // getchar();
	    continue;
	}
	if( _is_turn_white ){
	    if( _set_white.empty() ){
		break;
	    }
	    //select a piece from white that is alive
	    for( auto it = _set_white.begin(), it_e = _set_white.end(); it != it_e; ++it ){
		piece * p = *it;
		if( _set_alive.end() != _set_alive.find( p ) ){
		    list<pair<int,int> > valid_moves = generator_valid_moves_for_piece( p );
		    for( auto it_list = valid_moves.begin(), it_list_end = valid_moves.end(); it_list != it_list_end; ++it_list ){
			chess_move m;
			m.init_children_black_queen_killed(p);
			m._parent_move = &current_move;
			int move_y = it_list->first;
			int move_x = it_list->second;
			bool movable = move_piece( p, move_y, move_x, m );
			if( !movable ){
			    break;
			}
			_moves.push( m );
		    }
		}
	    }
	}else{
	    if( _set_black.empty() ){
		break;
	    }
	    //select a piece from black that is alive
	    for( auto it = _set_black.begin(), it_e = _set_black.end(); it != it_e; ++it ){
		piece * p = *it;
		if( _set_alive.end() != _set_alive.find( p ) ){
		    list<pair<int,int> > valid_moves = generator_valid_moves_for_piece( p );
		    for( auto it_list = valid_moves.begin(), it_list_end = valid_moves.end(); it_list != it_list_end; ++it_list ){
			chess_move m;
			m.init_children_black_queen_killed(p);
			m._parent_move = &current_move;
			int move_y = it_list->first;
			int move_x = it_list->second;
			bool movable = move_piece( p, move_y, move_x, m );
			if( !movable ){
			    break;
			}
			_moves.push( m );
		    }
		}
	    }
	}
    }
    if( _root_move._children_black_queen_killed ){
	return true;
    }else{
	return false;
    }
}

void chess_engine::draw(){
    for( int i = 0; i < _dim_y; ++i ){
	for( int j = 0; j < _dim_x; ++j ){
	    auto it = _pos_to_piece.find( std::pair<int,int>(i,j) );
	    if( it != _pos_to_piece.end() ){
		switch( it->second->_type ){
		case queen:
		    cout << "Q";
		    break;
		case knight:
		    cout << "N";
		    break;
		case bishop:
		    cout << "B";
		    break;
		default:
		    cout << "R";
		    break;
		}
	    }else{
		cout << "-";
	    }
	}
	cout << endl;
    }
}
