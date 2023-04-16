/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:35:39 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/16 18:21:01 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define ON_TABLE 0
# define IN_USE 1

typedef struct s_philo
{
    int must_eat;
    int ms_sleep;
    int ms_eat;
    int ms_die;
    int philo_nbr;
    int philo_id;
    int fork;
    int flag;
    int eat_counter;
    pthread_t philo;
    long start_sec;
    long start_usec;
    pthread_mutex_t *fork_mutex;
    struct s_philo *left_philo;
    struct s_philo *right_philo;
    // t_philo *philo;
}   t_philo;

#endif