#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fftw3.h>
#include <math.h>

// FFT function
void fft_lib(fftw_complex *in, fftw_complex *out, int size) {
    // Create a new FFTW plan for computing the FFT
    fftw_plan plan = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // Execute the FFT
    clock_t start = clock();
    fftw_execute(plan);
    clock_t end = clock();
    // Destroy the plan
    fftw_destroy_plan(plan);

    printf("FFT result for size %f:\n", log2(size));
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate vectors of different sizes and perform FFT on them
    for (int i = 10; i <= 25; i++) {
        int size = 1 << i;
        fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
        fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);

        // Generate random input vector
        for (int j = 0; j < size; j++) {
            in[j][0] = rand() / (double) RAND_MAX;
            in[j][1] = rand() / (double) RAND_MAX;
        }

        // Time the execution of FFT using the fft_lib function
        
        fft_lib(in, out, size);
        
        

        // Print the output and the elapsed time
        
        // Free memory
        fftw_free(in);
        fftw_free(out);
    }

    return 0;
}

