#include "data.h"

int W = 0;
char **vocab = NULL;
long long *freq = NULL;

/* Membaca file docword dan menghitung total frekuensi tiap kata */
void loadDocword(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Gagal membuka file %s\n", filename);
        return;
    }

    int D;
    long long N;

    // Membaca 3 baris header awal file docword
    if (fscanf(fp, "%d", &D) != 1 || fscanf(fp, "%d", &W) != 1 || fscanf(fp, "%lld", &N) != 1) {
        printf("Error: Format file docword tidak valid.\n");
        fclose(fp);
        return;
    }

    printf("\n=== INFORMASI DATASET ===\n");
    printf("Jumlah Dokumen : %d\n", D);
    printf("Jumlah Kata (W): %d\n", W);
    printf("Jumlah NNZ     : %lld\n", N);
    printf("=========================\n");

    // Alokasi aman menggunakan calloc agar default nilainya 0
    freq = (long long *)calloc(W + 1, sizeof(long long));
    if (freq == NULL) {
        printf("Error: Alokasi memori freq gagal\n");
        fclose(fp);
        return;
    }

    int docID, wordID, count;
    // Membaca sekuensial sisa baris data tripel (docID wordID count)
    while (fscanf(fp, "%d %d %d", &docID, &wordID, &count) == 3) {
        if (wordID >= 1 && wordID <= W) {
            freq[wordID] += count;
        }
    }

    fclose(fp);
    printf("Frekuensi kata berhasil dihitung.\n");
}

/* Membaca file vocabulary berdasarkan nilai W yang sudah didapatkan */
void loadVocabulary(const char *filename) {
    if (W == 0) {
        printf("Error: loadDocword harus dipanggil terlebih dahulu sebelum loadVocabulary.\n");
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Gagal membuka file %s\n", filename);
        return;
    }

    vocab = (char **)malloc((W + 1) * sizeof(char *));
    if (vocab == NULL) {
        printf("Error: Alokasi memori vocab utama gagal\n");
        fclose(fp);
        return;
    }

    char buffer[256];
    int id = 1;

    // Membaca baris demi baris kata dalam vocab
    while (fgets(buffer, sizeof(buffer), fp) != NULL && id <= W) {
        // Membersihkan karakter newline (\n atau \r) dari buffer kata
        buffer[strcspn(buffer, "\r\n")] = '\0';

        vocab[id] = (char *)malloc(strlen(buffer) + 1);
        if (vocab[id] == NULL) {
            printf("Error: Alokasi memori vocab string pada indeks %d gagal\n", id);
            fclose(fp);
            return;
        }

        strcpy(vocab[id], buffer);
        id++;
    }

    fclose(fp);
    printf("Vocabulary berhasil dimuat (%d kata).\n", id - 1);
}

/* Membebaskan memori dinamis secara bersih untuk mencegah kebocoran memori */
void freeData(void) {
    if (vocab != NULL) {
        for (int i = 1; i <= W; i++) {
            if (vocab[i] != NULL) {
                free(vocab[i]);
            }
        }
        free(vocab);
        vocab = NULL;
    }

    if (freq != NULL) {
        free(freq);
        freq = NULL;
    }
    W = 0;
}