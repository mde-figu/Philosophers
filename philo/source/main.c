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
			//printf("valor de i: %d arg é: %d \n", i, argv);
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

void	only_onephilo(t_dinner *one)
{
	printf("%ld %i has taken a fork\n", time_calc(one->params->start_time), one->philo->name);
	usleep(one->params->t_todie * 1000);
	printf("%ld %i died\n", time_calc(one->params->start_time), one->philo->name);
}

int	eating(t_dinner *dinner)
{
	pthread_mutex_lock(&dinner->params->forks[dinner->philo->fork_left]);
	printf("%ld %i has taken a fork\n", time_calc(dinner->params->start_time), dinner->philo->name);
	pthread_mutex_lock(&dinner->params->forks[dinner->philo->fork_right]);
	printf("%ld %i has taken a fork\n", time_calc(dinner->params->start_time), dinner->philo->name);
	printf("%ld %i is eating\n", time_calc(dinner->params->start_time), dinner->philo->name);
	dinner->philo->last_meal = phil_clockins();
	if (time_if_died(dinner->params->t_todie, dinner->philo->last_meal) == 0 && dinner->philo->satisfied == false)
	{
		dinner->params->death = true;
		return (1);
	}
	dinner->philo->meals++;
	if (dinner->philo->meals == dinner->params->meals_nbr)
		dinner->philo->satisfied = true;
	usleep(dinner->params->t_toeat * 1000);
	pthread_mutex_unlock(&dinner->params->forks[dinner->philo->fork_right]);
	pthread_mutex_unlock(&dinner->params->forks[dinner->philo->fork_left]);
	return (0);
}

int	sleeping(t_dinner *dinner)
{
	if (time_if_died(dinner->params->t_todie, dinner->philo->last_meal) == 0 && dinner->philo->satisfied == false)
	{
		dinner->params->death = true;
		return (1);
	}
	printf("%ld %i is sleeping\n", time_calc(dinner->params->start_time), dinner->philo->name);
	usleep(dinner->params->t_tosleep * 1000);
	return (0);
}

int	thinking(t_dinner *dinner)
{
	if (time_if_died(dinner->params->t_todie, dinner->philo->last_meal) == 0 && dinner->philo->satisfied == false)
	{
		dinner->params->death = true;
		return (1);
	}
	printf("%ld %i is thinking\n", time_calc(dinner->params->start_time), dinner->philo->name);
	usleep(dinner->params->t_tosleep * 1000);// ta certo isso?
	return (0);
}

void	routine(t_dinner *dinner)
{
	while (42 && dinner->params->death == false)
	{
		if (dinner->params->death == true)
			return ;
		if (dinner->philo->satisfied == true)
			return ;
		if (dinner->params->death == false && dinner->params->exit == false)
			eating(dinner);
		if (dinner->params->death == false && dinner->params->exit == false)
			sleeping(dinner);
		if (dinner->params->death == false && dinner->params->exit == false)
			thinking(dinner);
	}
}

void	*dinning(void *d_dinner)
{
	t_dinner	*dinner;
	
	dinner = d_dinner;
	if (dinner->params->philo_nbr == 1)
	{
		only_onephilo(dinner);
		return(NULL);
	}
	if (dinner->philo->name % 2 == 0)
		usleep(1000);
	routine(dinner);
	if (dinner->params->death == true && dinner->params->exit == false)
	{
		dinner->params->exit = true;
		printf("%ld %i died\n", time_calc(dinner->params->start_time), dinner->philo->name);
	}
	return NULL;
}

static void	init_philosophers(t_dinner *dinner, int total_philo, int i)
{
	while (i++ < total_philo)
	{
		dinner->philo[i].name = i;
		//printf("%d\n", i);
		dinner->philo[i].fork_right = i;
		dinner->philo[i].fork_left = (i + 1) % total_philo;
		dinner->philo[i].satisfied = false;
	}
	i = 0;
	while (i++ < total_philo)
	{
		pthread_create(&dinner->philo[i].thread_philo, NULL, dinning, dinner);
	}
	i = 0;
	while (i++ < total_philo)
	{
		pthread_join(dinner->philo[i].thread_philo, NULL);
	}
	free(dinner->philo);
}

static int	init_mutex(t_dinner *d)
{
	int	i;

	i = 0;
	while (d->params->philo_nbr > i)
	{
		if (pthread_mutex_init(d->params->forks + i, NULL))
			return (-1);
		i++;
	}
	return (0);
}

static int		init_dinner(t_dinner *dinner)
{
	if (alloc_struct(dinner))
		return (2);
	if (init_mutex(dinner))
		return (3);
	init_philosophers(dinner, dinner->params->philo_nbr, 0);
	if (dinner->philo->satisfied)
		printf("Tuco comeu tudo e saiu sem pagar\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_param		params;
	t_dinner	dinner;
	int i;

	i = 0;
	//init_struct(&dinner);
	dinner.params = &params;
	//ft_memset(&param, 0, sizeof(t_param));
	//ft_memset(philo, 0, sizeof(t_philo));
	if (validate_args(argc) != 0)
		return(1);
	if (entry_args_check(argc, argv) != 0)
		return(1);
	get_paramm(argv, &params);
	if (init_dinner(&dinner) != 0)
	{
		printf("rodou init_dinner, vai sair  com a comanda sem pagar, oh la!\n");
		return(1);
	}
	while (i < params.philo_nbr)
	{
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	free(params.forks);
	return(0);
}
