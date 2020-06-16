#include "chess_move.hpp"
#include "chess_engine.hpp"

bool chess_move::execute( chess_engine * e, bool & lost_white_queen, bool & lost_black_queen ){
    lost_white_queen = false;
    lost_black_queen = false;
    if( _kill_another ){
	e->add_piece_to_grave( _killed );
    }
    e->_pos_to_piece.erase( std::pair<int,int>( _y_pre, _x_pre ) );
    e->_pos_to_piece[ std::pair<int,int>( _y_post, _x_post ) ] = _piece;
    _piece->_y = _y_post;
    _piece->_x = _x_post;
    e->_count_move++;
    e->_is_turn_white = !e->_is_turn_white;
    _done = true;
    if( _kill_another && ( ( _killed->_colour == black ) && ( _killed->_type == queen ) ) ){
	lost_black_queen = true;
	return true;
    }else if( _kill_another && ( ( _killed->_colour == white ) && ( _killed->_type == queen ) ) ){
	lost_white_queen = true;
	return true;
    }else{
	return false;
    }
}
void chess_move::execute_inverse( chess_engine * e ){
    e->_pos_to_piece.erase( std::pair<int,int>( _y_post, _x_post ) );
    e->_pos_to_piece[ std::pair<int,int>( _y_pre, _x_pre ) ] = _piece;
    _piece->_y = _y_pre;
    _piece->_x = _x_pre;
    if( _kill_another ){
	_killed->_y = _y_post;
	_killed->_x = _x_post;
	e->add_piece_to_board( _killed );
    }
    e->_count_move--;
    e->_is_turn_white = !e->_is_turn_white;
}

void chess_move::record_child_result( bool black_queen_killed ){
    if( _piece->_colour == black ){
	_children_black_queen_killed |= black_queen_killed;
    }else if( _piece->_colour == white ){
	_children_black_queen_killed &= black_queen_killed;
    }
}
void chess_move::init_children_black_queen_killed( piece * p ){
    if( p->_colour == black ){
	_children_black_queen_killed = 0;
    }
    else if( p->_colour == white ){
	_children_black_queen_killed = 1;
    }
}
