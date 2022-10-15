#include<iostream>
#include<stdio.h>
#include<stdlib.h>

//˳��ջ

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
		int size;//��ʾռ�ݿռ�����������ջ�������� 
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
		if (dummyhead->top == dummyhead->base)//��ջΪ�� 
		{
			printf("GetTop erro\n");
			return 0;
		}
		return *(dummyhead->top - 1);
	}

	void push(eletype e)
	{
		if (dummyhead->top - dummyhead->base >= dummyhead->size)//����ָ�����������Ԫ�����
		{
			dummyhead->base = (eletype*)realloc(dummyhead->base, (dummyhead->size + Stack_increment) * sizeof(SqStack_int));
			if (!dummyhead->base)exit(0);
			dummyhead->top = dummyhead->base + Stack_increment;
			//�ǳ���Ҫ����Ϊǰ���S.top=S.base+Stack_incrementʵ���ϳ�����init�Ŀռ�
			//��֪����ʲô��ַ��Ҳ�������ַ������ջ������
			dummyhead->size += Stack_increment;
		}
		printf("push successfully\n");
		*dummyhead->top++ = e;
	}

	void pop_get(eletype& e)
	{
		if (dummyhead->top == dummyhead->base)//��ջΪ�� 
		{
			printf("pop erro\n");
			return;
		}
		e = *--dummyhead->top;//ע��topָ����ָ�����ǿյģ�ȡ����Ӧ���ǣ�top-1�������ݣ�����top����top-1������ʾtop-1��ջ 
	}
	eletype pop()
	{
		if (dummyhead->top == dummyhead->base)//��ջΪ�� 
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
		int size;//��ʾռ�ݿռ�����������ջ�������� 
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
		if (dummyhead->top == dummyhead->base)//��ջΪ�� 
		{
			printf("GetTop erro\n");
			return 0;
		}
		return *(dummyhead->top - 1);
	}

	void push(eletype e)
	{
		if (dummyhead->top - dummyhead->base >= dummyhead->size)//����ָ�����������Ԫ�����
		{
			dummyhead->base = (eletype*)realloc(dummyhead->base, (dummyhead->size + Stack_increment) * sizeof(SqStack_char));
			if (!dummyhead->base)exit(0);
			dummyhead->top = dummyhead->base + Stack_increment;
			//�ǳ���Ҫ����Ϊǰ���S.top=S.base+Stack_incrementʵ���ϳ�����init�Ŀռ�
			//��֪����ʲô��ַ��Ҳ�������ַ������ջ������
			dummyhead->size += Stack_increment;
		}
		printf("push successfully\n");
		*dummyhead->top++ = e;
	}

	void pop_get(eletype& e)
	{
		if (dummyhead->top == dummyhead->base)//��ջΪ�� 
		{
			printf("pop erro\n");
			return;
		}
		e = *--dummyhead->top;//ע��topָ����ָ�����ǿյģ�ȡ����Ӧ���ǣ�top-1�������ݣ�����top����top-1������ʾtop-1��ջ 
	}
	eletype pop()
	{
		if (dummyhead->top == dummyhead->base)//��ջΪ�� 
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