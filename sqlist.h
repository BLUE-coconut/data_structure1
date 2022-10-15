#include<iostream>
#include<stdio.h>
#include<stdlib.h>

//��̬˳�����̬����ռ䣩
class SqList_char
{
private:
	typedef char eletype;
	const int INIT_SPACE = 100;
	const int INCREMENT = 10;
	struct List
	{
		eletype* head;
		int len;//��ǰ˳�����
		int size;//��ǰ˳���ʹ�ÿռ�
	};
public:
	List* dummyhead = (List*)malloc(sizeof(List));

	SqList_char()
	{
		dummyhead->head = (eletype*)malloc(sizeof(eletype) * INIT_SPACE);
		dummyhead->len = 0;
		dummyhead->size = INIT_SPACE;
	}

	void add(eletype a)
	{
		if (dummyhead->len >= dummyhead->size)
		{
			dummyhead->head = (eletype*)realloc(dummyhead->head, sizeof(eletype)*(dummyhead->size+INCREMENT));
			dummyhead->size += INCREMENT;
		}
		
		*(dummyhead->head + dummyhead->len) = a;
		dummyhead->len++;
		printf("add successfully\n");
	}

	void insert(eletype a, int idex)
	{
		if (dummyhead->len >= dummyhead->size)
		{
			dummyhead->head = (eletype*)realloc(dummyhead->head, sizeof(eletype) * (dummyhead->size + INCREMENT));
			dummyhead->size += INCREMENT;
		}
		for (int i = idex; i <= dummyhead->len + 1; i++)
		{
			eletype temp = *(dummyhead->head + i);
			*(dummyhead->head + i) = a;
			a = temp;
		}
		dummyhead->len++;
		printf("insert successfully\n");
	}
};

class SqList_int
{
private:
	typedef int eletype;
	const int INIT_SPACE = 100;
	const int INCREMENT = 10;
	struct List
	{
		eletype* head;
		int len;//��ǰ������
		int size;//��ǰ����ʹ�ÿռ�
	};
public:
	List* dummyhead = (List*)malloc(sizeof(List));

	SqList_int()
	{
		dummyhead->head = (eletype*)malloc(sizeof(eletype) * INIT_SPACE);
		dummyhead->len = 0;
		dummyhead->size = INIT_SPACE;
	}

	void add(eletype a)
	{
		if (dummyhead->len >= dummyhead->size)
		{
			dummyhead->head = (eletype*)realloc(dummyhead->head, sizeof(eletype) * (dummyhead->size + INCREMENT));
			dummyhead->size += INCREMENT;
		}

		*(dummyhead->head + dummyhead->len) = a;
		dummyhead->len++;
		printf("add successfully\n");
	}

	void insert(eletype a, int idex)
	{
		if (dummyhead->len >= dummyhead->size)
		{
			dummyhead->head = (eletype*)realloc(dummyhead->head, sizeof(eletype) * (dummyhead->size + INCREMENT));
			dummyhead->size += INCREMENT;
		}
		for (int i = idex; i <= dummyhead->len + 1; i++)
		{
			eletype temp = *(dummyhead->head + i);
			*(dummyhead->head + i) = a;
			a = temp;
		}
		dummyhead->len++;
		printf("insert successfully\n");
	}
};