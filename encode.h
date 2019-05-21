#pragma once

#ifndef H_ENCODE
#define H_ENCODE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>

int print_bin(char* bin, FILE* fout, FILE* log);

void zip(FILE* fin, FILE* fout, FILE* log);

#endif