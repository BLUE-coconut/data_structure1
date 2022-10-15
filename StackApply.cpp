#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include"sqstack.h"
#include"cirlist.h"
using namespace std;
const int N = 12;

void basic_operation()
{
	SqStack_int sqs;
	int ele;
	int n;
	printf("�������ݸ�����");
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("�������ݣ�");
		scanf_s("%d", &ele);
		sqs.push(ele);
	}
	int ans;
	ans=sqs.GetTop();
	printf("%d\n", ans);
	sqs.pop_get(ans);
	ans=sqs.GetTop();
	printf("%d\n", ans);
	sqs.destroy();
}

int priority_judge(char a,char b)
{
	if (b == ')')
	{
		if (a == '(')return 2;
		else return 3;
	}
	switch (a)
	{
	case '+':
		if (b == '+' || b=='-')
		{
			return 1;//��ʾ������a
		}
		return 0;//'(' �� '*' �� '/'
	case '-':
		if (b == '+' || b == '-' )
		{
			return 1;//��ʾ������a
		}
		return 0;
	case '*':
		if (b == '(')
			return 0;
		else
			return 1;
	case '/':
		if (b == '(')
			return 0;
		else
			return 1;
	case '(':
		return 0;

	default:
		break;
	}
	return 3;//a==')'
}

int calculate(int a,int b,char op)
{
	int res;
	if (op == '+')
	{
		res = a + b;
	}
	else if (op == '-')
	{
		res = a - b;
	}
	else if (op == '*')
	{
		res = a * b;
	}
	else if (op == '/')
	{
		res = a / b;
	}
	else
	{
		cout << "calculate erro" << endl;
		return 0;
	}
	return res;
}

void line_editor(char input[])//�б༭��(#��ʾ�˸�@��ʾ��գ�=��ʾ����)
{
	SqStack_int num;
	SqStack_char op;
	int res;
	char inc;//Ҫ�����ʽ��
	int stat=0;//1��ʾǰ��һ������Ϊnum��2��ʾǰ��һ��Ϊop
	for (int i=0;i<strlen(input);i++)
	{
		inc = input[i];
		if (inc == '=')
		{
			while (!num.finish())
			{
				char cur = op.pop();
				
				num.push(calculate(num.pop(), num.pop(), cur));
				//printf("%c\n", cur);
			}
			res = num.GetTop();
			break;
		}
		if (inc == '#')
		{
			if (stat == 1)
			{
				num.pop();
			}
			else if(stat == 2)
			{
				op.pop();
			}
			else
			{
				cout << "del erro ,already empty" << endl;
			}
			continue;
		}
		else if (inc == '@')
		{
			op.clear();
			num.clear();
			stat = 0;
			continue;
		}
		if (inc >= '0' && inc <= '9')
		{
			num.push((int)inc - '0');
			//printf("%d\n", num.GetTop());
			stat = 1;

		}
		else if(inc =='-'||inc=='+'||inc=='*'||inc=='/'||inc=='('||inc==')')
		{
			if (op.empty())//ǰ��û�з��ţ�һ����ֱ�ӷ���
			{
				op.push(inc);
				continue;
			}
			else
			{
				int pd = priority_judge(op.GetTop(), inc);
				if (pd == 1)
				{
					char cur = op.pop();
					int ans = calculate(num.pop(), num.pop(), cur);
					num.push(ans);
					printf("%d\n",ans);
					if (inc != ')')op.push(inc);
				}
				else if (pd == 0)
				{
					op.push(inc);
				}
				else if (pd == 2)//��������
				{
					op.pop();
				}
				else if (pd == 3)
				{
					while (!num.finish())
					{
						char cur = op.pop();
						if (cur == '(')
						{
							break;
						}
						int ans = calculate(num.pop(), num.pop(), cur);
						num.push(ans);
					}
				}
				stat = 2;
			}
		}
		else
		{
			//������Ч����
			continue;
		}
		
	}
	num.destroy();
	op.destroy();
	printf("�𰸣�%d", res);
}


/*�򵥵ı༭��
int main()
{
	char hhlstr[30];
	gets_s(hhlstr);
	line_editor(hhlstr);
	return 0;
}*/

/*�͵����ã�ѭ����
int main()
{
	CircularStack cs;
	cs.CreateBasicCircle();
	cs.showall();
	cs.TurnAround();
	cs.showall();
	cs.destroy();
	return 0;
}*/
