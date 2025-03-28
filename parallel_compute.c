#ifdef _MSC_VER
#pragma comment(lib, "msmpi.lib")
#include "C:/Program Files (x86)/Microsoft SDKs/MPI/Include/mpi.h"
#else
#include <mpi.h>
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define MASTER 0

int main(int argc, char** argv) {
    int world_size, world_rank;
    double start_time, end_time;

    // MPI Başlatılıyor
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // İşlemci sayısını al
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // İşlemci sırasını belirle

    // Veri bölme hesaplamaları
    int chunk_size = ARRAY_SIZE / world_size;
    int remainder = ARRAY_SIZE % world_size;
    int my_chunk_size = (world_rank < remainder) ? chunk_size + 1 : chunk_size;
    
    
    int *data = NULL;
    int *sub_array = (int*) malloc(my_chunk_size * sizeof(int));
    if (!sub_array) MPI_Abort(MPI_COMM_WORLD, 1);

    // Veri Hazırlığı (Sadece Master İşlemci İçin)
    if (world_rank == MASTER) {
        data = (int*) malloc(ARRAY_SIZE * sizeof(int));
        if (!data) MPI_Abort(MPI_COMM_WORLD, 1);
        srand(time(NULL)); // Rastgele sayı üretimi başlatılıyor
        for (int i = 0; i < ARRAY_SIZE; i++) data[i] = rand() % 100;
    }

    MPI_Barrier(MPI_COMM_WORLD); // Tüm işlemciler senkronize ediliyor
    start_time = MPI_Wtime(); // Zaman ölçümü başlatılıyor

    int *sendcounts = NULL;
    int *displs = NULL;
    
    if (world_rank == MASTER) {
        // Veri Bölme ve Dağıtma (MPI Kullanımı)
        sendcounts = (int*)malloc(world_size * sizeof(int));
        displs = (int*)malloc(world_size * sizeof(int));
        if (!sendcounts || !displs) MPI_Abort(MPI_COMM_WORLD, 1);
        int offset = 0;
        for (int i = 0; i < world_size; i++) {
            sendcounts[i] = (i < remainder) ? chunk_size + 1 : chunk_size;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }
    
    // Verinin işlemcilere dağıtılması
    MPI_Scatterv(data, sendcounts, displs, MPI_INT, sub_array, my_chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);
    
    int local_even_count = 0;
    
    // Hesaplama (OpenMP Kullanımı - Paralel Çalıştırma)
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Thread %d / %d çalışıyor!\n", thread_id, num_threads);
    }
    
    // Çift sayıları sayma işlemi
    #pragma omp parallel for reduction(+:local_even_count)
    for (int i = 0; i < my_chunk_size; i++) {
        if (sub_array[i] % 2 == 0) local_even_count++;
    }
    
    int global_even_count = 0;
    
    // Sonuçların Toplanması (MPI Reduce)
    MPI_Reduce(&local_even_count, &global_even_count, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
    
    end_time = MPI_Wtime(); 

    if (world_rank == MASTER) {
        
        printf("Toplam Çift Sayı Adedi: %d\n", global_even_count);
        printf("Toplam Süre: %.6f saniye\n", end_time - start_time);
        
       
        free(sendcounts);
        free(displs);
        free(data);
    }
    
    free(sub_array); 
    MPI_Finalize(); // MPI programı sonlandırılıyor
    return 0;
}
