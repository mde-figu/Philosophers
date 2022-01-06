#include "../includes/philo.h"

int	validate_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (0);
	}
	return (1);
}

int	entry_args_check(int argc, char *argv[])
{
	int i;
	long int temp;

	i = 1;
	temp = 0;
	while (i <= argc)
	{
		if (!ft_isdigit(*argv[i]))
		{
			printf("Error: arguments must be all digits.\n");
			return(0);
		}
		temp = ft_atoi(argv[i]);
		if (!temp)
		{
			printf("Error: arguments must be integers.\n");
			return(0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	validate_args(argc);
	argc--;
	entry_args_check(argc, argv);
	printf("Deu bom :D\n");
	return(1);
}
