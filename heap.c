#include <stdio.h>
#include "heap.h"

// Fungsi pembantu untuk menukar dua elemen WordFreq
void swap(WordFreq *a, WordFreq *b) {
    WordFreq temp = *a;
    *a = *b;
    *b = temp;
}

// ============================================================================
// LOGIKA MIN-HEAP (Untuk mencari 'k' Frekuensi Terbesar / Paling Sering Muncul)
// ============================================================================

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
    // Jika heap belum penuh (kurang dari k elemen), masukkan saja langsung di akhir
    if (*size < k) {
        heap[*size] = item;
        (*size)++;
        
        // Lakukan heapify up untuk menjaga properti Min-Heap
        int i = *size - 1;
        while (i != 0 && heap[(i - 1) / 2].frequency > heap[i].frequency) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } 
    // Jika heap sudah penuh (ukuran k), bandingkan dengan elemen terkecil (akar/index 0)
    else if (item.frequency > heap[0].frequency) {
        heap[0] = item; // Ganti akar jika item baru punya frekuensi lebih besar
        minHeapify(heap, *size, 0); // Atur ulang properti heap ke bawah
    }
}

// ============================================================================
// LOGIKA MAX-HEAP (Untuk mencari 'k' Frekuensi Terkecil / Paling Jarang Muncul)
// ============================================================================

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
    // Jika heap belum penuh (kurang dari k elemen), masukkan saja langsung di akhir
    if (*size < k) {
        heap[*size] = item;
        (*size)++;
        
        // Lakukan heapify up untuk menjaga properti Max-Heap
        int i = *size - 1;
        while (i != 0 && heap[(i - 1) / 2].frequency < heap[i].frequency) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } 
    // Jika heap sudah penuh (ukuran k), bandingkan dengan elemen terbesar (akar/index 0)
    else if (item.frequency < heap[0].frequency) {
        heap[0] = item; // Ganti akar jika item baru punya frekuensi lebih kecil
        maxHeapify(heap, *size, 0); // Atur ulang properti heap ke bawah
    }
}

// ============================================================================
// LOGIKA HEAPSORT (Mengurutkan isi heap secara Descending Order)
// ============================================================================

void heapSortDescending(WordFreq heap[], int size, int isMinHeap) {
    // Langkah 1: Ubah array heap menjadi terurut menggunakan algoritma Heapsort biasa
    for (int i = size - 1; i > 0; i--) {
        // Pindahkan elemen akar (elemen ekstrem) ke akhir array
        swap(&heap[0], &heap[i]);
        
        // Lakukan heapify lagi pada heap yang mengecil
        if (isMinHeap) {
            minHeapify(heap, i, 0);
        } else {
            maxHeapify(heap, i, 0);
        }
    }

    /* Langkah 2: Karena tugas meminta keluaran disimpan dalam *descending order* (dari besar ke kecil) untuk Pilihan 1 & Pilihan 2, kita perlu memastikan:
       - Min-Heap setelah di-extract/sorted normal akan menghasilkan urutan ASCENDING.
         Maka untuk Min-Heap, array hasil sort harus dibalik (reverse) agar menjadi DESCENDING.
       - Max-Heap setelah di-extract/sorted normal otomatis menghasilkan urutan DESCENDING.
         Maka untuk Max-Heap tidak perlu dibalik lagi.
    */
    if (isMinHeap) {
        int start = 0;
        int end = size - 1;
        while (start < end) {
            swap(&heap[start], &heap[end]);
            start++;
            end--;
        }
    }
}
