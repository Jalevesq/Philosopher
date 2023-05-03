/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:17:40 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/03 10:20:04 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_death_watcher(t_philo *philo)
{
	if (ft_isdead(philo) == 1)
		return (1);
	else if (ft_isfirstdead(philo) == 1)
	{
		printf("%llu ms - Philo %d has died\n", get_time() - philo->start_ms, philo->philo_id);
		return (1);
	}
	return (0);
}

// problem? using global death_mutex too often ? Use different mutex for finish ?
int	ft_philo_have_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->finish_flag == NOT_FINISH)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
}

int	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock((philo->printf_mutex));
	if (ft_death_watcher(philo) != 1)
	{
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

void	ft_usleep(t_philo *philo, int sleep)
{
	uint64_t now;
	now = get_time();
	// (void)philo;
	usleep((sleep - 10) * 1000);
	if (philo->ms_die / sleep > 0)
	{
		while (1)
		{
			if (get_time() - now >= ((uint64_t)sleep))
				break ;
			usleep(50);
		}
	}
	else
	{
		if (philo->state == EATING)
		{
			// usleep((philo->ms_die - 10) * 1000);
			while (1)
			{
				if (get_time() - philo->last_meal >= philo->ms_die)
				{
					ft_printf(philo, "has died\n");
					pthread_mutex_lock(philo->death_mutex);
					*philo->is_dead = DEAD;
					pthread_mutex_unlock(philo->death_mutex);
					return ;
				}
				usleep(50);
			}
		}
		else if (philo->state == SLEEPING)
		{
			while (1)
			{
				// usleep((philo->ms_die - 10) * 1000);
				if (get_time() - philo->last_meal >= philo->ms_die)
				{
					ft_printf(philo, "has died\n");
					pthread_mutex_lock(philo->death_mutex);
					*philo->is_dead = DEAD;
					pthread_mutex_unlock(philo->death_mutex);
					return ;
				}
				usleep(50);
			}
		}
	}
}
