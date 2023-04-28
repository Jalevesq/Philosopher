/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/27 20:39:13 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_join_n_free(t_philo *philo, t_data *data)
{
    int i;
    int *status;

    i = 0;
    status = NULL;
    while (i < philo->philo_nbr)
    {
        pthread_join(data->philo[i], (void *)status);
        i++;
    }
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_destroy(philo[i].fork_mutex);
		pthread_mutex_destroy(philo[i].etat_mutex);
		i++;
	}
	i = 0;
	while (i < philo->philo_nbr)
	{
    	free(philo[i].fork_mutex);
		free(philo[i].etat_mutex);
		i++;
	}
}

void	ft_check_state(t_philo *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(philo[i].etat_mutex);
			if (philo[i].state == FIRST_DEAD)
			{
				pthread_mutex_unlock(philo[i].etat_mutex);
				i = 0;
				while (i < data->philo_nbr)
				{
					pthread_mutex_lock(philo[i].etat_mutex);
					philo[i].state = DEAD;
					pthread_mutex_unlock(philo[i++].etat_mutex);
				}
				return ;
			}
			pthread_mutex_unlock(philo[i].etat_mutex);
			i++;
		}
	}
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
		ft_check_state(philo, data);
		ft_join_n_free(philo, data);
		free(data->philo);
		free(philo);
		free(data);
    }
    return (0);
}
