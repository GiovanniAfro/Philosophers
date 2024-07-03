/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:25:16 by gcavanna          #+#    #+#             */
/*   Updated: 2024/07/03 17:36:13 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_matrix *g, t_philo **philos, t_fork **forks)
{
	t_philo	*philo;
	int		i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * g->n_philo);
	*forks = (t_fork *)malloc(sizeof(t_fork) * g->n_philo);
	if (!philos || !forks)
		return (0);
	i = -1;
	while (++i < g->n_philo)
	{
		philo = &(*philos)[i];
		philo->g = g;
		philo->id = i + 1;
		philo->last_meal = get_timestamp();
		philo->loop = 0;
		philo->right_fork = &((*forks)[i]);
		philo->left_fork = &((*forks)[i + 1]);
		if (philo->id == g->n_philo)
			philo->left_fork = &((*forks)[0]);
		philo->right_fork_state = 0;
		philo->left_fork_state = 0;
		pthread_mutex_init(&(philo->left_fork->fork_mutex), NULL);
	}
	return (1);
}

int	global_init(t_matrix *g)
{
	g->someone_died = 0;
	if (pthread_mutex_init(&(g->philo_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(g->death_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(g->print_mutex), NULL))
		return (0);
	return (1);
}

int	args_init(t_matrix *g, int argc, char **argv)
{
	g->n_philo = ft_get_number(argv[1]);
	if (g->n_philo < 1 || g->n_philo > 200)
		return (0);
	g->time_to_die = ft_get_number(argv[2]) * 1000;
	g->time_to_eat = ft_get_number(argv[3]) * 1000;
	g->time_to_sleep = ft_get_number(argv[4]) * 1000;
	g->n_loop = -1;
	if (argc == 6)
		g->n_loop = ft_get_number(argv[5]);
	return (1);
}
