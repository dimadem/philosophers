/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:32:58 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 11:33:10 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo);

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philosophers_number % 2 == 1)
		precise_usleep(philo->table, philo->table->time_to_eat / 2);
}
