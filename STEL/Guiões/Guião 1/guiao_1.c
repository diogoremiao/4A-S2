#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
    
    float lambda = atof(argv[1]);
    printf("Lambda: %.1f\n", lambda);

    int n_samples = atoi(argv[2]);
    printf("Nº de amostras: %d\n", n_samples);

    double x[n_samples];
    int i,j;
    double num;

    //generate exponential distribuited numbers
    for(i=0; i<n_samples;i++){
        num=(random()+1)/(double)RAND_MAX;
        x[i]=-1/lambda*log(num);
    }


    //create histogram
    int vmin = 0;
    float vmax = 5/lambda;
    float delta = (float)1/5*1/lambda;
    int size_histo=(vmax-vmin)/delta;
    int histograma[size_histo];

    for (i=0;i<size_histo;i++){
        histograma[i]=0;
        
        for(j=0;j<n_samples;j++){
            if(x[j]>=i*delta && x[j]<(i+1)*delta){
                histograma[i]++;
            }
        }
        printf("%d ", histograma[i]);
    }
    printf("\n");

    printf("bin size: %f\n",delta);
    
    //export data

    FILE *f;
    f = fopen("samples.txt", "w");
    if (f == NULL){
        printf("Error opening file!\n");
        return 0;
    }

    for(i=0; i<size_histo;i++){
        fprintf(f, "%d ", histograma[i]);
    }

    fclose(f);

    return 0;
}