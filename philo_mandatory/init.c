/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:53 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/15 17:47:07 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_table(t_table *table);

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	p_number;

	p_number = philo->table->philosophers_number;
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[philo_pos];
		philo->left_fork = &forks[(philo_pos + 1) % p_number];
	}
	else
	{
		philo->right_fork = &forks[(philo_pos + 1) % p_number];
		philo->left_fork = &forks[philo_pos];
	}
}

static void	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;	

	i = -1;
	while (++i < table->philosophers_number)
	{
		philo = table->philos_array + i;
		philo->id = i;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		mutex_handle(&philo->mutex, INIT);
		assign_forks(philo, table->forks_array, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	mutex_handle(&table->mutex, INIT);
	table->philos_array = malloc_handle(sizeof(t_philo) \
		* table->philosophers_number);
	table->forks_array = malloc_handle(sizeof(t_fork) \
		* table->philosophers_number);
	while (++i < table->philosophers_number)
	{
		mutex_handle(&table->forks_array[i].mutex, INIT);
		table->forks_array[i].id = i;
	}
	init_philos(table);
}
