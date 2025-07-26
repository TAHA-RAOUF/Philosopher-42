/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:31:29 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/26 15:02:23 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void ft_eat(t_philo *philo)
{
    // Deadlock prevention: odd philosophers pick left first, even pick right first
    if (philo->id % 2 == 1) {
        // Odd philosopher: left fork first
        pthread_mutex_lock(philo->left_fork);
        ft_print(philo, "has taken a fork");
        
        pthread_mutex_lock(philo->right_fork);
        ft_print(philo, "has taken a fork");
    } else {
        // Even philosopher: right fork first
        pthread_mutex_lock(philo->right_fork);
        ft_print(philo, "has taken a fork");
        
        pthread_mutex_lock(philo->left_fork);
        ft_print(philo, "has taken a fork");
    }
    
    ft_print(philo, "is eating");
    philo->last_meal_time = get_current_time() - philo->data->start_time; // Update last meal time (relative)
    philo->meals_eaten++;
    
    ft_sleep(philo->data->time_to_eat); // Simulate eating time
    
    // Always unlock in reverse order to prevent issues
    if (philo->id % 2 == 1) {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    } else {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}

void ft_sleep(int milliseconds)
{
    usleep(milliseconds * 1000); // Convert milliseconds to microseconds
}

void ft_think(t_philo *philo)
{
    ft_print(philo, "is thinking");
    // No sleep needed for thinking in the standard philosophers problem
}

void  *philosopher_routine(void *philo)
{
    t_philo *philos = (t_philo *)philo;
    while (!philos->data->simulation_over)
    {
        ft_eat(philos); // Philosopher eats
        if (philos->data->simulation_over) break;
        
        ft_print(philos, "is sleeping");
        ft_sleep(philos->data->time_to_sleep); // Philosopher sleeps
        if (philos->data->simulation_over) break;
        
        ft_think(philos); // Philosopher thinks
        if (philos->data->simulation_over) break;
    }
    return NULL;
}

void *start_execution(t_data *data)
{
    int i;
    pthread_t monitor_thread;

    // Start monitor thread
    if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
        return NULL;

    i = 0;
    while(i  < data->num_philosophers)
    {
        if (pthread_create(&data->philo[i].thread, NULL, philosopher_routine, &data->philo[i]) != 0)
        return NULL;
        i++; // Handle thread creation failure
    }
    
    // Wait for monitor thread to finish (when simulation ends)
    pthread_join(monitor_thread, NULL);
    
    i = 0;  // Reset i to 0
    while( i < data->num_philosophers)
    {
       pthread_join(data->philo[i].thread, NULL);
       i++; // Wait for all philosopher threads to finish
    }
    return NULL;
}
