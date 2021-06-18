#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "listas.h"

#define PARTIDA_GP 0
#define PARTIDA_AS 1
#define CHEGADA 2


double find_maximum(double[], int);
int generate_call_type();
double generate_arrival(double lambda);
double generate_departure_GP(double lambda);
double generate_departure_AS(double lambda);
double running_delay_average(double average, double delay, int n);

//gcc -lm guiao_4a.c listas.o -o run 
int main(int argc, char **argv){

    int n_samples = atoi(argv[1]);
    printf("Nº de amostras: %d\n", n_samples);

    int N = atoi(argv[2]);
    printf("Número de servidores GP: %d\n", N);

    int L = atoi(argv[3]);
    printf("Tamanho da fila de espera GP: %d\n", L);

    //declare variables
    int i, j, size_histo, busy, Q, count_arrivals, count_delays, count_all_delays, total_delays, blocked;
    double sum, sum_delays, sum_average_error, vmin, vmax, delta, c, d, delay[n_samples], delta_time_c, delta_time_d, delay_running_average, running_average_error[n_samples];
    lista  * lista_eventos = NULL;
    lista  * lista_espera = NULL;

    FILE *f;

    //random seed
    srand(time(0));

    blocked = 0;
    busy = 0;
    Q = 0;
    count_arrivals = 0;
    count_delays = 0;
    count_all_delays = 0;
    total_delays = 0;
    sum = 0;
    sum_delays = 0;
    delay_running_average = 0;
    sum_average_error = 0;

    //arrival rate
    double lambda = 1.33;
    //service rate gp
    double dm_gp = 2;

    //add initial element
    delta_time_c = 0;
    lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c, 0);

    while(count_arrivals < n_samples){

        //check if is arrival
        if(lista_eventos->tipo == CHEGADA){
            //not busy
            if(busy<N){
                //generate number c
                c = generate_arrival(lambda);
                count_arrivals ++;

                //generate number d

                d = generate_departure_GP(dm_gp);

                //for future averating
                sum+= c;

                //update list
                delta_time_c = lista_eventos->tempo + c;
                delta_time_d = lista_eventos->tempo + d;

                lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c, 0);
                lista_eventos = adicionar(lista_eventos, PARTIDA_GP, delta_time_d, 0);

                //update busy
                busy++;

                //remove previous arrival
                lista_eventos = remover(lista_eventos);
            }
            else if(busy == N){

                //check if there is space in queue
                if (Q < L){
                    Q++;
                    lista_espera = adicionar(lista_espera, CHEGADA, lista_eventos->tempo, 0);

                    //update total calls
                    count_arrivals ++;

                    //update the total number of delays
                    total_delays++;
                
                    //generate new arrival
                    c = generate_arrival(lambda);
                    sum+= c;
                    delta_time_c = lista_eventos->tempo + c;

                    //add to events list
                    lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c, 0);
                    lista_eventos = remover(lista_eventos);
                }
                //queue full
                else if (Q == L){
                    //update blocked
                    blocked++;

                    //update total calls
                    count_arrivals ++;

                    //generate new arrival
                    c = generate_arrival(lambda);
                    sum+= c;
                    delta_time_c = lista_eventos->tempo + c;

                    //add to events list
                    lista_eventos = adicionar(lista_eventos, CHEGADA, delta_time_c, 0);
                    lista_eventos = remover(lista_eventos);
                }
            }            
        }
        //check if is departure
        else if(lista_eventos->tipo == PARTIDA_GP){

            //check if there is anything in the queue
            if (Q > 0 ){
                //calculate delay
                delay[count_delays] = lista_eventos->tempo - lista_espera->tempo;
                sum_delays+=delay[count_delays];


                //printf("Difference between pred and real: %f\n", delay[count_delays] - delay_running_average);

                running_average_error[count_all_delays] = fabs(delay[count_delays] - delay_running_average);
                sum_average_error += running_average_error[count_all_delays];

                count_delays++;
                count_all_delays++;
                //update running delay average
                delay_running_average = running_delay_average(delay_running_average, delay[count_delays - 1], count_all_delays);
                //printf("New Delay: %f\n", delay[count_delays - 1]);
                //printf("Average: %f\n", delay_running_average);


                //generate new departure
                d = generate_departure_GP(dm_gp);
                delta_time_d = lista_eventos->tempo + d;
                lista_eventos = adicionar(lista_eventos, PARTIDA_GP, delta_time_d, 0);

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

                //no delay for that arrival
                
                //printf("Difference between pred and real: %f\n", delay[count_delays] - delay_running_average);

                running_average_error[count_all_delays] =fabs(0 - delay_running_average);
                sum_average_error += running_average_error[count_all_delays];

                count_all_delays++;

                //update running delay average
                delay_running_average = running_delay_average(delay_running_average, 0, count_all_delays);
                //printf("New Delay: 0\n");
                //printf("Average: %f\n", delay_running_average);
                
                
                //remove previous departure
                lista_eventos = remover(lista_eventos);
            }
        }    
    }


    //create histogram for delays

    //paramenters
    vmin = 0;
    vmax = find_maximum(delay,count_delays);
    delta = 0.25;
    size_histo = (vmax-vmin) / delta;
    int histograma_delays [size_histo];


    //check each element for its distribution
    for (i = 0; i < size_histo; i++){
        histograma_delays[i] = 0;
        
        for(j = 0; j < count_delays; j++){
            if(delay[j] >= i*delta && delay[j] < (i+1)*delta){
                histograma_delays[i]++;
            }
        }
    }

    //export data to file

    //try open the file
    f = fopen("samples_delays.txt", "w");
    if (f == NULL){
        printf("Error opening file!\n");
        return 0;
    }
    
    //write in the file
    for(i = 0; i < size_histo; i++){
        fprintf(f, "%d ", histograma_delays[i]);
    }
    fclose(f);

    //create histogram for delay error

    //paramenters
    vmin = 0;
    vmax = find_maximum(running_average_error,count_all_delays);
    delta = 0.01;
    size_histo = (vmax-vmin) / delta;
    int histograma_errors [size_histo];


    //check each element for its distribution
    for (i = 0; i < size_histo; i++){
        histograma_errors[i] = 0;
        
        for(j = 0; j < count_delays; j++){
            if(delay[j] >= i*delta && delay[j] < (i+1)*delta){
                histograma_errors[i]++;
            }
        }
    }

    //export data to file

    //try open the file
    f = fopen("samples_errors.txt", "w");
    if (f == NULL){
        printf("Error opening file!\n");
        return 0;
    }
    
    //write in the file
    for(i = 0; i < size_histo; i++){
        fprintf(f, "%d ", histograma_errors[i]);
    }
    fclose(f);

    //Print parameteres calculated
    printf("bin size: %.3f\n", delta);
    printf("Average Value: %.2f\n", 1 / (sum / (double) n_samples));
    printf("Probability of Delay: %.4f\n", (double)total_delays/n_samples*100);
    printf("Average Delay (not counting zeros): %.5f\n", sum_delays/count_delays);
    printf("Packet Loss Probability: %.2f%%\n", (double)blocked/n_samples*100);
    printf("Average Delay: %.2f\n", delay_running_average);
    printf("Average Absolute error: %.2f\n", sum_average_error/count_all_delays);
    printf("Average Relative error: %.2f%%\n", fabs((sum_average_error / count_all_delays - delay_running_average) / delay_running_average * 100));

    return 0;
}


double find_maximum(double a[], int n) {
  int c, index = 0;

  for (c = 1; c < n; c++)
    if (a[c] > a[index])
      index = c;

  return (double)a[index];
}


int generate_call_type() {
    double num;
    num = (rand()+1) / (double)RAND_MAX;

    if (num < 0.3)
        return PARTIDA_GP;
    else 
        return PARTIDA_AS;
}

double generate_arrival(double lambda){
    double num_c, c;
    
    num_c = (rand()+1) / (double)RAND_MAX;
    c = -1/lambda * log(num_c);

    return c;
}

double generate_departure_GP(double lambda){
    double num_d, d;
    while(1){
        num_d = (rand()+1) / (double)RAND_MAX;
        d = -lambda * log(num_d);
        if ((d > 1) && (d < 5))
            return d;
    }
}

double generate_departure_AS(double lambda){
    double num_d, d;
    
    while(1){
        num_d = (rand()+1) / (double)RAND_MAX;
        d = -lambda * log(num_d);
        if ((d > 1) && (d < 5))
            return d;
    }
}

double running_delay_average(double average, double delay, int n){

    return average*(double)(n-1)/n + delay/n;
}