#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define N 30
int len;//磁盘访问序列长度
int begin;//读写头起始位置
int disk_queue[N];//磁盘访问序列的队列
int flag[N];//标记该磁道是否被访问，1表示被访问，0表示未被访问
int sum;//移臂总量

FILE* P_SSTF,* P_SCAN;
////////////
void SSTF()
{
//	FILE *stream;
    P_SSTF=fopen("C:\\Users\\君如\\Desktop\\操作系统实验\\4.磁盘调度算法\\SSTF.txt","w+");
	int i,tmp,min_distance;
	int begin_SSTF=begin;
	fprintf(P_SSTF,"%d\n",begin_SSTF);
	sum=0;
	for(i=0;i<len;i++)
	{
		min_distance=INT_MAX;//定义最小距离并设定初始值
		for(int j=0;j<len;j++)//寻找最小距离
		{
			if(min_distance>abs(disk_queue[j]-begin_SSTF) && flag[j]==0)
			{
				min_distance=abs(disk_queue[j]-begin_SSTF);
				tmp=j;
			}
		}
		flag[tmp]=1;//tmp为寻找的索引号
		sum+=min_distance;
		fprintf(P_SSTF,"%d\n",disk_queue[tmp]);
		printf("\t\t%d\t   %d\n",disk_queue[tmp],min_distance);
		begin_SSTF=disk_queue[tmp];//调整磁道开始位置
	}
	fclose(P_SSTF);
}

////////////
void SCAN()
{
	P_SCAN=fopen("C:\\Users\\君如\\Desktop\\操作系统实验\\4.磁盘调度算法\\SCAN.txt","w+");
	int i,tmp,min_distance;
	int begin_SCAN=begin;
	fprintf(P_SCAN,"%d\n",begin_SCAN);
//	int l_r;//判断方向，为1表示向右边进行，为0表示向左边方向进行
	int len_l,len_r;//处在磁盘开始位置的左右边的磁道数目
	sum=0;
	len_r=len_l=0;
	//计算处在磁盘开始位置的左右边的磁道数目
	for(i=0;i<len;i++)
	{
		if(begin_SCAN<=disk_queue[i])
			len_r++;
	}
	len_l=len-len_r;
	for(i=0;i<len_r;i++)
	{
		min_distance=INT_MAX;//定义最小距离并设定初始值
		for(int j=0;j<len;j++)//寻找最小距离
		{
			if((disk_queue[j]-begin_SCAN)>=0 && min_distance>(disk_queue[j]-begin_SCAN) && flag[j]==0)
			{
				min_distance=disk_queue[j]-begin_SCAN;
				tmp=j;
			}
		}
		flag[tmp]=1;
		sum+=min_distance;
		fprintf(P_SCAN,"%d\n",disk_queue[tmp]);///
		printf("\t\t%d\t   %d\n",disk_queue[tmp],min_distance);
		begin_SCAN=disk_queue[tmp];//调整磁道开始位置
	}
	for(i=0;i<len_l;i++)
	{
		min_distance=INT_MAX;//定义最小距离并设定初始值
		for(int j=0;j<len;j++)//寻找最小距离
		{
			if((disk_queue[j]-begin_SCAN)<0 && min_distance>(begin_SCAN-disk_queue[j]) && flag[j]==0)
			{
				min_distance=begin_SCAN-disk_queue[j];
				tmp=j;
			}
		}
		flag[tmp]=1;
		sum+=min_distance;
		fprintf(P_SCAN,"%d\n",disk_queue[tmp]);//
		printf("\t\t%d\t   %d\n",disk_queue[tmp],min_distance);
		begin_SCAN=disk_queue[tmp];//调整磁道开始位置
	}
}


void main()
{
	printf("\n           欢迎来到磁盘移臂调度\n");
	printf("******************************************************\n");
	printf("磁盘访问序列长度：");
	scanf("%d",&len);
	printf("读写头起始位置：");
	scanf("%d",&begin);
	printf("请输入磁盘访问序列：");
	for(int i=0;i<len;i++)
	{
		scanf("%d",&disk_queue[i]);
		flag[i]=0;
	}
	printf("******************************************************\n");
	printf("                    *SSTF算法*\n");
	printf("                    **********\n\n");
	printf("\t访问的次磁道号\t移动的磁道数\n");
	SSTF();
	printf("\n\t\tSSTF移臂总量：%d\n",sum);
	printf("******************************************************\n");
	printf("                    *SCAN算法*\n");
	printf("                    *********\n\n");
	printf("\t访问的次磁道号\t移动的磁道数\n");
	for(i=0;i<len;i++)
	{
		flag[i]=0;
	}
	SCAN();
	printf("\n\t\tSCAN移臂总量：%d\n",sum);
}