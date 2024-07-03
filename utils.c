/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:26:01 by gcavanna          #+#    #+#             */
/*   Updated: 2023/07/14 04:27:17 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_number(char *arg)
{
	int	i;
	int	num;

	i = 0;
	num = -1;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
		{
			if (num == -1)
				num = 0;
			num = num * 10 + (arg[i] - '0');
		}
		else
		{
			printf("Error:YOU STUPID, Only positive INT \n");
			return (num);
		}
		i++;
	}
	return (num);
}

int	ft_neo(t_matrix *g, t_philo *philo, t_fork *forks)
{
	if (g)
	{
		if (pthread_mutex_destroy(&g->death_mutex))
			return (1);
		if (pthread_mutex_destroy(&g->philo_mutex))
			return (1);
	}
	if (philo)
		free(philo);
	if (forks)
	{
		if (pthread_mutex_destroy(&forks->fork_mutex))
			return (1);
		free(forks);
	}
	return (1);
}

int	ft_error(char *message, t_matrix *g, t_philo *philo, t_fork *forks)
{
	printf("%s\n", message);
	ft_neo(g, philo, forks);
	return (1);
}

time_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	someone_died(t_philo *philo)
{
	bool	state;

	pthread_mutex_lock(&(philo->g->death_mutex));
	state = philo->g->someone_died;
	pthread_mutex_unlock(&(philo->g->death_mutex));
	return (state);
}
