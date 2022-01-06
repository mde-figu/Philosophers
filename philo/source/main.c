#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	int i;
	long int temp;

	i = 1;
	temp = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (0);
	}
	argc--;
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
	printf("Deu bom :D\n");
	return(1);
}
