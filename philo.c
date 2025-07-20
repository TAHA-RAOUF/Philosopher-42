/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:31:29 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/20 17:59:10 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void ft_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork); // Pick up left fork
    ft_print(philo, "has taken a left fork");
    
    pthread_mutex_lock(philo->right_fork); // Pick up right fork
    ft_print(philo, "has taken a right fork");
    
    ft_print(philo, "is eating");
    philo->last_meal_time = get_cuurent_time(); // Update last meal time
    philo->meals_eaten++;
    
    ft_sleep(philo->data->time_to_eat); // Simulate eating time
    
    pthread_mutex_unlock(philo->right_fork); // Put down right fork
    pthread_mutex_unlock(philo->left_fork); // Put down left fork
}
void ft_sleep(int milliseconds)
{
    usleep(milliseconds * 1000); // Convert milliseconds to microseconds
}

void ft_think(t_philo *philo)
{
    ft_print(philo, "is thinking");
    ft_sleep(philo->data->time_to_sleep); // Simulate thinking time
}

void  *philosopher_routine(void *philo)
{
    t_philo *philos = (t_philo *)philo;
    while (1)
    {
        ft_eat(philos); // Philosopher eats
        ft_sleep(philos->data->time_to_sleep); // Philosopher sleeps
        ft_think(philos); // Philosopher thinks
    }
    return 0; // This should never be reached
}

void *start_execution(t_data *data)
{
    int i;

    if (init_mutexes(data) != 0)
        return NULL; // Handle mutex initialization failure
    if (init_philosophers(data) == NULL)
        return NULL; // Handle philosopher initialization failure
    i = 0;
    while(i  < data->num_philosophers)
    {
        if (pthread_create(&data->philo[i].thread, NULL, philosopher_routine, &data->philo[i]) != 0)
        return NULL;
        i++; // Handle thread creation failure
    }
    while( i < data->num_philosophers)
    {
       pthread_join(data->philo[i].thread, NULL);
       i++; // Wait for all philosopher threads to finish
    }
    return NULL;
}
