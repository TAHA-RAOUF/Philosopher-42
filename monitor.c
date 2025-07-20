/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:55:56 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/20 17:56:13 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        for (i = 0; i < data->num_philosophers; i++)
        {
            pthread_mutex_lock(data->philo[i].last_meal_time_mutex);
            if (get_cuurent_time() - data->philo[i].last_meal_time > data->time_to_die)
            {
                ft_print(&data->philo[i], "died");
                data->simulation_over = 1;
                pthread_mutex_unlock(data->philo[i].last_meal_time_mutex);
                return NULL;
            }
            pthread_mutex_unlock(data->philo[i].last_meal_time_mutex);
        }
        usleep(1000); // Check every millisecond
    }
}
