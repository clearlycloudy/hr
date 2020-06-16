#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <set>
#include <queue>
#include <bitset>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct item {
  uint32_t arr;
  int dim;
  int last_removed_is_white;
};

uint32_t remove_bit( uint32_t in, int pos ){
  uint32_t mask_lower = ((uint32_t)1 << pos) - 1;
  uint32_t mask_higher = ~(((uint32_t)1 << (pos+1)) - 1);
  uint32_t ret = (mask_lower & in) | (( mask_higher & in ) >> 1);
  return ret;
}

int gen_config( uint32_t arr, int dim, int bit_pos, item items [] ){
  //generate child configuration by removing a bit
  bool dimodd = (dim % 2) == 1;
  int mid = dim / 2;
  int bit_pos_mirror = dim - bit_pos - 1;
  bool bit_val = ((uint32_t)1 << bit_pos) & arr;
  bool bit_val_mirror = ((uint32_t)1 << bit_pos_mirror) & arr;
  if( dimodd && ( bit_pos == mid ) ){
    item i;
    i.dim = dim-1;
    i.arr = remove_bit( arr, bit_pos );
    i.last_removed_is_white = bit_val ? 1 : 0;    
    items[0] = i;
    return 1;
  }else{
    {
      item i;
      i.dim = dim-1;
      i.arr = remove_bit( arr, bit_pos_mirror );
      i.last_removed_is_white = bit_val_mirror ? 1 : 0;
      items[0] = std::move(i);
    }
    {
      item i;
      i.dim = dim-1;
      i.arr = remove_bit( arr, bit_pos );
      i.last_removed_is_white = bit_val ? 1 : 0;
      items[1] = std::move(i);
    }
    return 2;
  }
}

double f( item x, int k, unordered_map<uint64_t, double> & dictionary ){
  if( k <= 0 ){
    //finished leaf item
    return x.last_removed_is_white;
  }
  //dictionary lookup
  uint64_t memory_lookup = (( (uint64_t)x.dim << 32 ) | x.arr )| (((uint64_t)x.last_removed_is_white) << 40 );
  auto it_dict = dictionary.find( memory_lookup );
  if( it_dict != dictionary.end() ){
    double lookup_ret  = it_dict->second;
    // cout << "found existing item in dictionary: " << std::bitset<32>(x.arr) << ", size: " << x.dim << ", value: " << lookup_ret << endl;
    return lookup_ret;
  }
  int half_odd = x.dim % 2;
  int half = (x.dim/2) + half_odd;
  double level_expectation = 0;
  for( int i = 0; i < half; ++i ){
    int bit_pos = i;
    int bit_pos_mirror = x.dim - i - 1;
    double prob_mod;
    item candidates[2];
    int num_config = gen_config( x.arr, x.dim, bit_pos, candidates );
    double max_score = 0;      
    for( int u = 0; u < num_config; ++u ){
      item & j = candidates[u];
      double child_ret;
      int next_level = k - 1;
      if( next_level == 0 ){
	child_ret = j.last_removed_is_white;
      }else{
	child_ret = f( j, next_level, dictionary );
      }
      double score = child_ret / x.dim;
      if( max_score < score ){
	max_score = score;
      }
    }
    if( ! ( ( half_odd == 1 ) && i == half-1 ) ){
      level_expectation += max_score *2;
    }else{
      level_expectation += max_score;
    }
  }
  level_expectation += x.last_removed_is_white;
  //memorize
  double memory_val = level_expectation;
  uint64_t memory_key = ( ( (uint64_t)x.dim << 32 ) | x.arr ) | ( ((uint64_t)x.last_removed_is_white) << 40 );
  dictionary.insert(std::pair<uint64_t,double >(memory_key, memory_val));
  // cout << "new optimal: " << std::bitset<32>(x.arr) << ", size: " << x.dim << ", last removed is white: " << x.last_removed_is_white << ", expectation: " << level_expectation << ", memory insertion: " << std::bitset<64>(memory_key) << endl;
  // if( prunning.find(k) == prunning.end() ){
  //   prunning[k] = level_expectation;
  // }else{
  //   if( prunning[k] < level_expectation ){
  //     prunning[k] = level_expectation;
  //   }
  // }
  return level_expectation;
}

int main( int argc, char ** argv ) {
 
  //brief
  int dim, k;
  cin >> dim >> k;
  uint32_t in = 0;
  string str = "";
  cin >> str;
  //prep
  for( int a = 0; a < dim; ++a ){
    char c = str[a];
    if( c == 'W' ){
      in |= ((uint32_t)1 << (dim-a-1));
    }
  }
  double exp_scaling = 1;
  item i;
  i.arr = in;
  i.dim = dim;
  i.last_removed_is_white = 0;
  unordered_map<uint64_t,double> dictionary;
  dictionary.reserve(30000000);
  // unordered_map<int,int> prunning;
  dictionary[0] = 0;
  //kill
  double ans = f( i, k, dictionary );
  //reveal
  cout << std::setprecision(8) << ans << endl;
  return 0;
}
	 
