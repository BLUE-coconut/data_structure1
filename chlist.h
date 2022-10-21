#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>


//动态链表（用指针实现）
class LinkList_int
{
public:

	int len;
	typedef int eletype;
	typedef struct LinkNode
	{
		eletype data;
		struct LinkNode* next;
		LinkNode() : data(0), next(NULL) {}
		LinkNode(eletype v) : data(v), next(NULL) {}
		LinkNode(eletype v, struct LinkNode* x) : data(v), next(x) {}
	}LN;

	LN* dummyhead;
	LinkList_int()//构造函数，类对象构建时自动调用 
	//对实例化的对象属性进行初始化 
	{
		dummyhead = new LN();//使用new进行分配 
		len = 0;
	}

	//create&AddAtHead
	bool AddAtHead(eletype x)
	{
		LN* head = new LN(x, dummyhead->next);
		dummyhead->next = head;
		len++;
		printf( "create successfully\n");
		return true;
	}

	//insert element(insert after a)
	bool insert(int a, eletype x)
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("insert erro\n"); 
				return false;
			}
		}
		LN* newp = new LN(x, p->next);
		p->next = newp;
		len++;
		printf("insert successfully\n");
		return true;
	}

	//AddAtTail
	bool Add(eletype x)//AtTail
	{
		LN* p = dummyhead;
		for (int i = 1; i <= len; i++)
		{
			p = p->next;
		}
		LN* newp = new LN(x);
		printf("%d\n", newp->data);
		//printf("%p\n%p",newp,p);
		p->next = newp;
		len++;
		printf("Add successfully\n");
		return true;
	}

	//del element a 
	bool del(int a)
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
			//p is the node before a
		{
			if (p->next == NULL)//a does not exist 
			{
				printf("del erro\n");
				return false;
			}
		}
		LN* pdel = p->next;
		p->next = pdel->next;
		delete pdel;//与new配套使用 
		len--;
		printf("del successfully\n");
		return true;
	}

	//find element(according to index)
	bool findi(int a)//return bool
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("cannot find\n");
				return false;
			}
		}
		printf("find node successfully\n");
		return true;
	}

	//find element(according to data value)
	bool findx(eletype a)//return bool
	{
		LN* p = dummyhead->next;
		while (p != NULL)
		{
			if (p->data == a)return true;
			p = p->next;
		}
		printf("cannot find \n");
		return false;
	}

	//get element data(according to index)
	eletype get(int a)//return data
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("cannot find\n");
				return 0;
			}
		}
		printf("find %d successfully", p->data);
		return p->data;
	}
	//get tail 
	eletype get_tail()
	{
		return get(len);
	}
	//get length
	int get_len()
	{
		return len;
	}
	//clear & destroy
	void clear()//只剩头节点 
	{
		LN* p = dummyhead;
		LN* pcur = p->next;
		while (pcur != NULL)
		{
			LN* pnx = pcur->next;
			delete(pcur);
			pcur = pnx;
		}
		len = 0;
		printf("finish clearing\n");
	}
	void destroy()
	{
		clear();
		free(dummyhead);
		printf("destroy successful\n");
	}

	bool delx(eletype x)
	{
		LN* p = dummyhead;
		LN* pdel = p->next;
		if (pdel == NULL) {
			printf("del erro, not found\n");
			return false;
		}
		while (pdel->next != NULL)//a does not exist 
		{
			LN* px = pdel->next;
			if (px->data == x)
			{
				p->next = px;
				delete pdel;//与new配套使用 
				len--;
				printf("del successfully\n");
				return true;
			}
		}
		printf("del erro\n");
		return false;
	}

	void show(int a, int b)//展示第a个到第b个（包括头尾） 
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("nothing to show\n");
				return;
			}
		}
		for (int i = a; i <= b; i++)
		{
			if (p == NULL)
			{
				printf(" --> only get %d elements to show\n",(i - a ));
			}
			else
			{
				printf("%d ",p->data);
			}
			p = p->next;
		}
		printf("\n");
	}

	void showall()
	{
		LN* p = dummyhead->next;
		if (p == NULL)printf("nothing to show");
		while (p != NULL)
		{
			printf("%d ",p->data);
			p = p->next;
		}
		printf("\n");
	}
};

class LinkList_char
{
public:
	typedef char eletype;
	int len;
	typedef struct LinkNode
	{
		eletype data;
		struct LinkNode* next;
		LinkNode() : data(0), next(NULL) {}
		LinkNode(eletype v) : data(v), next(NULL) {}
		LinkNode(eletype v, struct LinkNode* x) : data(v), next(x) {}
	}LN;

	LN* dummyhead;
	LinkList_char()//构造函数，类对象构建时自动调用 
	//对实例化的对象属性进行初始化 
	{
		dummyhead = new LN();//使用new进行分配 
		len = 0;
	}

	//create&AddAtHead
	bool AddAtHead(eletype x)
	{
		LN* head = new LN(x, dummyhead->next);
		dummyhead->next = head;
		len++;
		printf("create successfully\n");
		return true;
	}

	//insert element(insert after a)
	bool insert(int a, eletype x)
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("insert erro\n");
				return false;
			}
		}
		LN* newp = new LN(x, p->next);
		p->next = newp;
		len++;
		printf("insert successfully\n");
		return true;
	}

	//AddAtTail
	bool Add(eletype x)//AtTail
	{
		LN* p = dummyhead;
		for (int i = 1; i <= len; i++)
		{
			p = p->next;
		}
		LN* newp = new LN(x);
		printf("%d\n", newp->data);
		//printf("%p\n%p",newp,p);
		p->next = newp;
		len++;
		printf("Add successfully\n");
		return true;
	}

	//del element a 
	bool del(int a)
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
			//p is the node before a
		{
			if (p->next == NULL)//a does not exist 
			{
				printf("del erro\n");
				return false;
			}
		}
		LN* pdel = p->next;
		p->next = pdel->next;
		delete pdel;//与new配套使用 
		len--;
		printf("del successfully\n");
		return true;
	}

	//find element(according to index)
	bool findi(int a)//return bool
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("cannot find\n");
				return false;
			}
		}
		printf("find node successfully\n");
		return true;
	}

	//find element(according to data value)
	bool findx(eletype a)//return bool
	{
		LN* p = dummyhead->next;
		while (p != NULL)
		{
			if (p->data == a)return true;
			p = p->next;
		}
		printf("cannot find \n");
		return false;
	}

	//get element data(according to index)
	eletype get(int a)//return data
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("cannot find\n");
				return 0;
			}
		}
		printf("find %d successfully", p->data);
		return p->data;
	}
	//get tail 
	eletype get_tail()
	{
		return get(len);
	}
	//get length
	int get_len()
	{
		return len;
	}
	//clear & destroy
	void clear()//只剩头节点 
	{
		LN* p = dummyhead;
		LN* pcur = p->next;
		while (pcur != NULL)
		{
			LN* pnx = pcur->next;
			delete(pcur);
			pcur = pnx;
		}
		len = 0;
		printf("finish clearing\n");
	}
	void destroy()
	{
		clear();
		free(dummyhead);
		printf("destroy successful\n");
	}
	bool delx(eletype x)
	{
		LN* p = dummyhead;
		LN* pdel = p->next;
		if (pdel == NULL) {
			printf("del erro, not found\n");
			return false;
		}
		while (pdel->next != NULL)//a does not exist 
		{
			LN* px = pdel->next;
			if (px->data == x)
			{
				p->next = px;
				delete pdel;//与new配套使用 
				len--;
				printf("del successfully\n");
				return true;
			}
		}
		printf("del erro\n");
		return false;
	}

	void show(int a, int b)//展示第a个到第b个（包括头尾） 
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("nothing to show\n");
				return;
			}
		}
		for (int i = a; i <= b; i++)
		{
			if (p == NULL)
			{
				printf(" --> only get %d elements to show\n", (i - a));
			}
			else
			{
				printf("%d ", p->data);
			}
			p = p->next;
		}
		printf("\n");
	}

	void showall()
	{
		LN* p = dummyhead->next;
		if (p == NULL)printf("nothing to show\n");
		while (p != NULL)
		{
			printf("%c ", p->data);
			p = p->next;
		}
		printf("\n");
	}
};


//静态链表用数组实现