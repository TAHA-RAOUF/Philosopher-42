

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"

int main(int argc, char *argv[])
{
    t_data data;
    if (ft_parse_args(argc, argv))
        return (EXIT_FAILURE);
    ft_memset(&data, 0, sizeof(t_data)); // Initialize data structure to zero
    init_data(argc, argv, &data);
    if(!init_mutexes(&data))
        return (EXIT_FAILURE);
    data.philo = init_philosophers(&data);
    if(!data.philo)
        return EXIT_FAILURE;
    start_execution(&data); // Start the philosopher simulation
    free(data.philo);
    free(data.forks);
    free(data.last_meal_time_mutex);
    free(data.meals_eaten_mutex);
    pthread_mutex_destroy(&data.print_mutex);
    pthread_mutex_destroy(&data.simulation_over_mutex);
    return (EXIT_SUCCESS);
}
