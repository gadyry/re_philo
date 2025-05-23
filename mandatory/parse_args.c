/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:51:55 by ael-gady          #+#    #+#             */
/*   Updated: 2025/05/14 19:30:48 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *str)
{
	int	cpt;

	cpt = 0;
	while (str[cpt])
		cpt++;
	return (cpt);
}

int	ft_parse_av(const char *str, long *out, int index)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (0);
		i++;
	}
	if (res == 0 && index != 5)
		return (0);
	*out = res;
	return (1);
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

long	*arr_of_nbr(int size, char **args)
{
	long	*arr_nbrs;
	int		i;

	arr_nbrs = malloc((size - 1) * (sizeof(long)));
	if (!arr_nbrs)
		return (NULL);
	i = 1;
	while (i < size)
	{
		if (!ft_parse_av(args[i], &arr_nbrs[i - 1], i))
		{
			print_error("Error: invalid argument\n");
			free(arr_nbrs);
			return (NULL);
		}
		i++;
	}
	return (arr_nbrs);
}

int ft_check_arguments(int ac, char **args)
{
	long	*nbrs;

	if (ac != 5 && ac != 6)
	{
		print_error("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	nbrs = arr_of_nbr(ac, args);
	if (!nbrs)
		return (0);
	if (nbrs[0] <= 0 || nbrs[0] > MAX_PHILOS)
	{
		print_error("Error: invalid number of philosophers\n");
		free(nbrs);
		return (0);
	}
	free(nbrs);
	return (1);
}
