#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#include <math.h>
#include <pthread.h>


complex float* naivefft(float *arrin, int size){
    complex float *ans = malloc(size * sizeof(complex float));;
    for(int k = 0; k < size; k++){
        ans[k] = 0;
        for(int n = 0; n < size; n++){
            ans[k] +=  arrin[k] * cexp(2*M_PI*I*k * n/size);
        }
    }

    // lets do a naieve one
    return ans;

}

//SIZE MUST BE A POWER OF 2 FOR THIS IMPLEMENTATION
#include <stdlib.h>
#include <complex.h>
#include <math.h>

complex float* normalfft(float *arrin, int size) {
    // Check if size is a power of 2
    if ((size & (size - 1)) != 0) {
        return NULL;
    }

    // Allocate memory to the answer
    complex float *ans = malloc(size * sizeof(complex float));
    if (ans == NULL) {
        return NULL;
    }

    if (size == 1) {
        ans[0] = arrin[0] + 0.0*I;
    } else {
        float *evens = malloc((size/2) * sizeof(float));
        float *odds = malloc((size/2) * sizeof(float));
        if (evens == NULL || odds == NULL) {
            free(ans);
            free(evens);
            free(odds);
            return NULL;
        }

        for (int m = 0; m < size/2; m++) {
            evens[m] = arrin[2*m];
            odds[m] = arrin[2*m + 1];
        }

        complex float* evens_ft = normalfft(evens, size/2);
        complex float* odds_ft = normalfft(odds, size/2);
        if (evens_ft == NULL || odds_ft == NULL) {
            free(ans);
            free(evens);
            free(odds);
            free(evens_ft);
            free(odds_ft);
            return NULL;
        }

        for (int k = 0; k < size/2; k++) {
            ans[k] = evens_ft[k] - cexp(-2 * M_PI * I * k/size) * odds_ft[k];
            ans[size/2 + k] = evens_ft[k] + cexp(-2 * M_PI * I * k/size) * odds_ft[k];
        }

        free(evens);
        free(odds);
        free(evens_ft);
        free(odds_ft);
    }
    
    return ans;
}



int main() {
    srand(time(NULL));

    for(int p = 0; p <= 25; p++){
        int size = pow(2, p);
        float *data = malloc(size * sizeof(float));


        // generate random data
        for(int i = 0; i < size; i++){
            data[i] = (float) rand() / (float) RAND_MAX * 10; 
        }

        // compute FFT
        clock_t start = clock();
        complex float* f = normalfft(data, size);
        clock_t end = clock();
        double elapsed_time = (double)(end - start);
        printf("FFT of size %f runs in %f\n", log2(size), elapsed_time/ CLOCKS_PER_SEC);

        // print results
        printf("\n");
        // free memory
        free(f);
    }
    
    return 0;
}








