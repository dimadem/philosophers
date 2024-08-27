/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:57 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 11:25:36 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all_threads(t_table *table);
void	*monitor_simulation(void *data);
int		ready_all_philo_threads(t_table *table);

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutex, &table->all_threads_ready))
		;
}

int	ready_all_philo_threads(t_table *table)
{
	int	ready;

	ready = 1;
	mutex_handle(&table->mutex, LOCK);
	if (table->philosophers_number == table->philo_threads_number)
		ready = 0;
	mutex_handle(&table->mutex, UNLOCK);
	return (ready);
}

void	*monitor_simulation(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (ready_all_philo_threads(table))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while ((++i < table->philosophers_number) \
				&& !simulation_finished(table))
		{
			if (dead(&table->philos_array[i]) == true)
			{
				write_status(DEAD, &table->philos_array[i], DEBUG_MODE);
				set_bool(&table->mutex, &table->end_simulation, true);
				break ;
			}
		}
	}
	return (NULL);
}
