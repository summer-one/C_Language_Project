#include<stdio.h>
#include<stdlib.h>
void main()
{
	int year;
	printf("请输入年份：");
	scanf("%d",&year);
	if(year % 400 == 0)
{
	printf("%d是闰年\n",year);
}
	else if (year % 4 == 0 && year % 100 != 0) {
		printf("%d是闰年\n",year);
	} else {
		printf("%d不是闰年\n",year);
	}
	system("pause");
}
