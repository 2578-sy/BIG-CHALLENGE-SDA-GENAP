#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Jumlah kata unik
extern int W;

// Vocabulary
extern char **vocab;

// Total frekuensi tiap kata
extern long long *freq;

// Membaca file vocab
void loadVocabulary(const char *filename);

// Membaca file docword
void loadDocword(const char *filename);

// Menampilkan beberapa data untuk testing
void printSample(int n);

// Membebaskan memori
void freeData(void);

#endif
