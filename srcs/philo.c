/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 14:06:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_join_n_free(t_philo *philo)
{
    int i;
    int *status;

    i = 0;
    status = NULL;
    while (i < philo->philo_nbr)
    {
        pthread_join(philo[i].philo, (void *)status);
        pthread_mutex_destroy(philo[i].fork_mutex);
        i++;
    }
	i = 0;
	while (i < philo->philo_nbr)
	{
		free(philo[i].philo);
    	free(philo[i++].fork_mutex);
		i++;
	}
}

void	ft_check_health(t_philo *philo, t_data *data)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			if (philo[i].state == DEAD)
			{
				j = 0;
				while (j < philo->philo_nbr)
				{
					philo[i].state = DEAD;
					j++;
				}
				return ;
			}
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
		ft_create_philo(philo, data->philo_nbr);
		ft_check_health(philo, data);
		ft_join_n_free(philo);
		free(philo);
		free(data);
    }
    return (0);
}
