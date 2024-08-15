#include "philosophers.h"


void error_input_checker(int argc, char **argv)
{
  (void)argv;
  if (5 > argc || 6 < argc)
  {
    error_exit("Wrong input: \n"
        WHITE"---------\n" RESET
        GREEN"Try with ./philo 5 800 200 200 [5]\n" RESET);
  }
}


int main(int argc, char **argv)
{
  t_table table;

  error_input_checker(argc, argv);
  init_table(&table);
  dinner(&table);
  // 4. clean(&table);
  return (0);
}
