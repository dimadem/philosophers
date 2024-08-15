/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:55 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/15 17:45:49 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_input_checker(int argc, char **argv)
{
	(void)argv;
	if (5 > argc || 6 < argc)
	{
		error_exit("Wrong input: \n"
			WHITE"---------\n" RESET
			GREEN"Try with ./philo 5 800 200 200 [5]\n" RESET);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	error_input_checker(argc, argv);
	parse_input(&table, argv);
	init_table(&table);
	dinner(&table);
	return (0);
}
