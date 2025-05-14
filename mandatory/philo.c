/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:47:57 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/14 03:53:49 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	cleanup_forks(pthread_mutex_t *forks, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	cleanup_mutex(t_controller *cntrl, pthread_mutex_t *forks)
{
	cleanup_forks(forks, cntrl->nbr_of_philo);
	pthread_mutex_destroy(&cntrl->is_dead_mutex);
	pthread_mutex_destroy(&cntrl->meal_mutex);
	pthread_mutex_destroy(&cntrl->print_mutex);
}

int	ft_execute_launch(t_controller *cntrl)
{
	
}

int	main(int ac, char **av)
{
	long			*arr_nbrs;
	int				nbr_of_philo;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	t_controller	cntrl;

	if (!ft_check_arguments(ac, av))
		return (1);
	arr_nbrs = arr_of_nbr(ac, av);
	if (!arr_nbrs)
		return (1);
	pass_data_to_philo(philos, arr_nbrs, nbr_of_philo);//done!
	free(arr_nbrs);
	if (!init_forks(forks, nbr_of_philo))//done
		return (1);
	if (prepare_controller(&cntrl, philos, nbr_of_philo))
		return (cleanup_forks(forks, nbr_of_philo), 1);
	setup_philosophers(philos, forks, &cntrl, nbr_of_philo);
	if (ft_execute_launch(&cntrl))//todo
		return (cleanup_mutex(&cntrl, forks), 1);
	cleanup_mutex(&cntrl, forks);
	return (0);
}
