#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "listas.h"

#define CHEGADA 1
#define PARTIDA 0

//gcc -lm guiao_3a.c listas.o -o run 
int main(int argc, char **argv){
    
    //read user values
    float lambda = atof(argv[1]);
    printf("Lambda: %.1f\n", lambda);

    int n_samples = atoi(argv[2]);
    printf("Nº de amostras: %d\n", n_samples);

    int N = atoi(argv[3]);
    printf("Número de servidores: %d\n", N);

    //declare variables
    double c[n_samples], d[n_samples], num_c, num_d, delta_time_c, delta_time_d, dm;
    int i, j, vmin, size_histo, tipo_ev, busy, blocked, count_arrivals;
    float sum, vmax, delta, average, tempo_ev;
    lista  * lista_eventos = NULL;
    FILE *f;

    //random seed
    srand(time(0));

    busy = 0;
    blocked = 0;
    dm = 0.008;
    count_arrivals = 0;
    sum = 0;

    //add initial element
    delta_time_c = 0;
    lista_eventos = adicionar(lista_eventos, 1, delta_time_c);
    //generate exponential distribuited numbers
    while(count_arrivals < n_samples){

        if(lista_eventos->tipo == CHEGADA){
            
            if (busy < N){
                //generate number c
                num_c = (rand()+1) / (double)RAND_MAX;
                c[count_arrivals] = -1/lambda * log(num_c);

                busy++;

                //generate number d
                num_d = (rand()+1) / (double)RAND_MAX;
                d[count_arrivals] = -dm * log(num_d);

                //for future averating
                sum+= c[count_arrivals];

                //update list
                delta_time_c = lista_eventos->tempo + c[count_arrivals];
                delta_time_d = lista_eventos->tempo + d[count_arrivals];

                //update total number of calls
                count_arrivals++;

                lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c);
                lista_eventos = adicionar(lista_eventos, PARTIDA, delta_time_d);



                //remove previous arrival
                lista_eventos = remover(lista_eventos);
            }
            else if(busy == N){
                blocked++;
            
                //generate new arrival
                num_c = (rand()+1) / (double)RAND_MAX;
                c[count_arrivals] = -1/lambda * log(num_c);
                sum+= c[count_arrivals];
                delta_time_c = lista_eventos->tempo + c[count_arrivals];
                lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c);



                //update total number of calls
                count_arrivals++;

                //remove previous arrival
                lista_eventos = remover(lista_eventos);

            }
        }
        else if(lista_eventos->tipo == PARTIDA){
            busy--;
            //remove departure
            lista_eventos = remover(lista_eventos);
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
            if(c[j] >= i*delta && c[j] < (i+1)*delta){
                histograma[i]++;
            }
        }
    }

    average = 1 / (sum / (float) n_samples);

    //Print paramenteres calculates
    printf("bin size: %.3f\n", delta);
    printf("Average Value: %.2f\n", average);
    printf("Blocked percentage: %.2f%%\n", (float)blocked/n_samples*100);
    

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