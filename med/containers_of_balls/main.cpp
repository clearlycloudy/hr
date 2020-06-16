#include <iostream>
#include <algorithm>

long containers [101];
long types [101];

int main(){
  int q;
  std::cin >> q;
  
  for(int i=0;i<q;++i){

    std::fill(types,types+101,0);
    std::fill(containers,containers+101,0);

    int n;
    std::cin >> n;
    
    for(int j=0;j<n;++j){

      for(int k=0;k<n;++k){
	long val;
	std::cin >> val;
	
	containers[j]+=val;
	types[k]+=val;
      }
    }

    std::sort(containers,containers+n);
    std::sort(types,types+n);

    bool bad = false;
    for(int j=0;j<n;++j){
      if(containers[j]!=types[j]){
	bad = true;
	break;
      }
    }
    if(bad){
      std::cout << "Impossible" << std::endl;
    }else{
      std::cout << "Possible" << std::endl;
    }
  }
  return 0;
}
