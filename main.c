

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"

void *thread_function1(void *arg)
{

    (void)arg; // To avoid unused parameter warning
    printf("Thread  is running\n");
    return NULL;
}





int main(int argc, char *argv[])
{
    t_data data;
    if (ft_parse_args(argc, argv))
        return EXIT_FAILURE;
    ft_memset(&data, 0, sizeof(t_data)); // Initialize data structure to zero
    init_data(argc, argv, &data);
    data.philo = init_philosophers(&data);
    if(!data.philo)
        return EXIT_FAILURE;
    if(!init_mutexes(&data))
        return EXIT_FAILURE;
    start_execution(&data); // Start the philosopher simulation
    return EXIT_SUCCESS;
}