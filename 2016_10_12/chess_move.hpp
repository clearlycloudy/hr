#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

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

class piece;
class chess_engine;

class chess_move{
public:
    chess_move * _parent_move;
    piece * _piece;
    int _y_pre;
    int _x_pre;
    int _y_post;
    int _x_post;
    bool _kill_another = false;
    piece * _killed;
    bool execute( chess_engine * e, bool & lost_white_queen, bool & lost_black_queen ); //return true if killed the black queen
    void execute_inverse( chess_engine * e );
    bool _done = false;
    bool _children_black_queen_killed; //initialize to 0 for black piece, 1 for white piece
    void init_children_black_queen_killed( piece * p ); //initialize to 0 for black piece, 1 for white piece
    void record_child_result( bool black_queen_killed );
};

#endif
