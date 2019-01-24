#include<stdio.h>
#include<stdlib.h>
#define PI 3.14159
void main()
{
	float r,s,l;
	printf("请输入圆的半径:\n");
	scanf("%f",&r);
	s=PI*r*r;
	l=2*PI*r;
	printf("圆的面积是%f:\n",s);
	printf("圆的周长是%f:\n",l);
	system("pause");
}
