
#ifndef philo_h
#define philo_h



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>



#define MAX_PHILOSOPHERS 200


typedef struct s_philo t_philo;
typedef struct s_data t_data;



typedef struct s_philo {
    int id;
    int meals_eaten;
    int last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *last_meal_time_mutex;
    pthread_mutex_t *meals_eaten_mutex;
    t_data *data;
} t_philo;

typedef struct s_data {
    int num_philosophers;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int meals_required;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *last_meal_time_mutex;
    int simulation_over;
    t_philo *philo;
} t_data;



void init_data(int ac, char *av[], t_data *data);
int init_mutexes(t_data *data);
t_philo *init_philosophers(t_data *data);
int ft_atoi(const char *str);
t_philo *init_philosophers(t_data *data);
void ft_memset(void *ptr, int value, size_t num);   
int ft_parse_args(int ac, char *av[]);
int ft_error(const char *msg);
void ft_print(t_philo *philo, const char *msg);
void ft_sleep(int milliseconds);
void ft_eat(t_philo *philo);
void ft_think(t_philo *philo);
void *start_execution(t_data *data);
int get_cuurent_time(void);
void ft_print(t_philo *philo, const char *msg);





#endif