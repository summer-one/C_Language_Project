#include<stdio.h>
#include<stdlib.h>
float area(int r)
{
	float s;
	s=3.14*r*r;
	return(s);
}
void main()
{
int r;
	float s;
	printf("请输入圆的半径：");
	scanf("%d",&r);
	s=area(r);
	printf("圆的面积是%f",s);
	system("pause");
}
