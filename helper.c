/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:22:11 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/30 09:49:12 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_memset(void *ptr, int value, size_t num) 
{
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
}

int get_current_time(void) 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_print(t_philo *philo, const char *msg) 
{
    int elapsed_time = get_current_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!is_simulation_over(philo->data)) {
        printf("%d %d %s\n", elapsed_time, philo->id, msg);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int is_simulation_over(t_data *data)
{
    int result;
    pthread_mutex_lock(&data->simulation_over_mutex);
    result = data->simulation_over;
    pthread_mutex_unlock(&data->simulation_over_mutex);
    return result;
}

void ft_clean(t_data *data)
{
    int i = 0;
    while(i < data->num_philosophers)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->last_meal_time_mutex[i]);
        pthread_mutex_destroy(&data->meals_eaten_mutex[i]);
        i++;
    }
    pthread_mutex_destroy(&data->simulation_over_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    free(data->philo);
    free(data->forks);
    free(data->last_meal_time_mutex);
    free(data->meals_eaten_mutex);
}
