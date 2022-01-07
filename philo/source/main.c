#include "../includes/philo.h"

static int	validate_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (1);
	}
	return (0);
}

static int	entry_args_check(int argc, char *argv[])
{
	int i;
	long int temp;

	i = 1;
	temp = 0;
	argc--;
	while (i <= argc)
	{
		if (!ft_isdigit(*argv[i]))
		{
			printf("Error: arguments must be all digits.\n");
			return(1);
		}
		temp = ft_atoi(argv[i]);
		if (!temp)
		{
			printf("Error: arguments must be integers.\n");
			return(1);
		}
		i++;
	}
	return (0);
}

int	init_philosophers(int i, char *argv[], int argc)
{
	//struct timeval time;
	t_philo *philo;
	t_para *param;

	(void) argv;
	i = i + 0;
	philo = NULL;
	param = (void *)malloc(sizeof(t_para));
	//memset(philo, 0, sizeof(t_philo));
	//philo->name = i;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
	//philo->param->start_time = (long int )malloc(sizeof(long int));
	philo->param->t_todie = ft_atoi(argv[2]);
	philo->param->t_toeat = ft_atoi(argv[3]);
	philo->param->t_tosleep = ft_atoi(argv[4]);
	if (argc == 5)
		philo->param->meals_nbr = ft_atoi(argv[5]);
	else
		philo->param->meals_nbr = 0;
	//gettimeofday(&time, NULL);
	//philo->param->start_time = time.tv_sec;
	//printf("Deu bom em %d :D\n", time.tv_usec);
	//printf("em segundos: %li\n", philo->param->start_time);
	return (0);
}

int	main(int argc, char *argv[])
{
	int i;
	
	i = 0;
	//param = (void *)malloc(sizeof(t_para));
	//param.start_time = NULL;
	if (validate_args(argc) != 0)
		return(1);
	if (entry_args_check(argc, argv) != 0)
		return(1);
	while (i++ <= *argv[1])
		init_philosophers(i, argv, argc);
	return(0);
}
