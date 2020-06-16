#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

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


enum piece_type{
    queen = 0,
    knight,
    bishop,
    rook,
};

enum colour{
    white = 0,
    black,
};

class piece{
public:
    int _y;
    int _x;
    piece_type _type;
    colour _colour;
};

class chess_engine{
public:
    int _count_move = 0;
    int _count_max_move;
    int _count_total = 0;
    int _count_total_queen_kills_white = 0;
    int _count_total_queen_kills_black = 0;
    int _dim_y;
    int _dim_x;
    bool _is_turn_white;
    std::set<piece*> _set_grave;
    std::set<piece*> _set_alive;
    std::stack<chess_move> _moves;
    std::set<piece*> _set_white;
    std::set<piece*> _set_black;
    std::map<std::pair<int/*y*/,int/*x*/>, piece*> _pos_to_piece;
    std::list<std::pair<int,int> > generator_valid_positions_for_piece( piece* p );
    std::list<std::pair<int,int> > generator_valid_moves_for_piece( piece* p );
    bool move_piece( piece* p, int dest_y, int dest_x, chess_move & m );
    void add_piece_to_board( piece * p );
    void add_piece_to_grave( piece * p );
    void print_pieces_on_board();
    void print_pieces_in_grave();
    void print_pos_to_piece_map();
    bool is_position_occupied( int y, int x, colour & piece_colour );
    bool play();
    void init_play();
    void draw();

    //sentinel root move and piece to record result
    chess_move _root_move;
    piece _root_piece;
};

#endif
