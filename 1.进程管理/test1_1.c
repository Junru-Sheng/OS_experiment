//ʵ��ʵ��ĵ�һ�����ݣ�������->�ӽ���1->�ӽ���2
#include<stdio.h>
#include<unistd.h>

int main()
{
	int pid=fork();
	if(pid==0)//�����ӽ���
	{
		//����һ���ӽ���p1
		printf("����һ���ӽ��̡�\n");
		printf("���ӽ��̵�pidΪ��%d.\n",getpid());
		//����һ���ӽ���p2
		pid=fork();
		if(pid==0)
		{
			//����һ���ӽ���p1-2
			printf("����һ�����ӽ��̡�\n");
			printf("�����ӽ��̵�pidΪ��%d.\n",getpid());
		}
		else if(pid<0)
		{
			//����ϵͳ�������ܽ��������ﵽ���޻�������ԭ��
			printf("fork() error.\n");
		}
	}
	else if(pid>0)
			//����������
		{
			printf("����һ�������̡�\n");
			printf("�����̵�pidΪ��%d.\n",getpid());
		}
	else 
	{
		//����ϵͳ�������ܽ��������ﵽ���޻�������ԭ��
		printf("fork() error.\n");
	}
	return 0;
}
