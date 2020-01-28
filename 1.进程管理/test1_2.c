//实现实验内容第二部分
#include<stdio.h>
#include<unistd.h>
int main()
{
	int pid;
	/*这里创建了一个子进程1*/
	pid=fork();
	if(pid==0)
	{
		printf("我是一个子进程p1。\n");
		printf("该子进程p1的pid为：%d.\n\n",getpid());
	}
	else if(pid>0)
	{		
		pid=fork();
		if(pid==0)
		{
			/*这里创建了一个子进程2*/
			printf("我是一个子进程p2。\n");
			printf("该子进程p2的pid为：%d.\n\n",getpid());
		}
		else if(pid>0)
		{
			//创建父进程
			printf("我是父进程。\n");
			printf("父进程的pid为：%d.\n\n",getpid());
		}
		else
		{
			//操作系统出错，可能进程数量达到上限或者其他原因
			printf("fork() error.\n");
		}
	}
	else
	{
		//操作系统出错，可能进程数量达到上限或者其他原因
		printf("fork() error.\n");
	}
	return 0;
}