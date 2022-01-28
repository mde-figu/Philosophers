#include "../includes/philo.h"

void	init_struct(t_param *param, t_philo *philo)
{
	philo->name = 0;
	philo->meals = 0;
	philo->last_meal = 0;
	philo->satisfied = false;
	philo->times_eat = 0;
	philo->fork_left = 0;
	philo->fork_right = 0;
	param->who_dead = 0;
	param->philo_nbr = 0;
	param->t_todie = 0;
	param->t_toeat = 0;
	param->t_tosleep = 0;
	param->meals_nbr = 0;
	param->start_time = 0;
}

void	get_paramm(char *argv[], t_param *param)
{
	int	i;

	i = 0;
	param->philo_nbr = ft_atoi(argv[1]);
	param->t_todie = ft_atoi(argv[2]);
	param->t_toeat = ft_atoi(argv[3]);
	param->t_tosleep = ft_atoi(argv[4]);
	if (argv[5])
		param->meals_nbr = ft_atoi(argv[5]);
	else
		param->meals_nbr = 0;
	param->start_time = 0;
	param->forks = malloc(sizeof(pthread_mutex_t) * (param->philo_nbr));
	while (i < param->philo_nbr)
	{
		pthread_mutex_init(&param->forks[i], NULL);
		i++;
	}
}
