#ifndef	PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int					philo_nbr;
	int					t_todie;
	int					t_toeat;
	int					t_tosleep;
	int					meals_nbr;
	long int		start_time;
}	t_param;

typedef struct s_philo
{
	int				name;
	long int		last_meal;
	int				death; //bool?
	int				satisfied; //bool?
	int				times_eat;
	int				fork_left;
	int				fork_rigth; 
	//t_param		*param;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*ft_memset(void *s, int c, size_t n);

#endif