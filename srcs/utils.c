/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:17:40 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/04 11:53:13 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_death_watcher(t_philo *philo, uint64_t now)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->is_dead == DEAD || *philo->finish_flag == FINISH)
	{
		pthread_mutex_unlock(philo->death_mutex);
		pthread_mutex_unlock(philo->printf_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->death_mutex);
	if (get_time() - philo->last_meal >= philo->ms_die)
	{
		pthread_mutex_lock(philo->death_mutex);
		*philo->is_dead = DEAD;
		pthread_mutex_unlock(philo->death_mutex);
		printf("%llu ms - Philo %d has died in first_dead\n", now - philo->start_ms, philo->philo_id);
		pthread_mutex_unlock(philo->printf_mutex);
		return (1);
	}
	return (0);
}

int	ft_printf_meal(t_philo *philo, char *str)
{
	pthread_mutex_lock((philo->printf_mutex));
	if (ft_death_watcher(philo, get_time()) == 1)
		return (1);
	else
	{
		philo->last_meal = get_time();
		printf("%llu ms - Philo %d %s", (philo->last_meal - philo->start_ms), philo->philo_id, str);
		pthread_mutex_unlock(philo->printf_mutex);
		return (0);
	}
	return (1);
}

int	ft_printf(t_philo *philo, char *str)
{
	uint64_t now;

	now = get_time();
	pthread_mutex_lock((philo->printf_mutex));
	if (ft_death_watcher(philo, now) == 1)
		return (1);
	else
	{
		printf("%llu ms - Philo %d %s", (now - philo->start_ms), philo->philo_id, str);
		pthread_mutex_unlock(philo->printf_mutex);
		return (0);
	}
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
	usleep((sleep - 10) * 1000);
	while (1)
	{
		if (get_time() - now >= ((uint64_t)sleep))
			break ;
		usleep(50);
	}
}
