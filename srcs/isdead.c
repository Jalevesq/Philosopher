/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isDead.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:24:57 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/01 10:42:25 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_lock(&philo->death_mutex);
		if (philo[i].is_dead == DEAD)
		{
			pthread_mutex_unlock(&philo->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->death_mutex);
		i++;
	}
	return (0);
}

int	ft_isfirstdead(t_philo *philo)
{
	if (get_time() - philo->last_meal >= philo->ms_die)
	{
		pthread_mutex_lock(&philo->death_mutex);
		philo->is_dead = DEAD;
		pthread_mutex_unlock(&philo->death_mutex);
		return (1);
	}
	return (0);
}