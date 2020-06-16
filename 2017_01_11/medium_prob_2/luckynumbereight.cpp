#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <list>
using namespace std;

long long arr[200000];
long long divisible3[10][10][10];
long long divisible2[10][10];
long long divisible1[10];
long long divisible_single[10];
long long divisible_double[10][10];
long long count1[200000][10];
long long count2[200000][10][10];

long long exponentiation_mod( long long base, long long exp, long long mod ){
  long long res = 1;
  while(exp>0){
    if(exp%2==1) res=(res*base) % mod;
    base=(base*base) % mod;
    exp/=2;
  }
  return res % mod;
}

int main() {
  //brief
  int n;
  cin >> n;
  string str;
  cin >> str;
  
  //prep
  memset( divisible3, 0, sizeof(divisible3) );
  memset( divisible2, 0, sizeof(divisible2) );
  memset( divisible1, 0, sizeof(divisible1) );
  memset( divisible_single, 0, sizeof(divisible_single) );
  memset( divisible_double, 0, sizeof(divisible_double) );
  memset( count1, 0, sizeof(count1) );
  memset( count2, 0, sizeof(count2) );
  int num = 0;
  while( num < 1000 ){
    int one = num % 10;
    int ten = (num/10) % 10;
    int hun = (num/100) % 10;
    divisible3[one][ten][hun] = 1;
    divisible2[one][ten] = 1;
    divisible1[one] = 1;
    if( num < 100 ){
      divisible_double[one][ten] = 1;
    }
    num += 8;
  }
  divisible_single[8] = 1;
  divisible_single[0] = 1;
  
  for( int i = 0; i < n; ++i ){
    arr[i] = str[i]-'0';
    count1[i][arr[i]] = 1;
  }

  long long ans = 0;
  long long ans_double = 0;
  
  //kill
  //partial sum from right
  for( int i = n-1; (i-1) >= 0; --i ){
    for( int j = 0; j < 10; ++j ){
      count1[i-1][j] = ( count1[i-1][j] + count1[i][j] ) % 1000000007;
    }
  }
  // for( int i = 0; i < n; ++i ){
  //   for( int j = 0; j < 10; ++j ){
  //     if( count1[i][j] > 0 ){
  //     	cout << i << ", " << j << ": " << count1[i][j] << endl;
  //     }
  //   }
  // }

  //single digit divisiblity
  ans = ( ans + ( count1[0][8] % 1000000007) ) % 1000000007;
  ans = ( ans + ( count1[0][0] % 1000000007) ) % 1000000007;
  //cout << "single digit divisibility: " << ans << endl;
  
  // cout << "===" <<endl;
  //2nd pass from right to find suitable divisible digits
  for( int i = n-2; i >= 0; --i ){
    for( int j = 0; j < 10; ++j ){
      if( count1[i+1][j] > 0 ){
	int dig_one = j;
	int dig_ten = arr[i];
	//test for >=3 digit divisibility
	if( divisible1[dig_one] > 0 ){
	  if( divisible2[dig_one][dig_ten] > 0 ){
	    // cout << "here: " << i <<": " << dig_ten << dig_one<< endl;
	    count2[i][dig_one][dig_ten] = (count2[i][dig_one][dig_ten] + count1[i+1][j]) % 1000000007;
	  }
	}
	//account for double digit divisibility
	if( divisible_double[dig_one][dig_ten] > 0 ){
	  ans = (ans + count1[i+1][j]) % 1000000007;
	  // ans_double = (ans_double+ count1[i+1][j]) % 1000000007;
	}
      }
    }
  }
  //cout << "double digit divisibility: " << ans_double << endl;
  
  for( int i = n-2; i >= 0; --i ){
    for( int j = 0; j < 10; ++j ){
      for( int k = 0; k < 10; ++k ){
	count2[i][j][k] = ( count2[i][j][k] + count2[i+1][j][k] ) % 1000000007;
      }
    }
  }
  // for( int i = 0; i < n; ++i ){
  //   for( int j = 0; j < 10; ++j ){
  //     for( int k = 0; k < 10; ++k ){
  // 	if( count2[i][j][k] > 0 )
  // 	  cout << i << ", " << j << ", " << k << ": " << count2[i][j][k] << endl;
  //     }
  //   }
  // }

  //3rd pass from right to find the final suitable divisible digits
  for( int i = n-3; i >= 0; --i ){
    for( int j = 0; j < 10; ++j ){
      for( int k = 0; k < 10; ++k ){
	int dig_one = j;
	int dig_ten = k;
	int dig_hun = arr[i];
	if( divisible1[dig_one] > 0 ){
	  if( divisible2[dig_one][dig_ten] > 0 ){
	    if( divisible3[dig_one][dig_ten][dig_hun] > 0 ){
	      if( count2[i+1][dig_one][dig_ten] > 0 ){
		long long comb = exponentiation_mod( 2, i, 1000000007 ) % 1000000007;
		comb = ( comb * count2[i+1][dig_one][dig_ten] ) % 1000000007;
		ans = ( ans + comb ) % 1000000007;
		// cout << "here: " << i <<": " << dig_hun << dig_ten << dig_one<< ", comb: " << comb << endl;
	      }
	    }
	  }
	}
      }
    }
  }
  cout << ans << endl;
  
  return 0;
}
	 
