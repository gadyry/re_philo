/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:26:39 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/16 19:09:24 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philosophers.h"

long	get_current_time_ms()
{
	//TODO
}

int	philo_is_died(t_philo *philos)
{
	long	current_time;

	current_time = get_current_time();//todo
	pthread_mutex_lock(philos->meal_mutex);
	if (current_time - philos->time_to_die >= philos->time_to_die)
	{
		pthread_mutex_lock(philos->print_mutex);
		printf("%ld %d is died \n", get_current_time, philos->id);
		pthread_mutex_lock(philos->print_mutex);
		
	}
	pthread_mutex_unlock(philos->meal_mutex);
}

void	*death_detection_monitor(void *argv)
{
	int				i;
	t_controller	*cntrl;
	long			current_time;
	long			last_meal;

	cntrl = (t_controller *)argv;
	while (1)
	{
		i = -1;
		current_time = get_current_time_ms();
		while (++i < cntrl->nbr_of_philo)
		{
			pthread_mutex_lock(&cntrl->meal_mutex);
			last_meal = cntrl->philos[i].time_to_die;
			if (current_time - last_meal >= cntrl->philos[i].time_to_die)
			{
				pthread_mutex_lock(&cntrl->is_dead_mutex);
				cntrl->is_dead = 1;
				pthread_mutex_unlock(&cntrl->is_dead_mutex);
				pthread_mutex_lock(&cntrl->print_mutex);
				printf("%ld %d is died\n", get_current_time_ms(), cntrl->philos[i].id);
				pthread_mutex_unlock(&cntrl->print_mutex);
				pthread_mutex_unlock(&cntrl->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&cntrl->meal_mutex);
		}
		usleep(600);
	}
	return (argv);
}
