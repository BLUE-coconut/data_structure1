#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"chlist.h"

int readline(FILE* fp)//每次读一行
{
    char* szTest = (char*)malloc(sizeof(char) * 100);
    int len = 0;

    if (!feof(fp))
    {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, fp); // 包含了换行符
        printf("%s", szTest);
    }
    else
    {
        return 0;
    }
    return 1;
}


class active_block
{
private:
    const int MAX_SPACE = 100;
    const int MAX_LINE = 100;
public:
    bool readline(FILE* fp, char* szTest)//每次读一行到szTest字符串中
    {
        int len = 0;

        if (!feof(fp))
        {
            memset(szTest, 0, sizeof(szTest));
            fgets(szTest, sizeof(szTest) - 1, fp); // 包含了换行符
            printf("get input line %s", szTest);
        }
        else
        {
            return false;
        }
        return true;
    }
};



int main()
{
    //文件打开
    char fdir[50] = "1.txt";
    FILE* fp;
    int errojudge = fopen_s(&fp, fdir, "r");
    if (errojudge != 0)
    {
        perror("failed to open \n");
        return 0;
    }
    while (readline(fp));








    fclose(fp);     //文件关闭
    return 0;
}