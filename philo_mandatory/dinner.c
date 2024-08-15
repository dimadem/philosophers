/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:43 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/15 17:49:41 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dinner(t_table *table);
void	*dinner_simulation(void *data);

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		printf("philo full: %d\n", philo->full);
		if (philo->full)
			break ;
		eating(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table, philo->table->time_to_sleep);
		thinking(philo);
	}
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	printf("table philosophers number: %ld\n", table->philosophers_number);
	if (0 == table->meals_number)
		return ;
	else if (1 == table->philosophers_number)
		;
	else
		while (++i < table->philosophers_number)
			thread_handle(&table->philos_array[i].thread_id, \
			dinner_simulation, &table->philos_array[i], CREATE);
	table->start_simulation = get_time(MILLISECONDS);
	set_bool(&table->mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philosophers_number)
		thread_handle(&table->philos_array[i].thread_id, NULL, NULL, JOIN);
}
