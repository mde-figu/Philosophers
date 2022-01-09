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

static void struct_init(t_param *param, t_philo *philo)
{
	philo->name = 0;
	philo->last_meal = 0;
	philo->death = 0;
	philo->satisfied = 0;
	philo->times_eat = 0;
	philo->fork_left = 0;
	philo->fork_rigth = 0;
	param->philo_nbr = 0;
	param->t_todie = 0;
	param->t_toeat = 0;
	param->t_tosleep = 0;
	param->meals_nbr = 0;
	param->start_time = 0; 
}

int	main(int argc, char *argv[])
{
	struct timeval time;
	t_param param;
	t_philo	philo;

	//param = (void *)malloc(sizeof(t_para));
	//param.start_time = NULL;
	struct_init(&param, &philo);
	if (validate_args(argc) != 0)
		return(1);
	if (entry_args_check(argc, argv) != 0)
		return(1);
	gettimeofday(&time, NULL);
	param.start_time = time.tv_sec;
	printf("Deu bom em %ld :D\n", time.tv_usec);
	printf("em segundos: %li\n", param.start_time);
	printf("Meals inicializado: %i\n", param.meals_nbr);
	printf("ultima ceia:%li \n", philo.last_meal);
	return(0);
}
