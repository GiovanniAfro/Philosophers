/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:26:20 by gcavanna          #+#    #+#             */
/*   Updated: 2023/07/14 06:23:26 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(char which_fork, t_philo *philo)
{
	bool	*fork_state;
	t_fork	*fork;

	if (which_fork == LEFT_FORK)
	{
		fork_state = &(philo->left_fork_state);
		fork = philo->left_fork;
	}
	else if (which_fork == RIGHT_FORK)
	{
		fork_state = &(philo->right_fork_state);
		fork = philo->right_fork;
	}
	if (someone_died(philo))
		return ;
	if (*fork_state == 0)
	{
		pthread_mutex_lock(&(fork->fork_mutex));
		*fork_state = 1;
		pthread_mutex_lock(&(philo->g->print_mutex));
		if (!someone_died(philo))
			printf("%ld %d has taken a fork \n", get_timestamp(), philo->id);
		pthread_mutex_unlock(&(philo->g->print_mutex));
	}
}

static void	put_fork(char which_fork, t_philo *philo)
{
	bool	*fork_state;
	t_fork	*fork;

	if (which_fork == LEFT_FORK)
	{
		fork_state = &(philo->right_fork_state);
		fork = philo->right_fork;
	}
	else if (which_fork == RIGHT_FORK)
	{
		fork_state = &(philo->left_fork_state);
		fork = philo->left_fork;
	}
	*fork_state = 0;
	pthread_mutex_unlock(&(fork->fork_mutex));
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(60000);
	while (!someone_died(philo) && philo->loop != philo->g->n_loop)
	{
		take_fork(LEFT_FORK, philo);
		if (philo->left_fork_state == 1 && philo->g->n_philo > 1)
			take_fork(RIGHT_FORK, philo);
		if (philo->left_fork_state == 1 && philo->right_fork_state == 1)
		{
			state_handler(EAT, philo, NULL);
			put_fork(RIGHT_FORK, philo);
			put_fork(LEFT_FORK, philo);
			state_handler(SLEEP, philo, NULL);
			state_handler(THINK, philo, NULL);
		}
	}
	if (philo->right_fork_state == 1)
		pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	if (philo->left_fork_state == 1)
		pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
	return (NULL);
}

static void	*ft_matrix(void *arg)
{
	t_matrix	*g;
	t_philo		**philos;
	int			i;

	philos = (t_philo **)arg;
	g = (*philos)->g;
	i = -1;
	while (1)
	{
		if (++i == g->n_philo)
			i = 0;
		pthread_mutex_lock(&(g->philo_mutex));
		if ((*philos)[i].loop == g->n_loop)
		{
			pthread_mutex_unlock(&(g->philo_mutex));
			return (NULL);
		}
		if (get_timestamp() - (*philos)[i].last_meal > g->time_to_die / 1000)
		{
			pthread_mutex_unlock(&(g->philo_mutex));
			return (state_handler(DEAD, &((*philos)[i]), g));
		}
		pthread_mutex_unlock(&(g->philo_mutex));
	}
	return (NULL);
}

int	thread_handler(t_matrix *g, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < g->n_philo)
	{
		if (pthread_create(&((*philos)[i].t_philosopher), NULL, \
			philosopher_routine, &((*philos)[i])))
			return (0);
	}
	if (pthread_create(&(g->t_morpheus), NULL, ft_matrix, philos))
		return (0);
	while (i--)
	{
		if (pthread_join((*philos)[i].t_philosopher, NULL))
			return (0);
	}
	if (pthread_join(g->t_morpheus, NULL))
		return (0);
	return (1);
}
