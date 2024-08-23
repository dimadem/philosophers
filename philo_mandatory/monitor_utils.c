/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:57 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/22 11:37:25 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all_threads(t_table *table);
void	*monitor_simulation(void *data);

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutex, &table->all_threads_ready))
		;
}

void	*monitor_simulation(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
    wait_all_threads(table);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philosophers_number && !simulation_finished(table))
		{
			if (dead(&table->philos_array[i]) == true)
            {
                set_bool(&table->mutex, &table->end_simulation, true);
                write_status(DEAD, &table->philos_array[i], DEBUG_MODE);
            }
		}
	}
	return (NULL);
}