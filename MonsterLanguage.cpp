#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"sqstack.h"
#include"sqqueue.h"
class Monster
{
private:
	SqQueue_char monster;
	SqQueue_char ans;
public:

	void create(char mstr[])
	{
		for (int i = 0; i < strlen(mstr); i++)
		{
			monster.push(mstr[i]);
		}
	}

	void trans(char ch ,SqQueue_char *con)
	{
		if (ch == 'A') 
		{
			char strA[] = "sae";
			for (int i = 0; i < strlen(strA); i++)
			{
				trans(strA[i], con);
			}
			
		}
		else if (ch == 'B')
		{
			char strB[] = "tAdA";
			for (int i = 0; i < strlen(strB); i++)
			{
				trans(strB[i], con);
			}
			
		}
		else
		{
			con->push(ch);
		}
		printf("trans ok\n");
	}

	//只满足单重括号：
	void answer(char cur)
	{
		trans(cur, &ans);
	}
	void translate()//使用队列来实现括号内语言的翻译
	{
		while (!monster.empty())
		{
			char cur = monster.pop_front();
			if (cur == '(')
			{
				char sigma = monster.pop_front();
				if(sigma==')')continue;
				SqStack_char tem;
				cur = monster.pop_front();
				if (monster.empty())
				{
					printf("erro! ) needed\n");
					answer(sigma);
					tem.destroy();
					break;
				}
				while (cur != ')'&&!monster.empty())
				{
					tem.push(cur);
					cur = monster.pop_front();
				}
				while (!tem.empty())
				{
					cur = tem.pop();
					answer(sigma);
					answer(cur);
				}
				answer(sigma);
				tem.destroy();
			}
			else
			{
				answer(cur);
			}

		}
	}

	//多重括号嵌套（从内往外）：
	void answer2(char cur, SqQueue_char* subans)//使用双端队列实现
	{
		if (cur == '(')
		{
			SqQueue_char sigma;

			char cur = monster.pop_front();
			if (cur != ')')
			{
				if (cur == '(')answer2(cur, &sigma);
				else trans(cur, &sigma);
				printf("sigma:");
				sigma.show_queue();
				printf("\n");
				SqQueue_char temp;
				while (!monster.empty())
				{
					cur = monster.pop_front();
					printf("get %c\n", cur);
					if (cur == ')')break;
					if (cur == '(')answer2(cur, &temp);
					else
					{
						trans(cur, &temp);
					}
				}
				subans->concat(sigma);
				while (!temp.empty())
				{
					char x= temp.pop_front();
					subans->push(x);
					subans->concat(sigma);
					
				}
			}

		}
		else
		{
			subans->push(cur);
		}
		printf("subanswer ok\n");
	}
	void translate2()
	{
		while (!monster.empty())
		{
			char cur = monster.pop_front();
			answer2(cur, &ans);
		}
	}

	/*void answer2(char cur, SqQueue_char* subans)
	{
		if (cur == '(')
		{
			SqQueue_char sigma;
			
			char cur = monster.pop_front();
			if (cur != ')')
			{
				if (cur == '(')answer2(cur, &sigma);
				else trans(cur, &sigma);
				printf("sigma:");
				sigma.show_queue();
				printf("\n");
				while (!monster.empty())
				{
					SqQueue_char temp;
					cur = monster.pop_front();
					printf("get %c\n", cur);
					if (cur == ')')break;
					if (cur == '(')answer2(cur, &temp);
					else trans(cur, &temp);
					subans->concat(sigma);
					subans->concat(temp);
				}
				
				subans->concat(sigma);
			}
			
		}
		else
		{
			subans->push(cur);
		}
		printf("subanswer ok\n");
	}
	void translate2()
	{
		while (!monster.empty())
		{
			char cur = monster.pop_front();
			answer2(cur, &ans);
		}
	}
	*/

	void answer3(char cur, SqQueue_char* subans)
	{
		if (cur == '(')
		{
			SqQueue_char sigma;
			SqQueue_char temp;

			char cur = monster.pop_front();
			if (cur != ')')
			{
				answer3(cur, &sigma);
				printf("sigma:");
				sigma.show_queue();
				printf("\n");
				while (!monster.empty())
				{
					cur = monster.pop_front();
					printf("get %c\n", cur);
					if (cur == ')')break;
					answer3(cur, &temp);
				}
				while (!temp.empty())
				{
					subans->concat(sigma);
					subans->push(temp.pop_rear());
				}
				subans->concat(sigma);
			}
		}
		else
		{
			subans->push(cur);
		}
		printf("subanswer ok\n");
	}
	void translate3()
	{
		SqQueue_char con;
		while (!monster.empty())
		{
			char cur = monster.pop_front();
			answer2(cur, &con);
		}
		while (!con.empty())
		{
			char cur = con.pop_front();
			if (cur == 'A')
			{
				SqQueue_char con;
				trans(cur, &con);
				while (!con.empty())
				{
					ans.push(con.pop_front());
				}
			}
			else if (cur == 'B')
			{
				SqQueue_char con;
				trans(cur, &con);
				while (!con.empty())
				{
					ans.push(con.pop_front());
				}
			}
			else
			{
				ans.push(cur);
			}
			printf("answer ok\n");
		}
	}

	
	void solve(char mstr[])
	{
		
		create(mstr);
		//translate();//只满足单一括号
		translate2();//满足括号嵌套
		printf("finish！Answer is as follow\n");
		ans.show_queue();
		ans.destroy();
	}
};

/*
int main()
{
	Monster hhlmonster;
	printf("please input monster's language:\n");
	char hhls[100];
	gets_s(hhls);
	hhlmonster.solve(hhls);
	return 0;
}
*/

