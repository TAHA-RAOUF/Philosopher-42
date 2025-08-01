/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:55:56 by moraouf           #+#    #+#             */
/*   Updated: 2025/08/01 22:20:37 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals_completed(t_data *data)
{
	int	i;
	int	philosophers_done;

	if (data->meals_required == -1)
		return (0);
	philosophers_done = 0;
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->meals_eaten_mutex[i]);
		if (data->philo[i].meals_eaten >= data->meals_required)
			philosophers_done++;
		pthread_mutex_unlock(&data->meals_eaten_mutex[i]);
		i++;
	}
	if (philosophers_done >= data->num_philosophers)
	{
		pthread_mutex_lock(&data->simulation_over_mutex);
		data->simulation_over = 1;
		pthread_mutex_unlock(&data->simulation_over_mutex);
		return (1);
	}
	return (0);
}

int	ft_check(t_data *data)
{
	int	current_time;
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		current_time = get_current_time() - data->start_time;
		pthread_mutex_lock(&data->last_meal_time_mutex[i]);
		if ((current_time - data->philo[i].last_meal_time) > data->time_to_die)
		{
			ft_print(&data->philo[i], "died");
			pthread_mutex_lock(&data->simulation_over_mutex);
			data->simulation_over = 1;
			pthread_mutex_unlock(&data->simulation_over_mutex);
			pthread_mutex_unlock(&data->last_meal_time_mutex[i]);
			return (0);
		}
		pthread_mutex_unlock(&data->last_meal_time_mutex[i]);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!is_simulation_over(data))
	{
		if (check_meals_completed(data))
			return (NULL);
		if (!ft_check(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
