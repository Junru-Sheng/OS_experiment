#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#include<windows.h>
FILE *p_fcfs,*p_rr,*p_sjf,*p_hrn;
//*********************************************
struct{
	char id;//进程名--
	int arrive_time;//到达时间--
	int serve_time;//服务时间--
	int remain_servetime;//剩余服务的时间
	int start_time;//开始执行时间
	int finish_time;//完成时间
	int route_time;//周转时间
	float rrt;//带权周转时间
}Process[20];//定义进程的相关结构信息
//*********************************************

//下面是全局变量定义
//*********************************************
int N;//总进程数目
int allover_time=0;//一共的执行时间
int ready_queue[20];//进程就绪队列
int time=0;//时间参数
int count_of_queue=0;//就绪队列中的进程数目
//*********************************************

//初始化每个进程
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
		allover_time+=Process[i].serve_time;//计算总共执行的时间
		ready_queue[i]=-1;//就绪队列为空
	}
}

//打印，将结果以美观的格式显示出来
void Print()
{
	
	float aver_rrt=0;//平均带权周转时间
	float aver_routetime=0;//平均周转时间
	printf("******************************************************************\n");
    printf("进程名  到达时间 服务时间 开始时间 完成时间 周转时间 带权周转时间\n");
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
	printf("\n\t平均周转时间:%.2f\t平均带权周转时间:%.2f\n",aver_routetime/N,aver_rrt/N);
	printf("******************************************************************\n");
}

//执行先来先服务算法
void fcfs()
{
	p_fcfs=fopen("./FCFS.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                   欢迎进入FCFS调度\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <时间序列>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("时  间：");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("进程名：");
	int earliest_arrive_time;//就绪队列中最早到达的进程的到达时间
	int pid;//模拟的最早到达的进程的进程号
	time=0;
	count_of_queue=0;
	while(time<=allover_time)
	{
		int i;
		count_of_queue=0;
		for(i=0;i<N;i++)//将到达时间在当前的time前的所有进程加入队列中
		{
			if(Process[i].arrive_time<=time && Process[i].remain_servetime!=0)
			//两个保证，一个是到达时间不能超过当前时间，一个是剩余服务时间不能为0
			{
				ready_queue[count_of_queue]=i;
				count_of_queue++;
			}
		}

		if(count_of_queue==0)//说明就绪队列为空
		{
			printf("   ");//记录过程
			time++;
		}
		else
		{
			//寻找此时最先到来的进程
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
				printf("%c  ",Process[pid].id);//记录过程
			}
			Process[pid].finish_time=time;
			Process[pid].remain_servetime=0;
			Process[pid].route_time=Process[pid].finish_time-Process[pid].arrive_time;
			Process[pid].rrt=(float)Process[pid].route_time/Process[pid].serve_time;
		}	
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("               FCFS先来先服务算法模拟\n");
	Print();//调用打印函数输出显示结果；
	fclose(p_fcfs);
}

void rr()
{
	p_rr=fopen("./RR.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                   欢迎进入RR(q=1)调度\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <时间序列>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("时  间：");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("进程名：");
	count_of_queue=0;
	int flag=-1;//标记进程是否执行完毕，-1为未执行完毕，否则为执行完毕
	int i;
	time=0;
	while(time<=allover_time)
	{
		//将在当前time时刻到达的进程加入就绪队列
		for(i=0;i<N;i++)
		{
			if(Process[i].arrive_time==time)
			{
				ready_queue[count_of_queue++]=i;
			}
		}
		if(flag!=-1)//执行完毕
		{
			ready_queue[count_of_queue++]=flag;
		}
		if(count_of_queue==0)//队列无进程
		{
			if(time<=allover_time)
				printf("   ");//记录过程
			time++;
		}
		else//取队首
		{
			if(Process[ready_queue[0]].remain_servetime==Process[ready_queue[0]].serve_time)
				Process[ready_queue[0]].start_time=time;//计算进程的开始时间
			if(Process[ready_queue[0]].remain_servetime<=1)//q=1,进程将要结束，两种情况，一种是本次执行完后变成结束状态，另一种是已经为结束状态
			{
				int t1=time;
				time+=Process[ready_queue[0]].remain_servetime;
				for(;t1<time;t1++)
				{
					char ch=Process[ready_queue[0]].id;
					fprintf(p_rr,"%c\n",ch);
				//	Sleep(600);
					printf("%c  ",Process[ready_queue[0]].id);//记录过程
				}
				Process[ready_queue[0]].finish_time=time;
				Process[ready_queue[0]].route_time=time-Process[ready_queue[0]].arrive_time;
				Process[ready_queue[0]].rrt=(float)Process[ready_queue[0]].route_time/Process[ready_queue[0]].serve_time;
				flag=-1;
			}
			else//进程未结束
			{
				time++;
				char ch=Process[ready_queue[0]].id;
				fprintf(p_rr,"%c\n",ch);
			//	Sleep(600);
				printf("%c  ",Process[ready_queue[0]].id);//记录过程
				Process[ready_queue[0]].remain_servetime--;
				flag=ready_queue[0];
			}
			//此时需要将进程调离出就绪队列
			for(i=0;i<(count_of_queue-1);i++)
			{
				ready_queue[i]=ready_queue[i+1];
			}
			count_of_queue--;
		}
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("               RR轮转(q=1)\n");
	Print();//调用打印函数输出显示结果；
	fclose(p_rr);
}

void SJF()//算法思想和FCFS一样，只是参考的标准不一样
{
	p_sjf=fopen("./SJF.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                   欢迎进入SJF调度\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <时间序列>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("时  间：");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("进程名：");
	//////////////////////////////////
	int shortest_serve_time;//就绪队列中服务时间最短的进程的服务时间
	int pid;//模拟的服务时间最短的进程的进程号
	time=0;
	count_of_queue=0;
	while(time<=allover_time)
	{
		int i;
		count_of_queue=0;
		for(i=0;i<N;i++)//将到达时间在当前的time前的所有进程加入队列中
		{
			if(Process[i].arrive_time<=time && Process[i].remain_servetime!=0)
			//两个保证，一个是到达时间不能超过当前时间，一个是剩余服务时间不能为0
			{
				ready_queue[count_of_queue]=i;
				count_of_queue++;
			}
		}

		if(count_of_queue==0)//说明就绪队列为空
		{
			if(time<=allover_time)
				printf("   ");//记录过程
			time++;
		}
		else
		{
			//寻找此时最先到来的进程
			shortest_serve_time=Process[ready_queue[0]].serve_time;
			pid=ready_queue[0];
			//找出就绪队列中最短服务时间的进程
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
				printf("%c  ",Process[pid].id);//记录过程
			}
			Process[pid].finish_time=time;
			Process[pid].remain_servetime=0;
			Process[pid].route_time=Process[pid].finish_time-Process[pid].arrive_time;
			Process[pid].rrt=(float)Process[pid].route_time/Process[pid].serve_time;
		}	
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("               SJF最短进程优先\n");
	Print();//调用打印函数输出显示结果
	fclose(p_sjf);
}

//最高响应比优先算法
//思想：R=1+(wait_ime/serve_time),其中R为优先权，根据优先权来进行调度进程的执行
//记W_S=wait_ime/serve_time
void HRN()
{
	p_hrn=fopen("./HRN.txt","w+");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("				 欢迎进入HRN调度\n\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("			  <时间序列>\n");
	printf("			  ^^^^^^^^^^\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("时  间：");
	for(int q=0;q<=30;q++)
	{
		if(q<9)
			printf("%d  ",q);
		else
			printf("%d ",q);
	}
	printf("\n");
	printf("进程名：");
	float W_S;////记W_S=max(wait_ime/serve_time)
	int pid;//模拟的W_S的进程的进程号
	time=0;
	count_of_queue=0;
	time=0;
	while(time<=allover_time)
	{
		int i;
		count_of_queue=0;
		for(i=0;i<N;i++)//将到达时间在当前的time前的所有进程加入队列中
		{
			if(Process[i].arrive_time<=time && Process[i].remain_servetime!=0)
			//两个保证，一个是到达时间不能超过当前时间，一个是剩余服务时间不能为0
			{
				ready_queue[count_of_queue]=i;
				count_of_queue++;
			}
		}

		if(count_of_queue==0)//说明就绪队列为空
		{
			if(time<=allover_time)
				printf("   ");//记录过程
			time++;
		}
		else
		{
			W_S=(float)(time-Process[ready_queue[0]].arrive_time)/Process[ready_queue[0]].serve_time;
			pid=ready_queue[0];
			////找出就绪队列中W_S进程
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
				printf("%c  ",Process[pid].id);//记录过程
			}
			Process[pid].finish_time=time;
			Process[pid].remain_servetime=0;
			Process[pid].route_time=Process[pid].finish_time-Process[pid].arrive_time;
			Process[pid].rrt=(float)Process[pid].route_time/Process[pid].serve_time;
		}
	}
	printf("\n-----------------------------------------------------------------------------------------------------\n\n");
	printf("               HRN最高响应比优先\n");
	Print();
	fclose(p_hrn);
}

void main()
{   
	printf("本次运行的进程数目（不大于20个）：");
	cin>>N;
	cout<<"*********************请输入有关进程*************************"<<endl;
	cout<<"请按照如右格式输入进程信息：<进程名> <到达时间> <服务时间>"<<endl<<endl;
	for(int i=0;i<N;i++)
	{
		cout<<"第"<<i+1<<"个进程："<<'\t';
		cin>>Process[i].id>>Process[i].arrive_time>>Process[i].serve_time;
	}
	cout<<"************************************************************"<<endl;
	//进行fcfs算法
	Initialize_Process();	
    fcfs();

	//进行轮转法(q=1)
    Initialize_Process();
	rr();

	//进行SJF最短进程优先
	Initialize_Process();
    SJF();

	//HRN最高响应比优先
	Initialize_Process();
    HRN();
}
