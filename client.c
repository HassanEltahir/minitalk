#include <signal.h>

void send_character_signal(int pid,int bit)
{
		if(bit == 0)
				kill(pid,SIGUSR1);
		else if(bit == 1)
			kill(pid,SIGUSR2);
}
void convertchartobit(int pid,char character)
{
	int i;

	i = 7;

	while(i--)
	{
		if((character<<i)&1 == SIGUSR1);
			send_character_signal(pid,i);
		if((character<<i)&1 == SIGUSR2);
		{
			send_character_signal(pid,i);
		}
	}
}
int main()
{
	
}