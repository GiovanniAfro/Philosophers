/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:29:21 by gcavanna          #+#    #+#             */
/*   Updated: 2023/07/14 05:49:02 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_state
{
	THINK,
	EAT,
	SLEEP,
	DEAD
};

# define LEFT_FORK -42
# define RIGHT_FORK 42

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct s_matrix
{
	int				n_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				n_loop;
	bool			someone_died;
	pthread_t		t_morpheus;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	philo_mutex;
}					t_matrix;

typedef struct s_philo
{
	t_matrix		*g;
	unsigned char	id;
	pthread_t		t_philosopher;
	int				loop;
	time_t			last_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	bool			right_fork_state;
	bool			left_fork_state;
}					t_philo;

int			thread_handler(t_matrix *g, t_philo **philos);
void		*state_handler(char state, t_philo *philo, t_matrix *g);

int			someone_died(t_philo *philo);
time_t		get_timestamp(void);
int			ft_get_number(char *arg);
int			ft_neo(t_matrix *g, t_philo *philo, t_fork *forks);
int			ft_error(char *message, t_matrix *g, t_philo *philo, t_fork *forks);
int			philo_init(t_matrix *g, t_philo **philos, t_fork **forks);
int			global_init(t_matrix *g);
int			args_init(t_matrix *g, int argc, char **argv);

#endif
