#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPATTERN 17
#define ASCIISIZE 256
#define TRUE 1

void create_table(unsigned char pattern[MAXPATTERN], int *shift) {
	int i, pattern_len = strlen(pattern);

	if (pattern_len == 1)
		for (i = 0; i < ASCIISIZE; ++i)
			shift[i] = 1;
	else {
		for (i = 0; i < ASCIISIZE; ++i)
			shift[i] = pattern_len;
		for (i = 0; i <= pattern_len - 2; i++)
			shift[pattern[i]] = pattern_len - i - 1;
	}
}

int print_protocol(unsigned char pattern[MAXPATTERN], unsigned char input[MAXPATTERN], int *shift, int blink, FILE *fout) {
	int i = 0, displacement = 0;
	int pattern_len = strlen(pattern);

	i = pattern_len;
	if (input[i - 1] != pattern[i - 1])
		fprintf(fout, "%d ", i + blink);
	else
		while ((i != 0) && (input[i - 1] == pattern[i - 1])) {
			fprintf(fout, "%d ", i + blink);
			i--;
			if (i != 0)
				if (input[i - 1] != pattern[i - 1])
					fprintf(fout, "%d ", i + blink);
		}

	displacement = shift[input[pattern_len - 1]];

	return displacement;
}

int main() {
	unsigned char pattern[MAXPATTERN] = { 0 }, input[MAXPATTERN] = { 0 };
	int shift[256] = { 0 };
	int blink = 0, displacement = 0;

	FILE *fin = fopen("in.txt", "r");
	FILE *fout = fopen("out.txt", "w");

	fgets(pattern, MAXPATTERN, fin);
	int pattern_len = strlen(pattern);
	if (pattern[pattern_len - 1] == '\n')
		pattern[--pattern_len] = '\0';
	create_table(pattern, shift);

	fgets(input, pattern_len + 1, fin);
	if (input[0] == '\n')
		fgets(input, pattern_len + 1, fin);
	int input_len = strlen(input);

	if (pattern_len == input_len) {
		displacement = print_protocol(pattern, input, shift, blink, fout);
		blink += displacement;
		memmove(input, input + displacement, input_len - displacement);
		while (TRUE) {
			fgets(input + strlen(input) - displacement, displacement + 1, fin);
			if (strlen(input) == pattern_len && !feof(fin)) {
				displacement = print_protocol(pattern, input, shift, blink, fout);
				blink += displacement;
				memmove(input, input + displacement, input_len - displacement);
			}
			else
				break;
		};
	}
	fclose(fin);
	fclose(fout);
	return 0;
}