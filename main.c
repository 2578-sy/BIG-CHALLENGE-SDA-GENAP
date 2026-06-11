#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "heap.h"

// Konstanta default kapasitas heap sesuai menu tugas
#define K 100

/* Menyimpan hasil ke file teks */
void saveResult(const char *filename, WordFreq heap[], int size, double elapsedTime) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Gagal membuat file hasil %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        // Menggunakan %d karena heap[i].frequency bertipe int
        fprintf(fp, "%s (%d)\n", vocab[heap[i].wordID], heap[i].frequency);
    }
    
    fprintf(fp, "\nWaktu untuk mengurutkan: %.0f ms\n", elapsedTime);
    fclose(fp);
}

/* Menampilkan hasil ke layar monitor */
void displayResult(WordFreq heap[], int size, double elapsedTime) {
    if (size == 0) {
        printf("Data belum diproses. Silakan jalankan Menu 1 atau Menu 2 terlebih dahulu.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%3d. %-25s (%d)\n", i + 1, vocab[heap[i].wordID], heap[i].frequency);
    }
    printf("\nWaktu untuk mengurutkan: %.0f ms\n", elapsedTime);
}

int main() {
    char docwordFile[256];
    char vocabFile[256];

    WordFreq frequentHeap[K];
    WordFreq rareHeap[K];

    int frequentSize = 0;
    int rareSize = 0;

    double frequentTime = 0;
    double rareTime = 0;

    int choice;

    // Input nama file di awal program
    printf("Masukkan file docword : ");
    scanf("%255s", docwordFile);

    printf("Masukkan file vocab   : ");
    scanf("%255s", vocabFile);

    // Proses pemuatan data (Urutan pemanggilan WAJIB Docword baru Vocab)
    loadDocword(docwordFile);
    loadVocabulary(vocabFile);

    do {
        printf("\n=====================================\n");
        printf("1. Top 100 kata paling sering\n");
        printf("2. Top 100 kata paling jarang\n");
        printf("3. Tampilkan kata paling sering\n");
        printf("4. Tampilkan kata paling jarang\n");
        printf("5. Keluar\n");
        printf("=====================================\n");
        printf("Pilihan : ");
        if (scanf("%d", &choice) != 1) {
            printf("Pilihan harus berupa angka.\n");
            break;
        }

        switch (choice) {
            case 1: {
                frequentSize = 0;
                clock_t start = clock();

                // Membaca linear seluruh kata unik, disaring via Min-Heap berkapasitas K
                for (int i = 1; i <= W; i++) {
                    if (freq[i] > 0) {
                        WordFreq item;
                        item.wordID = i;
                        item.frequency = (int)freq[i];
                        insertMinHeap(frequentHeap, &frequentSize, K, item);
                    }
                }

                // Melakukan Heapsort
                heapSortDescending(frequentHeap, frequentSize, 1);
                clock_t end = clock();

                frequentTime = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
                
                // Menyimpan otomatis hasil urutan descending ke file teks
                saveResult("top100_frequent.txt", frequentHeap, frequentSize, frequentTime);

                printf("\nTop 100 kata paling sering berhasil disimpan ke 'top100_frequent.txt'.\n");
                printf("Waktu proses: %.0f ms\n", frequentTime);
                break;
            }

            case 2: {
                rareSize = 0;
                clock_t start = clock();

                // Membaca linear seluruh kata unik, disaring via Max-Heap berkapasitas K
                for (int i = 1; i <= W; i++) {
                    if (freq[i] > 0) {
                        WordFreq item;
                        item.wordID = i;
                        item.frequency = (int)freq[i];
                        insertMaxHeap(rareHeap, &rareSize, K, item);
                    }
                }

                // Melakukan Heapsort
                heapSortDescending(rareHeap, rareSize, 0);
                clock_t end = clock();

                rareTime = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

                // Menyimpan otomatis hasil urutan descending ke file teks
                saveResult("top100_rare.txt", rareHeap, rareSize, rareTime);

                printf("\nTop 100 kata paling jarang berhasil disimpan ke 'top100_rare.txt'.\n");
                printf("Waktu proses: %.0f ms\n", rareTime);
                break;
            }

            case 3: {
                printf("\n===== TOP 100 PALING SERING =====\n");
                displayResult(frequentHeap, frequentSize, frequentTime);
                break;
            }

            case 4: {
                printf("\n===== TOP 100 PALING JARANG =====\n");
                displayResult(rareHeap, rareSize, rareTime);
                break;
            }

            case 5: {
                printf("\nProgram selesai. Membebaskan seluruh memori...\n");
                break;
            }

            default: {
                printf("\nPilihan menu tidak valid.\n");
            }
        }
    } while (choice != 5);

    // Pembersihan akhir memori pointer
    freeData();
    return 0;
}