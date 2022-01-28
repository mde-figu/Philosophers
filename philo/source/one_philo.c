#include "../includes/philo.h"

void	only_onephilo(t_philo *one)
{
	printf("%ld %i has taken a fork\n", time_calc(one->params->start_time),
		one->name);
	usleep(one->params->t_todie * 1000);
	printf("%ld %i died\n", time_calc(one->params->start_time), one->name);
}
