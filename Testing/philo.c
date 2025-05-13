// philo.c - improved main function
int main(int ac, char **av)
{
    long arr_nbrs[5] = {0};
    t_philo philos[MAX_PHILOS];
    pthread_mutex_t forks[MAX_PHILOS];
    t_simulation sim;
    pthread_t monitor_thread;

    if (!ft_check_arguments(ac, av))
        return 1;

    long *numbers = arr_of_nbr(ac, av);
    if (!numbers)
        return 1;

    int nbr_of_philo = numbers[0];
    if (nbr_of_philo > MAX_PHILOS)
    {
        free(numbers);
        print_error("Error: too many philosophers\n");
        return 1;
    }

    pass_data_to_philo(philos, numbers, nbr_of_philo);
    free(numbers);

    if (!init_forks(forks, nbr_of_philo) ||
        setup_philosophers(philos, forks, &sim, nbr_of_philo) ||
        init_simulation(&sim, philos, nbr_of_philo))
    {
        cleanup_forks(forks, nbr_of_philo);
        return 1;
    }

    // Handle single philosopher case
    if (nbr_of_philo == 1)
    {
        printf("%ld 1 has taken a fork\n", get_time_ms());
        usleep(philos[0].time_to_die * 1000);
        printf("%ld 1 died\n", get_time_ms());
        cleanup_simulation(&sim);
        cleanup_forks(forks, nbr_of_philo);
        return 0;
    }

    if (pthread_create(&monitor_thread, NULL, death_detection_monitor, &sim))
    {
        print_error("Error: create monitor thread failed\n");
        cleanup_simulation(&sim);
        cleanup_forks(forks, nbr_of_philo);
        return 1;
    }

    if (start_simulation(philos, nbr_of_philo))
    {
        pthread_mutex_lock(&sim.stop_mutex);
        sim.stop_simulation = 1;
        pthread_mutex_unlock(&sim.stop_mutex);
    }

    pthread_join(monitor_thread, NULL);
    cleanup_simulation(&sim);
    cleanup_forks(forks, nbr_of_philo);
    return 0;
}