/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 23:05:08 by moraouf           #+#    #+#             */
/*   Updated: 2025/08/01 23:26:16 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	int					last_meal_time;
	int					last_param;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_philosophers;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					meals_required;
	int					start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*last_meal_time_mutex;
	pthread_mutex_t		*meals_eaten_mutex;
	pthread_mutex_t		simulation_over_mutex;
	pthread_mutex_t		*death;
	int					simulation_over;
	t_philo				*philo;
}						t_data;

void					init_data(int ac, char *av[], t_data *data);
int						init_mutexes(t_data *data);
t_philo					*init_philosophers(t_data *data);
int						ft_atoi(const char *str);
t_philo					*init_philosophers(t_data *data);
void					ft_memset(void *ptr, int value, size_t num);
int						ft_parse_args(int ac, char *av[]);
int						ft_error(const char *msg);
void					ft_print(t_philo *philo, const char *msg);
void					ft_sleep(int milliseconds);
void					ft_eat(t_philo *philo);
void					ft_think(t_philo *philo);
void					*philosopher_routine(void *philo);
void					*start_execution(t_data *data);
void					*monitor(void *arg);
int						check_meals_completed(t_data *data);
int						is_simulation_over(t_data *data);
void					ft_clean(t_data *data);
int						lock_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);
int						get_current_time(void);

#endif