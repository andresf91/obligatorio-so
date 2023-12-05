#include <iostream>
#include <semaphore.h>
#include <pthread.h>

sem_t cocinar_sem;
int platosDia = 0; // con cuántos platos comienzo el día
int mostradorLibre = 27; // cuántos espacios libres hay en el mostrador

void *cocinero(void *arg) { // defino el proceso de cada cocinero, como puntero

    int id = *((int *)arg); // inicializo el entero id para poder usarlo desde el pthread_create

    while ((platosDia + id) < 180) { // mientras no corramos riesgo de pasarnos de 180 platos diarios
        sem_wait(&cocinar_sem); // espero que el semáforo esté libre y lo tomo
        // Sección crítica
        platosDia++; // aumento la cantidad de platos cocinados hoy
        mostradorLibre--; // disminuyo el espacio libre en el mostrador
        sem_post(&cocinar_sem);
    }
    pthread_exit(NULL); // salgo del thread
}

int main() {
    sem_init(&cocinar_sem, 0, 1); // inicio el semáforo

    int cocineros = 3, i; // límite de cocineros trabajando es 3. variable i es auxiliar

    pthread_t tid[cocineros]; 

    for (i = 0; i < cocineros; i++) { // un hilo por cocinero
        int *id = new int(i); // para pasar el parámetro del id de cocinero
        pthread_create(&tid[i], NULL, cocinero, (void *)id); // creo el hilo
    }

    for (i = 0; i < cocineros; i++) {
        pthread_join(tid[i], NULL); // ejecuto el hilo
    }

    sem_destroy(&cocinar_sem); // destruyo el semáforo

    return 0;
}
