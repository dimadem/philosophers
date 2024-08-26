/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:46 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/22 11:26:53 by dmdemirk         ###   ########.fr       */
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
	mutex_handle(&philo->first_fork->mutex, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	mutex_handle(&philo->second_fork->mutex, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	if ((philo->table->meals_number > 0)
		&& (philo->meals_counter == philo->table->meals_number))
		set_bool(&philo->mutex, &philo->full, true);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLISECONDS));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table, philo->table->time_to_eat);
	mutex_handle(&philo->first_fork->mutex, UNLOCK);
	mutex_handle(&philo->second_fork->mutex, UNLOCK);
}
