#include "data.h"

int W = 0;

char **vocab = NULL;
long long *freq = NULL;

// ============================================================================
// Membaca file vocabulary
// ============================================================================

void loadVocabulary(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: gagal membuka file %s\n", filename);
        return;
    }

    vocab = (char **)malloc((W + 1) * sizeof(char *));

    if (vocab == NULL)
    {
        printf("Error: alokasi memori vocab gagal\n");
        fclose(fp);
        return;
    }

    char buffer[256];
    int id = 1;

    while (fgets(buffer, sizeof(buffer), fp) != NULL && id <= W)
    {
        // Hapus karakter newline
        buffer[strcspn(buffer, "\n")] = '\0';

        vocab[id] = (char *)malloc(strlen(buffer) + 1);

        if (vocab[id] == NULL)
        {
            printf("Error: alokasi memori vocab[%d] gagal\n", id);
            fclose(fp);
            return;
        }

        strcpy(vocab[id], buffer);
        id++;
    }

    fclose(fp);

    printf("Vocabulary berhasil dimuat (%d kata)\n", id - 1);
}

// ============================================================================
// Membaca file docword dan menghitung total frekuensi tiap kata
// ============================================================================

void loadDocword(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: gagal membuka file %s\n", filename);
        return;
    }

    int D;
    long long N;

    // 3 baris header
    fscanf(fp, "%d", &D);
    fscanf(fp, "%d", &W);
    fscanf(fp, "%lld", &N);

    printf("Jumlah Dokumen : %d\n", D);
    printf("Jumlah Kata    : %d\n", W);
    printf("Jumlah NNZ     : %lld\n", N);

    // Alokasi array frekuensi
    freq = (long long *)calloc(W + 1, sizeof(long long));

    if (freq == NULL)
    {
        printf("Error: alokasi memori freq gagal\n");
        fclose(fp);
        return;
    }

    int docID;
    int wordID;
    int count;

    // Format:
    // docID wordID count
    while (fscanf(fp,
                  "%d %d %d",
                  &docID,
                  &wordID,
                  &count) == 3)
    {
        if (wordID >= 1 && wordID <= W)
        {
            freq[wordID] += count;
        }
    }

    fclose(fp);

    printf("Frekuensi kata berhasil dihitung\n");
}

// ============================================================================
// Menampilkan beberapa data untuk testing
// ============================================================================

void printSample(int n)
{
    if (vocab == NULL || freq == NULL)
    {
        printf("Data belum dimuat\n");
        return;
    }

    printf("\n===== SAMPLE DATA =====\n");

    for (int i = 1; i <= n && i <= W; i++)
    {
        printf("%5d. %-25s (%lld)\n",
               i,
               vocab[i],
               freq[i]);
    }

    printf("=======================\n");
}

// ============================================================================
// Mengubah data menjadi array WordFreq
// Dipakai untuk heap
// ============================================================================

WordFreq *createWordArray(void)
{
    WordFreq *words =
        (WordFreq *)malloc(W * sizeof(WordFreq));

    if (words == NULL)
    {
        printf("Error: alokasi WordFreq gagal\n");
        return NULL;
    }

    for (int i = 1; i <= W; i++)
    {
        words[i - 1].wordID = i;

        strcpy(words[i - 1].word, vocab[i]);

        words[i - 1].frequency = freq[i];
    }

    return words;
}

// ============================================================================
// Membebaskan memori
// ============================================================================

void freeData(void)
{
    if (vocab != NULL)
    {
        for (int i = 1; i <= W; i++)
        {
            if (vocab[i] != NULL)
            {
                free(vocab[i]);
            }
        }

        free(vocab);
        vocab = NULL;
    }

    if (freq != NULL)
    {
        free(freq);
        freq = NULL;
    }

    W = 0;
}
