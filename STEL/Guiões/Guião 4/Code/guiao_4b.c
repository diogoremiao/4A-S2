#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "listas.h"

#define PARTIDA_GP 0
#define PARTIDA_AS 1
#define CHEGADA 2

#define PI 3.14159265


double find_maximum(double[], int);
int generate_call_type();
double generate_arrival(double lambda);
double generate_departure_GP(double lambda);
double generate_departure_AS(double lambda);
double generate_departure_AS_GP(double mean, double deviation);
double running_delay_average(double average, double delay, int n);

//gcc -lm guiao_4b.c listas.o -o run 
int main(int argc, char **argv){

    int n_samples = atoi(argv[1]);
    printf("Nº de amostras: %d\n", n_samples);

    int N_GP = atoi(argv[2]);
    printf("Número de servidores GP: %d\n", N_GP);

    int N_AS = atoi(argv[3]);
    printf("Número de servidores AS: %d\n", N_AS);

    int L = atoi(argv[4]);
    printf("Tamanho da fila de espera GP: %d\n", L);

    //declare variables
    int i, j, size_histo, busy_gp, busy_as, Q_gp, Q_as, count_arrivals, count_delays, count_all_delays, total_delays, blocked, count_as;
    double sum, sum_delays, sum_average_error, sum_relative_error, vmin, vmax, delta, c, d, delay[n_samples], delta_time_c, delta_time_d, delay_running_average, running_average_error[n_samples], sum_total_wait_as;
    lista  * lista_eventos_gp = NULL;
    lista  * lista_eventos_as = NULL;
    lista  * lista_espera_gp = NULL;
    lista  * lista_espera_as = NULL;

    FILE *f;

    //random seed
    srand(time(0));

    blocked = 0;
    busy_gp = 0;
    busy_as = 0;
    Q_gp = 0;
    Q_as = 0;
    count_arrivals = 0;
    count_delays = 0;
    count_all_delays = 0;
    total_delays = 0;
    sum = 0;
    sum_delays = 0;
    delay_running_average = 1;
    sum_average_error = 0;
    sum_relative_error = 0;
    sum_total_wait_as = 0;
    count_as = 0;

    //arrival rate
    double lambda = 1.33;
    //service rate gp
    double dm_gp = 2;
    //service rate gp_as
    double mean_as = 1;
    double phi_as = 0.33;
    //service rate as
    double dm_as = 2.5;




    //add initial element
    delta_time_c = 0;
    lista_eventos_gp = adicionar(lista_eventos_gp, CHEGADA, delta_time_c, 0);

    while(count_arrivals < n_samples){

        //GP service
        if(lista_eventos_gp->tipo == CHEGADA){
            //printf("Chegada de uma chamada no servidor General Purpose\n");
            //not busy_gp
            if(busy_gp<N_GP){
                //printf("Há servidores disponíveis no servidor General Purpose\n");
                //generate number c
                //printf("Gera nova chegada no servidor General Purpose\n");
                c = generate_arrival(lambda);
                count_arrivals ++;

                //for future averating
                sum+= c;

                //update list
                delta_time_c = lista_eventos_gp->tempo + c;

                lista_eventos_gp = adicionar(lista_eventos_gp, CHEGADA, delta_time_c, 0);
                          
                //generate number d

                if (generate_call_type() == PARTIDA_GP){
                    //printf("Chamada é General Purpose\n");
                    d = generate_departure_GP(dm_gp);
                    delta_time_d = lista_eventos_gp->tempo + d;
                    lista_eventos_gp = adicionar(lista_eventos_gp, PARTIDA_GP, delta_time_d, 0);
                }

                else{
                    //printf("Chamada é Area Specific\n");
                    d = generate_departure_AS_GP(mean_as, phi_as);
                    delta_time_d = lista_eventos_gp->tempo + d;
                    lista_eventos_gp = adicionar(lista_eventos_gp, PARTIDA_AS, delta_time_d, lista_eventos_gp->tempo);
                }

                //update busy_gp
                busy_gp++;

                //remove previous arrival
                lista_eventos_gp = remover(lista_eventos_gp);
            }
            else if(busy_gp == N_GP){
                //printf("Não há servidores disponíveis no servidor General Purpose\n");
                //check if there is space in queue
                if (Q_gp < L){
                    //printf("Há espaço na fila no servidor General Purpose\n");
                    Q_gp++;
                    lista_espera_gp = adicionar(lista_espera_gp, CHEGADA, lista_eventos_gp->tempo, 0);

                    //update total calls
                    count_arrivals ++;

                    //update the total number of delays
                    total_delays++;
                
                    //generate new arrival
                    //printf("Gera nova chegada no servidor General Purpose\n");
                    c = generate_arrival(lambda);
                    sum+= c;
                    delta_time_c = lista_eventos_gp->tempo + c;

                    //add to events list
                    lista_eventos_gp = adicionar(lista_eventos_gp, CHEGADA, delta_time_c, 0);
                    lista_eventos_gp = remover(lista_eventos_gp);
                }
                //queue full
                else if (Q_gp == L){
                    //printf("Não há espaço na fila no servidor General Purpose\n");

                    //update blocked
                    blocked++;

                    //update total calls
                    count_arrivals ++;

                    //generate new arrival
                    //printf("Gera nova chegada no servidor General Purpose\n");

                    c = generate_arrival(lambda);
                    sum+= c;
                    delta_time_c = lista_eventos_gp->tempo + c;

                    //add to events list
                    lista_eventos_gp = adicionar(lista_eventos_gp, CHEGADA, delta_time_c, 0);
                    lista_eventos_gp = remover(lista_eventos_gp);
                }
            }            
        }
        else if(lista_eventos_gp->tipo == PARTIDA_GP){

            //printf("Partida de uma chamada General Purpose no servidor General Purpose\n");
            //check if there is anything in the queue
            if (Q_gp > 0 ){
                //printf("Há chamadas na fila de espera no servidor General Purpose\n");
                //calculate delay
                delay[count_delays] = lista_eventos_gp->tempo - lista_espera_gp->tempo;
                sum_delays+=delay[count_delays];


                //printf("Difference between pred and real: %f\n", delay[count_delays] - delay_running_average);

                running_average_error[count_all_delays] = fabs(delay[count_delays] - delay_running_average);
                sum_average_error += running_average_error[count_all_delays];
                sum_relative_error += (running_average_error[count_all_delays]/delay_running_average);

                //printf("AVRG %.2f\n", delay_running_average);
                //printf("DELAY %.2f\n", delay[count_delays]);
                //printf("ASB %.2f\n", running_average_error[count_all_delays]);
                //printf("REL %.2f\n\n", running_average_error[count_all_delays]/delay_running_average);


                count_delays++;
                count_all_delays++;
                //update running delay average
                delay_running_average = running_delay_average(delay_running_average, fabs(delay[count_delays - 1]), count_all_delays);
                //printf("New Delay: %f\n", delay[count_delays - 1]);
                //printf("Average: %f\n", delay_running_average);


                if (generate_call_type() == PARTIDA_GP){
                    //printf("Nova chamada é General Purpose\n");
                    d = generate_departure_GP(dm_gp);
                    delta_time_d = lista_eventos_gp->tempo + d;
                    lista_eventos_gp = adicionar(lista_eventos_gp, PARTIDA_GP, delta_time_d, 0);
                }

                else{
                    //printf("Nova chamada é Area Specific\n");
                    d = generate_departure_AS_GP(mean_as, phi_as);
                    delta_time_d = lista_eventos_gp->tempo + d;
                    lista_eventos_gp = adicionar(lista_eventos_gp, PARTIDA_AS, delta_time_d, lista_espera_gp->tempo);
                }

                //remove previous departure
                lista_eventos_gp = remover(lista_eventos_gp);

                //remove from queue and update
                lista_espera_gp = remover(lista_espera_gp);
                Q_gp--;

            }
            //queue empty
            else if (Q_gp == 0) {
                //printf("Não há chamadas na fila de espera no servidor General Purpose\n");

                //update busy
                busy_gp--;

                //no delay for that arrival
                
                //printf("Difference between pred and real: %f\n", delay[count_delays] - delay_running_average);

                running_average_error[count_all_delays] =fabs(0 - delay_running_average);
                sum_average_error += running_average_error[count_all_delays];
                sum_relative_error += (running_average_error[count_all_delays]/delay_running_average);
               
                //printf("AVRG %.2f\n", delay_running_average);
                //printf("DELAY 0\n");
                //printf("ASB %.2f\n", running_average_error[count_all_delays]);
                //printf("REL %.2f\n\n", running_average_error[count_all_delays]/delay_running_average);

                count_all_delays++;

                //update running delay average
                delay_running_average = running_delay_average(delay_running_average, 0, count_all_delays);
                //printf("New Delay: 0\n");
                //printf("Average: %f\n", delay_running_average);
                
                
                //remove previous departure
                lista_eventos_gp = remover(lista_eventos_gp);
            }
        }
        else if(lista_eventos_gp->tipo == PARTIDA_AS){
            //printf("Partida de uma chamada Area Specific no servidor General Purpose\n");

            //add initial element to as event list
            lista_eventos_as = adicionar(lista_eventos_as, CHEGADA, lista_eventos_gp->tempo, lista_eventos_gp->tempo_inicial_as);
            //printf("Reencaminhar chamada para o servidor Area Specific\n");

            if (Q_gp > 0 ){
                //printf("Há chamadas na fila de espera no servidor General Purpose\n");

                //calculate delay
                delay[count_delays] = lista_eventos_gp->tempo - lista_espera_gp->tempo;
                sum_delays+=delay[count_delays];


                //printf("Difference between pred and real: %f\n", delay[count_delays] - delay_running_average);

                running_average_error[count_all_delays] = fabs(delay[count_delays] - delay_running_average);
                sum_average_error += running_average_error[count_all_delays];
                sum_relative_error += (running_average_error[count_all_delays]/delay_running_average);

                //printf("AVRG %.2f\n", delay_running_average);
                //printf("DELAY %.2f\n", delay[count_delays]);                
                //printf("ASB %.2f\n", running_average_error[count_all_delays]);
                //printf("REL %.2f\n\n", running_average_error[count_all_delays]/delay_running_average);

                count_delays++;
                count_all_delays++;
                //update running delay average
                delay_running_average = running_delay_average(delay_running_average, fabs(delay[count_delays - 1]), count_all_delays);
                //printf("New Delay: %f\n", delay[count_delays - 1]);
                //printf("Average: %f\n", delay_running_average);


                //generate number d

                if (generate_call_type() == PARTIDA_GP){
                    //printf("Nova chamada é General Purpose\n");                    
                    d = generate_departure_GP(dm_gp);
                    delta_time_d = lista_eventos_gp->tempo + d;
                    lista_eventos_gp = adicionar(lista_eventos_gp, PARTIDA_GP, delta_time_d, 0);
                }

                else{
                    //printf("Nova chamada é Area Specific\n");                    
                    d = generate_departure_AS_GP(mean_as, phi_as);
                    delta_time_d = lista_eventos_gp->tempo + d;
                    lista_eventos_gp = adicionar(lista_eventos_gp, PARTIDA_AS, delta_time_d, lista_espera_gp->tempo);
                }

                //remove previous departure
                lista_eventos_gp = remover(lista_eventos_gp);

                //remove from queue and update
                lista_espera_gp = remover(lista_espera_gp);
                Q_gp--;

            }
            //queue empty
            else if (Q_gp == 0) {
                //printf("Não há chamadas na fila de espera no servidor General Purpose\n");

                //update busy
                busy_gp--;

                //no delay for that arrival
                
                //printf("Difference between pred and real: %f\n", delay[count_delays] - delay_running_average);

                running_average_error[count_all_delays] =fabs(0 - delay_running_average);
                sum_average_error += running_average_error[count_all_delays];
                sum_relative_error += (running_average_error[count_all_delays]/delay_running_average);

                //printf("AVRG %.2f\n", delay_running_average);
                //printf("DELAY 0\n");
                //printf("ASB %.2f\n", running_average_error[count_all_delays]);
                //printf("REL %.2f\n\n", running_average_error[count_all_delays]/delay_running_average);

                count_all_delays++;

                //update running delay average
                delay_running_average = running_delay_average(delay_running_average, 0, count_all_delays);
                //printf("New Delay: 0\n");
                //printf("Average: %f\n", delay_running_average);
                
                
                //remove previous departure
                lista_eventos_gp = remover(lista_eventos_gp);
            }
        }

        //AS service
        if(lista_eventos_as != NULL){
            //printf("Há chamadas no servidor Area Specific\n");

            if(lista_eventos_as->tipo == CHEGADA){   
                //printf("Chegada de uma chamada no servidor Area Specific\n");
                //not busy_gp
                if(busy_as<N_AS){
                    //printf("Há servidores disponíveis no servidor Area Specific\n");
                    //generate number d

                    //printf("Gerar partida da chamada no servidor Area Specific");
                    d = generate_departure_AS(dm_as);
                    delta_time_d = lista_eventos_as->tempo + d;
                    lista_eventos_as = adicionar(lista_eventos_as, PARTIDA_AS, delta_time_d, lista_eventos_as->tempo_inicial_as);

                    //update busy_as
                    busy_as++;

                    //remove previous arrival
                    lista_eventos_as = remover(lista_eventos_as);
                }
                else if(busy_as == N_AS){
                    //printf("Não há servidores disponíveis no servidor Area Specific\n");

                    Q_as++;
                    lista_espera_as = adicionar(lista_espera_as, CHEGADA, lista_eventos_as->tempo, lista_eventos_as->tempo_inicial_as);
                
                    lista_eventos_as = remover(lista_eventos_as);

                } 
            }
            else if(lista_eventos_as->tipo == PARTIDA_AS){
                //printf("Partida de uma chamada no servidor Area Specific\n");

                //check if there is anything in the queue
                if (Q_as > 0 ){
                    //printf("Há chamadas na fila de espera no servidor Area Specific\n");
                    //generate number d

                    //printf("Gerar partida da chamada na fila de espera no servidor Area Specific\n");
                    d = generate_departure_AS(dm_as);
                    delta_time_d = lista_eventos_as->tempo + d;
                    lista_eventos_as = adicionar(lista_eventos_as, PARTIDA_AS, delta_time_d, lista_espera_as->tempo_inicial_as);

                    sum_total_wait_as+=(lista_eventos_as->tempo - lista_espera_as->tempo_inicial_as);
                    count_as ++;


                    //remove previous departure
                    lista_eventos_as = remover(lista_eventos_as);

                    //remove from queue and update
                    lista_espera_as = remover(lista_espera_as);
                    Q_as--;

                }
                //queue empty
                else if (Q_as == 0) {
                    //printf("Não há chamadas na fila de espera no servidor Area Specific\n");

                    sum_total_wait_as+=(lista_eventos_as->tempo - lista_eventos_as->tempo_inicial_as);
                    count_as ++;

                    //update busy
                    busy_as--;
                    
                    //remove previous departure
                    lista_eventos_as = remover(lista_eventos_as);
                }     
            }
        }
    }


    //create histogram for delays

    //paramenters
    vmin = 0;
    vmax = find_maximum(delay,count_delays);
    delta = 0.10;
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
    //vmax = find_maximum(running_average_error,count_all_delays);
    vmax = 5 * sum_average_error/count_all_delays;
    delta = 0.01;
    size_histo = (vmax-vmin) / delta;
    int histograma_errors [size_histo];


    //check each element for its distribution
    for (i = 0; i < size_histo; i++){
        histograma_errors[i] = 0;
        if (i != size_histo - 1){
            for(j = 0; j < count_delays; j++){
                if(running_average_error[j] >= i*delta && running_average_error[j] < (i+1)*delta){
                    histograma_errors[i]++;
                }
            }
        }
        else {
            for(j = 0; j < count_delays; j++){
                if(running_average_error[j] >= i*delta){
                    histograma_errors[i]++;
                }
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
    printf("Probability of Delay in GP: %.4f\n", (double)total_delays/count_all_delays*100);
    printf("Average Delay (not counting zeros): %.5f\n", sum_delays/count_delays);
    printf("Packet Loss Probability: %.2f%%\n", (double)blocked/n_samples*100);
    printf("Average Delay: %.2f\n", delay_running_average);
    printf("Average Absolute error: %.2f\n", sum_average_error/count_all_delays);
    printf("Average Relative error: %.2f%%\n", sum_relative_error/count_all_delays*100);
    printf("Average Total Time for GP + AS : %.2f\n", sum_total_wait_as/count_as);
    printf("Average Total Wait Time : %.5f\n", sum_total_wait_as/count_as - 4.5);

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

double generate_departure_AS_GP(double mean, double deviation){
    double num_1, num_2, phi, r, x;
    
    while(1){
        num_1 = (rand()+1) / (double)RAND_MAX;
        num_2 = (rand()+1) / (double)RAND_MAX;
        
        phi = 2 * PI * num_1;
        r = sqrt(-2*log(num_2));

        x = r * cos(phi);
        x= x*deviation + mean;
        if ((x>0.5) && (x<2)){
             //printf("AS_GP: %f\n",x);
             return x;
        }
    }
}

double generate_departure_AS(double lambda){
    double num_d, d;
    
    while(1){
        num_d = (rand()+1) / (double)RAND_MAX;
        d = -lambda * log(num_d);
        if (d > 1){
            //printf("AS: %f\n",d);
            return d;
        }
    }
}

double running_delay_average(double average, double delay, int n){

    if (n == 1) return 1;

    return average*(double)(n-1)/n + delay/n;
}