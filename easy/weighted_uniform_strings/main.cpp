#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_set>

int main(){
  std::string st;
  int q;
  int prev = -1;
  int count = 0;

  std::cin >> st;

  std::unordered_set<int> ss;
  
  for(int i=0;i<st.size();++i){
    if(prev==st[i]){
      count++;
    }else{
      prev=st[i];
      count=1;
    }
    int v = count*(st[i]-'a'+1);
    ss.insert(v);
  }
  
  std::cin>>q;
  for(int i=0;i<q;++i){
    int val;
    std::cin>>val;
    if(ss.find(val)!=ss.end()){
      std::cout << "Yes"<<std::endl;
    }else{
      std::cout << "No"<<std::endl;
    }
  }
  
  return 0;
}
