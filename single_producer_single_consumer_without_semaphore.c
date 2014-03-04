/*

    Based on http://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem

    To compile & link, run 
    gcc -Wall -O2 -c single_producer_single_consumer_without_semaphore.c
    gcc -lpthread single_producer_single_consumer_without_semaphore.o 

*/

#include <pthread.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define BUFFER_SIZE 37

/*
    prod_idx : head of the buffer (producer)
    cons_idx : tail of the buffer (consume)
*/
volatile unsigned short prod_cnt = 0, cons_cnt = 0, prod_idx = 0, cons_idx = 0;
volatile char buffer[BUFFER_SIZE]; 

void *producer(void *arg) {
	while (1) {
		while (prod_cnt - cons_cnt == BUFFER_SIZE) sleep(1);
		assert(buffer[prod_idx] == 0);
		buffer[prod_idx] = 1;  /* produce item */
		asm volatile ("" ::: "memory");
		++prod_cnt, prod_idx = (prod_idx + 1) % BUFFER_SIZE;
	}
}

void *consumer(void *arg) {
	while (1) {
		while (prod_cnt - cons_cnt == 0) sleep(1);
		assert(buffer[cons_idx] == 1);
		buffer[cons_idx] = 0;  /* consume item */
		asm volatile ("" ::: "memory");
		++cons_cnt, cons_idx = (cons_idx + 1) % BUFFER_SIZE;
	}
}

int main(int argc, char *argv[]) {
	pthread_t prod, cons;
	memset((void *)buffer, 0, BUFFER_SIZE * sizeof(char));
	pthread_create(&prod, NULL, &producer, NULL);
	pthread_create(&cons, NULL, &consumer, NULL);
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	exit(0);
}
