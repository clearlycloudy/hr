#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>

std::vector<std::pair<int,int>> moves(int x, int y ){
  std::vector<std::pair<int,int>> v = { {x-2,y+1},{x-2,y-1},{x+1,y-2},{x-1,y-2} };
  auto it_end = std::remove_if( v.begin(), v.end(),
				[](auto a){ return a.first < 1 || a.first > 15 ||
					    a.second < 1 || a.second > 15; });
  v.resize( std::distance(v.begin(),it_end) );
  return v;
}

bool simulate(int x, int y, std::map<std::pair<int,int>,bool> & cache ){
  
  auto m = moves(x,y);
  if (m.empty()){
    return false; //no moves left, current player loses
  }

  auto mem = cache.find({x,y});
  if(mem!=cache.end()){
    return mem->second;
  }

  bool current_player_win = false;
  for(auto i: m){
    bool result = !simulate(i.first,i.second, cache );
    current_player_win |= result;
  }

  cache[{x,y}] = current_player_win;
  
  return current_player_win;
}

int main(){
  
  int q;

  std::cin >> q;

  std::map<std::pair<int,int>,bool> cache;
  
  for(int i=0;i<q;++i){
    int x,y;
    std::cin >> x >> y;
    bool ret = simulate(x,y,cache);
    if(ret){ std::cout << "First" << std::endl; }
    else{ std::cout << "Second" << std::endl; }
  }
  
  return 0;
}
