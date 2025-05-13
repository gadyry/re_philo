/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:05:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/12 14:59:58 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	cleanup_resources(t_simulation *sim, pthread_mutex_t *forks, int forks_count)
{
	int	i;

	if (sim)
	{
		pthread_mutex_destroy(&sim->print_mutex);
		pthread_mutex_destroy(&sim->stop_mutex);
		pthread_mutex_destroy(&sim->meal_mutex);
		pthread_mutex_destroy(&sim->is_dead_mutex);
	}
	if (forks && forks_count > 0)
	{
		i = 0;
		while (i < forks_count)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
}

static int	initialize_simulation(t_simulation *sim, t_philo *philos, 
								pthread_mutex_t *forks, int nbr_of_philo)
{
	if (!init_forks(forks, nbr_of_philo))
	{
		print_error("Error: fork initialization failed\n");
		return (0);
	}
	if (setup_philosophers(philos, forks, sim, nbr_of_philo))
	{
		cleanup_forks(forks, nbr_of_philo);
		print_error("Error: philosopher setup failed\n");
		return (0);
	}
	if (init_simulation(sim, philos, nbr_of_philo))
	{
		cleanup_forks(forks, nbr_of_philo);
		print_error("Error: simulation initialization failed\n");
		return (0);
	}
	return (1);
}

static int	handle_single_philosopher(t_philo *philo)
{
	printf("%ld 1 has taken a fork\n", get_time_ms());
	usleep(philo->time_to_die * 1000);
	printf("%ld 1 died\n", get_time_ms());
	return (0);
}

int	main(int ac, char **av)
{
	long			arr_nbrs[5];
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	t_simulation	sim;
	pthread_t		monitor_thread;
	long			*nbrs;

	if (ac != 5 && ac != 6)
		return (print_error("Error: invalid argument count\n"), 1);
	if (!ft_check_arguments(ac, av))
		return (1);
	nbrs = arr_of_nbr(ac, av);
	if (!nbrs)
		return (1);
	if (nbrs[0] <= 0 || nbrs[0] > MAX_PHILOS)
	{
		free(nbrs);
		return (print_error("Error: invalid philosopher count\n"), 1);
	}
	pass_data_to_philo(philos, nbrs, nbrs[0]);
	free(nbrs);
	if (nbrs[0] == 1)
		return (handle_single_philosopher(&philos[0]));
	if (!initialize_simulation(&sim, philos, forks, nbrs[0]))
		return (1);
	if (pthread_create(&monitor_thread, NULL, death_detection_monitor, &sim))
	{
		cleanup_resources(&sim, forks, nbrs[0]);
		return (print_error("Error: monitor thread creation failed\n"), 1);
	}
	if (start_simulation(philos, nbrs[0]))
	{
		pthread_mutex_lock(&sim.stop_mutex);
		sim.stop_simulation = 1;
		pthread_mutex_unlock(&sim.stop_mutex);
	}
	pthread_join(monitor_thread, NULL);
	cleanup_resources(&sim, forks, nbrs[0]);
	return (0);
}