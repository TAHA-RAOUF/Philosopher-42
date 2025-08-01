/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:09:59 by moraouf           #+#    #+#             */
/*   Updated: 2025/08/01 22:18:56 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	logic_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_simulation_over(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (is_simulation_over(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	ft_print(philo, "has taken a fork");
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		logic_odd(philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (is_simulation_over(philo->data))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		if (is_simulation_over(philo->data))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		ft_print(philo, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	if (is_simulation_over(philo->data))
		return ;
	take_fork(philo);
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->last_meal_time_mutex[philo->id - 1]);
	philo->last_meal_time = get_current_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->last_meal_time_mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->data->meals_eaten_mutex[philo->id - 1]);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_eaten_mutex[philo->id - 1]);
	ft_sleep(philo->data->time_to_eat);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
