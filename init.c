/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:15:13 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/20 16:50:48 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_philosophers(t_data *data)
{
    int i;
    i = 0;
    data->philo = malloc(sizeof(t_philo) * data->num_philosophers);
    if (!data->philo)
        return NULL; // Handle memory allocation failure
    while (i < data->num_philosophers)
    {
        data->philo[i].id = i + 1;
        data->philo[i].meals_eaten = 0;
        data->philo[i].last_meal_time = get_cuurent_time(); // Initialize last meal time
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].data = data;
        data->philo[i].right_fork = &data->forks[(i + 1) % data->num_philosophers]; // Next philo
        i++;
    }
    return (data->philo);
}

void init_data(int ac, char *av[], t_data *data)
{
    data->num_philosophers = ft_atoi(av[1]);
    data->time_to_eat = ft_atoi(av[2]);
    data->time_to_sleep = ft_atoi(av[3]);
    data->time_to_die = ft_atoi(av[4]);
    if (ac == 6)
        data->meals_required = ft_atoi(av[5]);
    else
        data->meals_required = -1;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    data->philo = init_philosophers(data);
}

int init_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return -1;
        i++;
    }
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return -1;
    return 0;
}

