/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:31:29 by moraouf           #+#    #+#             */
/*   Updated: 2025/08/01 22:26:55 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Helper to lock forks in correct order

int	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*r_f;
	pthread_mutex_t	*l_f;

	r_f = philo->left_fork;
	l_f = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		r_f = philo->right_fork;
		l_f = philo->left_fork;
	}
	pthread_mutex_lock(r_f);
	if (is_simulation_over(philo->data))
		return (pthread_mutex_unlock(r_f), 0);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(l_f);
	if (is_simulation_over(philo->data))
	{
		pthread_mutex_unlock(l_f);
		pthread_mutex_unlock(r_f);
		return (0);
	}
	ft_print(philo, "has taken a fork");
	return (1);
}

// Helper to unlock forks in correct order
void	unlock_forks(t_philo *philo)
{
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

void	*philosopher_routine(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	if (philos->data->num_philosophers == 1)
	{
		ft_print(philo, "has taken a fork");
		usleep(philos->data->time_to_die);
		return (NULL);
	}
	if (philos->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_over(philos->data))
	{
		if (is_simulation_over(philos->data))
			break ;
		ft_eat(philos);
		if (is_simulation_over(philos->data))
			break ;
		ft_print(philos, "is sleeping");
		ft_sleep(philos->data->time_to_sleep);
		if (is_simulation_over(philos->data))
			break ;
		ft_think(philos);
	}
	return (NULL);
}

void	*start_execution(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		return (NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philosopher_routine,
				&data->philo[i]) != 0)
			return (NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (NULL);
}
