/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:22:11 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/20 17:58:54 by moraouf          ###   ########.fr       */
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

int get_cuurent_time(void) 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // Convert to milliseconds
}

void ft_print(t_philo *philo, const char *msg) 
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("Philosopher %d %s at time %d ms\n", philo->id, msg, get_cuurent_time());
    pthread_mutex_unlock(&philo->data->print_mutex);
}