/**
 *
 * File:   main.c
 * Author: Tyler Vodden
 * Lab 6
 *
 **/
#include <stdlib.h>     /* NULL */
#include  <stdio.h>	/* printf */
#include  <sys/types.h>	/* pid_t */
#include <unistd.h>	/* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h> 	/* wait */
#include <pthread.h>

#define PRODUCER_NO 5	//Number of producers
#define NUM_PRODUCED 2000 //Number of items to be produced

void *generator_function(void);
void *print_function(void);
long sum; /* Sum of generated values*/
long finished_producers; /* number of the producer that finished producing */

//C: Mutex declaration and initialization
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//F: Condition variable declaration and initialization
pthread_cond_t waiter = PTHREAD_COND_INITIALIZER;

int main(void) {
    /* initialize random seed: */
    
    pthread_t counterThread[5];
    pthread_t printThread;
    srand(time(NULL));
    sum = 0;
    //A: Creates five generator thread
     
    pthread_create(&counterThread[0], (void *) 0, generator_function, NULL);
    pthread_create(&counterThread[1], (void *) 0, generator_function, NULL);
    pthread_create(&counterThread[2], (void *) 0, generator_function, NULL);
    pthread_create(&counterThread[3], (void *) 0, generator_function, NULL);
    pthread_create(&counterThread[4], (void *) 0, generator_function, NULL);
    

    pthread_join( counterThread[0], NULL);
    pthread_join( counterThread[1], NULL);
    pthread_join( counterThread[2], NULL);
    pthread_join( counterThread[3], NULL);
    pthread_join( counterThread[4], NULL);
    
    //D: Creates print thread
     pthread_create(&printThread, (void *) 0, print_function, NULL);
    //B: Makes sure that all generator threads has finished before proceeding
     
    print_function();
    //E: Makes sure that print thread has finished before proceeding
    pthread_join(printThread, NULL);
    return (0);

}

void *generator_function(void) {

    long counter = 0;
    long sum_this_generator = 0;

    while (counter < 2000L) {

        long tmpNumber = sum;
        long rnd_number = rand() % 10;
        printf("current sum of the generated number up to now is %ld going to add %ld to it.\n", tmpNumber, rnd_number);
        sum = tmpNumber + rnd_number;
        counter++;
        sum_this_generator += rnd_number;
        usleep(1000);
    }
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    printf("The sum of produced items for this number generator at the end is: %ld \n", sum_this_generator);
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    finished_producers++;
    //H: If all generator has finished fire signal for condition variable
    return (0);
}

void *print_function(void) {
    //G: Wait until all generator has finished
    while (finished_producers != 5L)
    {
        pthread_cond_wait(&waiter, &mutex);
    }
    
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("The value of counter at the end is: %ld \n", sum);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}



