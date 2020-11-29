#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define FOR(i,n) for(int (i)=0;(i)<(n);++(i))

typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vector<ull> > matrix;
const int MOD = 1000000000 + 7;

matrix mmul(matrix M1, matrix M2)
{
   matrix R(15);
   FOR(i, 15)
   {
      R[i].assign(15, 0);
      FOR(j, 15)
      {       
         FOR(k, 15)
         {
            R[i][j] = (R[i][j] + M1[i][k] * M2[k][j]) % MOD;
         }
      }
   }
   return R;
}

matrix mpow(matrix M, ull n)
{
   if(n == 0)
   {
      matrix M1(15);
      FOR(i, 15)
      {
         M1[i].assign(15, 0);
         FOR(j, 15)
         {
            if(i == j)
               M1[i][j] = 1;
         }
      }
      return M1;
   }
   else if(n % 2 == 0)
   {
      matrix R = mpow(M, n / 2);
      return mmul(R, R);
   }
   else
   {
      matrix R = mpow(M, n - 1);
      return mmul(R, M);
   }
}

template<class T>
ostream& operator<<(ostream &o, vector<vector<T>> const & a){
    for(auto &i: a){
	for(auto j: i){
	    o << j << " ";
	}
        o << endl;
    }
    return o;
}


ull V[15];
int main()
{
//GENERATE M
   matrix M(15);
   FOR(i, 15)
   {
      M[i].assign(15, 0);
      FOR(j, 15)
      {
         if(i + 1 == j)
         {
            M[i][j] = 1;
         }
      }
   }
//INPUT
   int k;
   ull n;
   vi jumps;
   vi res;
   ull tmp;

   cin >> n;
   cin >> k;
   FOR(i, 15)
   {
      V[i] = 0;
   }      
   M[14].assign(15, 0);
   FOR(i, k)
   {
      cin >> tmp;
      M[14][14 - tmp + 1] = 1;  
   }      
   FOR(i, 15)
   {
      FOR(j, i + 1)
      {
         if(M[14][14 - j] == 1) 
         {
            if(i - j == 0)
            {
               V[i]++;
            }
            else 
            {
               V[i] += V[i - j - 1];
            }
         }
      }
   }
   if(n <= 15)
   {
      ull res = 0;
      res = (V[n - 1] * 2) % MOD;
      cout << res << endl;
   }
   else
   {
      cout << M << endl;
       
      matrix R = mpow(M, n - 15);
      
      cout << R << endl;
      
      ull res = 0;
      FOR(j, 15)
      {
         res = (res + R[14][j] * V[j]) % MOD;
      }
      res = (res * 2) % MOD;
      cout << res << endl;   
   }
   return 0;
}
