/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/02 20:06:32 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_take_own_fork(t_philo *philo)
{
		philo->fork = IN_USE_OWN;
		if (ft_printf(philo, "take left fork (own)\n") == 1)
			return (1);
		if (philo->philo_id == 1)
		{
			if (philo->philo_nbr == 1)
			{
				usleep(philo->ms_die);
				ft_printf(philo, "has died\n");
				pthread_mutex_lock(&philo->death_mutex);
				*philo->is_dead = DEAD;
				pthread_mutex_unlock(&philo->death_mutex);
				return (1);
			}
		}
	return (0);
}

int	ft_take_right_fork(t_philo *philo)
{
		*philo->right_fork = IN_USE;
		if (ft_printf(philo, "take right fork\n") == 1)
			return (1);
	return (0);
}

int	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (ft_take_own_fork(philo) == 1)
	{
		philo->fork = ON_TABLE;
		pthread_mutex_unlock(&philo->fork_mutex);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork_mutex);
	if (ft_take_right_fork(philo) == 1)
	{
		philo->fork = ON_TABLE;
		*philo->right_fork = ON_TABLE;
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	philo->state = EATING;
	if (ft_printf(philo, "is eating\n") == 1)
	{
		philo->fork = ON_TABLE;
		*philo->right_fork = ON_TABLE;
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->start_mutex);
	philo->eat_counter += 1;
	pthread_mutex_unlock(&philo->start_mutex);
	philo->last_meal = get_time();
	ft_usleep(philo, philo->ms_eat);
	philo->fork = ON_TABLE;
	*philo->right_fork = ON_TABLE;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	if (ft_printf(philo, "is sleeping\n") == 1)
		return (1);
	ft_usleep(philo, philo->ms_sleep);
	philo->state = THINKING;
	if (ft_printf(philo, "is thinking\n") == 1)
		return (1);
	return (0);
}

void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->start_mutex);
	pthread_mutex_unlock(&philo->start_mutex);
	if (philo->philo_id % 2 == 0)
		usleep(philo->ms_eat);
	while (1)
	{
		if (ft_take_fork(philo) == 1)
			break;
		if (ft_eat(philo) == 1)
			break;
		if (ft_sleep(philo) == 1)
			break;
	}
	return (NULL);
}
