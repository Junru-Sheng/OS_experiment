//ʵ��ʵ�����ݵڶ�����
#include<stdio.h>
#include<unistd.h>
int main()
{
	int pid;
	/*���ﴴ����һ���ӽ���1*/
	pid=fork();
	if(pid==0)
	{
		printf("����һ���ӽ���p1��\n");
		printf("���ӽ���p1��pidΪ��%d.\n\n",getpid());
	}
	else if(pid>0)
	{		
		pid=fork();
		if(pid==0)
		{
			/*���ﴴ����һ���ӽ���2*/
			printf("����һ���ӽ���p2��\n");
			printf("���ӽ���p2��pidΪ��%d.\n\n",getpid());
		}
		else if(pid>0)
		{
			//����������
			printf("���Ǹ����̡�\n");
			printf("�����̵�pidΪ��%d.\n\n",getpid());
		}
		else
		{
			//����ϵͳ�������ܽ��������ﵽ���޻�������ԭ��
			printf("fork() error.\n");
		}
	}
	else
	{
		//����ϵͳ�������ܽ��������ﵽ���޻�������ԭ��
		printf("fork() error.\n");
	}
	return 0;
}