#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_CYLINDERS 100
#define NUM_REQUESTS 20

int compare( const void *a, const void *b);

int main()
{

    int initial_pos = 47;
    int StartSlot = 1000;
    int requests[NUM_REQUESTS];
    int new_requests[NUM_REQUESTS];


    for (int i = 0; i < NUM_REQUESTS; i++)
    {
        requests[i] = rand() % NUM_CYLINDERS;
    }

    qsort(requests,NUM_REQUESTS,sizeof(int),compare);

    for(int i = 0; i < NUM_REQUESTS; i++){
        printf("SLOT: %d VALUE: %d \n", i, requests[i]);
    }

    for(int i = 0; i < NUM_REQUESTS; i++){
        if((requests[i] % initial_pos) < initial_pos)
            initial_pos = i;
    }


    for(int i = 0; i < NUM_REQUESTS; i++){
        new_requests[i%StartSlot] =  requests[i];
    }

    for(int i = 0; i < NUM_REQUESTS; i++){
        printf("SLOT: %d VALUE: %d \n", i, requests[i]);
    }
    
}

int compare(const void *a, const void *b){
    
    int *x = (int*) a;
    int *y = (int*) b;

    

    return *x-*y;
}