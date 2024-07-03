/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:29:34 by gcavanna          #+#    #+#             */
/*   Updated: 2023/07/14 04:04:36 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_matrix	g;
	t_philo		*philos;
	t_fork		*forks;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong number of args\n", NULL, NULL, NULL));
	if (!args_init(&g, argc, argv))
		return (ft_error("Invalid input\n", &g, NULL, NULL));
	if (!global_init(&g))
		return (ft_error("Mutex init failure\n", &g, NULL, NULL));
	if (!philo_init(&g, &philos, &forks))
		return (ft_error("Malloc failure\n", &g, philos, forks));
	if (!thread_handler(&g, &philos))
		return (ft_error("Some errors with threads\n", &g, philos, forks));
	return (ft_neo(&g, philos, forks));
}
