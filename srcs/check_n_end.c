/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:24:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/05 13:15:20 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_philo_all_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_lock(&philo[i].eat_mutex);
		if (philo[i].eat_counter >= philo[i].must_eat)
		{
			pthread_mutex_unlock(&philo[i].eat_mutex);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&philo[i].eat_mutex);
			return (0);
		}
	}
	return (1);
}

void	ft_check_state(t_philo *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(philo[i].death_mutex);
			if (*philo[i].is_dead == DEAD)
			{
				pthread_mutex_unlock(philo[i].death_mutex);
				return ;
			}
			pthread_mutex_unlock(philo[i].death_mutex);
			if (ft_philo_all_eat(philo) == 1 && data->must_eat > 0)
			{
				pthread_mutex_lock(philo[i].death_mutex);
				*philo->finish_flag = FINISH;
				pthread_mutex_unlock(philo[i].death_mutex);
				return ;
			}
			i++;
		}
		usleep(2000);
	}
}