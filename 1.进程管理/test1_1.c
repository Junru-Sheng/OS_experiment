//实现实验的第一个内容：父进程->子进程1->子进程2
#include<stdio.h>
#include<unistd.h>

int main()
{
	int pid=fork();
	if(pid==0)//创建子进程
	{
		//创建一个子进程p1
		printf("我是一个子进程。\n");
		printf("该子进程的pid为：%d.\n",getpid());
		//创建一个子进程p2
		pid=fork();
		if(pid==0)
		{
			//创建一个子进程p1-2
			printf("我是一个子子进程。\n");
			printf("该子子进程的pid为：%d.\n",getpid());
		}
		else if(pid<0)
		{
			//操作系统出错，可能进程数量达到上限或者其他原因
			printf("fork() error.\n");
		}
	}
	else if(pid>0)
			//创建父进程
		{
			printf("我是一个父进程。\n");
			printf("父进程的pid为：%d.\n",getpid());
		}
	else 
	{
		//操作系统出错，可能进程数量达到上限或者其他原因
		printf("fork() error.\n");
	}
	return 0;
}
