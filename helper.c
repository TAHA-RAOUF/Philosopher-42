/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:22:11 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/26 15:02:20 by moraouf          ###   ########.fr       */
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
    printf("%d %d %s\n", elapsed_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
}