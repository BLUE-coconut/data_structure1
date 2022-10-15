#include<iostream>
#include<stdio.h>
#include<stdlib.h>
const int MAXSPACE = 200;
//��Ҫ�����к�����

//˳��洢:Ϊ�˽��������(�ռ�δ�������)����ȡѭ���ķ�ʽ�����ÿռ�(ȡmod�ķ�ʽ)
class SqQueue_int
{
private:
	typedef int eletype;
	const int Queue_init_size = 100;
	const int Queue_increment = 10;

	typedef struct MyQueue
	{
		eletype* base;//�洢eletype���ݣ�queue�ĵ�һ���洢�ռ�ָ��
		int front;//������λָ��
		int rear;
		int space;//ʹ�õĴ洢�ռ�����
		int len;//��Ч����
	}MQ;
public:
	MQ* dummyhead = (MQ*)malloc(sizeof(MQ));
	SqQueue_int()
	{
		dummyhead->base = (eletype*)malloc(sizeof(eletype) * Queue_init_size);
		dummyhead->space = Queue_init_size;
		dummyhead->front = 0;
		dummyhead->rear = 0;//rear ��ָ�ڵ�Ϊ��
		dummyhead->len = 0;
	}

	void push(eletype e)//��rear
	{

		if (dummyhead->len == dummyhead->space)//����
		{
			dummyhead->base = (eletype*)realloc(dummyhead->base, sizeof(eletype) * (dummyhead->space + Queue_increment));
			if (!dummyhead->base)exit(0);
			else dummyhead->space += Queue_increment;
			printf("add space\n");
		}
		*(dummyhead->base + dummyhead->rear++ % dummyhead->space) = e;
		dummyhead->len++;
		printf("push %c successfuly\n", e);
	}
	eletype pop_front()
	{
		int mod = dummyhead->space;
		if (dummyhead->len == 0)
		{
			printf("pop front erro,queue is empty\n");
			return 0;
		}
		dummyhead->len--;
		eletype e = *(dummyhead->base + dummyhead->front);
		dummyhead->front = (dummyhead->front + 1) % mod;
		printf("pop front %c successfuly\n", e);
		return e;
	}
	eletype pop_rear()
	{
		int mod = dummyhead->space;
		if (dummyhead->len == 0)
		{
			printf("pop erro,queue is empty\n");
			return 0;
		}
		eletype e = *(dummyhead->base + dummyhead->rear - 1);//ע�⣡dummyhead->base + dummyhead->rear�����һ����ЧԪ�غ�Ŀս��
		dummyhead->len--;
		dummyhead->rear = (dummyhead->rear + dummyhead->space - 1) % mod;
		printf("pop rear %c successfuly\n", e);
		return e;
	}
	eletype front()
	{
		if (dummyhead->rear == dummyhead->front)
		{
			printf("queue is empty,get front failed\n");
			return 0;
		}
		return *(dummyhead->base + dummyhead->front);
	}
	eletype rear()
	{
		if (dummyhead->rear == dummyhead->front)
		{
			printf("queue is empty,get rear failed\n");
			return 0;
		}
		return *(dummyhead->base + dummyhead->rear % dummyhead->space);
	}
	void concat(SqQueue_int que)//��que���е����ݽӵ���ǰ��β
	{
		SqQueue_int q;
		que.copy(&q);
		while (!q.empty())
		{
			eletype e = q.pop_front();
			printf("concating %c\n", e);
			push(e);
		}
	}
	void copy(SqQueue_int* to)
	{
		int mod = dummyhead->space;
		for (int i = 0; i < dummyhead->len; i++)
		{

			eletype e = *(dummyhead->base + (i + dummyhead->front) % mod);
			to->push(e);
		}
	}

	bool empty()
	{
		return dummyhead->front == dummyhead->rear;
	}
	void show_queue()
	{
		printf("showing\nlen=%d\n", dummyhead->len);
		for (int i = 0; i < dummyhead->len; i++)
		{
			printf("%c ", *(dummyhead->base + dummyhead->front + i));
		}
	}
	int length()
	{
		return dummyhead->len;
	}
	void destroy()
	{
		free(dummyhead->base);
		free(dummyhead);
	}
};

class SqQueue_char
{
private:
	typedef char eletype;
	const int Queue_init_size = 100;
	const int Queue_increment = 10;

	typedef struct MyQueue
	{
		eletype* base;//�洢eletype���ݣ�queue�ĵ�һ���洢�ռ�ָ��
		int front;//������λָ��
		int rear;
		int space;//ʹ�õĴ洢�ռ�����
		int len;//��Ч����
	}MQ;
public:
	MQ* dummyhead = (MQ*)malloc(sizeof(MQ));
	SqQueue_char()
	{
		dummyhead->base = (eletype*)malloc(sizeof(eletype) * Queue_init_size);
		dummyhead->space = Queue_init_size;
		dummyhead->front = 0;
		dummyhead->rear = 0;//rear ��ָ�ڵ�Ϊ��
		dummyhead->len = 0;
	}

	void push(eletype e)//��rear
	{

		if (dummyhead->len == dummyhead->space)//����
		{
			dummyhead->base = (eletype*)realloc(dummyhead->base, sizeof(eletype) * (dummyhead->space + Queue_increment));
			if (!dummyhead->base)exit(0);
			else dummyhead->space += Queue_increment;
			printf("add space\n");
		}
		*(dummyhead->base + dummyhead->rear++ % dummyhead->space) = e;
		dummyhead->len++;
		printf("push %c successfuly\n", e);
	}
	eletype pop_front()
	{
		int mod = dummyhead->space;
		if (dummyhead->len == 0)
		{
			printf("pop front erro,queue is empty\n");
			return 0;
		}
		dummyhead->len--;
		eletype e = *(dummyhead->base + dummyhead->front);
		dummyhead->front = (dummyhead->front + 1) % mod;
		printf("pop front %c successfuly\n", e);
		return e;
	}
	eletype pop_rear()
	{
		int mod = dummyhead->space;
		if (dummyhead->len == 0)
		{
			printf("pop erro,queue is empty\n");
			return 0;
		}
		eletype e = *(dummyhead->base + dummyhead->rear - 1);//ע�⣡dummyhead->base + dummyhead->rear�����һ����ЧԪ�غ�Ŀս��
		dummyhead->len--;
		dummyhead->rear = (dummyhead->rear + dummyhead->space - 1) % mod;
		printf("pop rear %c successfuly\n", e);
		return e;
	}
	eletype front()
	{
		if (dummyhead->rear == dummyhead->front)
		{
			printf("queue is empty,get front failed\n");
			return 0;
		}
		return *(dummyhead->base + dummyhead->front);
	}
	eletype rear()
	{
		if (dummyhead->rear == dummyhead->front)
		{
			printf("queue is empty,get rear failed\n");
			return 0;
		}
		return *(dummyhead->base + dummyhead->rear % dummyhead->space);
	}
	void concat(SqQueue_char que)//��que���е����ݽӵ���ǰ��β
	{
		SqQueue_char q;
		que.copy(&q);
		while (!q.empty())
		{
			eletype e = q.pop_front();
			printf("concating %c\n", e);
			push(e);
		}
	}
	void copy(SqQueue_char* to)
	{
		int mod = dummyhead->space;
		for (int i = 0; i < dummyhead->len; i++)
		{

			eletype e = *(dummyhead->base + (i + dummyhead->front) % mod);
			to->push(e);
		}
	}

	bool empty()
	{
		return dummyhead->front == dummyhead->rear;
	}
	void show_queue()
	{
		printf("showing\nlen=%d\n", dummyhead->len);
		for (int i = 0; i < dummyhead->len; i++)
		{
			printf("%c ", *(dummyhead->base + dummyhead->front + i));
		}
	}
	int length()
	{
		return dummyhead->len;
	}
	void destroy()
	{
		free(dummyhead->base);
		free(dummyhead);
	}
};


//ѭ�����У�˳��洢��,Ϊ�˽�������磬��ȡѭ���ķ�ʽ�����ÿռ�(ȡmod�ķ�ʽ)
/*class CircularQueue
{
private :
	typedef int eletype;
	struct cirque
	{
		eletype* first;
	}*dummyhead;
	int TotalSpace=MAXSPACE;
	int UsedSpace=0;
public:
	//����emptyʱ��front��end����Ϊ��
	int front = 0;
	int end = front;
	int size()//��Ч���г���
	{
		return UsedSpace;
	}
	bool empty()
	{
		return UsedSpace == 0;
	}
	bool full()
	{
		return UsedSpace == TotalSpace;
	}
	CircularQueue()
	{
		eletype* head = (eletype*)malloc(sizeof(eletype) * TotalSpace);
		dummyhead->first = head;
	}
	eletype leftpop()
	{
		if (empty())
		{
			printf("leftpop erro,queue is empty\n");
			return NULL;
		}
		eletype p = *(dummyhead->first+front);
		front = (front+1)%TotalSpace;
		UsedSpace--;
		return p;
	}
	eletype rightpop()
	{
		if (empty())
		{
			printf("rightpop erro,queue is empty\n");
			return NULL;
		}
		eletype p = *(dummyhead->first + end);
		end = (end - 1 + TotalSpace) % TotalSpace;
		UsedSpace--;
		return p;
	}
	void leftpush(eletype p)
	{
		if (full())
		{
			printf("leftpush erro,queue is full\n");
			return ;
		}
		if (empty())//˫�˶��е�empty�е����⣬front��end��ͬһ���Ҿ�Ϊ��
		{
			*(dummyhead->first + front) = p;
		}
		else
		{
			front = (front - 1 + TotalSpace) % TotalSpace;//���Ƶ���λ�ã���д������
			*(dummyhead->first + front) = p;
		}
		UsedSpace++;
	}
	void rightpush(eletype p)
	{
		if (full())
		{
			printf("rightpush erro,queue is full\n");
			return ;
		}
		if (empty())//˫�˶��е�empty�е����⣬front��end��ͬһ���Ҿ�Ϊ��
		{
			*(dummyhead->first + end) = p;
		}
		else
		{
			end = (end + 1) % TotalSpace;//���Ƶ���λ�ã���д������
			*(dummyhead->first + end) = p;
		}
		UsedSpace++;
	}
	eletype front()
	{
		if (empty())
		{
			printf("get front erro,queue is empty\n");
			return NULL;
		}
		return *(dummyhead->first + front);
	}
	eletype end()
	{
		if (empty())
		{
			printf("get end erro,queue is empty\n");
			return NULL;
		}
		return *(dummyhead->first + end);
	}

	void showall()
	{
		int p = front;
		for (int i = 1; i <= size(); i++)
		{
			if (p == end)
			{
				printf("show erro\n");
				return;
			}
			printf("%d ", *(dummyhead->first + p));
			p = (p + 1) % TotalSpace;
		}
		printf("\n");
	}
};*/
