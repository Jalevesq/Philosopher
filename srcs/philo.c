/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/30 14:12:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_join_n_free(t_philo *philo, t_data *data)
{
    int i;

    while (i < philo->philo_nbr)
    {
        pthread_join(data->philo[i], NULL);
        i++;
    }
	ft_usleep(data->ms_sleep + data->ms_eat);
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_destroy(&philo[i].printf_mutex);
		pthread_mutex_destroy(&philo[i].fork_mutex);
		pthread_mutex_destroy(&philo[i].start_mutex);
		pthread_mutex_destroy(&philo[i].death_mutex);
		i++;
	}
	i = 0;
}


// -fsanitize=thread
// To do:
// 1- Start simulation time for every philosopher at the same time.
// 2- Wait for every thread to be created before starting.
int main(int ac, char **av)
{
    (void)ac;
    if (ac > 1)
    {
        t_data *data;
		t_philo *philo;

        data = malloc(sizeof(t_data));
        if (!data)
            return (1);
		philo = malloc(sizeof(t_philo) * (atoi(av[1])));
		if (!philo)
			return (1);
        ft_init_philo(philo, data, av);
		ft_create_philo(philo, data, data->philo_nbr);
		ft_join_n_free(philo, data);
		free(data->philo);
		free(philo);
		free(data);
    }
    return (0);
}
