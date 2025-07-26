/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:55:56 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/26 15:02:23 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while( i < data->num_philosophers)
        {
            pthread_mutex_lock(&data->last_meal_time_mutex[i]);
            int current_relative_time = get_current_time() - data->start_time;
            if (current_relative_time - data->philo[i].last_meal_time > data->time_to_die)
            {
                ft_print(&data->philo[i], "died");
                data->simulation_over = 1;
                pthread_mutex_unlock(&data->last_meal_time_mutex[i]);
                return NULL;
            }
            pthread_mutex_unlock(&data->last_meal_time_mutex[i]);
            i++;
        }
        usleep(1000); // Check every millisecond
    }
}
