#include <stdio.h>
#include "heap.h"

/* Fungsi utilitas untuk menukar posisi dua elemen WordFreq */
static void swap(WordFreq *a, WordFreq *b) {
    WordFreq temp = *a;
    *a = *b;
    *b = temp;
}

/* --- IMPLEMENTASI MIN-HEAP --- */
void minHeapify(WordFreq heap[], int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].frequency < heap[smallest].frequency)
        smallest = left;
    if (right < size && heap[right].frequency < heap[smallest].frequency)
        smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void insertMinHeap(WordFreq heap[], int *size, int k, WordFreq item) {
    if (*size < k) {
        heap[*size] = item;
        (*size)++;
        int i = *size - 1;
        while (i != 0 && heap[(i - 1) / 2].frequency > heap[i].frequency) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (item.frequency > heap[0].frequency) {
        heap[0] = item;
        minHeapify(heap, *size, 0);
    }
}

/* --- IMPLEMENTASI MAX-HEAP --- */
void maxHeapify(WordFreq heap[], int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].frequency > heap[largest].frequency)
        largest = left;
    if (right < size && heap[right].frequency > heap[largest].frequency)
        largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

void insertMaxHeap(WordFreq heap[], int *size, int k, WordFreq item) {
    if (*size < k) {
        heap[*size] = item;
        (*size)++;
        int i = *size - 1;
        while (i != 0 && heap[(i - 1) / 2].frequency < heap[i].frequency) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (item.frequency < heap[0].frequency) {
        heap[0] = item;
        maxHeapify(heap, *size, 0);
    }
}

/* --- IMPLEMENTASI HEAPSORT --- */
void heapSortDescending(WordFreq heap[], int size, int isMinHeap) {
    // 1. Lakukan ekstraksi Heapsort standar
    for (int i = size - 1; i > 0; i--) {
        swap(&heap[0], &heap[i]);
        if (isMinHeap) minHeapify(heap, i, 0);
        else maxHeapify(heap, i, 0);
    }

    // 2. Koreksi Logika Pengurutan agar KEDUANYA menghasilkan Descending:
    // - Hasil Heapsort dari Min-Heap secara alami sudah descending, JANGAN dibalik.
    // - Hasil Heapsort dari Max-Heap secara alami adalah ascending, WAJIB dibalik.
    if (!isMinHeap) {
        int start = 0, end = size - 1;
        while (start < end) {
            swap(&heap[start], &heap[end]);
            start++;
            end--;
        }
    }
}