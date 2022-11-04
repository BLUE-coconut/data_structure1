#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"chlist.h"

using namespace std;
const int Max_len = 60;
class hhlSet :public LinkList_char
{
public:
	hhlSet() {}
	hhlSet(char* set_name)//���ඨ���˹��캯������ִ�и��࣬��ִ������
	{
		name = set_name;
	}
private :
	char* name;
	int dict_len = 26;
	
public :
	void set_add_element(eletype ch)//���ϵĹ�����������ģ����ֵ���
	{
		LN* pre = dummyhead;
		LN* p = dummyhead->next;
		LN* pnew = new LN(ch);
		while (p)
		{
			if (p->data>ch)
			{
				pnew->next = p;
				pre->next = pnew;
				printf("add element %c successfully\n",ch);
				return;
			}
			else if (p->data == ch)
			{
				printf("%c already exist in set%c\n",ch,name);
				return;
			}
			else
			{
				pre = p;
				p = p->next;
			}
		}
		pnew->next = pre->next;
		pre->next = pnew;
		printf("add element %c successfully\n",ch);
	}

	void create_set(eletype str[])
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if(str[i]<='z'&&str[i]>='a')
				set_add_element(str[i]);
		}
	}

	LN* copy()
	{
		LN* cp_dummy = new LN();
		LN* p = dummyhead;
		LN* cp_p = cp_dummy;
		while (p->next)
		{
			p = p->next;
			LN* cp_new = new LN(p->data);
			cp_p->next = cp_new;
			cp_p = cp_p->next;
		}
		return cp_dummy;
	}

	LN* calculate(LN* setB , char op)
	{
		LN* ans = copy();
		LN* pa = ans;
		LN* pb = setB;
		if (op == '&')  //����
		{
			while (pa->next && pb->next)
			{
				if (pb->next->data < pa->next->data)
				{
					pb = pb->next;
				}
				else if (pb->next->data == pa->next->data)
				{
					pa = pa->next;
					pb = pb->next;
				}
				else
				{
					pa->next = pa->next->next;
				}
			}
			if (pa->next)
			{
				pa->next = NULL;
			}
			
		}
		else if (op == '|')  //����
		{
			while (pa->next && pb->next)
			{
				if (pb->next->data < pa->next->data)
				{
					LN* pnew = new LN(pb->next->data);
					pnew->next = pa->next;
					pa->next = pnew;
					printf("add element %c successfully\n", pb->next->data);
				}
				else if (pb->next->data == pa->next->data)
				{
					pa = pa->next;
					pb = pb->next;
				}
				else
				{
					pa = pa->next;
				}
			}
			if(pb->next)
			{
				pa->next = pb->next;
			}
		}
		else if (op == '-')  //�
		{
			while (pa->next && pb->next)
			{
				if (pb->next->data < pa->next->data)
				{
					pb = pb->next;
				}
				else if (pb->next->data == pa->next->data)
				{
					pa->next = pa->next->next;
				}
				else
				{
					pa = pa->next;
				}
			}
		}
		
		else
		{
			printf("operate erro");
			return NULL;
		}

		//show answer
		printf("ans: ");
		LN* p = ans->next;
		if (p == NULL)printf("�ռ�");
		while (p != NULL)
		{
			printf("%c ", p->data);
			p = p->next;
		}
		printf("\n");
		return ans;
	}

	int relation(LN* setB)//���Ϲ�ϵ
	{
		// A����B = 2��A������B = 1��AB��� = 0��ABû�ض���ϵ = -1
		LN* pa = dummyhead;
		LN* pb = setB;
		int flag = 0;//��ʼ״̬AB��ͬ
		// A ���� Bû�е�Ԫ�� flag=1��else flag = -1
		while (pa->next && pb->next)
		{
			//printf("%d\n", flag);
			if (pa->next->data < pb->next->data)// A ���� Bû�е�Ԫ��
			{
				if (flag == 1)
				{
					printf("A Bû�ض���ϵ\n");
					return -1;
				}
				if(flag==0)flag = 2;
				pa = pa->next;
			}
			else if (pa->next->data > pb->next->data)// B ���� Aû�е�Ԫ��
			{
				if (flag == 2)
				{
					printf("A Bû�ض���ϵ\n");
					return -1;
				}
				if (flag == 0)flag = 1;
				pb = pb->next;
			}
			else
			{
				pa = pa->next;
				pb = pb->next;
			}
		}
		if (pb->next)
		{
			if(flag==2)printf("A Bû���ض���ϵ\n");
			else printf("A������B\n");
			return 1;
		}
		else if (pa->next)
		{
			if (flag == 1)printf("A Bû���ض���ϵ\n");
			else printf("A����B\n");
			return 2;
		}
		else
		{
			printf("A=B\n");
			return 0;
		}

	}

	int relation_ele(char ele)//������Ԫ�صĹ�ϵ
	{
		LN* head = dummyhead;
		while (head->next)
		{
			if (head->next->data == ele)//Ԫ�����ڵ�ǰ����
			{
				return 1;
			}
			head = head->next;
		}
		return 0;
	}

	void help()
	{
		printf("\n & ��ʾ�󽻼�\n | ��ʾ�󲢼�\n - ��ʾ��\n U ��ʾ�󲹼�\n");
	}
};


typedef struct exist
{
	hhlSet* SET;
	char* name;
	exist* next;
	exist() :SET(NULL),name(NULL), next(NULL) {}
	exist(hhlSet* cur,char *nm) :SET(cur),name(nm), next(NULL) {}
}en;
en* set_dummyhead = new exist();
en* tail = set_dummyhead;
void new_set(hhlSet* cur,char *name)
{
	exist* newset = new exist(cur,name);
	tail->next = newset;
	tail = newset;
}
void show_sets()//���ӻ��������м���
{
	en* cur = set_dummyhead;
	printf("ALL SETS:\n");
	while(cur->next)
	{
		printf("%s = ",cur->next->name);
		cur->next->SET->showall();
		printf("\n");
		cur = cur->next;
	}
}
hhlSet get_set(char* name)//����set name
{
	en* cur = set_dummyhead;
	int flag = 0;
	//printf("newset:%s\n", name);
	show_sets();
	while (cur->next)
	{
		if (*(cur->next->name) == *name)//��ǰ���ϴ���
		{
			return *(cur->next->SET);
		}
		cur = cur->next;
	}
	return NULL;
}
bool just_find_set(char* name)
{
	en* cur = set_dummyhead;
	int flag = 0;
	printf("newset:%s\n", name);
	while (cur->next)
	{
		//printf("find:%s\n", cur->next->name);
		if (*(cur->next->name) == *name)//��ǰ���ϴ���
		{
			flag = 1;
			break;
		}
		cur = cur->next;
	}
	if (flag)return true;
	else return false;
}
/*
int main()//�������棬�ɽ����������
{
	hhlSet* S = new hhlSet();
	printf("����������򡪡�hhl����\n");

	//��������ȫ��
	printf("����ȫ��S:\n");
	printf("������ȫ����С��(����0����Ĭ����26��Сд��ĸΪȫ��)\n");
	int n;
	cin >> n;
	if (n<=0)
	{
		char x[] = "abcdefghijklmnopqrstuvwxyz";
		S->create_set(x);
	}
	else
	{
		printf("���뼯�����ݣ�\n");
		char set[Max_len];
		cin >> set;
		S->create_set(set);
	}

	int op = 1;
	while (1)
	{
		if (op == 1)
		{
			printf("����������򡪡�hhl����\n");
			printf("����0�����˳�\n");
			printf("����1����������ҳ��\n");
			printf("����2�������뼯��\n");
			printf("����3������������\n");
			printf("����4�������ϼ��ϵ����\n");
			printf("����5����������Ԫ������\n");
			cin >> op;

		}
		else if (op == 0)
		{
			break;
		}
		else if (op == 2)
		{
			char* name = (char*)malloc(sizeof(char)*30);
			printf("���뼯�����ƣ�\n");
			cin >> name;
			//show_sets();
			while (1)
			{
				if (!just_find_set(name))//������
				{
					break;
				}
				else
				{
					printf("�������Ѵ��ڣ��������뼯�����ƣ�\n");
					cin >> name;
				}
			}
			printf("���뼯�����ݣ�\n");
			char set[Max_len];
			cin >> set;
			hhlSet* A=new hhlSet(name);
			A->create_set(set);
			new_set(A, name);//���set��������
			show_sets();//���ӻ����е����м���

			cin >> op;
		}
		else if (op == 3)//�������㣨�������������
		{
			printf("��������\n");
			if (!set_dummyhead->next)
			{
				printf("no exist sets\n");
				op = 1; // ����������
				continue;
			}
			else
			{
				printf("exits sets:");
				show_sets();
			}
			char* chooseA = (char*)malloc(sizeof(char) * 30);
			char* chooseB = (char*)malloc(sizeof(char) * 30);

			printf("�����������setA��\n");
			cin >> chooseA;
			hhlSet A;
			while (!just_find_set(chooseA))
			{
				printf("�����ڣ����������������setA��\n");
				cin >> chooseA;
			}
			A = get_set(chooseA);
			A.help();//��ʾ����ָ��

			printf("���е��������");
			printf("opertor:");
			char oper;
			cin >> oper;
			if (oper == 'U')
			{
				printf("S:");
				S->showall();

				S->calculate(A.dummyhead,'-');
			}
			else
			{
				printf("�����������setB��\n");
				cin >> chooseB;
				hhlSet B;
				while (!just_find_set(chooseB))
				{
					printf("�����ڣ����������������setB��\n");
					cin >> chooseB;
				}
				B = get_set(chooseB);
				A.calculate(B.dummyhead, oper);
			}

			cin >> op;

		}
		else if (op == 4)//���Ϲ�ϵ����
		{
			char* chooseA = (char*)malloc(sizeof(char) * 30);
			char* chooseB = (char*)malloc(sizeof(char) * 30);
			printf("�����������setA��\n");
			cin >> chooseA;
			hhlSet A;
			while (!just_find_set(chooseA))
			{
				printf("�����ڣ����������������setA��\n");
				cin >> chooseA;
			}
			A = get_set(chooseA);

			printf("�����������setB��\n");
			cin >> chooseB;
			hhlSet B ;
			while (!just_find_set(chooseB))
			{
				printf("�����ڣ����������������setA��\n");
				cin >> chooseB;
			}
			B = get_set(chooseB);

			printf("setA: ");
			A.showall();
			printf("setB: ");
			B.showall();
			A.relation(B.dummyhead);

			cin >> op;
		}
		else if (op == 5)//������Ԫ�ع�ϵ����
		{
			char* chooseA = (char*)malloc(sizeof(char) * 30);
			printf("�����������setA��\n");
			cin >> chooseA;
			hhlSet A ;
			while (!just_find_set(chooseA))
			{
				printf("�����ڣ����������������setA��\n");
				cin >> chooseA;
			}
			A = get_set(chooseA);
			printf("setA: ");
			A.showall();
			char ele;
			printf("��������Ԫ��ele��\n");
			cin >> ele;
			if (A.relation_ele(ele))
			{
				printf("Ԫ��%c���ڼ���%s", ele, chooseA);
			}
			else
			{
				printf("Ԫ��%c�����ڼ���%s", ele, chooseA);
			}

			cin >> op;
		}
		
		else
		{
			printf("op invalid,�������룺\n");
			cin >> op;

		}
	}

}


int main()//�򵥵Ķ���������(�������������)
{
	char setA[30],setB[30];
	printf("setA=");
	cin>>setA;
	printf("setB=");
	cin>>setB;
	hhlSet A('A');
	hhlSet B('B');
	A.create_set(setA);
	B.create_set(setB);
	printf("setA:");
	A.showall();
	printf("setB:");
	B.showall();
	A.help();//�������˵��
	printf("opertor:");
	char op;
	cin>>op;
	A.calculate(B.dummyhead,op);
	A.relation(B.dummyhead);
	A.destroy();
	B.destroy();
	return 0;
}*/