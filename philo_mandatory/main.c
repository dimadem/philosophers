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
	printf("table philosophers number: %ld\n", table.philosophers_number);
	printf("table time to die: %ld\n", table.time_to_die);
	printf("table time to eat: %ld\n", table.time_to_eat);
	printf("table time to sleep: %ld\n", table.time_to_sleep);
	printf("table meals number: %ld\n", table.meals_number);
	printf("table start simulation: %ld\n", table.start_simulation);
	printf("table all threads ready: %d\n", table.all_threads_ready);
	printf("table simulation finished: %d\n", table.end_simulation);
	printf("table philos array: %p\n", table.philos_array);
	printf("table forks array: %p\n", table.forks_array);

	dinner(&table);
	return (0);
}
