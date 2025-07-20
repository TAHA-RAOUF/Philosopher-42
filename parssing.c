/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:28:25 by moraouf           #+#    #+#             */
/*   Updated: 2025/07/16 10:43:58 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(const char *str)
{
    int result = 0;
    int i = 0;
    while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    int sign = 1;
    if(str[i] == '-' || str[i] == '+') {
        if(str[i] == '-')
            sign = -1;
        i++; 
    }
    while(str[i] >= '0' && str[i] <= '9') {
        if(result > (2147483647 - (str[i] - '0')) / 10) {
            return -1; // Overflow
        }
        result = result * 10 + (str[i] - '0');
        i++;
    
    }
    if(str[i] != '\0') {
        return -2; // Invalid characters found
    }
    return result * sign;   
}


int ft_parse_args(int ac, char *av[]) {

    if(ac != 5 && ac != 6)
        return(printf("Error\n Invalid number of arguments\n"), 1);
    int i = 1;
    while (i < ac) {
        int num = ft_atoi(av[i]);
        if(num == -1)
            return(printf("Error\nOverflow in argument %d\n", i), 1);
        else if(num == -2)
            return(printf("Error\n No digits in argument %d\n", i), 1);
        if(num <= 0)
            return(printf("Error\n Argument %d must be positive\n", i), 1);
        if(i == 1 && num > MAX_PHILOSOPHERS)
            return(printf("Error: Number of philosophers exceeds maximum (%d)\n", MAX_PHILOSOPHERS), 1);
        i++;
    }
    return 0;
}

