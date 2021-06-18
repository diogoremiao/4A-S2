#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "listas.h"

int main(int argc, char **argv){
    
    //read user values
    float lambda = atof(argv[1]);
    printf("Lambda: %.1f\n", lambda);

    int n_samples = atoi(argv[2]);
    printf("Nº de amostras: %d\n", n_samples);

    //declare variables
    double x[n_samples], num, delta_time, clock = 0;
    int i = 0, j, vmin, size_histo, tipo_ev, count=0;
    float sum = 0, vmax, delta, average, tempo_ev;
    lista  * lista_eventos = NULL;
    FILE *f;

    //define delta
    delta = 0.001;
    //random seend
    srand(time(0));


    //add initial element
    delta_time = 0;
    lista_eventos = adicionar(lista_eventos, 1, delta_time);
    //generate exponential distribuitedhistogram.xlsx numbers
    while(count < n_samples){
        //update time
        clock+=delta;
        num = (rand()+1) / (double)RAND_MAX;
        //check for probability
        if (num<=lambda*delta){
            //calculate time interval
            delta_time = clock - lista_eventos->tempo;
            //for future averaging
            sum += delta_time;
            count++;
            x[i] = delta_time;
            i++;
            //update list
            lista_eventos = adicionar(lista_eventos, 1, clock);
            if ( lista_eventos != NULL){
		        lista_eventos = remover(lista_eventos);
	        }
        }

    }
    //create histogram

    //paramenters
    vmin = 0;
    vmax = 5/lambda;
    delta = (float)1/5 * 1/lambda;
    size_histo = (vmax-vmin) / delta;
    int histograma [size_histo];


    //check each element for its distribution
    for (i = 0; i < size_histo; i++){
        histograma[i] = 0;
        
        for(j = 0; j < n_samples; j++){
            if(x[j] >= i*delta && x[j] < (i+1)*delta){
                histograma[i]++;
            }
        }
    }

    average = 1 / (sum / (float) n_samples);

    //Print paramenteres calculates
    printf("bin size: %.2f\n", delta);
    printf("Average Value: %.2f\n", average);
    

    //export data to file

    //try open the file
    f = fopen("samples.txt", "w");
    if (f == NULL){
        printf("Error opening file!\n");
        return 0;
    }
    
    //writein the file
    for(i = 0; i < size_histo; i++){
        fprintf(f, "%d ", histograma[i]);
    }
    fclose(f);

    return 0;
}