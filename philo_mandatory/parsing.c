#include "philosophers.h"

void	parse_input(t_table *table, char **argv);

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static	const char *valid_input(const char *str)
{
	int len; //len of the str
	const char *number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Accepted only positive numbers");
	if (!is_digit(*str))
		error_exit("Accept only digits");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("Number is too big");
	return (number);
}

static long ft_atol(const char *str)
{
	long 	number;

	number = 0;
	str = valid_input(str);
	while (is_digit(*str))
		number = number * 10 + (*str++ - '0');
	if (number > INT_MAX)
		error_exit("Number is too big");
	return (number);
}

void	parse_input(t_table *table, char **argv)
{
	table->philosophers_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 60e3
		|| table->time_to_eat < 60e3
		|| table->time_to_sleep < 60e3)
		error_exit("Timestamps should be > 60 ms");
	if (argv[5])
		table->meals_number = ft_atol(argv[5]);
	else
		table->meals_number = -1;
}
