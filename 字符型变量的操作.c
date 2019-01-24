#include<stdio.h>
#include<stdlib.h>
void main()
{
	char x,y;
	x=97;
	y=98;
	printf("以字符格式输出x和y的值：");
	printf("x=%c,y=%c\n",x,y);
	printf("以整型格式输出x和y的值：");
	printf("%d,%d\n",x,y);
	x=x-32;
	y=y-32;
	printf("字符型x=%c,y=%c 整型x=%d,y=%d\n",x,y,x,y);
	system("pause");
}
