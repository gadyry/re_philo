/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:49:01 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/14 03:54:06 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>//printf...
# include <stdlib.h>//malloc...
# include <pthread.h>//for threads
# include <unistd.h>//for write
# include <limits.h>//for max/min
# include <sys/time.h>//for gettimeofday()

# define MAX_PHILOS 200

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_required;//num_times_to_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meal_mutex;
}	t_philo;

typedef struct s_controller
{
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	is_dead_mutex;
	int				nbr_of_philo;
}	t_controller;

void	print_error(const char *msg);
int		ft_check_arguments(int ac, char **args);
void	pass_data_to_philo(t_philo *philos, long *arr_nbrs, int nbr_of_philo);
int		init_forks(pthread_mutex_t *forks, int nbr_of_philo);
int		prepare_controller(t_controller *cntrl, t_philo *philo, int nbr_of_philo);
void	cleanup_mutex(t_controller *cntrl, pthread_mutex_t *forks);
void	setup_philosophers(t_philo *philos, pthread_mutex_t *forks, t_controller *cntrl, int nbr_of_philo);

#endif
