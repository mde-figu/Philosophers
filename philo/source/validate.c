#include "../includes/philo.h"

long long	ft_atol(const char *str)
{
	int				i;
	int				negative;
	long long int	number;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	negative = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
		negative = -1;
	}
	number = 0;
	while (ft_isdigit(str[i]))
		number = (number * 10) + (negative * (str[i++] - '0'));
	return (number);
}

int	validate_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (1);
	}
	return (0);
}

int	entry_args_check(int argc, char *argv[])
{
	int			i;
	long int	temp;

	i = 1;
	temp = 0;
	while (i < argc)
	{
		if (ft_atol(argv[i]) > 2147483647)
		{
			printf("Error: argument bigger than maximun integer.\n");
			return (1);
		}
		else if (argv[i][0] == 45)
		{
			printf("Error: invalid argument, use positive numbers.\n");
			return (1);
		}
		else if (!ft_isdigit(*argv[i]))
		{
			printf("Error: arguments must be all digits.\n");
			return (1);
		}
		else if (ft_atoi(argv[i]) == 0)
		{
			printf("Error: invalid argument, use non zero arguments.\n");
			return (1);
		}
		temp = ft_atoi(argv[i]);
		if (!temp)
		{
			printf("Error: arguments must be integers.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
