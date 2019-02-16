#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
    FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "a");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		return 0;
	}

	int N; //TODO вынести в отдельную ф-ю
	fscanf(input_file, "%d", &N); //число вершин
	if(N < 0 || N > 5000) {
	    fputs("bad number of vertices", output_file);
	    return 0;
	}
	
	int S, F; //начало и конец пути
	fscanf(input_file, "%d %d", &S, &F); //начало и конец пути
	if(S < 1 || F < 1 || S > N || F > N) {
	    fputs("bad vertex", output_file);
	    return 0;
	}
	
	int M;
	fscanf(input_file, "%d", &M); //число ребер в графе
	if(M < 0 || M > N*(N - 1)/2) {
	    fputs("bad number of edges", output_file);
	    return 0;
	}
	
	int B, E, L;
	for(int i = 0; i < M; i++){
	    fscanf(input_file, "%d %d %d", &B, &E, &L); //начало -- конец -- длина ребра
	    if(B < 1 || E < 1 || B > N || E > N) {
	        fputs("bad vertex", output_file);
	        return 0;
	    } 
	    if(L < 0 || L > INT_MAX){
	        fputs("bad length", output_file);
	        return 0;
	    }
	    //TODO если строк не M
	    //fputs("bad number of lines", output_file);
	    //return 0;
	}

	fclose(input_file);
	fclose(output_file);

	return 0;
}