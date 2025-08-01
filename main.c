/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:38:26 by moraouf           #+#    #+#             */
/*   Updated: 2025/08/01 22:20:10 by moraouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (ft_parse_args(argc, argv))
		return (EXIT_FAILURE);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(argc, argv, &data);
	if (!init_mutexes(&data))
		return (EXIT_FAILURE);
	data.philo = init_philosophers(&data);
	if (!data.philo)
		return (EXIT_FAILURE);
	start_execution(&data);
	ft_clean(&data);
	return (EXIT_SUCCESS);
}
