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

static void	get_paramm(char *argv[], t_param *param)
{
	int i;

	i = 0;
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
	param->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (param->philo_nbr + 32));
	while (i < param->philo_nbr)
	{
		pthread_mutex_init(&param->forks[i], NULL);
		i++;
	}
	//printf("Deu bom em %d :D\n", time->tv_usec);
	printf("em segundos: %li\n", param->start_time);
}

void	*dinner()
{
	//(void)caio;
	printf("Vou comer sem pagar, pq sou desses\n");
	return NULL;
}

static void	init_philosophers(t_philo *philo, t_param *param, int total_philo, int i)
{
	//t_philo *philo;
	//philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_philo);
	philo = (t_philo *)malloc(sizeof(t_philo) * total_philo + 64);
	while (i++ < total_philo)
	{
		printf("CHEGO O %i NA MESA!\n", i);
		//memset(&philo[i], 0, sizeof(t_philo));
		philo[i].name = i;
		philo[i].fork_rigth = i;
		philo[i].fork_left = (i + 1) % total_philo;
		//pthread_mutex_init(&philo[i].forks[i], NULL);
		philo[i].params = param;
	}
	i = 0;
	while (i++ < total_philo)
	{
		pthread_create(&philo[i].t_philo, NULL, &dinner, (void *)&philo[i]);
	}
	i = 0;
	while (i++ < total_philo)
	{
		pthread_join(philo[i].t_philo, NULL);
	}
	free(philo);
	//printf("philo_name: %i\n", philo[1].name);
	//printf("philo_nbr: %i\n", param->philo_nbr);
	//printf("time_die: %i\n", param->t_todie);
	//printf("time_eat: %i\n", param->t_toeat);
	//printf("time_sleep: %i\n", param->t_tosleep);
}

static int		init_dinner(t_philo *philo, t_param *param)
{
	printf("CHEGUEI NA MESA!\n");
	//philo = NULL;
	init_philosophers(philo, param, param->philo_nbr, 0);
	return (0);
}

void init_struct(t_param *param, t_philo *philo)
{
	//philo->param = NULL;
	philo->name = 0;
	philo->last_meal = 0;
	philo->death = false;
	philo->satisfied = false;
	philo->times_eat = 0;
	philo->fork_left = 0;
	philo->fork_rigth = 0;
	param->philo_nbr = 0;
	param->t_todie = 0;
	param->t_toeat = 0;
	param->t_tosleep = 0;
	param->meals_nbr = 0;
	param->start_time = 0;
	// printf("philo_name: %i\n", philo->name);
	// printf("philo_nbr: %i\n", philo->param->philo_nbr);
	// printf("time_die: %i\n", philo->param->t_todie);
	// printf("time_eat: %i\n", philo->param->t_toeat);
	// printf("time_sleep: %i\n", philo->param->t_tosleep);
}

int	main(int argc, char *argv[])
{
	t_param param;
	t_philo philo;

	init_struct(&param, &philo);
	//ft_memset(&param, 0, sizeof(t_param));
	//param = (void *)malloc(sizeof(t_param));
	//param.start_time = NULL;
	if (validate_args(argc) != 0)
		return(1);
	if (entry_args_check(argc, argv) != 0)
		return(1);
	get_paramm(argv, &param);
	printf("meals_nbr: %i\n", param.meals_nbr);
	if (init_dinner(&philo, &param) != 0)
	{
		printf("rodou init_dinner, vai sair  com a comanda sem pagar, oh la!\n");
		return(1);
	}
	free(param.forks);
	//while (i++ <= *argv[1])
	//	init_philosophers(i, argv, argc);
	return(0);
}
