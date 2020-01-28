#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define N 50

int page_num;//内存中物理页面数目m
int len;//页面引用序列长度
int ready_queue[N];//存放页面引用序列的队列a
int mem_queue[N];//存放在主存中的序列的队列b
int flag[N];//缺页状态标记，0为不缺页，1为缺页
int miss_num;//缺页数目no
float miss_ratio;//缺页率qyl
int f,r;//队列的首，尾

int checkup(int i)//检查内存中是否有这队列的页号，LRU和FIFO共享使用
{
	for(int j=f;j<=r;j++)
	{
		if(mem_queue[j]==ready_queue[i])				
			return 1;
	}
	return 0;
}

void Unfull_page(int i)//物理页面未满时的页面调度，LRU和FIFO共享使用
{
	int j;
	int k;
	if(checkup(i)==0)//缺页时，将新页面加进去，不缺页时不用操作
		{	
			mem_queue[++r]=ready_queue[i];
			flag[i]=1;
		}
	printf("调入页号:%d",ready_queue[i]);
	printf("\t");
	for(j=f;j<=r;j++)//输出这次的过程
	{
		Sleep(400);//////////////////////////////////
		printf("%d ",mem_queue[j]);
	}
	k=page_num-(r-f+1);
	switch(k)
	{
	    case 0:
		{
			printf(" \t淘汰页:None\t缺页：%d\n",flag[i]);
			break;
		}
		case 1:
		{
			printf("   \t淘汰页:None\t缺页：%d\n",flag[i]);
			break;
		}
		case 2:
		{
			printf("     \t淘汰页:None\t缺页：%d\n",flag[i]);
			break;			
		}
	}
}

void FIFO()
{
	int i,j;
	miss_num=0;
	miss_ratio=0.00;
	f=r=0;
	mem_queue[0]=ready_queue[0];
	flag[0]=1;
	printf("调入页号:%d",ready_queue[0]);///////////
	printf("\t%d",mem_queue[0]);
	for(i=0;i<page_num-2;i++)
	{
		printf("\t");

	}
	printf("淘汰页:None\t缺页：%d\n",flag[0]);
	for(i=1;i<len;i++)
	{
		flag[i]=0;
		//说明物理页面未满
		if((r-f+1)<page_num)
		{
			Unfull_page(i);
		}
		else//说明物理页面已满
		{
			if(checkup(i)==0)//缺页
			{
				flag[i]=1;
				mem_queue[++r]=ready_queue[i];
				f++;
				printf("调入页号:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//输出这次的过程
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t淘汰页:%d\t缺页：%d\n",mem_queue[f-1],flag[i]);
			}
			else//不缺页
			{
				printf("调入页号:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//输出这次的过程
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t淘汰页:None\t缺页：%d\n",flag[i]);
			}
		}
	}
	//计算缺页数目
	for(i=0;i<len;i++)
	{
		if(flag[i]==1)
			miss_num++;
	}
	miss_ratio=(float)miss_num/len;
}

int search_LRU(int i)//查找最近使用的m个页面中最近最少使用的页号
{
	int j,t,cnt=0;
	int buff[N];//数值为1表示最近有使用
	for(j=0;j<N;j++)//清0
	{
		buff[j]=0;
	}
	for(t=i-1;t>=0;t--)
	{
		if(buff[ready_queue[t]]==0)
		{
			buff[ready_queue[t]]=1;
			cnt++;
			if(cnt==page_num)//达到了物理页面数目
			{
				for(j=f;j<=r;j++)
				{
					if(mem_queue[j]==ready_queue[t])
					{
						return j;
					}
				}
			}
		}
	}
	return 0;
}

//模拟LRU算法
void LRU()
{
	int i,j;
	miss_num=0;
	miss_ratio=0.00;
	f=r=0;
	mem_queue[0]=ready_queue[0];
	flag[0]=1;
	printf("调入页号:%d",ready_queue[0]);
	printf("\t%d",mem_queue[0]);
	for(i=0;i<page_num-2;i++)
	{
		printf("\t");

	}
	printf("淘汰页:None\t缺页：%d\n",flag[0]);
	//置换执行
	for(i=1;i<len;i++)
	{
		flag[i]=0;
		//说明物理页面未满，操作同FIFO一样
		if((r-f+1)<page_num)
		{
				Unfull_page(i);
		}
		else
		//说明物理页面已满，操作与FIFO不同
		{
			if(checkup(i)==0)//缺页
			{
				flag[i]=1;
				//替换
				int tmp=mem_queue[search_LRU(i)];//调用寻找LRU的索引
				mem_queue[search_LRU(i)]=ready_queue[i];
				printf("调入页号:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//输出这次的过程
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t淘汰页:%d\t缺页：%d\n",tmp,flag[i]);
			}
			else//不缺页
			{
				printf("调入页号:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//输出这次的过程
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t淘汰页:None\t缺页：%d\n",flag[i]);
			}
		}
	}
	//计算缺页数目
	for(i=0;i<len;i++)
	{
		if(flag[i]==1)
			miss_num++;
	}
	miss_ratio=(float)miss_num/len;
}

void main()
{
	printf("           欢迎来到页面置换存储管理\n");
	printf("******************************************************\n");
	printf("页面引用序列长度：");
	scanf("%d",&len);
	printf("物理页面数目：");
	scanf("%d",&page_num);
	printf("\n请输入页面引用序列：\t");
	for(int i=0;i<len;i++)
	{
		scanf("%d",&ready_queue[i]);
	}
	printf("******************************************************\n");
	printf("                    *FIFO算法*\n");
	printf("                    **********\n\n");
	FIFO();
	printf("\n\t缺页次数：%d\t缺页率：%.2f\n",miss_num,miss_ratio);
	printf("******************************************************\n");
	printf("                    *LRU算法*\n");
	printf("                    *********\n\n");
	LRU();
	printf("\n\t缺页次数：%d\t缺页率：%.2f\n",miss_num,miss_ratio);
}