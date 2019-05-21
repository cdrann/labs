#pragma once

#define _CRT_SECURE_NO_WARNINGS 

#include "binary_tree.h"
#include "decode.h"
#include "encode.h"

#define INF (int)1e9
#define SIZE_BUFF (int)1e4

int main() {
	FILE *fin = fopen("in.txt", "rb");
	FILE *fout = fopen("out.txt", "wb");
	FILE* log = fopen("log.txt", "w");

	if (!fin) {
		puts("error openning file");
		system("pause");
		exit(0);
	}

	fseek(fin, 0, SEEK_END);
	int size = ftell(fin);
	fseek(fin, 0, SEEK_SET); // rewind (fin);  
	if (size == 3)  // TODO 
		exit(0); // TODO return

	unsigned char buff[4];
	fread(buff, sizeof(unsigned char), 3, fin);

	char mode = buff[0];
	if (mode == 'c')
		zip(fin, fout, log);
	else if (mode == 'd')
		unzip(fin, fout, log);
	else
		puts("incorrect format, try again");

	fclose(fin);
	fclose(fout);
	return 0;
}