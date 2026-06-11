#ifndef HEAP_H
#define HEAP_H

/* Struktur data untuk menyimpan pasangan ID kata dan total frekuensinya */
typedef struct {
    int wordID;
    int frequency;
} WordFreq;

/* Mengatur ulang susunan node pada Min-Heap agar memenuhi sifat Min-Heap */
void minHeapify(WordFreq heap[], int size, int index);

/* Memasukkan elemen baru ke dalam Min-Heap dengan batas maksimum k elemen */
void insertMinHeap(WordFreq heap[], int *size, int k, WordFreq item);

/* Mengatur ulang susunan node pada Max-Heap agar memenuhi sifat Max-Heap */
void maxHeapify(WordFreq heap[], int size, int index);

/* Memasukkan elemen baru ke dalam Max-Heap dengan batas maksimum k elemen */
void insertMaxHeap(WordFreq heap[], int *size, int k, WordFreq item);

/* Mengurutkan isi array di dalam heap dari frekuensi terbesar ke terkecil (descending) */
void heapSortDescending(WordFreq heap[], int size, int isMinHeap);

#endif