/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logique.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:25:56 by moraouf           #+#    #+#             */
/*   Updated: 2025/08/01 22:26:13 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_eat(t_philo *philo)
{
	if (is_simulation_over(philo->data))
		return ;
	if (!lock_forks(philo))
		return ;
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->last_meal_time_mutex[philo->id - 1]);
	philo->last_meal_time = get_current_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->last_meal_time_mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->data->meals_eaten_mutex[philo->id - 1]);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_eaten_mutex[philo->id - 1]);
	ft_sleep(philo->data->time_to_eat);
	unlock_forks(philo);
}

void	ft_sleep(int milliseconds)
{
	usleep(milliseconds * 1000);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	if (philo->data->num_philosophers % 2 != 0
		&& philo->data->time_to_eat >= philo->data->time_to_sleep)
		usleep(philo->data->time_to_eat * 1000);
}
