/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:54:05 by haeltahi          #+#    #+#             */
/*   Updated: 2024/01/14 12:16:57 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static void	ft_print(int nb, int fd)
{
	char	c;

	if (nb > 0)
	{
		ft_print(nb / 10, fd);
		c = nb % 10 + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == 0)
	{
		write(fd, "0", 1);
	}
	else if (nb == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		nb = 147483648;
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	ft_print(nb, fd);
}

void	signal_handler(int signal1, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	character = 0;
	int			pid;
	int			mask;

	(void)context;
	pid = info->si_pid;
	if (signal1 == SIGUSR1)
	{
		mask = 1 << i++;
		character = (character | mask);
	}
	else if (signal1 == SIGUSR2)
		i++;
	if (i == 8)
	{
		if (character == '\0')
			kill(pid, SIGUSR1);
		else
		{
			i = 0;
			write(1, &character, 1);
			character = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sw;

	ft_putstr_fd("PID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigemptyset(&sw.sa_mask);
	sw.sa_flags = SA_SIGINFO;
	sw.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &sw, NULL);
	sigaction(SIGUSR2, &sw, NULL);
	while (1)
	{
		pause();
	}
}
