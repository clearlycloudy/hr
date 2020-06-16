#include <bits/stdc++.h>

using namespace std;

int diff( int arr1 [3][3], int arr2 [3][3] ){
    int ret = 0;
    for(int i = 0; i < 3; ++i){
	for(int j = 0; j < 3; ++j){
	    ret += std::abs(arr1[i][j]-arr2[i][j]);
    	}
    }
    return ret;
}

void rot( int arr [3][3] ){
    for(int i = 0; i < 2; ++i){
	int j = 0;
	int ti = i;
	int tj = j;
	int temp = arr[i][j];
	for(int cycle = 0; cycle < 4; ++cycle){
	    int ii = ti-1;
	    int jj = tj-1;
	    int roti = -jj+1;
	    int rotj = ii+1;
	    int v = arr[roti][rotj];
	    arr[roti][rotj] = temp;
	    temp = v;
	    ti = roti;
	    tj = rotj;
	}
    }
}

void reflect( int arr[3][3], bool v ){
    if(v){
	for(int i = 0; i < 1; ++i){
	    for(int j = 0; j < 3; ++j){
		int t = arr[3-i-1][j];
		arr[3-i-1][j] = arr[i][j];
		arr[i][j] = t;
	    }
	}
    }else{
	for(int i = 0; i < 3; ++i){
	    for(int j = 0; j < 1; ++j){
		int t = arr[i][3-j-1];
		arr[i][3-j-1] = arr[i][j];
		arr[i][j] = t;
	    }
	}
    }
}

// Complete the formingMagicSquare function below.
int formingMagicSquare(vector<vector<int>> s) {
    int const magic = 15;
    int ref [3][3] = { {2,7,6},{9,5,1},{4,3,8} };
    int temp [3][3] = { 0 };
    std::copy(&ref[0][0], &ref[0][0]+9, &temp[0][0]);
	
    int ss [3][3] = { 0 };
    int idx = 0;
    for(auto &i: s){
	std::copy(i.begin(),i.end(),&ss[idx][0]);
	idx++;
    }
	
    int ret = std::numeric_limits<int>::max();
    
    ret = std::min(diff(ss,temp), ret);
    
    reflect(temp,true);
    ret = std::min(diff(ss,temp), ret);
    reflect(temp,true);

    reflect(temp,false);
    ret = std::min(diff(ss,temp), ret);
    reflect(temp,false);
	
    for(int i = 0; i < 3; ++i){
	
	rot(temp);
	
	ret = std::min(diff(ss,temp), ret);
	
	reflect(temp,true);
	ret = std::min(diff(ss,temp), ret);
	reflect(temp,true);

	reflect(temp,false);
	ret = std::min(diff(ss,temp), ret);
	reflect(temp,false);
    }
    return ret;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);
    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> s[i][j];
        }

        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = formingMagicSquare(s);

    cout << result << endl;
    // fout << result << "\n";

    // fout.close();

    return 0;
}
