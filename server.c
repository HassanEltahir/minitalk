/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:48:12 by haeltahi          #+#    #+#             */
/*   Updated: 2024/01/05 15:50:37 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	signal_handler(int signum)
{
	static int	recieved_bits;
	static char	charachter;
	int			mask;

	recieved_bits = 0;
	charachter = 0;
	if (signum == SIGUSR1)
	{
		mask = 1 << recieved_bits;
		charachter = (charachter | mask);
		recieved_bits++;
	}
	else if (signum == SIGUSR2)
	{
		recieved_bits++;
	}
	if (recieved_bits == 8)
	{
		recieved_bits = 0;
		write(1, &charachter, 1);
		charachter = 0;
	}
}

int	main(void)
{
	printf("PID: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
}
