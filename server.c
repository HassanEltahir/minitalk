#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>



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
void sig_handler(int signum,siginfo_t *info,void* context)
{
	(void)context;

	static int bit_count;

	bit_count = 0;

	recieved_data = 1;

	if(signum == SIGUSR2)
		bit_count++;
	else if(signum == SIGUSR1)
	{
		int byte_count = bit_count /8;
		printf("Recieved%d bytes \n",byte_count);
		bit_count = 0;
		recieved_data = 0;
	}
}
int main(int ac,char **av)
{

	struct sigaction sa;
	sa.sa_sigaction = &sig_handler;
	sa.sa_flags = SA_SIGINFO;
	(void)av;
	while(ac != 1)
		ft_putstr_fd("Enter a correct PID",2);
	printf("Service PID : %d\n",getpid());
while (1)
{
	pause();
}


}
