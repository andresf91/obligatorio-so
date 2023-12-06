#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <cstdlib>

sem_t servirSem;
int platosDia=0;
int flanesHeladera=25; // postres en heladera
                       // suponemos que el repostero la repone cuando se vacía
int platosMostrador=0; // platos de albóndiga en la mesas
                       // suponemos que los cocineros van reponiendo

void *mozo(void *arg) { // defino el proceso de cada mozo, como puntero

    int id = *((int *)arg); // inicializo el entero id para poder usarlo desde el pthread_create
                            // desreferencio el puntero, obteniendo el valor al que apunta
                            // me costó bastante llegar a esta solución para generar
                            // varios hilos, cada uno con el id del mozo
                            // que necesito, para la suma de la siguiente instrucción
    int pedido;

    while ((platosDia + id) < 180) {
        
        // simulamos el pedido
        pedido = rand() % 2; // 0 para albóndigas, 1 para flan

        if (pedido==0){
            // albóndiga
            sem_wait(&servirSem);
            // sección crítica

            if (platosMostrador>3){ // si hay 4 platos de albóndiga o más...

                // me llevo en una bandeja 4 platos de albóndigas
                platosMostrador=platosMostrador-4;
            }
            // si no hay 4, vuelve al bucle
            
            sem_post(&servirSem); // libero el semáforo
        }
        else {
            // flan
            sem_wait(&servirSem);
            // sección crítica

            if (flanesHeladera>5){ // si hay 6 flanes o más...

                // me llevo en una bandeja 6 flanes
                flanesHeladera=flanesHeladera-6;
            }
            // si no hay 6, vuelve al bucle
            
            sem_post(&servirSem); // libero el semáforo
            
        }
    }
    
    pthread_exit(NULL); // salgo del thread al terminar el día

}

int main(){

    sem_init(&servirSem, 0, 1); // inicio el semáforo

    int mozos = 5, i; // límite de mozos trabajando es 5. variable i es auxiliar

    pthread_t tid[mozos]; // array de identificadores de hilo

    for (i = 0; i < mozos; i++) { // un hilo por cocinero
        int *id = new int(i); // para pasar el parámetro del id del mozo
        pthread_create(&tid[i], NULL, mozo, (void *)id); // creo el hilo
        pthread_join(tid[i], NULL); // ejecuto el hilo
    }

    sem_close(&servirSem); // destruyo el semáforo

    return 0;
}