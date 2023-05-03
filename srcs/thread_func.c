/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:13:48 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/03 15:34:06 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_sleep_die(t_philo *philo)
{
	uint64_t now;

	now = get_time();
	usleep((philo->ms_die - 10) * 1000);
	while (1)
	{
		if (get_time() - now >= philo->ms_die)
		{
			ft_printf(philo, "has died in sleep_die\n");
			pthread_mutex_lock(philo->death_mutex);
			*philo->is_dead = DEAD;
			pthread_mutex_unlock(philo->death_mutex);
			break ;
		}
		usleep(50);
	}
}

int	ft_eat(t_philo *philo)
{
	philo->state = EATING;
	if (ft_printf_meal(philo, "is eating\n") == 1)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eat_counter += 1;
	pthread_mutex_unlock(&philo->eat_mutex);
	if (philo->ms_eat >= philo->ms_die)
	{
		ft_sleep_die(philo);
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	else
		ft_usleep(philo->ms_eat);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	if (ft_printf(philo, "is sleeping\n") == 1)
		return (1);
	if (philo->ms_sleep + philo->ms_eat >= philo->ms_die)
	{
		philo->state = THINKING;
		ft_sleep_die(philo);
		return (1);
	}
	else
		ft_usleep(philo->ms_sleep);
	philo->state = THINKING;
	if (ft_printf(philo, "is thinking\n") == 1)
		return (1);
	return (0);
}