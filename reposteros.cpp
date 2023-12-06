#include <iostream>
#include <semaphore.h>
#include <pthread.h>

int main() {

    // para este no necesitamos threads porque es un solo repostero

    sem_t hacerPostresSem;
    int flanesHeladera=25; // postres en heladera
    int check=flanesHeladera; // variable auxiliar de chequeo
    int i;

    sem_init(&hacerPostresSem, 0, 1); // inicio el semáforo

    while(true){ // inicio "superbucle" para mantener proceso corriendo

        while (check>0){
            // mientras haya flanes en la heladera
            // solamente actualizo la variable de chequeo
            // para el próximo bucle

            sem_wait(&hacerPostresSem); // espero que el semáforo esté libre y lo tomo
            check=flanesHeladera;
            sem_post(&hacerPostresSem); // libero el semáforo

        }

        // cuando se terminen los flanes en la heladera
        // cocino 25 flanes

        for (i=0;i<25;i++){
            sem_wait(&hacerPostresSem); // espero que el semáforo esté libre y lo tomo
            // preparo un flan
            flanesHeladera++;
            sem_post(&hacerPostresSem); // libero el semáforo
        }

        check=flanesHeladera; // actualizo variable de chequeo para el próximo superbucle

    }

    return 0;


}