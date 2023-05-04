/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_odd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/04 12:59:05 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_take_own_fork_odd(t_philo *philo)
{
	if (ft_printf(philo, "take left fork (own)\n") == 1)
		return (1);
	if (philo->philo_id == 1 && philo->philo_nbr == 1)
	{
		ft_usleep(philo->ms_die);
		ft_printf(philo, "has died\n");
		pthread_mutex_lock(philo->death_mutex);
		*philo->is_dead = DEAD;
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	return (0);
}

static int	ft_take_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (ft_take_own_fork_odd(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork_mutex);
	if (ft_printf(philo, "take right fork\n") == 1)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	return (0);
}

void	*ft_philosopher_odd(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start_odd_mutex);
	pthread_mutex_unlock(philo->start_odd_mutex);
	while (1)
	{
		if (ft_take_fork_odd(philo) == 1)
			break ;
		if (ft_eat(philo) == 1)
			break ;
		if (ft_sleep(philo) == 1)
			break ;
	}
	return (NULL);
}
