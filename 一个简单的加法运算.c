#include<stdio.h>
#include<stdlib.h>
void main(void)
{
	int a,b,c;
	printf("请依次输入两个数字a和b，中间用空格隔开\n");
	scanf("%d %d",&a,&b);
	c=a+b;
	printf("结果是c=%d\n",c);
	system("pause");
}
