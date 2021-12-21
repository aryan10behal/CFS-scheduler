/* Name: Aryan Behal
   Roll_Number: 2019026 */

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h> 
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>
#include <errno.h> 
#include<string.h>


#define _GNU_SOURCE
#define SYS_rt_nice 441

int process(int pid,long time)
{
	if(time>0)
		{
		syscall(SYS_rt_nice,pid,time);
		//for getting success or error mssg
		printf("\nSyscall was called...\nMessage: %s\n", strerror(errno));
		printf("Syscall returned %d\n\n",errno);
		if(errno==0)
			{
				for(long i=0;i<10000000000;i++);
				return 0;
			}
		return -1;
		}
	else
		{
			for(long i=0;i<10000000000;i++);
			return 0;
		}
}	
int main()
{
	long time;
	pid_t ret_value;
	int status;
	clock_t begin,end; 
	int pid;
	//forking
	ret_value=fork();
	if(ret_value<0)
		{
			printf("could not fork..\n");
			//couldn't create child process
		}
	else if(ret_value == 0)
	{
		//child
		printf("\nProcess With soft real-time requirements....\n\nEnter soft real-time req: ");
		scanf("%ld",&time);
		printf("Enter pid: ");
		scanf("%d",&pid);
		begin =clock();
		int err=process(pid,time);
		end =clock();
		if(err==0)
			printf("\n--> This is time with syscall: %lf\n",(double)(end-begin)/CLOCKS_PER_SEC);
		exit(0);
	}
	else
	{
		//parent
		waitpid(ret_value,&status,0);
		printf("\n->> Enter -1 to exit: ");
		int ex=0;
		scanf("%d",&ex);
		if(ex==-1)
			exit(0);
		printf("\n\nNow without soft real-time requirements..\n\nEnter pid: ");
		scanf("%d",&pid);
		begin =clock();
		int err=process(pid,0);
		end =clock();
		if(err==0)
		printf("\n--> This is time without syscall: %lf\n",(double)(end-begin)/CLOCKS_PER_SEC);
		exit(0);
	}
}
