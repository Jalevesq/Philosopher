/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:13:48 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/05 11:57:24 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check if no data race
void	ft_sleep_die(t_philo *philo)
{
	if (philo->state == EATING)
		usleep((philo->ms_die - 10) * 1000);
	else
		usleep(((philo->ms_die - philo->ms_eat) - 10) * 1000);
	while (1)
	{
		if (get_time() - philo->start_ms >= philo->ms_die)
		{
			pthread_mutex_lock(philo->death_mutex);
			if (*philo->is_dead != DEAD)
			{
				*philo->is_dead = DEAD;
				pthread_mutex_unlock(philo->death_mutex);
				pthread_mutex_lock(philo->printf_mutex);
				if (*philo->finish_flag != FINISH)
					printf("%llu ms - Philo %d died\n",
						get_time() - philo->start_ms, philo->philo_id);
				pthread_mutex_unlock(philo->printf_mutex);
				break ;
			}
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

static void	ft_init_thread(t_philo *philo, t_data *data, int i)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_create(&data->philo[i], NULL,
			ft_philosopher_even, philo);
	}
	else
	{
		pthread_create(&data->philo[i], NULL,
			ft_philosopher_odd, philo);
	}
}

void	ft_create_philo(t_philo *philo, t_data *data, int philo_nbr)
{
	int			i;
	uint64_t	now;

	pthread_mutex_lock(&data->start_even_mutex);
	pthread_mutex_lock(&data->start_odd_mutex);
	i = 0;
	now = get_time();
	while (i < philo_nbr)
	{
		philo[i].start_ms = now;
		philo[i].last_meal = now;
		ft_init_thread(&philo[i], data, i);
		i++;
	}
	pthread_mutex_unlock(&data->start_odd_mutex);
	ft_usleep(philo->ms_eat);
	pthread_mutex_unlock(&data->start_even_mutex);
}
