#include<iostream>
#include<stdio.h>
#include<stdlib.h>

class ChStack_int
{
private:
	typedef int eletype;
	typedef struct stackNode
	{
		eletype data;
		stackNode* next;
	}SN;
	int size = 0;//记录栈中数据数量

	SN* GetTopPre()//用于pop
	{
		//先要确保不空
		if (empty())
		{
			printf("pop erro\n");
			return NULL;
		}
		SN* pre = dummyhead;
		SN* p = pre->next;
		while (p->next)
		{
			pre = p;
			p = pre->next;
		}
		return pre;
	}
	SN* GetTop()//用于push
	{
		return top;
	}

public:
	
	SN *dummyhead = (SN*)malloc(sizeof(SN));//头节点为空
	
	ChStack_int()
	{
		dummyhead->next = NULL;
	}
	SN* top = dummyhead;
	eletype Top()
	{
		if (empty())
		{
			printf("top erro ,stack empty");
			return NULL;
		}
		return top->data;
	}
	eletype pop()
	{
		SN* num = (SN*)malloc(sizeof(SN));
		if (empty())
		{
			printf("pop erro\n");
			return NULL;
		}
		SN* prenode = GetTopPre();
		SN* popnode = top;
		num->data = popnode->data;

		top = prenode;
		prenode->next = NULL;
		free(popnode);
		size--;

		printf("pop successful\n");
		return num->data;
	}
	void push(eletype p)
	{
		SN* newnode = (SN*)malloc(sizeof(SN));
		if (!newnode)
		{
			printf("push erro\n");
			return;
		}
		SN* top = GetTop();
		newnode->data = p;
		newnode->next = NULL;
		top->next = newnode;
		top = top->next;
		size++;
		printf("push successful\n");
	}
	void clear()
	{
		while (!empty())
		{
			pop();
		}
		size = 0;
		printf("clear successful\n");
	}
	void destroy()
	{
		clear();
		free(dummyhead);
		printf("destroy successful\n");
	}
	bool empty()
	{
		return dummyhead== top;
	}
	int getsize()
	{
		return size;
	}
};