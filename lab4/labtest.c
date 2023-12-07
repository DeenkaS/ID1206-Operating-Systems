#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_CYLINDERS 5000
#define NUM_REQUESTS 1000

int main()
{

    int initial_pos = 1234;
    int requests[NUM_REQUESTS];

    for (int i = 0; i < NUM_REQUESTS; i++)
    {
        requests[i] = rand() % NUM_CYLINDERS;
    }

    int movement_count = 0;
    int current_pos = initial_pos;
    int passes = 0;
    int new_requests[NUM_REQUESTS];
    int candidate = 0;

    for (int i = 0; i < NUM_REQUESTS; i++)
        for (int j = 0; j < NUM_REQUESTS; j++)
        {
            candidate = 5000;
            if (abs(candidate - initial_pos) > abs(requests[j] - initial_pos))
            {
                new_requests[i] = requests[candidate];
            }
        }

    for (int i = 0; i < NUM_REQUESTS; i++)
    {
        printf("SLOT: %d VALUE: %d \n", i, new_requests[i]);
    }
}