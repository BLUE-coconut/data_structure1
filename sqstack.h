#include<iostream>
#include<stdio.h>
#include<stdlib.h>

//顺序栈

class SqStack_int
{
private:
	typedef int eletype;
	const int Stack_init_size = 100;
	const int Stack_increment = 10;

	typedef struct stackNode
	{
		eletype *top;
		eletype *base;
		int size;//表示占据空间数，而不是栈中数据数 
	}SN;

public:

	SN *dummyhead = (SN *)malloc(sizeof(SN));
	SqStack_int()
	{
		dummyhead->base = (eletype*)malloc(Stack_init_size * sizeof(eletype));
		if (!dummyhead->base)exit(0);
		dummyhead->top = dummyhead->base;
		dummyhead->size = Stack_init_size;
		printf("create ok\n");
	}

	eletype GetTop()
	{
		if (dummyhead->top == dummyhead->base)//即栈为空 
		{
			printf("GetTop erro\n");
			return 0;
		}
		return *(dummyhead->top - 1);
	}

	void push(eletype e)
	{
		if (dummyhead->top - dummyhead->base >= dummyhead->size)//两个指针相减而不是元素相减
		{
			dummyhead->base = (eletype*)realloc(dummyhead->base, (dummyhead->size + Stack_increment) * sizeof(SqStack_int));
			if (!dummyhead->base)exit(0);
			dummyhead->top = dummyhead->base + Stack_increment;
			//非常重要，因为前面的S.top=S.base+Stack_increment实际上超出了init的空间
			//不知道是什么地址，也就是其地址不是与栈连续的
			dummyhead->size += Stack_increment;
		}
		printf("push successfully\n");
		*dummyhead->top++ = e;
	}

	void pop_get(eletype& e)
	{
		if (dummyhead->top == dummyhead->base)//即栈为空 
		{
			printf("pop erro\n");
			return;
		}
		e = *--dummyhead->top;//注意top指针所指本身是空的，取出的应该是（top-1）的数据，并把top置于top-1出，表示top-1出栈 
	}
	eletype pop()
	{
		if (dummyhead->top == dummyhead->base)//即栈为空 
		{
			printf("pop erro\n");
			return ' ';
		}
		return *--dummyhead->top;
	}

	void destroy()
	{
		free(dummyhead->base);
		free(dummyhead);
	}
	void clear()
	{
		dummyhead->top = dummyhead->base;
	}
	bool empty()
	{
		return dummyhead->top == dummyhead->base;
	}
	bool finish()
	{
		return dummyhead->top == dummyhead->base+1;
	}
};


class SqStack_char
{
private:
	typedef char eletype;
	const int Stack_init_size = 100;
	const int Stack_increment = 10;

	typedef struct stackNode
	{
		eletype* top;
		eletype* base;
		int size;//表示占据空间数，而不是栈中数据数 
	}SN;

public:

	SN* dummyhead = (SN*)malloc(sizeof(SN));
	SqStack_char()
	{
		dummyhead->base = (eletype*)malloc(Stack_init_size * sizeof(eletype));
		if (!dummyhead->base)exit(0);
		dummyhead->top = dummyhead->base;
		dummyhead->size = Stack_init_size;
		printf("create ok\n");
	}

	eletype GetTop()
	{
		if (dummyhead->top == dummyhead->base)//即栈为空 
		{
			printf("GetTop erro\n");
			return 0;
		}
		return *(dummyhead->top - 1);
	}

	void push(eletype e)
	{
		if (dummyhead->top - dummyhead->base >= dummyhead->size)//两个指针相减而不是元素相减
		{
			dummyhead->base = (eletype*)realloc(dummyhead->base, (dummyhead->size + Stack_increment) * sizeof(SqStack_char));
			if (!dummyhead->base)exit(0);
			dummyhead->top = dummyhead->base + Stack_increment;
			//非常重要，因为前面的S.top=S.base+Stack_increment实际上超出了init的空间
			//不知道是什么地址，也就是其地址不是与栈连续的
			dummyhead->size += Stack_increment;
		}
		printf("push successfully\n");
		*dummyhead->top++ = e;
	}

	void pop_get(eletype& e)
	{
		if (dummyhead->top == dummyhead->base)//即栈为空 
		{
			printf("pop erro\n");
			return;
		}
		e = *--dummyhead->top;//注意top指针所指本身是空的，取出的应该是（top-1）的数据，并把top置于top-1出，表示top-1出栈 
	}
	eletype pop()
	{
		if (dummyhead->top == dummyhead->base)//即栈为空 
		{
			printf("pop erro\n");
			return ' ';
		}
		return *--dummyhead->top;
	}

	void destroy()
	{
		free(dummyhead->base);
		free(dummyhead);
	}
	void clear()
	{
		dummyhead->top = dummyhead->base;
		printf("clear successfully\n");
	}
	bool empty()
	{
		return dummyhead->top == dummyhead->base;
	}

};