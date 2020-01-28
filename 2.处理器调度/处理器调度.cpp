#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#include<windows.h>
FILE *p_fcfs,*p_rr,*p_sjf,*p_hrn;
//*********************************************
struct{
	char id;//������--
	int arrive_time;//����ʱ��--
	int serve_time;//����ʱ��--
	int remain_servetime;//ʣ������ʱ��
	int start_time;//��ʼִ��ʱ��
	int finish_time;//���ʱ��
	int route_time;//��תʱ��
	float rrt;//��Ȩ��תʱ��
}Process[20];//������̵���ؽṹ��Ϣ
//*********************************************

//������ȫ�ֱ�������
//*********************************************
int N;//�ܽ�����Ŀ
int allover_time=0;//һ����ִ��ʱ��
int ready_queue[20];//���̾�������
int time=0;//ʱ�����
int count_of_queue=0;//���������еĽ�����Ŀ
//*********************************************

//��ʼ��ÿ������
void Initialize_Process()
{
	int i=0;
	for(;i<N;i++)
	{
		Process[i].start_time=0;
		Process[i].finish_time=0;
		Process[i].route_time=0;
		Process[i].rrt=0;
		Process[i].remain_servetime=Process[i].serve_time;
		allover_time+=Process[i].serve_time;//�����ܹ�ִ�е�ʱ��
		ready_queue[i]=-1;//��������Ϊ��
	}
}

//��ӡ������������۵ĸ�ʽ��ʾ����
void Print()
{
	
	float aver_rrt=0;//ƽ����Ȩ��תʱ��
	float aver_routetime=0;//ƽ����תʱ��
	printf("******************************************************************\n");
    printf("������  ����ʱ�� ����ʱ�� ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ��\n");
	for(int i=0;i<N;i++)
	{
		aver_rrt+=Process[i].rrt;
		aver_routetime+=Process[i].route_time;
		printf("%2c\t",Process[i].id);
		printf("%5d\t",Process[i].arrive_time);
		printf("%5d\t",Process[i].serve_time);
		printf(" %5d\t",Process[i].start_time);
		printf(" %5d\t",Process[i].finish_time);
		printf("  %5d\t",Process[i].route_time);
		printf("   %7.2f\n",Process[i].rrt);
	}
	printf("\n\tƽ����תʱ��:%.2f\tƽ����Ȩ��תʱ��:%.2f\n",aver_routetime/N,aver_rrt/N);
	printf("******************************************************************\n");
}

//ִ�������ȷ����㷨
void fcfs()
{
	p_fcfs=fopen("./FCFS.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                   ��ӭ����FCFS����\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <ʱ������>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("ʱ  �䣺");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("��������");
	int earliest_arrive_time;//�������������絽��Ľ��̵ĵ���ʱ��
	int pid;//ģ������絽��Ľ��̵Ľ��̺�
	time=0;
	count_of_queue=0;
	while(time<=allover_time)
	{
		int i;
		count_of_queue=0;
		for(i=0;i<N;i++)//������ʱ���ڵ�ǰ��timeǰ�����н��̼��������
		{
			if(Process[i].arrive_time<=time && Process[i].remain_servetime!=0)
			//������֤��һ���ǵ���ʱ�䲻�ܳ�����ǰʱ�䣬һ����ʣ�����ʱ�䲻��Ϊ0
			{
				ready_queue[count_of_queue]=i;
				count_of_queue++;
			}
		}

		if(count_of_queue==0)//˵����������Ϊ��
		{
			printf("   ");//��¼����
			time++;
		}
		else
		{
			//Ѱ�Ҵ�ʱ���ȵ����Ľ���
			earliest_arrive_time=Process[ready_queue[0]].arrive_time;
			pid=ready_queue[0];
			for(i=1;i<count_of_queue;i++)
			{
				if(earliest_arrive_time>Process[ready_queue[i]].arrive_time)//swap
				{
					earliest_arrive_time=Process[ready_queue[i]].arrive_time;
					pid=ready_queue[i];
				}	
			}
			Process[pid].start_time=time;//find the first process's start time;
			int t1=time;
			time+=Process[pid].serve_time;
			for(;t1<time;t1++)
			{
				char ch=Process[pid].id;

			//	fputc(ch,p_fcfs);/////
				fprintf(p_fcfs,"%c\n",ch);
			//	Sleep(600);
				printf("%c  ",Process[pid].id);//��¼����
			}
			Process[pid].finish_time=time;
			Process[pid].remain_servetime=0;
			Process[pid].route_time=Process[pid].finish_time-Process[pid].arrive_time;
			Process[pid].rrt=(float)Process[pid].route_time/Process[pid].serve_time;
		}	
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("               FCFS�����ȷ����㷨ģ��\n");
	Print();//���ô�ӡ���������ʾ�����
	fclose(p_fcfs);
}

void rr()
{
	p_rr=fopen("./RR.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                   ��ӭ����RR(q=1)����\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <ʱ������>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("ʱ  �䣺");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("��������");
	count_of_queue=0;
	int flag=-1;//��ǽ����Ƿ�ִ����ϣ�-1Ϊδִ����ϣ�����Ϊִ�����
	int i;
	time=0;
	while(time<=allover_time)
	{
		//���ڵ�ǰtimeʱ�̵���Ľ��̼����������
		for(i=0;i<N;i++)
		{
			if(Process[i].arrive_time==time)
			{
				ready_queue[count_of_queue++]=i;
			}
		}
		if(flag!=-1)//ִ�����
		{
			ready_queue[count_of_queue++]=flag;
		}
		if(count_of_queue==0)//�����޽���
		{
			if(time<=allover_time)
				printf("   ");//��¼����
			time++;
		}
		else//ȡ����
		{
			if(Process[ready_queue[0]].remain_servetime==Process[ready_queue[0]].serve_time)
				Process[ready_queue[0]].start_time=time;//������̵Ŀ�ʼʱ��
			if(Process[ready_queue[0]].remain_servetime<=1)//q=1,���̽�Ҫ���������������һ���Ǳ���ִ������ɽ���״̬����һ�����Ѿ�Ϊ����״̬
			{
				int t1=time;
				time+=Process[ready_queue[0]].remain_servetime;
				for(;t1<time;t1++)
				{
					char ch=Process[ready_queue[0]].id;
					fprintf(p_rr,"%c\n",ch);
				//	Sleep(600);
					printf("%c  ",Process[ready_queue[0]].id);//��¼����
				}
				Process[ready_queue[0]].finish_time=time;
				Process[ready_queue[0]].route_time=time-Process[ready_queue[0]].arrive_time;
				Process[ready_queue[0]].rrt=(float)Process[ready_queue[0]].route_time/Process[ready_queue[0]].serve_time;
				flag=-1;
			}
			else//����δ����
			{
				time++;
				char ch=Process[ready_queue[0]].id;
				fprintf(p_rr,"%c\n",ch);
			//	Sleep(600);
				printf("%c  ",Process[ready_queue[0]].id);//��¼����
				Process[ready_queue[0]].remain_servetime--;
				flag=ready_queue[0];
			}
			//��ʱ��Ҫ�����̵������������
			for(i=0;i<(count_of_queue-1);i++)
			{
				ready_queue[i]=ready_queue[i+1];
			}
			count_of_queue--;
		}
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("               RR��ת(q=1)\n");
	Print();//���ô�ӡ���������ʾ�����
	fclose(p_rr);
}

void SJF()//�㷨˼���FCFSһ����ֻ�ǲο��ı�׼��һ��
{
	p_sjf=fopen("./SJF.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                   ��ӭ����SJF����\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <ʱ������>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("ʱ  �䣺");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("��������");
	//////////////////////////////////
	int shortest_serve_time;//���������з���ʱ����̵Ľ��̵ķ���ʱ��
	int pid;//ģ��ķ���ʱ����̵Ľ��̵Ľ��̺�
	time=0;
	count_of_queue=0;
	while(time<=allover_time)
	{
		int i;
		count_of_queue=0;
		for(i=0;i<N;i++)//������ʱ���ڵ�ǰ��timeǰ�����н��̼��������
		{
			if(Process[i].arrive_time<=time && Process[i].remain_servetime!=0)
			//������֤��һ���ǵ���ʱ�䲻�ܳ�����ǰʱ�䣬һ����ʣ�����ʱ�䲻��Ϊ0
			{
				ready_queue[count_of_queue]=i;
				count_of_queue++;
			}
		}

		if(count_of_queue==0)//˵����������Ϊ��
		{
			if(time<=allover_time)
				printf("   ");//��¼����
			time++;
		}
		else
		{
			//Ѱ�Ҵ�ʱ���ȵ����Ľ���
			shortest_serve_time=Process[ready_queue[0]].serve_time;
			pid=ready_queue[0];
			//�ҳ�������������̷���ʱ��Ľ���
			for(i=1;i<count_of_queue;i++)
			{
				if(shortest_serve_time>Process[ready_queue[i]].serve_time)//swap
				{
					shortest_serve_time=Process[ready_queue[i]].serve_time;
					pid=ready_queue[i];
				}	
			}
			Process[pid].start_time=time;//find the first process's start time;
			int t1=time;
			time+=Process[pid].serve_time;
			for(;t1<time;t1++)
			{
				char ch=Process[pid].id;
				fprintf(p_sjf,"%c\n",ch);
		//		Sleep(600);
				printf("%c  ",Process[pid].id);//��¼����
			}
			Process[pid].finish_time=time;
			Process[pid].remain_servetime=0;
			Process[pid].route_time=Process[pid].finish_time-Process[pid].arrive_time;
			Process[pid].rrt=(float)Process[pid].route_time/Process[pid].serve_time;
		}	
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("               SJF��̽�������\n");
	Print();//���ô�ӡ���������ʾ���
	fclose(p_sjf);
}

//�����Ӧ�������㷨
//˼�룺R=1+(wait_ime/serve_time),����RΪ����Ȩ����������Ȩ�����е��Ƚ��̵�ִ��
//��W_S=wait_ime/serve_time
void HRN()
{
	p_hrn=fopen("./HRN.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("				 ��ӭ����HRN����\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <ʱ������>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("ʱ  �䣺");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("��������");
	float W_S;////��W_S=max(wait_ime/serve_time)
	int pid;//ģ���W_S�Ľ��̵Ľ��̺�
	time=0;
	count_of_queue=0;
	time=0;
	while(time<=allover_time)
	{
		int i;
		count_of_queue=0;
		for(i=0;i<N;i++)//������ʱ���ڵ�ǰ��timeǰ�����н��̼��������
		{
			if(Process[i].arrive_time<=time && Process[i].remain_servetime!=0)
			//������֤��һ���ǵ���ʱ�䲻�ܳ�����ǰʱ�䣬һ����ʣ�����ʱ�䲻��Ϊ0
			{
				ready_queue[count_of_queue]=i;
				count_of_queue++;
			}
		}

		if(count_of_queue==0)//˵����������Ϊ��
		{
			if(time<=allover_time)
				printf("   ");//��¼����
			time++;
		}
		else
		{
			W_S=(float)(time-Process[ready_queue[0]].arrive_time)/Process[ready_queue[0]].serve_time;
			pid=ready_queue[0];
			////�ҳ�����������W_S����
			for(i=0;i<count_of_queue;i++)
			{
				if(W_S<(float)(time-Process[ready_queue[i]].arrive_time)/Process[ready_queue[i]].serve_time)
				{
					W_S=(float)(time-Process[ready_queue[i]].arrive_time)/Process[ready_queue[i]].serve_time;
					pid=ready_queue[i];			
				}			
			}
			Process[pid].start_time=time;//find the first process's start time;
			int t1=time;
			time+=Process[pid].serve_time;
			for(;t1<time;t1++)
			{
				char ch=Process[pid].id;
				fprintf(p_hrn,"%c\n",ch);
	//			Sleep(600);
				printf("%c  ",Process[pid].id);//��¼����
			}
			Process[pid].finish_time=time;
			Process[pid].remain_servetime=0;
			Process[pid].route_time=Process[pid].finish_time-Process[pid].arrive_time;
			Process[pid].rrt=(float)Process[pid].route_time/Process[pid].serve_time;
		}
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n\n");
	printf("               HRN�����Ӧ������\n");
	Print();
	fclose(p_hrn);
}

void main()
{   
	printf("�������еĽ�����Ŀ��������20������");
	cin>>N;
	cout<<"*********************�������йؽ���*************************"<<endl;
	cout<<"�밴�����Ҹ�ʽ���������Ϣ��<������> <����ʱ��> <����ʱ��>"<<endl<<endl;
	for(int i=0;i<N;i++)
	{
		cout<<"��"<<i+1<<"�����̣�"<<'\t';
		cin>>Process[i].id>>Process[i].arrive_time>>Process[i].serve_time;
	}
	cout<<"************************************************************"<<endl;
	//����fcfs�㷨
	Initialize_Process();	
    fcfs();

	//������ת��(q=1)
    Initialize_Process();
	rr();

	//����SJF��̽�������
	Initialize_Process();
    SJF();

	//HRN�����Ӧ������
	Initialize_Process();
    HRN();
}
