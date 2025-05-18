/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:26:39 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/17 19:38:20 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philosophers.h"

long	get_current_time_ms()
{
	struct timeval	tv;
	long			current_time;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error("Error : gettimeofday() failed !\n");
		return (-1);
	}
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time);
}

void	*death_detection_monitor(void *argv)
{
	int				i;
	t_controller	*cntrl;
	long			since_meal;

	cntrl = (t_controller *)argv;
	while (1)
	{
		i = -1;
		while (++i < cntrl->nbr_of_philo)
		{
			pthread_mutex_lock(&cntrl->meal_mutex);
			since_meal = get_current_time_ms() - cntrl->philos[i].time_to_die;
			if (since_meal >= cntrl->philos[i].time_to_die)
			{
				pthread_mutex_lock(&cntrl->is_dead_mutex);
				cntrl->is_dead = 1;
				pthread_mutex_unlock(&cntrl->is_dead_mutex);
				pthread_mutex_lock(&cntrl->print_mutex);
				printf("%ld %d has died\n", get_current_time_ms(), cntrl->philos[i].id);
				pthread_mutex_unlock(&cntrl->print_mutex);
				pthread_mutex_unlock(&cntrl->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&cntrl->meal_mutex);
		}
		usleep(1000);
	}
	return (argv);
}
