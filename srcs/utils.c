/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:17:40 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/02 14:22:18 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_death_watcher(t_philo *philo)
{
	if (ft_isdead(philo) == 1)
		return (1);
	else if (ft_isfirstdead(philo) == 1)
	{
		// pthread_mutex_lock(philo->printf_mutex);
		printf("%llu ms - Philo %d has died\n", get_time() - philo->start_ms, philo->philo_id);
		return (1);
	}
	return (0);
}

int	ft_philo_have_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->start_mutex);
	if (*philo->finish_flag == NOT_FINISH)
	{
		pthread_mutex_unlock(&philo->start_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->start_mutex);
		return (1);
	}
}

int	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock((philo->printf_mutex));
	if (ft_death_watcher(philo) != 1)
	{
		if (philo->state == EATING)
		{
			pthread_mutex_lock(&philo->start_mutex);
			philo->eat_counter += 1;
			pthread_mutex_unlock(&philo->start_mutex);
		}
		if (ft_philo_have_eat(philo) == 1)
		{
			pthread_mutex_unlock(philo->printf_mutex);
			return (1);
		}
		printf("%llu ms - Philo %d %s", (get_time() - philo->start_ms), philo->philo_id, str);
		pthread_mutex_unlock(philo->printf_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->printf_mutex);
		return (1);
	}
	return (0);
}

uint64_t get_time(void)
{
	struct timeval time;
	uint64_t now;
	gettimeofday(&time, NULL);
	now = ((time.tv_sec * (uint64_t)1000)) + (time.tv_usec / 1000);
	return (now);
}

void	ft_usleep(int sleep)
{
	uint64_t now;

	now = get_time();
	while (1)
	{
		if (get_time() - now >= (uint64_t)sleep)
			break;
		usleep(50);
	}
}