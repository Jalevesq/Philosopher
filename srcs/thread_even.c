/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_even.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:06:37 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/03 10:24:20 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int	ft_take_own_fork_even(t_philo *philo)
{
		philo->fork = IN_USE_OWN;
		if (ft_printf(philo, "take left fork (own)\n") == 1)
			return (1);
	return (0);
}

int	ft_take_right_fork_even(t_philo *philo)
{
		*philo->right_fork = IN_USE;
		if (ft_printf(philo, "take right fork\n") == 1)
			return (1);
		// for when only 1 philo.
		// if (philo->philo_id == 1)
		// {
		// 	if (philo->philo_nbr == 1)
		// 	{
		// 		usleep(philo->ms_die);
		// 		ft_printf(philo, "has died\n");
		// 		pthread_mutex_lock(&philo->death_mutex);
		// 		*philo->is_dead = DEAD;
		// 		pthread_mutex_unlock(&philo->death_mutex);
		// 		return (1);
		// 	}
		// }
	return (0);
}

int	ft_take_fork_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	if (ft_take_right_fork_even(philo) == 1)
	{
		*philo->right_fork = ON_TABLE;
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->fork_mutex);
	if (ft_take_own_fork_even(philo) == 1)
	{
		*philo->right_fork = ON_TABLE;
		philo->fork = ON_TABLE;
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	return (0);
}

void	*ft_philosopher_even(void *arg)
{
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start_even_mutex);
	pthread_mutex_unlock(philo->start_even_mutex);
	while (1)
	{
		if (ft_take_fork_even(philo) == 1)
			break;
		if (ft_eat(philo) == 1)
			break;
		if (ft_sleep(philo) == 1)
			break;
	}
	return (NULL);
}
