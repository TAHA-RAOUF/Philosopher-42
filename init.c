/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:15:13 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/28 15:32:33 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void assign_forks(t_data *data)
{
    int i;

    i = 0;
   while(i < data->num_philosophers)
   {
        if(i == data->num_philosophers - 1)
        {
            data->philo[i].left_fork = &data->forks[i];
            data->philo[i].right_fork = &data->forks[0];
        }
        else
        {
            data->philo[i].left_fork = &data->forks[i];
            data->philo[i].right_fork = &data->forks[i + 1];
        }
        i++;
   }
}


t_philo *init_philosophers(t_data *data)
{
    int i;
    t_philo *philos;

    philos = malloc(sizeof(t_philo) * data->num_philosophers);
    if (!philos)
        return NULL;

    i = 0;
    while (i < data->num_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal_time = 0; // Start with 0 (relative to start_time)
        philos[i].data = data;
        // pthread_mutex_init(&philos[i].last_meal_time_mutex, NULL);
        // pthread_mutex_init(&philos[i].meals_eaten_mutex, NULL);
        i++;
    }
    data->philo = philos;  // Set data->philo before calling assign_forks
    assign_forks(data);
    return (philos);
}


void init_data(int ac, char *av[], t_data *data)
{
    data->num_philosophers = ft_atoi(av[1]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->time_to_die = ft_atoi(av[2]);
    if (ac == 6)
        data->meals_required = ft_atoi(av[5]);
    else
        data->meals_required = -1;
    data->simulation_over = 0;
    data->start_time = get_current_time(); // Set simulation start time
}

int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->forks)
        return 0;

    i = 0;
    while(i < data->num_philosophers)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    data->last_meal_time_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->last_meal_time_mutex)
        return 0;
    i = 0;  // Reset i to 0
    while(i < data->num_philosophers)
    {
        pthread_mutex_init(&data->last_meal_time_mutex[i], NULL);
        i++;
    }
    data->meals_eaten_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->meals_eaten_mutex)
        return 0;
    i = 0;  // Reset i to 0
    while(i < data->num_philosophers)
    {
        pthread_mutex_init(&data->meals_eaten_mutex[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->simulation_over_mutex, NULL);
    return 1; 
}





