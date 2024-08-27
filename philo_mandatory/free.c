/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:23:06 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 12:10:03 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_table *table);

void	free_all(t_table *table)
{
	int		i;
	t_philo	*curr_philo;
	t_fork	*curr_fork;

	i = -1;
	while (++i < table->philosophers_number)
	{
		curr_philo = &table->philos_array[i];
		mutex_handle(&curr_philo->mutex, DESTROY);
	}
	i = -1;
	while (++i < table->philosophers_number)
	{
		curr_fork = &table->forks_array[i];
		mutex_handle(&curr_fork->mutex, DESTROY);
	}
	mutex_handle(&table->mutex, DESTROY);
	mutex_handle(&table->write, DESTROY);
	i = -1;
	while (++i < table->philosophers_number)
	{
		free(&table->philos_array[i]);
		free(&table->forks_array[i]);
	}
}
