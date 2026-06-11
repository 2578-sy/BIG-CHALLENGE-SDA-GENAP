#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int W;

extern char **vocab;

extern long long *freq;

// Membaca file vocab
void loadVocabulary(const char *filename);

// Membaca file docword
void loadDocword(const char *filename);

// Menampilkan sampel data
void printSample(int n);

// Membebaskan memori
void freeData(void);

#endif
