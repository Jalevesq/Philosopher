/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/15 17:43:26 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *doSomeThing(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    struct timeval current;
    struct timeval start;
    
    int long time;
    gettimeofday(&current, NULL);
    printf("Philo %d \n", philo->philo_id);  
        if (philo->philo_id % 2 == 0)
    {
        while (1)
        {
            gettimeofday(&start, NULL);
            time = ((start.tv_sec - current.tv_sec) * 1000) + ((start.tv_usec - current.tv_usec) / 1000);
            if (time >= philo->ms_die)
            {
                printf("%ld ms Philo %d died\n", time, philo->philo_id);
                exit(EXIT_SUCCESS);
            }
        }
        // pthread_mutex_lock(philo->philo_mutex);
        // pthread_mutex_unlock(philo->philo_mutex);
    }
    else
    {
        while (1)
        {
            gettimeofday(&start, NULL);
            time = ((start.tv_sec - current.tv_sec) * 1000) + ((start.tv_usec - current.tv_usec) / 1000);
            if (time >= philo->ms_die)
            {
                printf("%ld ms Philo %d died\n", time, philo->philo_id);
                exit(EXIT_SUCCESS);
            }
        }
    }
    
    return (NULL);
}

void    ft_init_philo(int philo_nbr, t_philo *philo, char **av)
{
   int  i;
   int  j;

    i = 0;
    j = 1;
    while (i < philo_nbr)
    {
        philo[i].ms_die = atoi(av[2]);
        philo[i].philo_id = j;
        philo[i].philo_mutex = malloc(sizeof(pthread_mutex_t));
        philo[i].philo = NULL;
        if (!philo[i].philo_mutex)
            return ;
        pthread_mutex_init(philo[i].philo_mutex, NULL);
        i++;
        j++;
    }
    i = -1;
}

void    ft_create_philo(int philo_nbr, t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo_nbr)
    {
        pthread_create(&philo[i].philo, NULL, doSomeThing, &philo[i]);
        usleep(50);
        i++;
    }
}

void    ft_join_and_delete_philo(int philo_nbr, t_philo *philo)
{
    int i;
    int *status;

    i = 0;
    status = NULL;
    while (i < philo_nbr)
    {
        pthread_join(philo[i].philo, (void *)status);
        pthread_mutex_destroy(philo[i].philo_mutex);
        i++;
    }
    i = 0;
    while (i < philo_nbr)
        free(philo[i++].philo_mutex);
    free(philo);
}

int main(int ac, char **av)
{
    (void)ac;
    if (ac > 1)
    {
        int philo_nbr;
        t_philo *philo;

        philo_nbr = atoi(av[1]);
        philo = malloc(sizeof(t_philo) * philo_nbr);
        if (!philo)
            return (1);
        ft_init_philo(philo_nbr, philo, av);
        ft_create_philo(philo_nbr, philo);
        ft_join_and_delete_philo(philo_nbr, philo);
    }
    return (0);
}
