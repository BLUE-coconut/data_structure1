#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
const int MAXSPACE = 200;
//不要搞混队列和链表

//顺序存储:为了解决假上溢(空间未充分利用)，采取循环的方式来利用空间(取mod的方式)
class SqQueue_int
{
private:
	typedef int eletype;
	const int Queue_init_size = 100;
	const int Queue_increment = 10;

	typedef struct MyQueue
	{
		eletype* base;//存储eletype数据，queue的第一个存储空间指针
		int front;//用来定位指针
		int rear;
		int space;//使用的存储空间总数
		int len;//有效长度
	}MQ;
public:
	MQ* dummyhead = (MQ*)malloc(sizeof(MQ));
	SqQueue_int()
	{
		dummyhead->base = (eletype*)malloc(sizeof(eletype) * Queue_init_size);
		dummyhead->space = Queue_init_size;
		dummyhead->front = 0;
		dummyhead->rear = 0;//rear 所指节点为空
		dummyhead->len = 0;
	}

	void push(eletype e)//在rear
	{

		if (dummyhead->len == dummyhead->space)//满了
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
		eletype e = *(dummyhead->base + dummyhead->rear - 1);//注意！dummyhead->base + dummyhead->rear是最后一个有效元素后的空结点
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
	void concat(SqQueue_int que)//把que队列的内容接到当前队尾
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
		eletype* base;//存储eletype数据，queue的第一个存储空间指针
		int front;//用来定位指针
		int rear;
		int space;//使用的存储空间总数
		int len;//有效长度
	}MQ;
public:
	MQ* dummyhead = (MQ*)malloc(sizeof(MQ));
	SqQueue_char()
	{
		dummyhead->base = (eletype*)malloc(sizeof(eletype) * Queue_init_size);
		dummyhead->space = Queue_init_size;
		dummyhead->front = 0;
		dummyhead->rear = 0;//rear 所指节点为空
		dummyhead->len = 0;
	}

	void push(eletype e)//在rear
	{

		if (dummyhead->len == dummyhead->space)//满了
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
		eletype e = *(dummyhead->base + dummyhead->rear - 1);//注意！dummyhead->base + dummyhead->rear是最后一个有效元素后的空结点
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
	void concat(SqQueue_char que)//把que队列的内容接到当前队尾
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


