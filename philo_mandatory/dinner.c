/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:43 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 11:27:46 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dinner(t_table *table);
void	*dinner_simulation(void *data);
void	*one_philo_dinner(void *data);

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	mutex_handle(&philo->table->mutex, LOCK);
	philo->table->philo_threads_number++;
	mutex_handle(&philo->table->mutex, UNLOCK);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
		eating(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table, philo->table->time_to_sleep);
		thinking(philo);
	}
	return (NULL);
}

void	*one_philo_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	mutex_handle(&philo->table->mutex, LOCK);
	philo->table->philo_threads_number++;
	mutex_handle(&philo->table->mutex, UNLOCK);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLISECONDS));
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->meals_number)
		return ;
	else if (1 == table->philosophers_number)
		thread_handle(&table->philos_array[0].thread_id, \
				one_philo_dinner, &table->philos_array[0], CREATE);
	else
		while (++i < table->philosophers_number)
			thread_handle(&table->philos_array[i].thread_id, \
					dinner_simulation, &table->philos_array[i], CREATE);
	thread_handle(&table->monitor, monitor_simulation, table, CREATE);
	table->start_simulation = get_time(MILLISECONDS);
	set_bool(&table->mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philosophers_number)
		thread_handle(&table->philos_array[i].thread_id, \
				dinner_simulation, &table->philos_array[i], JOIN);
	set_bool(&table->mutex, &table->end_simulation, true);
	thread_handle(&table->monitor, monitor_simulation, table, JOIN);
}
