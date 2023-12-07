#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define NUM_CYLINDERS 5000
#define NUM_REQUESTS 1000

int Fcfs(int requests[], int initial_pos);
int Sstf(int requests[], int initial_pos);
int Scan(int requests[], int initial_pos);
int CScan(int requests[], int initial_pos);
int Look(int requests[], int initial_pos);
int CLook(int requests[], int initial_pos);

int compare(const void *a, const void *b); //Compare function for q-sort

int main(int argc, char *argv[])
{
    srand(time(0));

    if (argc < 2)
    {
        printf("Usage: %s [initial head position]\n", argv[0]);
        return 1;
    }

    if (atoi(argv[1]) > 4999)
    {
        printf("ERROR Max head position is 4999. terminating program \n");
        exit(0);
    }

    // printf("argv[0]: %s\n" , argv[0]);
    // printf("argv[1]: %s\n" , argv[1]);

    int initial_pos = atoi(argv[1]);
    int requests[NUM_REQUESTS];

    for (int i = 0; i < NUM_REQUESTS; i++)
    {
        requests[i] = rand() % NUM_CYLINDERS;
    }

    printf("Total head movement for FCFS: %d\n", Fcfs(requests, initial_pos));
    printf("Total head movement for SSTF: %d\n", Sstf(requests, initial_pos));
    //printf("Total head movement for SCAN: %d\n", Scan(requests, initial_pos));
    //printf("Total head movement for C-SCAN: %d\n", CScan(requests, initial_pos));
    printf("Total head movement for Look: %d\n", Look(requests, initial_pos));
    //printf("Total head movement for C-Look: %d\n", CLook(requests, initial_pos));

    return 0;
}

int Fcfs(int requests[], int initial_pos)
{
    int movement_count = 0;
    int current_pos = initial_pos;

    for (int i = 0; i < NUM_REQUESTS; i++)
    {
        movement_count += abs(current_pos - requests[i]);
        current_pos = requests[i];
    }

    return movement_count;
}

int Sstf(int requests[], int initial_pos)
{
    int movement_count = 0;
    int current_pos = initial_pos;
    int new_requests[NUM_REQUESTS];
    int shortest_distance, shortest_index;

    // Copy requests to new_requests
    for (int i = 0; i < NUM_REQUESTS; i++){
        new_requests[i] = requests[i];
    }

    for (int i = 0; i < NUM_REQUESTS; i++){
        shortest_distance = INT_MAX;

        // Find request with shortest distance
        for (int j = 0; j < NUM_REQUESTS; j++){
            int distance = abs(current_pos - new_requests[j]);
            if (new_requests[j] != -1 && distance < shortest_distance){
                shortest_distance = distance;
                shortest_index = j;
            }
        }

        // Add shortest distance to movement count
        movement_count += shortest_distance;
        // Update current position
        current_pos = new_requests[shortest_index];
        // Mark request as processed
        new_requests[shortest_index] = -1;
    }

    return movement_count;
}

int Scan(int requests[], int initial_pos)
{
    int movement_count = 0;
    int current_pos = initial_pos;
    int new_requests[NUM_REQUESTS];
    
    int min = 5000;
    
    for(int i = 0; i < NUM_REQUESTS; i++){
        new_requests[i] = requests[i];
    }

    for(int i = 0; i < NUM_REQUESTS; i++){
        if(min > new_requests[i]){
            min = new_requests[i];
        }
    }

    movement_count += abs(current_pos - 4999);
    if(initial_pos > min)
    movement_count += abs(4999-min);



    return movement_count;
}



int Look(int requests[], int initial_pos){
    int movement_count = 0;
    int current_pos = initial_pos;
    int new_requests[NUM_REQUESTS];
    int candidate = 0;
    
    for(int i = 0; i < NUM_REQUESTS; i++){
        new_requests[i] = requests[i];
    }
    
    qsort(new_requests,NUM_REQUESTS,sizeof(int),compare);
    
    int closest = 5000;
    
    for(int i = 0; i < NUM_REQUESTS; i++){
        if(closest < abs(new_requests[i] - current_pos))
            closest = abs(new_requests[i] - current_pos);
            current_pos = i;
    }
    printf("inital position: %d\n", initial_pos);
    for(int i = current_pos; i < NUM_REQUESTS; i++){
        movement_count += abs(current_pos - new_requests[i]);
        current_pos = new_requests[i];
        new_requests[i] = -1;
    }
    for(int i = current_pos-1; i >= 0; i--){
        movement_count += abs(current_pos - new_requests[i]);
        current_pos = new_requests[i];
        new_requests[i] = -1;
    }
    return movement_count;
}

int compare(const void *a, const void *b){
    
    int *x = (int*) a;
    int *y = (int*) b;

    return *x-*y;
}