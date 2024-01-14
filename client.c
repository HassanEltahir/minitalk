/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:10:30 by haeltahi          #+#    #+#             */
/*   Updated: 2024/01/13 22:29:16 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!(s))
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32 && *str))
		str++;
	if (*str == '-')
		sign = -1;
	if ((*str == '+' || *str == '-') && *str)
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result = 10 * result + (*str - '0');
		str++;
		if ((result > LONG_MAX / 10) || (result == LONG_MAX / 10 && (*str
					- '0') > LONG_MAX % 10))
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (sign * result);
}

void	handler(int signal1, siginfo_t *info, void *context)
{
	int	pid;

	(void)(context);
	pid = info->si_pid;
	while (1)
	{
		if (signal1 == SIGUSR1)
		{
			printf("we recieved");
			break ;
		}
	}
}

void	convertchartobit(int pid, char character)
{
	int	i;
	int	mask;

	i = 0;
	while (i < 8)
	{
		mask = 1 << i;
		if ((character & mask) == 0)
		{
			kill(pid, SIGUSR2);
		}
		else
		{
			kill(pid, SIGUSR1);
		}
		i++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	int					i;
	int					pid;
	char				*message;
	struct sigaction	sw;
	int					j;

	(void)ac;
	if (ac == 3)
	{
		sigemptyset(&sw.sa_mask);
		sw.sa_flags = SA_SIGINFO;
		sw.sa_sigaction = &handler;
		sigaction(SIGUSR1, &sw, NULL);
		i = 0;
		pid = ft_atoi(av[1]);
		message = av[2];
		j = 0;
		while (message[j])
			j++;
		while (i < j)
			convertchartobit(pid, message[i++]);
		convertchartobit(pid, '\0');
	}
	else
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", 2);
}
