/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:06:40 by gcavanna          #+#    #+#             */
/*   Updated: 2023/07/14 03:47:22 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*eat_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->g->print_mutex));
	if (!someone_died(philo))
		printf("%ld %d is eating \n", get_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->g->print_mutex));
	pthread_mutex_lock(&(philo->g->philo_mutex));
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&(philo->g->philo_mutex));
	usleep(philo->g->time_to_eat);
	pthread_mutex_lock(&(philo->g->philo_mutex));
	philo->loop++;
	pthread_mutex_unlock(&(philo->g->philo_mutex));
	return (NULL);
}

static void	*sleep_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->g->print_mutex));
	if (!someone_died(philo))
		printf("%ld %d is sleeping \n", get_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->g->print_mutex));
	usleep(philo->g->time_to_sleep);
	return (NULL);
}

static void	*think_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->g->print_mutex));
	if (!someone_died(philo))
		printf("%ld %d is thinking \n", get_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->g->print_mutex));
	return (NULL);
}

static void	*dead_state(t_philo *philo, t_matrix *g)
{
	pthread_mutex_lock(&(g->death_mutex));
	g->someone_died = true;
	pthread_mutex_unlock(&(g->death_mutex));
	pthread_mutex_lock(&((*philo).g->print_mutex));
	printf("%ld %d died \n", get_timestamp(), (*philo).id);
	pthread_mutex_unlock(&((*philo).g->print_mutex));
	return (NULL);
}

void	*state_handler(char state, t_philo *philo, t_matrix *g)
{
	if (state == EAT)
		return (eat_state(philo));
	else if (state == SLEEP)
		return (sleep_state(philo));
	else if (state == THINK)
		return (think_state(philo));
	else if (state == DEAD)
		return (dead_state(philo, g));
	return (NULL);
}
