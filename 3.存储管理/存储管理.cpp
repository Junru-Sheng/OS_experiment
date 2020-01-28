#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define N 50

int page_num;//�ڴ�������ҳ����Ŀm
int len;//ҳ���������г���
int ready_queue[N];//���ҳ���������еĶ���a
int mem_queue[N];//����������е����еĶ���b
int flag[N];//ȱҳ״̬��ǣ�0Ϊ��ȱҳ��1Ϊȱҳ
int miss_num;//ȱҳ��Ŀno
float miss_ratio;//ȱҳ��qyl
int f,r;//���е��ף�β

int checkup(int i)//����ڴ����Ƿ�������е�ҳ�ţ�LRU��FIFO����ʹ��
{
	for(int j=f;j<=r;j++)
	{
		if(mem_queue[j]==ready_queue[i])				
			return 1;
	}
	return 0;
}

void Unfull_page(int i)//����ҳ��δ��ʱ��ҳ����ȣ�LRU��FIFO����ʹ��
{
	int j;
	int k;
	if(checkup(i)==0)//ȱҳʱ������ҳ��ӽ�ȥ����ȱҳʱ���ò���
		{	
			mem_queue[++r]=ready_queue[i];
			flag[i]=1;
		}
	printf("����ҳ��:%d",ready_queue[i]);
	printf("\t");
	for(j=f;j<=r;j++)//�����εĹ���
	{
		Sleep(400);//////////////////////////////////
		printf("%d ",mem_queue[j]);
	}
	k=page_num-(r-f+1);
	switch(k)
	{
	    case 0:
		{
			printf(" \t��̭ҳ:None\tȱҳ��%d\n",flag[i]);
			break;
		}
		case 1:
		{
			printf("   \t��̭ҳ:None\tȱҳ��%d\n",flag[i]);
			break;
		}
		case 2:
		{
			printf("     \t��̭ҳ:None\tȱҳ��%d\n",flag[i]);
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
	printf("����ҳ��:%d",ready_queue[0]);///////////
	printf("\t%d",mem_queue[0]);
	for(i=0;i<page_num-2;i++)
	{
		printf("\t");

	}
	printf("��̭ҳ:None\tȱҳ��%d\n",flag[0]);
	for(i=1;i<len;i++)
	{
		flag[i]=0;
		//˵������ҳ��δ��
		if((r-f+1)<page_num)
		{
			Unfull_page(i);
		}
		else//˵������ҳ������
		{
			if(checkup(i)==0)//ȱҳ
			{
				flag[i]=1;
				mem_queue[++r]=ready_queue[i];
				f++;
				printf("����ҳ��:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//�����εĹ���
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t��̭ҳ:%d\tȱҳ��%d\n",mem_queue[f-1],flag[i]);
			}
			else//��ȱҳ
			{
				printf("����ҳ��:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//�����εĹ���
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t��̭ҳ:None\tȱҳ��%d\n",flag[i]);
			}
		}
	}
	//����ȱҳ��Ŀ
	for(i=0;i<len;i++)
	{
		if(flag[i]==1)
			miss_num++;
	}
	miss_ratio=(float)miss_num/len;
}

int search_LRU(int i)//�������ʹ�õ�m��ҳ�����������ʹ�õ�ҳ��
{
	int j,t,cnt=0;
	int buff[N];//��ֵΪ1��ʾ�����ʹ��
	for(j=0;j<N;j++)//��0
	{
		buff[j]=0;
	}
	for(t=i-1;t>=0;t--)
	{
		if(buff[ready_queue[t]]==0)
		{
			buff[ready_queue[t]]=1;
			cnt++;
			if(cnt==page_num)//�ﵽ������ҳ����Ŀ
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

//ģ��LRU�㷨
void LRU()
{
	int i,j;
	miss_num=0;
	miss_ratio=0.00;
	f=r=0;
	mem_queue[0]=ready_queue[0];
	flag[0]=1;
	printf("����ҳ��:%d",ready_queue[0]);
	printf("\t%d",mem_queue[0]);
	for(i=0;i<page_num-2;i++)
	{
		printf("\t");

	}
	printf("��̭ҳ:None\tȱҳ��%d\n",flag[0]);
	//�û�ִ��
	for(i=1;i<len;i++)
	{
		flag[i]=0;
		//˵������ҳ��δ��������ͬFIFOһ��
		if((r-f+1)<page_num)
		{
				Unfull_page(i);
		}
		else
		//˵������ҳ��������������FIFO��ͬ
		{
			if(checkup(i)==0)//ȱҳ
			{
				flag[i]=1;
				//�滻
				int tmp=mem_queue[search_LRU(i)];//����Ѱ��LRU������
				mem_queue[search_LRU(i)]=ready_queue[i];
				printf("����ҳ��:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//�����εĹ���
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t��̭ҳ:%d\tȱҳ��%d\n",tmp,flag[i]);
			}
			else//��ȱҳ
			{
				printf("����ҳ��:%d",ready_queue[i]);
				printf("\t");
				for(j=f;j<=r;j++)//�����εĹ���
				{
					Sleep(400);//////////////////////////////////
					printf("%d ",mem_queue[j]);
				}
				printf("\t��̭ҳ:None\tȱҳ��%d\n",flag[i]);
			}
		}
	}
	//����ȱҳ��Ŀ
	for(i=0;i<len;i++)
	{
		if(flag[i]==1)
			miss_num++;
	}
	miss_ratio=(float)miss_num/len;
}

void main()
{
	printf("           ��ӭ����ҳ���û��洢����\n");
	printf("******************************************************\n");
	printf("ҳ���������г��ȣ�");
	scanf("%d",&len);
	printf("����ҳ����Ŀ��");
	scanf("%d",&page_num);
	printf("\n������ҳ���������У�\t");
	for(int i=0;i<len;i++)
	{
		scanf("%d",&ready_queue[i]);
	}
	printf("******************************************************\n");
	printf("                    *FIFO�㷨*\n");
	printf("                    **********\n\n");
	FIFO();
	printf("\n\tȱҳ������%d\tȱҳ�ʣ�%.2f\n",miss_num,miss_ratio);
	printf("******************************************************\n");
	printf("                    *LRU�㷨*\n");
	printf("                    *********\n\n");
	LRU();
	printf("\n\tȱҳ������%d\tȱҳ�ʣ�%.2f\n",miss_num,miss_ratio);
}