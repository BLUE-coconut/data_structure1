#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//循环链表

class Circular_chain_List
{
private:
	const int INITSPACE = 10;
	typedef int element;
	typedef struct StackNode
	{
		element data;
		StackNode* next;
	}SN;

public:
	SN* dummyhead = (SN*)malloc(sizeof(SN));
	Circular_chain_List()
	{
		SN* first = (SN*)malloc(sizeof(SN));
		dummyhead->data = 0;
		dummyhead->next = first;
		first->next = first;
	}
	void CreateBasicCircle()
	{
		SN* pre = dummyhead->next;
		for (int i = 1; i <= INITSPACE; i++)
		{
			SN* newnode = (SN*)malloc(sizeof(SN));
			newnode->next = pre->next;
			newnode->data = i;
			pre->next = newnode;
			pre = newnode;
		}
	}
	void showall()
	{
		SN* p = dummyhead->next;
		while (p->next != dummyhead->next)
		{
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");
	}
	void TurnAround()//就地逆置
	{
		SN* pre = dummyhead->next;
		SN* nex = dummyhead->next->next;
		while (1)
		{
			SN* nexnex = nex->next;
			if (nex == dummyhead->next)
			{
				nex->next = pre;
				break;
			}
			nex->next = pre;
			pre = nex;
			nex = nexnex;
		}

	}
	void destroy()
	{
		SN* p = dummyhead->next;
		for(int i=1;i<=INITSPACE;i++)
		{
			SN* cur = p;
			p = p->next;
			free(cur);
		}
	}
};