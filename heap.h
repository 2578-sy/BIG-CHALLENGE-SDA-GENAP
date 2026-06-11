#ifndef HEAP_H
#define HEAP_H

// Struktur data untuk menyimpan pasangan WordID dan Frekuensinya
typedef struct {
    int wordID;
    int frequency;
} WordFreq;

// --- FUNGSI UNTUK MIN-HEAP (Pilihan 1: Kata Paling Sering Muncul) ---
// Melakukan heapify down pada Min-Heap
void minHeapify(WordFreq heap[], int size, int index);
// Memasukkan data baru ke dalam Min-Heap berukuran k
void insertMinHeap(WordFreq heap[], int *size, int k, WordFreq item);

// --- FUNGSI UNTUK MAX-HEAP (Pilihan 2: Kata Paling Jarang Muncul) ---
// Melakukan heapify down pada Max-Heap
void maxHeapify(WordFreq heap[], int size, int index);
// Memasukkan data baru ke dalam Max-Heap berukuran k
void insertMaxHeap(WordFreq heap[], int *size, int k, WordFreq item);

// --- FUNGSI PENGURUTAN (HEAPSORT) ---
// Mengurutkan isi heap secara descending order (dari besar ke kecil)
void heapSortDescending(WordFreq heap[], int size, int isMinHeap);

#endif
