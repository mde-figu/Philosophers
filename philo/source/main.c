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

long int	phil_clockins(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);

	return (time.tv_sec / 1000);
}

static void	get_param(char *argv[], t_param *param)
{

	param->philo_nbr = ft_atoi(argv[1]);
	param->t_todie = ft_atoi(argv[2]);
	printf("apos guardar o valor, t_todie tem %i\n",param->t_todie);
	param->t_toeat = ft_atoi(argv[3]);
	param->t_tosleep = ft_atoi(argv[4]);
	if (argv[5])
		param->meals_nbr = ft_atoi(argv[5]);
	else
		param->meals_nbr = 0;
	param->start_time = phil_clockins();
	printf("em segundos: %li\n", param->start_time);
}

static void struct_init(t_param *param, t_philo *philo)
{
	philo->name = 0;
	philo->last_meal = 0;
	philo->death = 0;
	philo->satisfied = 0;
	philo->times_eat = 0;
	philo->fork_left = 0;
	philo->fork_right = 0;
	param->philo_nbr = 0;
	param->t_todie = 0;
	param->t_toeat = 0;
	param->t_tosleep = 0;
	param->meals_nbr = 0;
	param->start_time = 0; 
}

int	main(int argc, char *argv[])
{
	t_param param;
	t_philo	philo;

	struct_init(&param, &philo);
	if (validate_args(argc) != 0)
		return(1);
	if (entry_args_check(argc, argv) != 0)
		return(1);
	get_param(argv, &param);
	printf("philo_nbr inicializado: %i\n", param.philo_nbr);
	printf("time to die inicializado: %i\n", param.t_todie);
	printf("time to eat inicializado: %i\n", param.t_toeat);
	printf("time to sleep: %i\n", param.t_tosleep);
	printf("Meals inicializado: %i\n", param.meals_nbr);
	printf("Tempo de 1970: %ld\n", param.start_time);
	printf("nome :%i \n", philo.name);
	printf("ultima ceia:%li \n", philo.last_meal);
	printf("morte do philo:%i \n", philo.death);
	printf("pança cheia:%i \n", philo.satisfied);
	printf("hora de comer:%i \n", philo.times_eat);
	printf("Garfo esq:%i \n", philo.fork_left);
	printf("Garfo dir:%i \n", philo.fork_right);

	return(0);
}
