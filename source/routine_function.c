/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportaka <mportaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:35:56 by melisportak       #+#    #+#             */
/*   Updated: 2024/09/01 14:13:15 by mportaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->forks[philo->id]);
		print_kill(*philo, TAKE_FORK, 0);
		pthread_mutex_lock(&philo->info->forks[(philo->id + 1)
			% philo->info->number_of_philos]);
		print_kill(*philo, TAKE_FORK, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks[(philo->id + 1)
			% philo->info->number_of_philos]);
		print_kill(*philo, TAKE_FORK, 0);
		pthread_mutex_lock(&philo->info->forks[philo->id]);
		print_kill(*philo, TAKE_FORK, 0);
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print_kill(*philo, EATING, 0);
	sensitive_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->id]);
	pthread_mutex_unlock(&philo->info->forks[(philo->id + 1)
		% philo->info->number_of_philos]);
}

void	sleep_philo(t_philo *philo)
{
	print_kill(*philo, SLEEPING, 0);
	sensitive_usleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_kill(*philo, THINKING, 0);
	if (philo->info->number_of_philos % 2 != 0)
		sensitive_usleep(philo->info->time_to_eat / 2);
}
