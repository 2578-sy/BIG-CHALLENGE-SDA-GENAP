#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Jumlah kata unik
extern int W;

// Vocabulary
// vocab[wordID] -> kata
extern char **vocab;

// Total frekuensi setiap kata
extern long long *freq;

// Menyimpan informasi kata dan frekuensinya
typedef struct
{
    int wordID;
    char word[100];
    long long freq;
} WordFreq;

// Membaca file vocab.*.txt
void loadVocabulary(const char *filename);

// Membaca file docword.*.txt
// sekaligus menghitung total frekuensi kata
void loadDocword(const char *filename);

// Menampilkan beberapa data untuk pengecekan
void printSample(int n);

// Membebaskan memori yang digunakan
void freeData(void);

#endif
