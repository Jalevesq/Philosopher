/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/02 15:24:18 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_take_own_fork(t_philo *philo)
{
	if (philo->fork == ON_TABLE)
	{
		philo->fork = IN_USE_OWN;
		if (ft_printf(philo, "take left fork (own)\n") == 1)
			return (1);
	}
	return (0);
}

int	ft_take_right_fork(t_philo *philo)
{
	if (*philo->right_fork == ON_TABLE)
	{
		*philo->right_fork = IN_USE;
		if (ft_printf(philo, "take right fork\n") == 1)
			return (1);
	}
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
	// if (philo->fork == IN_USE_OWN && *philo->right_fork == IN_USE)
	// {
		philo->state = EATING;
		if (ft_printf(philo, "is eating\n") == 1)
		{
			philo->fork = ON_TABLE;
			*philo->right_fork = ON_TABLE;
			pthread_mutex_unlock(&philo->fork_mutex);
			pthread_mutex_unlock(philo->right_fork_mutex);
			return (1);
		}
		if (philo->state == EATING)
		{
			pthread_mutex_lock(&philo->start_mutex);
			philo->eat_counter += 1;
			pthread_mutex_unlock(&philo->start_mutex);
		}
		philo->last_meal = get_time();
		ft_usleep(philo->ms_eat);
		philo->fork = ON_TABLE;
		*philo->right_fork = ON_TABLE;
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		if (ft_death_watcher(philo) == 1)
			return (1);
	// }
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	// if (philo->state == EATING)
	// {
	philo->state = SLEEPING;
	if (ft_printf(philo, "is sleeping\n") == 1)
		return (1);
	ft_usleep(philo->ms_sleep);
	philo->state = THINKING;
	if (ft_printf(philo, "is thinking\n") == 1)
		return (1);
	// }
	// else
	// 	return (1);
	return (0);
}

void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->start_mutex);
	pthread_mutex_unlock(&philo->start_mutex);
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->ms_eat);
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
	// gettimeofday(&curr, NULL);
	// now = ((curr.tv_sec * (uint64_t)1000)) + (curr.tv_usec / 1000);
	// printf("%llu\n", now - philo->start_ms);

	// Use to start every philosopher at the same time.
	// if (philo->philo_nbr == 1)
	// {x
	// 	pthread_mutex_lock(&philo->death_mutex);
	// 	*philo->is_dead = DEAD;
	// 	pthread_mutex_unlock(&philo->death_mutex);
	// 	ft_usleep(philo->ms_die);
	// 	printf("%llu ms - Philo %d has died\n", get_time() - philo->start_ms, philo->philo_id);
	// 	return (NULL);
	// }