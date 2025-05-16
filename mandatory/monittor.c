/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monittor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:59:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/16 17:37:01 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Monitor Function (Death Detection)
void *death_detection_monitor(void *arg)
{
	t_controller *cntrl = (t_controller *)arg;
	int i;

	while (1)
	{
		i = -1;
		while (++i < cntrl->nbr_of_philo)
		{
			pthread_mutex_lock(&cntrl->meal_mutex);
			long current_time = get_current_time_ms();
			if (current_time - cntrl->philos[i].time_to_die >= cntrl->philos[i].time_to_die)
			{
				pthread_mutex_lock(&cntrl->is_dead_mutex);
				cntrl->is_dead = 1;
				pthread_mutex_unlock(&cntrl->is_dead_mutex);

				pthread_mutex_lock(&cntrl->print_mutex);
				printf("%ld %d died\n", current_time, cntrl->philos[i].id);
				pthread_mutex_unlock(&cntrl->print_mutex);
				pthread_mutex_unlock(&cntrl->meal_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&cntrl->meal_mutex);
		}
		usleep(1000);
	}
	return NULL;
}

// Philosopher Routine
void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);

		// Eating
		pthread_mutex_lock(philo->meal_mutex);
		philo->time_to_die = get_current_time_ms();
		pthread_mutex_unlock(philo->meal_mutex);

		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d is eating\n", get_current_time_ms(), philo->id);
		pthread_mutex_unlock(philo->print_mutex);

		usleep(philo->time_to_eat * 1000);

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// Sleeping
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d is sleeping\n", get_current_time_ms(), philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		usleep(philo->time_to_sleep * 1000);

		// Thinking
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d is thinking\n", get_current_time_ms(), philo->id);
		pthread_mutex_unlock(philo->print_mutex);

		pthread_mutex_lock(&philo->cntrl->is_dead_mutex);
		if (philo->cntrl->is_dead)
		{
			pthread_mutex_unlock(&philo->cntrl->is_dead_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->cntrl->is_dead_mutex);
	}
	return NULL;
}
