#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "heap.h"

#define K 100

// Menyimpan hasil ke file
void saveResult(const char *filename, WordFreq heap[], int size)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Gagal membuat file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(fp,
                "%s (%lld)\n",
                vocab[heap[i].wordID],
                heap[i].frequency);
    }

    fclose(fp);
}

// Menampilkan hasil ke layar
void displayResult(WordFreq heap[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%3d. %-25s (%lld)\n",
               i + 1,
               vocab[heap[i].wordID],
               heap[i].frequency);
    }
}

int main()
{
    char docwordFile[256];
    char vocabFile[256];

    WordFreq frequentHeap[K];
    WordFreq rareHeap[K];

    int frequentSize = 0;
    int rareSize = 0;

    double frequentTime = 0;
    double rareTime = 0;

    int choice;

    // Input file

    printf("Masukkan file docword : ");
    scanf("%255s", docwordFile);

    printf("Masukkan file vocab   : ");
    scanf("%255s", vocabFile);

    // Load data

    loadDocword(docwordFile);
    loadVocabulary(vocabFile);

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("1. Top 100 kata paling sering\n");
        printf("2. Top 100 kata paling jarang\n");
        printf("3. Tampilkan kata paling sering\n");
        printf("4. Tampilkan kata paling jarang\n");
        printf("5. Keluar\n");
        printf("=====================================\n");
        printf("Pilihan : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                frequentSize = 0;

                clock_t start = clock();

                for (int i = 1; i <= W; i++)
                {
                    WordFreq item;

                    item.wordID = i;
                    item.frequency = freq[i];

                    insertMinHeap(
                        frequentHeap,
                        &frequentSize,
                        K,
                        item
                    );
                }

                heapSortDescending(
                    frequentHeap,
                    frequentSize,
                    1
                );

                clock_t end = clock();

                frequentTime =
                    ((double)(end - start) * 1000)
                    / CLOCKS_PER_SEC;

                saveResult(
                    "top100_frequent.txt",
                    frequentHeap,
                    frequentSize
                );

                printf("\nTop 100 kata paling sering berhasil disimpan.\n");
                printf("Waktu proses : %.3f ms\n",
                       frequentTime);

                break;
            }

            case 2:
            {
                rareSize = 0;

                clock_t start = clock();

                for (int i = 1; i <= W; i++)
                {
                    if (freq[i] > 0)
                    {
                        WordFreq item;

                        item.wordID = i;
                        item.frequency = freq[i];

                        insertMaxHeap(
                            rareHeap,
                            &rareSize,
                            K,
                            item
                        );
                    }
                }

                heapSortDescending(
                    rareHeap,
                    rareSize,
                    0
                );

                clock_t end = clock();

                rareTime =
                    ((double)(end - start) * 1000)
                    / CLOCKS_PER_SEC;

                saveResult(
                    "top100_rare.txt",
                    rareHeap,
                    rareSize
                );

                printf("\nTop 100 kata paling jarang berhasil disimpan.\n");
                printf("Waktu proses : %.3f ms\n",
                       rareTime);

                break;
            }

            case 3:
            {
                printf("\n===== TOP 100 PALING SERING =====\n");

                displayResult(
                    frequentHeap,
                    frequentSize
                );

                printf("\nWaktu proses : %.3f ms\n",
                       frequentTime);

                break;
            }

            case 4:
            {
                printf("\n===== TOP 100 PALING JARANG =====\n");

                displayResult(
                    rareHeap,
                    rareSize
                );

                printf("\nWaktu proses : %.3f ms\n",
                       rareTime);

                break;
            }

            case 5:
            {
                printf("\nProgram selesai.\n");
                break;
            }

            default:
            {
                printf("\nPilihan tidak valid.\n");
            }
        }

    } while (choice != 5);

    freeData();

    return 0;
}
