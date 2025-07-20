/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:15:13 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/20 18:33:50 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_philosophers(t_data *data)
{
    int i;
    t_philo *philos;

    philos = malloc(sizeof(t_philo) * data->num_philosophers);
    if (!philos)
        return NULL;
    
    while (i < data->num_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal_time = get_cuurent_time();
        philos[i].data = data;
        assign_forks(data);
        pthread_mutex_init(&philos[i].last_meal_time_mutex, NULL);
        pthread_mutex_init(&philos[i].meals_eaten_mutex, NULL);
        i++;
    }
    return (philos);
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
    data->simulation_over = 0;
}

int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->forks)
        return 0;

    while(i < data->num_philosophers)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    data->last_meal_time_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->last_meal_time_mutex)
        return 0;
    while(i < data->num_philosophers)
    {
        pthread_mutex_init(&data->last_meal_time_mutex[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    return 1; 
}

void assign_forks(t_data *data)
{
    int i;

    for (i = 0; i < data->num_philosophers; i++)
    {
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
    }
}




