#include "../includes/philo.h"

void init_struct(t_dinner *dinner)
{
	//philo->param = NULL;
	dinner->philo->name = 0;
	dinner->philo->meals = 0;
	dinner->philo->last_meal = 0;
	//philo->death = false;
	dinner->philo->satisfied = false;
	dinner->philo->times_eat = 0;
	dinner->philo->fork_left = 0;
	dinner->philo->fork_right = 0;
	dinner->params->death = false;
	dinner->params->exit = false;
	dinner->params->philo_nbr = 0;
	dinner->params->t_todie = 0;
	dinner->params->t_toeat = 0;
	dinner->params->t_tosleep = 0;
	dinner->params->meals_nbr = 0;
	dinner->params->start_time = 0;
	// printf("philo_name: %i\n", philo->name);
	// printf("philo_nbr: %i\n", philo->param->philo_nbr);
	// printf("time_die: %i\n", philo->param->t_todie);
	// printf("time_eat: %i\n", philo->param->t_toeat);
	// printf("time_sleep: %i\n", philo->param->t_tosleep);
}

void	get_paramm(char *argv[], t_param *param)
{
	int i;

	i = 0;
	param->philo_nbr = ft_atoi(argv[1]);
	param->t_todie = ft_atoi(argv[2]);
	param->t_toeat = ft_atoi(argv[3]);
	param->t_tosleep = ft_atoi(argv[4]);
	if (argv[5])
		param->meals_nbr = ft_atoi(argv[5]);
	else
		param->meals_nbr = 0;
	param->start_time = phil_clockins();
	// param->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (param->philo_nbr + 32));
	// while (i < param->philo_nbr)
	// {
	// 	pthread_mutex_init(&param->forks[i], NULL);
	// 	i++;
	// }
	//printf("Deu bom em %d :D\n", time->tv_usec);
	//printf("em segundos: %li\n", param->start_time);
}

int	alloc_struct(t_dinner *dinner)
{
	dinner->philo = malloc(sizeof(*dinner->philo) * dinner->params->philo_nbr);
	if (dinner->philo == 0)
		return (-1);
	dinner->params->forks = malloc(sizeof(*dinner->params->forks) * dinner->params->philo_nbr);
	if (dinner->params == 0)
		return (-1);
	return (0);
}
