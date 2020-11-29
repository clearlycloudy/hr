#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t M = 1'000'000'007;

ostream& operator<<(ostream &o, vector<vector<uint64_t>> const & a){
    for(auto &i: a){
	for(auto j: i){
	    o << j << " ";
	}
        o << endl;
    }
    return o;
}

//form linear transition matrix
vector<vector<uint64_t>> init_matrix(vector<uint64_t> const & indicator){
    vector<vector<uint64_t>> m(15, vector<uint64_t>(15,0));
    for(int i=0; i<15-1;++i){
	m[i][i+1] = 1;
    }
    for(int i=0; i<15;++i){
	m[14][i] = indicator[15-i];
    }
    
    // cout << "transition matrix" << endl;
    // cout << m << endl;
    return m;
}

vector<vector<uint64_t>> ones(){
    vector<vector<uint64_t>> m(15, vector<uint64_t>(15,0));
    for(int i=0; i<15; ++i){
	m[i][i] = 1;
    }
    return m;
}

vector<vector<uint64_t>> zeros(){
    vector<vector<uint64_t>> m(15, vector<uint64_t>(15,0));
    return m;
}

auto mul(vector<vector<uint64_t>> const & a, vector<vector<uint64_t>> const & b){
    auto ret = zeros();
    for(int i=0; i<15; ++i){
	for(int j=0; j<15; ++j){
	    for(int k=0; k<15; ++k){
		ret[i][j] = (ret[i][j] + (a[i][k] * b[k][j]) % M) % M;
	    }
	}
    }
    return ret;
}

auto mul(vector<vector<uint64_t>> const & a, vector<uint64_t> const & b){
    vector<uint64_t> ret(15, 0);
    for(int i=0; i<15; ++i){
	for(int j=0; j<15; ++j){
	    ret[i] = (ret[i] + (a[i][j]*b[j] % M) ) % M;
	}
    }
    return ret;
}

using matrix = vector<vector<uint64_t>>;

matrix mmul(matrix M1, matrix M2)
{
   matrix R(15);
   for(int i=0;i<15;++i){
      R[i].assign(15, 0);
      for(int j=0;j<15;++j){
	  for(int k=0;k<15;++k){
	      R[i][j] = (R[i][j] + M1[i][k] * M2[k][j]) % M;
	  }
      }
   }
   return R;
}

// using matrix = vector<vector<uint64_t>>;

matrix mpow(matrix M, uint64_t n)
{
   if(n == 0)
   {
      matrix M1(15);
      for(int i=0; i<15; ++i){
         M1[i].assign(15, 0);
	 for(int j=0; j<15; ++j){
            if(i == j)
               M1[i][j] = 1;
         }
      }
      return M1;
   }
   else if(n % 2 == 0)
   {
      matrix R = mpow(M, n / 2);
      return mul(R, R);
   }
   else
   {
      matrix R = mpow(M, n - 1);
      return mul(R, M);
   }
}

auto pow_mat(vector<vector<uint64_t>> m, uint64_t power){
    auto ret = ones();
    while(power){
	//cout << "power: " << power << endl;
	if(power&1){
	    ret = mul(ret, m);
	    //cout << "m: " << endl;
	    // cout << ret << endl;
	}
	power >>= 1;
	m = mul(m, m);
    }
    return ret;
}

uint64_t solve(uint64_t n, vector<uint64_t> & arr){
    vector<uint64_t> v(15,0);
    vector<uint64_t> temp(16,0);
    temp[0]=1;
    for(auto i: arr){
	temp[i] = 1;
    }
    for(int i=1;i<=15;++i){
	if(temp[i]){
	    v[i-1] = (v[i-1]+1) % M;
	}
	for(int j=1;j<i;++j){
	    if(i-j-1>=0){
		v[i-1] = (v[i-1] + (temp[j] * v[i-j-1]) % M) % M;
	    }
	}
    }
    
    // for(auto i: v){
    // 	cout << i << " ";
    // }
    // cout << endl;
    
    if(n<=15){
	// cout << "res: " << v[n-1] << endl;
	return v[n-1];
    }else{
	auto m = init_matrix(temp);
	// auto mm = pow_mat(m, n-15);
	auto mm = mpow(m, n-15);
	// cout << mm << endl;
	auto result = mul(mm, v);
	// cout << "res: " << result[14] << endl;
	return result[14];
    }
}

int main(){
    uint64_t n, k;
    cin>>n>>k;
    vector<uint64_t> arr(k);
    for(auto &i: arr){
	cin >> i;
    }
//    cout << n << " , " << k << endl;
    
    cout << (solve(n,arr)*2) % M << endl;
}
