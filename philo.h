/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:35:39 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/15 20:43:13 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

// typedef struct s_philo
// {
//     int philo_id;
//     pthread_t philo;
//     pthread_mutex_t *philo_mutex;
//     int left_fork;
//     int right_fork;
// }   t_philo;

typedef struct s_philo
{
    int must_eat;
    int ms_sleep;
    int ms_eat;
    int ms_die;
    int philo_nbr;
    int philo_id;
    pthread_t philo;
    pthread_mutex_t *philo_mutex;
    int left_fork;
    int right_fork;
    // t_philo *philo;
}   t_philo;

#endif