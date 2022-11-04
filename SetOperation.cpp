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
	hhlSet(char* set_name)//子类定义了构造函数，先执行父类，再执行子类
	{
		name = set_name;
	}
private :
	char* name;
	int dict_len = 26;
	
public :
	void set_add_element(eletype ch)//集合的构建是是有序的（按字典序）
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
		if (op == '&')  //交集
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
		else if (op == '|')  //并集
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
		else if (op == '-')  //差集
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
		if (p == NULL)printf("空集");
		while (p != NULL)
		{
			printf("%c ", p->data);
			p = p->next;
		}
		printf("\n");
		return ans;
	}

	int relation(LN* setB)//集合关系
	{
		// A包含B = 2、A包含于B = 1、AB相等 = 0、AB没特定关系 = -1
		LN* pa = dummyhead;
		LN* pb = setB;
		int flag = 0;//起始状态AB相同
		// A 包含 B没有的元素 flag=1，else flag = -1
		while (pa->next && pb->next)
		{
			//printf("%d\n", flag);
			if (pa->next->data < pb->next->data)// A 包含 B没有的元素
			{
				if (flag == 1)
				{
					printf("A B没特定关系\n");
					return -1;
				}
				if(flag==0)flag = 2;
				pa = pa->next;
			}
			else if (pa->next->data > pb->next->data)// B 包含 A没有的元素
			{
				if (flag == 2)
				{
					printf("A B没特定关系\n");
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
			if(flag==2)printf("A B没有特定关系\n");
			else printf("A包含于B\n");
			return 1;
		}
		else if (pa->next)
		{
			if (flag == 1)printf("A B没有特定关系\n");
			else printf("A包含B\n");
			return 2;
		}
		else
		{
			printf("A=B\n");
			return 0;
		}

	}

	int relation_ele(char ele)//集合与元素的关系
	{
		LN* head = dummyhead;
		while (head->next)
		{
			if (head->next->data == ele)//元素属于当前集合
			{
				return 1;
			}
			head = head->next;
		}
		return 0;
	}

	void help()
	{
		printf("\n & 表示求交集\n | 表示求并集\n - 表示求差集\n U 表示求补集\n");
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
void show_sets()//可视化所有现有集合
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
hhlSet get_set(char* name)//查找set name
{
	en* cur = set_dummyhead;
	int flag = 0;
	//printf("newset:%s\n", name);
	show_sets();
	while (cur->next)
	{
		if (*(cur->next->name) == *name)//当前集合存在
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
		if (*(cur->next->name) == *name)//当前集合存在
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
int main()//交互界面，可建立多个集合
{
	hhlSet* S = new hhlSet();
	printf("集合运算程序——hhl制作\n");

	//首先设置全集
	printf("设置全集S:\n");
	printf("请输入全集大小：(输入0，则默认以26个小写字母为全集)\n");
	int n;
	cin >> n;
	if (n<=0)
	{
		char x[] = "abcdefghijklmnopqrstuvwxyz";
		S->create_set(x);
	}
	else
	{
		printf("输入集合内容：\n");
		char set[Max_len];
		cin >> set;
		S->create_set(set);
	}

	int op = 1;
	while (1)
	{
		if (op == 1)
		{
			printf("集合运算程序——hhl制作\n");
			printf("输入0——退出\n");
			printf("输入1——返回主页面\n");
			printf("输入2——输入集合\n");
			printf("输入3——集合运算\n");
			printf("输入4——集合间关系运算\n");
			printf("输入5——集合与元素运算\n");
			cin >> op;

		}
		else if (op == 0)
		{
			break;
		}
		else if (op == 2)
		{
			char* name = (char*)malloc(sizeof(char)*30);
			printf("输入集合名称：\n");
			cin >> name;
			//show_sets();
			while (1)
			{
				if (!just_find_set(name))//不存在
				{
					break;
				}
				else
				{
					printf("集合名已存在，重新输入集合名称：\n");
					cin >> name;
				}
			}
			printf("输入集合内容：\n");
			char set[Max_len];
			cin >> set;
			hhlSet* A=new hhlSet(name);
			A->create_set(set);
			new_set(A, name);//添加set入容器中
			show_sets();//可视化现有的所有集合

			cin >> op;
		}
		else if (op == 3)//集合运算（交、并、差、补）
		{
			printf("集合运算\n");
			if (!set_dummyhead->next)
			{
				printf("no exist sets\n");
				op = 1; // 返回主界面
				continue;
			}
			else
			{
				printf("exits sets:");
				show_sets();
			}
			char* chooseA = (char*)malloc(sizeof(char) * 30);
			char* chooseB = (char*)malloc(sizeof(char) * 30);

			printf("输入运算对象setA：\n");
			cin >> chooseA;
			hhlSet A;
			while (!just_find_set(chooseA))
			{
				printf("不存在，重新输入运算对象setA：\n");
				cin >> chooseA;
			}
			A = get_set(chooseA);
			A.help();//显示操作指令

			printf("进行的运算操作");
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
				printf("输入运算对象setB：\n");
				cin >> chooseB;
				hhlSet B;
				while (!just_find_set(chooseB))
				{
					printf("不存在，重新输入运算对象setB：\n");
					cin >> chooseB;
				}
				B = get_set(chooseB);
				A.calculate(B.dummyhead, oper);
			}

			cin >> op;

		}
		else if (op == 4)//集合关系运算
		{
			char* chooseA = (char*)malloc(sizeof(char) * 30);
			char* chooseB = (char*)malloc(sizeof(char) * 30);
			printf("输入运算对象setA：\n");
			cin >> chooseA;
			hhlSet A;
			while (!just_find_set(chooseA))
			{
				printf("不存在，重新输入运算对象setA：\n");
				cin >> chooseA;
			}
			A = get_set(chooseA);

			printf("输入运算对象setB：\n");
			cin >> chooseB;
			hhlSet B ;
			while (!just_find_set(chooseB))
			{
				printf("不存在，重新输入运算对象setA：\n");
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
		else if (op == 5)//集合与元素关系运算
		{
			char* chooseA = (char*)malloc(sizeof(char) * 30);
			printf("输入运算对象setA：\n");
			cin >> chooseA;
			hhlSet A ;
			while (!just_find_set(chooseA))
			{
				printf("不存在，重新输入运算对象setA：\n");
				cin >> chooseA;
			}
			A = get_set(chooseA);
			printf("setA: ");
			A.showall();
			char ele;
			printf("输入运算元素ele：\n");
			cin >> ele;
			if (A.relation_ele(ele))
			{
				printf("元素%c属于集合%s", ele, chooseA);
			}
			else
			{
				printf("元素%c不属于集合%s", ele, chooseA);
			}

			cin >> op;
		}
		
		else
		{
			printf("op invalid,重新输入：\n");
			cin >> op;

		}
	}

}


int main()//简单的二集合运算(不包含补集求解)
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
	A.help();//运算符号说明
	printf("opertor:");
	char op;
	cin>>op;
	A.calculate(B.dummyhead,op);
	A.relation(B.dummyhead);
	A.destroy();
	B.destroy();
	return 0;
}*/