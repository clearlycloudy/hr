#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

int max(int a, int b){
    return a < b ? b : a;
}

long int dp [4000002] = {0};
long int fromleft [4000002] = {0};
long int fromright [4000002] = {0};
long int fromlefttop [4000002] = {0};
long int fromrighttop [4000002] = {0};

// Complete the matrixLand function below.
int matrixLand(int A_rows, int A_columns, int** A) {
    
    for(int r=0; r<A_rows; ++r){
	    
	for(int i=1; i< A_columns+1; ++i){
	    fromleft[i] = max(fromleft[i-1] + A[r][i-1], 0);
	}
	for(int i=A_columns; i>=1; --i){
	    fromright[i] = max(fromright[i+1] + A[r][i-1], 0);
	}
	for(int i=1; i< A_columns+1; ++i){
	    if(i==1){
		fromlefttop[i] = dp[i] + A[r][i-1] + fromleft[i-1]; //force carry over from previous row
	    }else{
		fromlefttop[i] = max(fromlefttop[i-1] + A[r][i-1],
				     dp[i] + A[r][i-1] + fromleft[i-1]);
	    }
	}
	for(int i=A_columns; i>=1; --i){
	    if(i==A_columns){
		fromrighttop[i] = dp[i] + A[r][i-1] + fromright[i+1]; //force carry over
	    }else{
		fromrighttop[i] = max(fromrighttop[i+1] + A[r][i-1],
				      dp[i] + A[r][i-1] + fromright[i+1]);
	    }
	}

	for(int i=1; i< A_columns+1; ++i){
	    dp[i] = max(fromlefttop[i]+fromright[i+1], fromrighttop[i]+fromleft[i-1]);
	}
    }
    
    long int res = 0;
    
    for(int i=0; i< A_columns+2; ++i){
	res = max(dp[i], res);
    }

    return (int)res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    // assert(fptr);
    char** nm = split_string(readline());

    char* n_endptr;
    char* n_str = nm[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* m_endptr;
    char* m_str = nm[1];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    int** A = (int**) malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(A + i) = (int*) malloc(m * (sizeof(int)));

        char** A_item_temp = split_string(readline());

        for (int j = 0; j < m; j++) {
            char* A_item_endptr;
            char* A_item_str = *(A_item_temp + j);
            int A_item = strtol(A_item_str, &A_item_endptr, 10);

            if (A_item_endptr == A_item_str || *A_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(A + i) + j) = A_item;
        }
    }

    int A_rows = n;
    int A_columns = m;

    int result = matrixLand(A_rows, A_columns, A);

    fprintf(fptr, "%d\n", result);
    fflush(fptr);
    fclose(fptr);

    return 0;
}

constexpr size_t alloc_length = 1024*1024*16;
char data[alloc_length];

char* readline() {

    size_t data_length = 0;
    // char* data = (char*) malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }
	assert(false);
        // size_t new_length = alloc_length << 1;
        // data = (char*) realloc(data, new_length);

        // if (!data) { break; }

        // alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    // data = (char*) realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = (char**) realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
