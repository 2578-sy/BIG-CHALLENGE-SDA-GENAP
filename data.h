#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Jumlah kata unik dalam dataset
extern int W;

// Array pembantu penampung Vocabulary & Frekuensi (Global)
extern char **vocab;
extern long long *freq;

// Prototipe Fungsi Utama Manajemen File
void loadDocword(const char *filename);
void loadVocabulary(const char *filename);
void freeData(void);

#endif