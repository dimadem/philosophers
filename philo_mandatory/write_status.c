/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:25 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/22 11:29:51 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_status(t_p_status status, t_philo *philo, bool debug);

static void	write_status_debug(t_p_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(GREEN"%-6ld %d has taken a first fork"RESET
			"\t"RED"fork id -> [ %d ]\n"RESET, elapsed, philo->id, philo->first_fork->id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf(GREEN"%-6ld %d has taken a second fork"RESET
			"\t"RED"fork id -> [ %d ]\n"RESET, elapsed, philo->id, philo->second_fork->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(YELLOW"%-6ld %d is eating"RESET
			"\t"RED"meals c -> [ %ld ]\n"RESET, elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(BLUE"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(CYAN"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	else if (DEAD == status)
		printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
}

void	write_status(t_p_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = (get_time(MILLISECONDS) - philo->table->start_simulation);
	mutex_handle(&philo->table->write, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(GREEN "%-6ld %d has taken a fork\n"RESET,
				elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(YELLOW"%-6ld %d is eating\n"RESET, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(BLUE  "%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(CYAN  "%-6ld %d is thinking\n"RESET, elapsed, philo->id);
		else if (DEAD == status)
			printf(RED   "%-6ld %d died\n"RESET, elapsed, philo->id);
	}
	mutex_handle(&philo->table->write, UNLOCK);
}
