/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:28:02 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 11:28:48 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	dead(t_philo *philo);

bool	dead(t_philo *philo)
{
	long	elapsed_time;
	long	time_to_die;
	long	current_time;
	long	last_meal_time;

	if (get_bool(&philo->mutex, &philo->full) == true)
		return (false);
	current_time = get_time(MILLISECONDS);
	last_meal_time = get_long(&philo->mutex, &philo->last_meal_time);
	elapsed_time = (current_time - last_meal_time) * 1e3;
	if (elapsed_time == current_time * 1e3)
		elapsed_time = 0;
	time_to_die = philo->table->time_to_die;
	if (elapsed_time > time_to_die)
		return (true);
	return (false);
}
