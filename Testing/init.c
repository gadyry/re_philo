// init.c - improved version
#include "philosophers.h"

void cleanup_simulation(t_simulation *sim)
{
	if (sim)
	{
		pthread_mutex_destroy(&sim->is_dead_mutex);
		pthread_mutex_destroy(&sim->meal_mutex);
		pthread_mutex_destroy(&sim->print_mutex);
		pthread_mutex_destroy(&sim->stop_mutex);
	}
}

int init_simulation(t_simulation *sim, t_philo *philos, int nbr_of_philo)
{
	sim->is_dead = 0;
	sim->stop_simulation = 0;
	sim->philos_full = 0;
	sim->philo = philos;
	sim->nbr_of_philo = nbr_of_philo;
	
	if (pthread_mutex_init(&sim->is_dead_mutex, NULL) ||
		pthread_mutex_init(&sim->meal_mutex, NULL) ||
		pthread_mutex_init(&sim->print_mutex, NULL) ||
		pthread_mutex_init(&sim->stop_mutex, NULL))
	{
		cleanup_simulation(sim);
		return (1);
	}
	return 0;
}

void pass_data_to_philo(t_philo *philos, long *arr_nbrs, int nbr_of_philo)
{
	for (int i = 0; i < nbr_of_philo; i++)
	{
		philos[i].id = i + 1;
		philos[i].time_to_die = arr_nbrs[1];
		philos[i].time_to_eat = arr_nbrs[2];
		philos[i].time_to_sleep = arr_nbrs[3];
		philos[i].meals_required = arr_nbrs[4] > 0 ? arr_nbrs[4] : -1;
		philos[i].lst_meal_time = 0;
	}
}

void cleanup_forks(pthread_mutex_t *forks, int nbr_of_philo)
{
	for (int i = 0; i < nbr_of_philo; i++)
		pthread_mutex_destroy(&forks[i]);
}

int init_forks(pthread_mutex_t *forks, int nbr_of_philo)
{
	for (int i = 0; i < nbr_of_philo; i++)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			cleanup_forks(forks, i);
			print_error("Error: fork mutex init failed\n");
			return 0;
		}
	}
	return 1;
}

int setup_philosophers(t_philo *philos, pthread_mutex_t *forks,
					 t_simulation *sim, int nbr_of_philo)
{
	for (int i = 0; i < nbr_of_philo; i++)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % nbr_of_philo];
		philos[i].print_lock = &sim->print_mutex;
		philos[i].sim = sim;
		
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL))
		{
			print_error("Error: meal mutex init failed\n");
			for (int j = 0; j < i; j++)
				pthread_mutex_destroy(&philos[j].meal_mutex);
			return 1;
		}
	}
	return 0;
}
