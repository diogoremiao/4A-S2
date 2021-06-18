#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "listas.h"

#define CHEGADA 1
#define PARTIDA 0

float find_maximum(double[], int);

//gcc -lm guiao_3c.c listas.o -o run 
int main(int argc, char **argv){
    
    //read user values
    float lambda = atof(argv[1]);
    printf("Lambda: %.1f\n", lambda);

    int n_samples = atoi(argv[2]);
    printf("Nº de amostras: %d\n", n_samples);

    int N = atoi(argv[3]);
    printf("Número de servidores: %d\n", N);

    int L = atoi(argv[4]);
    printf("Tamanho da fila de espera: %d\n", L);

    //declare variables
    double c, d, delay[n_samples], num_c, num_d, delta_time_c, delta_time_d, dm;
    int i, j, size_histo, tipo_ev, busy, Q, count_arrivals, count_delays, total_delays, blocked;
    float sum, sum_delays, vmin, vmax, delta, average, tempo_ev, prob_delay, average_delay;
    lista  * lista_eventos = NULL;
    lista  * lista_espera = NULL;

    FILE *f;

    //random seed
    srand(time(0));
    blocked = 0;
    busy = 0;
    Q = 0;
    dm = 0.008;
    count_arrivals = 0;
    count_delays = 0;
    total_delays = 0;
    sum = 0;
    sum_delays = 0;

    //add initial element
    delta_time_c = 0;
    lista_eventos = adicionar(lista_eventos, 1, delta_time_c);
    //generate exponential distribuited numbers

    while(count_arrivals < n_samples){

        //check if is arrival
        if(lista_eventos->tipo == CHEGADA){
            //not busy
            if(busy<N){
                //generate number c
                num_c = (rand()+1) / (double)RAND_MAX;
                c = -1/lambda * log(num_c);
                count_arrivals ++;

                //generate number d
                num_d = (rand()+1) / (double)RAND_MAX;
                d = -dm * log(num_d);

                //for future averating
                sum+= c;

                //update list
                delta_time_c = lista_eventos->tempo + c;
                delta_time_d = lista_eventos->tempo + d;

                lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c);
                lista_eventos = adicionar(lista_eventos, PARTIDA, delta_time_d);

                //update busy
                busy++;

                //remove previous arrival
                lista_eventos = remover(lista_eventos);
            }
            else if(busy == N){

                //check if there is space in queue
                if (Q < L){
                    Q++;
                    lista_espera = adicionar(lista_espera, CHEGADA, lista_eventos->tempo);

                    //update total calls
                    count_arrivals ++;

                    //update the total number of delays
                    total_delays++;
                
                    //generate new arrival
                    num_c = (rand()+1) / (double)RAND_MAX;
                    c = -1/lambda * log(num_c);
                    sum+= c;
                    delta_time_c = lista_eventos->tempo + c;

                    //add to events list
                    lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c);
                    lista_eventos = remover(lista_eventos);
                }
                //queue full
                else if (Q == L){
                    //update blocked
                    blocked++;

                    //update total calls
                    count_arrivals ++;

                    //generate new arrival
                    num_c = (rand()+1) / (double)RAND_MAX;
                    c = -1/lambda * log(num_c);
                    sum+= c;
                    delta_time_c = lista_eventos->tempo + c;

                    //add to events list
                    lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c);
                    lista_eventos = remover(lista_eventos);
                }
            }            
        }
        //check if is departure
        else if(lista_eventos->tipo == PARTIDA){

            //check if there is anything in the queue
            if (Q > 0 ){
                //calculate delay
                delay[count_delays] = lista_eventos->tempo - lista_espera->tempo;
                sum_delays+=delay[count_delays];

                count_delays++;


                //generate new departure
                num_d = (rand()+1) / (double)RAND_MAX;
                d = -dm * log(num_d);
                delta_time_d = lista_eventos->tempo + d;
                lista_eventos = adicionar(lista_eventos, PARTIDA, delta_time_d);

                //remove previous departure
                lista_eventos = remover(lista_eventos);

                //remove from queue and update
                lista_espera = remover(lista_espera);
                Q--;

            }
            //queue empty
            else if (Q == 0) {
                //update busy
                busy--;

                //no deplay for that arrival
                delay[count_delays] = 0;
                count_delays++;

                //remove previous departure
                lista_eventos = remover(lista_eventos);
            }
        }    
    }


    //create histogram

    //paramenters
    vmin = 0;
    vmax = find_maximum(delay,count_delays);
    delta = 0.001;
    size_histo = (vmax-vmin) / delta;
    int histograma [size_histo];


    //check each element for its distribution
    for (i = 0; i < size_histo; i++){
        histograma[i] = 0;
        
        for(j = 0; j < count_delays; j++){
            if(delay[j] >= i*delta && delay[j] < (i+1)*delta){
                histograma[i]++;
            }
        }
    }

    average = 1 / (sum / (float) n_samples);
    prob_delay = (float)total_delays/n_samples*100;
    average_delay = sum_delays/count_delays;

    //Print paramenteres calculates
    printf("bin size: %.3f\n", delta);
    printf("Average Value: %.2f\n", average);
    printf("Probability of Delay: %.4f\n", prob_delay);
    printf("Average Delay: %.5f\n", average_delay);
    printf("Packet Loss Probability: %.2f%%\n", (float)blocked/n_samples*100);


    

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


float find_maximum(double a[], int n) {
  int c, index = 0;

  for (c = 1; c < n; c++)
    if (a[c] > a[index])
      index = c;

  return (float)a[index];
}