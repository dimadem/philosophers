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

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutex, &table->all_threads_ready))
		;
}
