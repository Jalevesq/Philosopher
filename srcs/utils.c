/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:17:40 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/30 14:10:48 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock((&philo->printf_mutex));
	printf("%llu ms - Philo %d %s", get_time() - philo->start_ms, philo->philo_id, str);
	pthread_mutex_unlock(&philo->printf_mutex);
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
	while (get_time() - now <= (uint64_t)sleep)
		;
}