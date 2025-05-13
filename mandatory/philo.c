/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:47:57 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/14 00:36:57 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	main(int ac, char ** av)
// {
// 	t_philo			philos[MAX_PHILOS];
// 	pthread_mutex_t	forks[MAX_PHILOS];
// 	int				nbr_of_philo;
// 	long			*arr_nbrs;

// 	if (ac == 5 || ac == 6)
// 	{
// 		if (ft_check_arguments(ac, av))
// 		{
// 			arr_nbrs = arr_of_nbr(ac, av);
// 			if (!arr_nbrs)
// 				return (0);
// 			nbr_of_philo = arr_nbrs[0];
// 			if (nbr_of_philo > MAX_PHILOS)
// 			{
// 				free(arr_nbrs);
// 				print_error("Error: too many philosophers\n");
// 				return (0);
// 			}
// 			pass_data_to_philo(philos, arr_nbrs, nbr_of_philo);//todo
// 			free(arr_nbrs);
// 		}
// 	}
// 	else
// 		print_error("Error: invalid argument\n");
// 	return (0);
// }

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
	if (setup_philosophers(philos, forks, &cntrl, nbr_of_philo))
		return (cleanup_forks(forks, nbr_of_philo), 1);//todo
	if (start_simulation(philos, nbr_of_philo))
		return (cleanup(&cntrl, forks, nbr_of_philo), 1);//todo
	cleanup(&cntrl, forks, nbr_of_philo);//todo
	return (0);
}
