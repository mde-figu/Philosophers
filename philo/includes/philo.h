#ifndef	PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int					philo_nbr;
	int					t_todie;
	bool				death;
	int					t_toeat;
	int					t_tosleep;
	int					meals_nbr;
	long int			start_time;
	bool				exit;
	pthread_mutex_t		*forks;
}	t_param;

typedef struct s_philo
{
	int					name;
	long int			last_meal;
	int					meals;
	bool				satisfied;
	int					times_eat;
	int					fork_left;
	int					fork_right;
	pthread_t			thread_philo;
	//t_param				*params;
}	t_philo;

typedef struct s_dinner
{
	t_param				*params;
	t_philo				*philo;
}	t_dinner;


/********
** DINNER
*********/
void		*dinner();

/********
** PARSE
*********/
void	init_struct(t_dinner *dinner);
void	get_paramm(char *argv[], t_param *param);
int		alloc_struct(t_dinner *dinner);

/********
** TIME
*********/
unsigned long int	time_calc(long int start_time);
unsigned long int	phil_clockins(void);
int time_if_died(long int dead_time, long int last_meal);

/********
** UTILS
*********/

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif