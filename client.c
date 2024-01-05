/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:47:52 by haeltahi          #+#    #+#             */
/*   Updated: 2024/01/05 16:25:31 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
		usleep(200);
	}
}

int	main(int ac, char **argv)
{
	int		server_pid;
	char	*message;
	int		i;

	if (ac != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	while (i < ft_strlen(message))
	{
		convertchartobit(server_pid, message[i]);
		i++;
	}
}
