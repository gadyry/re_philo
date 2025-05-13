#include "philosophers.h"

int ft_strlen(const char *str)
{
	int cpt = 0;
	while (str[cpt])
		cpt++;
	return cpt;
}

int ft_parse_av(const char *str, long *out, int index)
{
	long res = 0;
	int i = 0;
	
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return 0;
		
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return 0;
		i++;
	}
	
	if (res == 0 && index != 5)
		return 0;
		
	*out = res;
	return 1;
}

void print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

long *arr_of_nbr(int size, char **args)
{
	long *arr_nbrs = malloc((size - 1) * sizeof(long));
	if (!arr_nbrs)
		return NULL;
		
	for (int i = 1; i < size; i++)
	{
		if (!ft_parse_av(args[i], &arr_nbrs[i - 1], i))
		{
			print_error("Error: invalid argument\n");
			free(arr_nbrs);
			return NULL;
		}
	}
	return arr_nbrs;
}

int ft_check_arguments(int ac, char **args)
{
	if (ac != 5 && ac != 6)
	{
		print_error("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return 0;
	}
	
	long *nbrs = arr_of_nbr(ac, args);
	if (!nbrs)
		return 0;
		
	if (nbrs[0] <= 0 || nbrs[0] > MAX_PHILOS)
	{
		print_error("Error: invalid number of philosophers\n");
		free(nbrs);
		return 0;
	}
	
	free(nbrs);
	return 1;
}
