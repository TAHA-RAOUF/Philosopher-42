/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:55:56 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/27 18:26:22 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int current_time;

    while (!is_simulation_over(data))
    {
        i = 0;
        while( i < data->num_philosophers)
        {
            current_time = get_current_time() - data->start_time;
            pthread_mutex_lock(&data->last_meal_time_mutex[i]);
            if ((current_time - data->philo[i].last_meal_time) > data->time_to_die)
            {
                // printf("\n%d\n",data->time_to_die);
                // printf("%d",current_time - data->philo[i].last_meal_time);
                ft_print(&data->philo[i], "died");
                pthread_mutex_lock(&data->simulation_over_mutex);
                data->simulation_over = 1;
                pthread_mutex_unlock(&data->simulation_over_mutex);
                pthread_mutex_unlock(&data->last_meal_time_mutex[i]);
                return NULL;
            }
            pthread_mutex_unlock(&data->last_meal_time_mutex[i]);
            i++;
        }
        usleep(1000); // Check every millisecond
    }
    return NULL;
}
