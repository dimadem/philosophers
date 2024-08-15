/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:46 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/15 17:47:58 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo);

/*
   1. grab the forks
   2. eat - update last meal, update meals counter
   3. release the forks
 */

void	eating(t_philo *philo)
{
	printf("\n\n EATING \n\n");
	printf("philo full: %d\n", philo->full);
	printf("philo meals counter: %ld\n", philo->meals_counter);
	printf("philo id %d\n", philo->id);
	printf("philo last meal time %ld\n", philo->last_meal_time);
	printf("philo left fork %d\n", philo->left_fork->id);
	printf("philo right fork %d\n", philo->right_fork->id);
	printf("--------------------\n");
	
	mutex_handle(&philo->left_fork->mutex, LOCK);
	write_status(TAKE_LEFT_FORK, philo, DEBUG_MODE);
	mutex_handle(&philo->right_fork->mutex, LOCK);
	write_status(TAKE_RIGHT_FORK, philo, DEBUG_MODE);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLISECONDS));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table, philo->table->time_to_eat);
	if ((philo->table->meals_number > 0)
		&& (philo->meals_counter == philo->table->meals_number))
		set_bool(&philo->mutex, &philo->full, true);
	mutex_handle(&philo->left_fork->mutex, UNLOCK);
	mutex_handle(&philo->right_fork->mutex, UNLOCK);
}
