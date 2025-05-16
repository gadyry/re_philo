/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:34:57 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/16 17:40:47 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pass_data_to_philo(t_philo *philos, long *arr_nbrs, int nbr_of_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].time_to_die = arr_nbrs[1];
		philos[i].time_to_eat = arr_nbrs[2];
		philos[i].time_to_sleep = arr_nbrs[3];
		if (arr_nbrs[4] > 0)
			philos[i].meals_required = arr_nbrs[4];
		else
			philos[i].meals_required = -1;
	}
}

int	init_forks(pthread_mutex_t *forks, int nbr_of_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
			return (print_error("Error : fork mutex init failed "), 0);
	}
	return (1);
}

void	setup_philosophers(t_philo *philos, pthread_mutex_t *forks, t_controller *cntrl, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % nbr_of_philo];
		philos[i].meal_mutex = &cntrl->meal_mutex;
		philos[i].print_mutex = &cntrl->print_mutex;
	}
}

int		prepare_controller(t_controller *cntrl, t_philo *philos, int nbr_of_philo)
{
	cntrl->is_dead = 0;
	cntrl->philos = philos;
	cntrl->nbr_of_philo = nbr_of_philo;
	if (pthread_mutex_init(&cntrl->meal_mutex, NULL))
		return (print_error("Error: Failed to initialize meal mutex\n"), 1);
	if (pthread_mutex_init(&cntrl->print_mutex, NULL))
		return (print_error("Error: Failed to initialize print mutex\n"), 1);
	if (pthread_mutex_init(&cntrl->is_dead_mutex, NULL))
		return (print_error("Error: Failed to initialize dead mutex\n"), 1);
	return (0);
}

