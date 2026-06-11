#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "heap.h"

// Konstanta default kapasitas heap sesuai spesifikasi tugas (Halaman 4: k=100)
#define K 100

/* Menyimpan hasil pengurutan ke file teks. Menggunakan %lld untuk mencetak long long frekuensi. */
void saveResult(const char *filename, WordFreq heap[], int size, double elapsedTime) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Gagal membuat file hasil %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s (%lld)\n", vocab[heap[i].wordID], heap[i].frequency);
    }
    
    // Menuliskan catatan waktu di akhir berkas sesuai instruksi soal (Halaman 4)
    fprintf(fp, "\nWaktu untuk mengurutkan: %.0f ms\n", elapsedTime);
    fclose(fp);
}

/* Menampilkan hasil pengurutan ke layar monitor dengan penentu format %lld */
void displayResult(WordFreq heap[], int size, double elapsedTime) {
    if (size == 0) {
        printf("Data belum diproses. Silakan jalankan Menu 1 atau Menu 2 terlebih dahulu.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%3d. %-25s (%lld)\n", i + 1, vocab[heap[i].wordID], heap[i].frequency);
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

    // ========================================================================
    // LOGIKA INTERAKTIF: Meminta input secara terus-menerus jika file salah/tidak ada
    // ========================================================================
    while (1) {
        printf("Masukkan file docword : ");
        if (scanf("%255s", docwordFile) != 1) return 1;

        printf("Masukkan file vocab   : ");
        if (scanf("%255s", vocabFile) != 1) return 1;

        // Mencoba memuat data berkas
        loadDocword(docwordFile);
        loadVocabulary(vocabFile);

        // Jika data berhasil dimuat (W > 0 dan vocab tidak NULL), keluar dari loop input
        if (W > 0 && vocab != NULL) {
            break; 
        }

        // Jika gagal dimuat, bersihkan memori sampah sisa alokasi, lalu ulangi prompt input
        printf("\n[Peringatan]: File tidak ditemukan atau gagal dimuat.\n");
        printf("Silakan periksa kembali nama berkas dan pastikan berada di folder yang sama.\n\n");
        freeData(); 
    }

    // 2. Masuk ke loop menu utama setelah file dijamin sukses dimuat
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
            // Membersihkan input buffer jika pengguna memasukkan karakter non-angka
            while (getchar() != '\n'); 
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: {
                frequentSize = 0;
                clock_t start = clock();

                // Membaca seluruh frekuensi kata unik, disaring via Min-Heap berkapasitas K
                for (int i = 1; i <= W; i++) {
                    if (freq[i] > 0) {
                        WordFreq item;
                        item.wordID = i;
                        item.frequency = freq[i]; // Tanpa type casting karena tipe datanya sudah seragam (long long)
                        insertMinHeap(frequentHeap, &frequentSize, K, item);
                    }
                }

                // Melakukan pengurutan Heapsort Descending
                heapSortDescending(frequentHeap, frequentSize, 1);
                clock_t end = clock();

                frequentTime = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
                
                // Menyimpan otomatis hasil urutan descending ke berkas teks top100_frequent.txt
                saveResult("top100_frequent.txt", frequentHeap, frequentSize, frequentTime);

                printf("\nTop 100 kata paling sering berhasil disimpan ke 'top100_frequent.txt'.\n");
                printf("Waktu proses: %.0f ms\n", frequentTime);
                break;
            }

            case 2: {
                rareSize = 0;
                clock_t start = clock();

                // Membaca seluruh frekuensi kata unik, disaring via Max-Heap berkapasitas K
                for (int i = 1; i <= W; i++) {
                    if (freq[i] > 0) {
                        WordFreq item;
                        item.wordID = i;
                        item.frequency = freq[i]; // Tanpa type casting karena tipe datanya sudah seragam (long long)
                        insertMaxHeap(rareHeap, &rareSize, K, item);
                    }
                }

                // Melakukan pengurutan Heapsort Descending
                heapSortDescending(rareHeap, rareSize, 0);
                clock_t end = clock();

                rareTime = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

                // Menyimpan otomatis hasil urutan descending ke berkas teks top100_rare.txt
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

    // Pembersihan akhir memori pointer sebelum keluar program
    freeData();
    return 0;
}